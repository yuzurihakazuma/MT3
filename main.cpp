#include <Novice.h>
#include "Sphere.h"
#include "Matrix4x4.h"
#include <imgui.h>

using namespace MatrixMath;
using namespace MathSphere;

const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 camaraRotate{ 0.26f,0.0f,0.0f };
	Vector3 cameraPos{ 0.0f,2.0f,10.0f };

	// 球データ
	Sphere sphere = { {0.0f, 0.0f, 0.0f}, 1.0f, static_cast<int>(0xFFFFFFFF) }; // 初期色：白

	// 平面データ（Y=0 の床面）
	Plane plane = { {0.0f, 1.0f, 0.0f}, -0.5f }; // 法線Y上向き、原点通過

	// 初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		/// --- 行列関連 ---
		Matrix4x4 worldMatrix = MakeAffine({ 1.0f,1.0f,1.0f }, camaraRotate, cameraTranslate);
		Matrix4x4 cameraMatrix = MakeAffine({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPos);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = PerspectiveFov(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = Viewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

#ifdef _DEBUG
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &camaraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::DragFloat3("PlaneNormal", &plane.distance, 0.01f);
		ImGui::End();
#endif

		/// --- 衝突判定 ---
		if (IsCollision(sphere, plane)) {
			sphere.color = 0xFF0000FF; // 赤（ARGB）
		} else {
			sphere.color = 0xFFFFFFFF; // 白
		}

		/// --- 描画処理 ---
		DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, sphere.color);
		DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, 0x8800FF00); // 緑で平面可視化

		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}