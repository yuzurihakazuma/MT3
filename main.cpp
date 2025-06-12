#include <Novice.h>
#include <cmath>
#include <Windows.h>
#include <imgui.h>

const char kWindowTitle[] = "LE2C_ユズリハ_カズマ";

// ------------------------ 基本構造体 ------------------------
struct Vector3 {
	float x, y, z;
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
};

struct Sphere {
	Vector3 center;
	float radius;
};

struct Vector2 {
	float x, y;
};

struct Matrix4x4 {
	float m[4][4];
};

// ------------------------ ベクトル関数 ------------------------
Vector3 Subtract(const Vector3& a, const Vector3& b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector3 Add(const Vector3& a, const Vector3& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 Multiply(const Vector3& v, float scalar) {
	return { v.x * scalar, v.y * scalar, v.z * scalar };
}

float Dot(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Cross(const Vector3& a, const Vector3& b) {
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

float Length(const Vector3& v) {
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v) {
	float len = Length(v);
	if (len == 0.0f) return { 0, 0, 0 };
	return Multiply(v, 1.0f / len);
}

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	float d = Dot(v2, v2);
	if (d == 0.0f) return { 0, 0, 0 };
	float t = Dot(v1, v2) / d;
	return Multiply(v2, t);
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 diff = segment.diff;
	Vector3 toPoint = Subtract(point, segment.origin);
	Vector3 projected = Project(toPoint, diff);
	float t = Dot(projected, diff) / Dot(diff, diff);
	t = std::fmax(0.0f, std::fmin(1.0f, t));
	return Add(segment.origin, Multiply(diff, t));
}

// ------------------------ 行列関数 ------------------------
Matrix4x4 MakeIdentityMatrix() {
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i) {
		result.m[i][i] = 1.0f;
	}
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
	result.m[3][2] = -nearZ * farZ / (farZ - nearZ);
	return result;
}

Matrix4x4 MakeViewMatrix(const Vector3& eye, const Vector3& target, const Vector3& up) {
	Vector3 zAxis = Normalize(Subtract(target, eye));
	Vector3 xAxis = Normalize(Cross(up, zAxis));
	Vector3 yAxis = Cross(zAxis, xAxis);

	Matrix4x4 result = MakeIdentityMatrix();
	result.m[0][0] = xAxis.x;
	result.m[1][0] = xAxis.y;
	result.m[2][0] = xAxis.z;
	result.m[0][1] = yAxis.x;
	result.m[1][1] = yAxis.y;
	result.m[2][1] = yAxis.z;
	result.m[0][2] = zAxis.x;
	result.m[1][2] = zAxis.y;
	result.m[2][2] = zAxis.z;
	result.m[3][0] = -Dot(xAxis, eye);
	result.m[3][1] = -Dot(yAxis, eye);
	result.m[3][2] = -Dot(zAxis, eye);
	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result = MakeIdentityMatrix();
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	return result;
}

// ------------------------ 座標変換 ------------------------
Vector3 Transform(const Vector3& v, const Matrix4x4& m) {
	float x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	float y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	float z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	if (w != 0.0f) {
		x /= w;
		y /= w;
		z /= w;
	}
	return { x, y, z };
}

Vector2 Project(const Vector3& v, const Matrix4x4& viewProjection, const Matrix4x4& viewport) {
	Vector3 viewProjected = Transform(v, viewProjection);
	Vector3 result = Transform(viewProjected, viewport);
	return { result.x, result.y };
}

// ------------------------ 描画関数 ------------------------
void DrawGrid(const Matrix4x4& vp, const Matrix4x4& viewport) {
	const float gridSize = 2.0f;
	const int divisions = 10;
	const float interval = (gridSize * 2) / divisions;

	for (int i = 0; i <= divisions; ++i) {
		float pos = -gridSize + i * interval;

		Vector2 sX = Project({ pos, 0, -gridSize }, vp, viewport);
		Vector2 eX = Project({ pos, 0, gridSize }, vp, viewport);
		uint32_t colorX = std::abs(pos) < 0.01f ? 0x000000FF : 0xAAAAAAFF;
		Novice::DrawLine((int)sX.x, (int)sX.y, (int)eX.x, (int)eX.y, colorX);

		Vector2 sZ = Project({ -gridSize, 0, pos }, vp, viewport);
		Vector2 eZ = Project({ gridSize, 0, pos }, vp, viewport);
		uint32_t colorZ = std::abs(pos) < 0.01f ? 0x000000FF : 0xAAAAAAFF;
		Novice::DrawLine((int)sZ.x, (int)sZ.y, (int)eZ.x, (int)eZ.y, colorZ);
	}
}

void DrawPoint(const Vector3& point, const Matrix4x4& vp, const Matrix4x4& viewport, uint32_t color) {
	Vector2 screen = Project(point, vp, viewport);
	Novice::DrawEllipse((int)screen.x, (int)screen.y, 5, 5, 0.0f, color, kFillModeSolid);
}

void DrawSegment(const Segment& seg, const Matrix4x4& vp, const Matrix4x4& viewport, uint32_t color) {
	Vector2 a = Project(seg.origin, vp, viewport);
	Vector2 b = Project(Add(seg.origin, seg.diff), vp, viewport);
	Novice::DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, color);
}

// ------------------------ メイン関数 ------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Novice::Initialize(kWindowTitle, 1280, 720);

	// カメラ設定
	Vector3 cameraPos = { 0, 3, -6 };
	Vector3 cameraTarget = { 0, 0, 0 };
	Vector3 up = { 0, 1, 0 };

	// 行列
	Matrix4x4 viewMatrix = MakeViewMatrix(cameraPos, cameraTarget, up);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
	Matrix4x4 viewProjection = Multiply(viewMatrix, projectionMatrix);
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720, 0.0f, 1.0f);

	// 初期データ
	Segment segment = { {-2, -1, 0}, {5, 3, 2} };
	Vector3 point = { -1.5f, 0.6f, 0.6f };

	char keys[256] = {};
	char preKeys[256] = {};

	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		// 最近接点計算
		Vector3 closest = ClosestPoint(point, segment);

		// ImGui GUI
		ImGui::Begin("Segment Control");
		ImGui::DragFloat3("Segment Origin", &segment.origin.x, 0.1f);
		ImGui::DragFloat3("Segment Diff", &segment.diff.x, 0.1f);
		ImGui::DragFloat3("Point", &point.x, 0.1f);
		ImGui::End();

		// 描画
		DrawGrid(viewProjection, viewportMatrix);
		DrawSegment(segment, viewProjection, viewportMatrix, 0x0000FFFF);
		DrawPoint(point, viewProjection, viewportMatrix, 0xFF0000FF);       // 点（赤）
		DrawPoint(closest, viewProjection, viewportMatrix, 0x00FF00FF);     // 最近接点（緑）

		Novice::EndFrame();
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) break;
	}

	Novice::Finalize();
	return 0;
}