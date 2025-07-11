#include <Novice.h>
#include "Sphere.h"
#include "Matrix4x4.h"
#include <imgui.h>


using namespace MatrixMath;
const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	



	Vector3 cameraPosition = { 0.0f,0.0f,-1.0f };

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	
	Triangle triangle = {
		{{ 0.0f, 0.0f, 0.0f },
		 { 1.0f, 0.0f, 0.0f },
		 { 0.0f, 1.0f, 0.0f }}
	};
	Segment segment = {
	{-1.0f, 0.5f, 0.0f},
	{ 1.0f, 0.5f, 0.0f}
	};
	Vector3 point{ -1.5f,0.6f,0.6f };

	unsigned int color = BLACK;

	//pointを線分に射影したベクトル。今回は正しく計算できているかを確認するためだけに使う
	//Vector3 closestPoint = ClosestPoint(point, segment);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///



		

		// ビュー行列（カメラ位置と向き）
		Matrix4x4 cameraMatrix = MakeAffine({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = MatrixMath::Inverse(cameraMatrix);

		// プロジェクション行列
		Matrix4x4 projectionMatrix = PerspectiveFov(
			0.45f,
			float(kWindowWidth) / float(kWindowHeight),
			0.1f,
			100.0f
		);

		// ワールド行列（グリッドや球の位置）
		Matrix4x4 worldMatrix =  MakeIdentity4x4();


		// 各種行列の合成
		Matrix4x4 viewProjectionMatrix =Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

		// ビューポート行列
		Matrix4x4 viewportMatrix = Viewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);





		///																							
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///



		ImGui::Begin("Control");
		ImGui::DragFloat3("Segment Start", &segment.start.x, 0.01f);
		ImGui::DragFloat3("Segment End", &segment.end.x, 0.01f);
		ImGui::DragFloat3("Triangle V0", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("Triangle V1", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("Triangle V2", &triangle.vertices[2].x, 0.01f);
		ImGui::End();
		// 衝突判定
		if (IsCollision(triangle, segment)) {
			color = RED;
		} else {
			color = WHITE;
		}



		// 線分描画
		Vector3 screenStart = Transform(Transform(segment.start, worldViewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(segment.end, worldViewProjectionMatrix), viewportMatrix);
		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, color);

		// 三角形描画
		Matrix4x4 triangleTransform = Multiply(worldViewProjectionMatrix, viewportMatrix);
		DrawTriangle(triangle, triangleTransform, WHITE);
		
		
		DrawGrid(worldViewProjectionMatrix, viewportMatrix, 0.0f);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}