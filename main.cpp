#include <Novice.h>
#include <cmath>
#include <imgui.h>

const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

struct Matrix4x4 {
    float m[4][4];
};

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Sphere {
    Vector3 center;
    float radius;
};

float Dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Normalize(const Vector3& v) {
    float length = std::sqrt(Dot(v, v));
    return { v.x / length, v.y / length, v.z / length };
}

Vector3 Transform(const Vector3& v, const Matrix4x4& m) {
    float x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
    float y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
    float z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
    float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

    if (std::abs(w) < 1e-5f) w = 1.0f; // 0除算防止
    return { x / w, y / w, z / w };
}

Matrix4x4 MakeIdentity() {
    Matrix4x4 result{};
    for (int i = 0; i < 4; ++i) result.m[i][i] = 1.0f;
    return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& t) {
    Matrix4x4 result = MakeIdentity();
    result.m[3][0] = t.x;
    result.m[3][1] = t.y;
    result.m[3][2] = t.z;
    return result;
}

Matrix4x4 MakeRotateX(float angle) {
    Matrix4x4 result = MakeIdentity();
    result.m[1][1] = cosf(angle);
    result.m[1][2] = sinf(angle);
    result.m[2][1] = -sinf(angle);
    result.m[2][2] = cosf(angle);
    return result;
}

Matrix4x4 MakeRotateY(float angle) {
    Matrix4x4 result = MakeIdentity();
    result.m[0][0] = cosf(angle);
    result.m[0][2] = -sinf(angle);
    result.m[2][0] = sinf(angle);
    result.m[2][2] = cosf(angle);
    return result;
}

Matrix4x4 MakeRotateZ(float angle) {
    Matrix4x4 result = MakeIdentity();
    result.m[0][0] = cosf(angle);
    result.m[0][1] = sinf(angle);
    result.m[1][0] = -sinf(angle);
    result.m[1][1] = cosf(angle);
    return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
    return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspect, float nearZ, float farZ) {
    Matrix4x4 result{};
    float f = 1.0f / tanf(fovY / 2.0f);
    result.m[0][0] = f / aspect;
    result.m[1][1] = f;
    result.m[2][2] = farZ / (farZ - nearZ);
    result.m[2][3] = 1.0f;
    result.m[3][2] = (-nearZ * farZ) / (farZ - nearZ);
    return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
    Matrix4x4 result = MakeIdentity();
    result.m[0][0] = width / 2.0f;
    result.m[1][1] = -height / 2.0f;
    result.m[2][2] = maxDepth - minDepth;
    result.m[3][0] = left + width / 2.0f;
    result.m[3][1] = top + height / 2.0f;
    result.m[3][2] = minDepth;
    return result;
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
    const float kGridHalfWidth = 2.0f;
    const uint32_t kSubdivision = 10;
    const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

    for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
        float x = -kGridHalfWidth + xIndex * kGridEvery;
        Vector3 start = Transform({ x, 0.0f, -kGridHalfWidth }, viewProjectionMatrix);
        Vector3 end = Transform({ x, 0.0f, kGridHalfWidth }, viewProjectionMatrix);
        start = Transform(start, viewportMatrix);
        end = Transform(end, viewportMatrix);
        uint32_t color = (std::abs(x) < 0.001f) ? 0x000000FF : 0xAAAAAAFF;
        Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
    }

    for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
        float z = -kGridHalfWidth + zIndex * kGridEvery;
        Vector3 start = Transform({ -kGridHalfWidth, 0.0f, z }, viewProjectionMatrix);
        Vector3 end = Transform({ kGridHalfWidth, 0.0f, z }, viewProjectionMatrix);
        start = Transform(start, viewportMatrix);
        end = Transform(end, viewportMatrix);
        uint32_t color = (std::abs(z) < 0.001f) ? 0x000000FF : 0xAAAAAAFF;
        Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
    }
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
    const uint32_t kSubdivision = 16;
    const float pi = 3.141592f;
    const float kLatEvery = pi / kSubdivision;
    const float kLonEvery = 2 * pi / kSubdivision;

    for (uint32_t lat = 0; lat < kSubdivision; ++lat) {
        float latA = -pi / 2.0f + lat * kLatEvery;
        float latB = latA + kLatEvery;
        for (uint32_t lon = 0; lon < kSubdivision; ++lon) {
            float lonA = lon * kLonEvery;
            float lonB = lonA + kLonEvery;

            Vector3 a{
                sphere.radius * cosf(latA) * cosf(lonA) + sphere.center.x,
                sphere.radius * sinf(latA) + sphere.center.y,
                sphere.radius * cosf(latA) * sinf(lonA) + sphere.center.z
            };
            Vector3 b{
                sphere.radius * cosf(latB) * cosf(lonA) + sphere.center.x,
                sphere.radius * sinf(latB) + sphere.center.y,
                sphere.radius * cosf(latB) * sinf(lonA) + sphere.center.z
            };
            Vector3 c{
                sphere.radius * cosf(latA) * cosf(lonB) + sphere.center.x,
                sphere.radius * sinf(latA) + sphere.center.y,
                sphere.radius * cosf(latA) * sinf(lonB) + sphere.center.z
            };

            a = Transform(a, viewProjectionMatrix);
            a = Transform(a, viewportMatrix);
            b = Transform(b, viewProjectionMatrix);
            b = Transform(b, viewportMatrix);
            c = Transform(c, viewProjectionMatrix);
            c = Transform(c, viewportMatrix);

            Novice::DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, color);
            Novice::DrawLine((int)a.x, (int)a.y, (int)c.x, (int)c.y, color);
        }
    }
}

bool IsCollision(const Sphere& s1, const Sphere& s2) {
    Vector3 diff{
        s1.center.x - s2.center.x,
        s1.center.y - s2.center.y,
        s1.center.z - s2.center.z
    };
    float distanceSquared = Dot(diff, diff);
    float radiusSum = s1.radius + s2.radius;
    return distanceSquared <= (radiusSum * radiusSum);
}

// 〜（省略）〜 既存コードそのまま

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, 1280, 720);
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
    Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };
    Sphere sphere{ {0.0f, 0.0f, 0.0f}, 1.0f };

    // ▶ 追加した小さい球体
    Sphere smallSphere{ {1.5f, 0.0f, 0.0f}, 0.5f };

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        Matrix4x4 cameraT = MakeTranslateMatrix({ -cameraTranslate.x, -cameraTranslate.y, -cameraTranslate.z });
        Matrix4x4 cameraRY = MakeRotateY(-cameraRotate.y);
        Matrix4x4 cameraRX = MakeRotateX(-cameraRotate.x);
        Matrix4x4 viewMatrix = Multiply(cameraT, Multiply(cameraRY, cameraRX));

        Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
        Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
        Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720, 0.0f, 1.0f);

        ImGui::Begin("Window");
        ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
        ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

        ImGui::SeparatorText("Main Sphere");
        ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.02f);
        ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);

        ImGui::SeparatorText("Small Sphere");  // ▶ 小さい球体の操作
        ImGui::DragFloat3("SmallSphereCenter", &smallSphere.center.x, 0.02f);
        ImGui::DragFloat("SmallSphereRadius", &smallSphere.radius, 0.01f);
        ImGui::End();

        DrawGrid(viewProjectionMatrix, viewportMatrix);
        // 当たり判定と色変更
        bool isHit = IsCollision(sphere, smallSphere);
        uint32_t sphereColor = isHit ? 0xFF0000FF : 0x000000FF;

        DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, sphereColor);
        DrawSphere(smallSphere, viewProjectionMatrix, viewportMatrix, 0x000000FF);

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) break;
    }

    Novice::Finalize();
    return 0;
}