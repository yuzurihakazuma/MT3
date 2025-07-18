#include <Novice.h>
#include "Sphere.h"
#include "Matrix4x4.h"
#include <imgui.h>


using namespace MatrixMath;
const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	AABB aabb1 = { ( -0.5f,-0.5f,-0.5f ) , ( 0.0f,0.0f,0.0f ) };
	AABB aabb2 = { ( 0.2f,0.2f,0.2f ) , ( 1.0f,1.0f,1.0f ) };

	unsigned int aabbColor1 = WHITE;
	unsigned int aabbColor2 = WHITE;

	

	Vector3 cameraPosition = { 0.0f,0.0f,-1.0f };

	Vector3 cameraTranslate { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate { 0.26f,0.0f,0.0f };


	/*Triangle triangle = {
		{{ 0.0f, 0.0f, 0.0f },
		 { 1.0f, 0.0f, 0.0f },
		 { 0.0f, 1.0f, 0.0f }}
	};
	Segment segment = {
	{-1.0f, 0.5f, 0.0f},
	{ 1.0f, 0.5f, 0.0f}
	};
	Vector3 point { -1.5f,0.6f,0.6f };*/

	

	//pointを線分に射影したベクトル。今回は正しく計算できているかを確認するためだけに使う
	//Vector3 closestPoint = ClosestPoint(point, segment);


	// ウィンドウの×ボタンが押されるまでループ
	while ( Novice::ProcessMessage() == 0 ) {
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
		Matrix4x4 worldMatrix = MakeIdentity4x4();


		// 各種行列の合成
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

		// ビューポート行列
		Matrix4x4 viewportMatrix = Viewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);





		///																							
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		ImGui::SetNextWindowPos(ImVec2(980, 10), ImGuiCond_Once);  // 右上に配置
		ImGui::SetNextWindowSize(ImVec2(280, 230), ImGuiCond_Once); // サイズ調整

		ImGui::Begin("Debug"); // ←これを必ず入れる！見た目の枠の開始

		ImGui::Text("Camera Debug");
		ImGui::DragFloat3("Camera Position", &cameraTranslate.x, 0.05f);
		ImGui::DragFloat3("Camera Rotation", &cameraRotate.x, 0.01f);

		ImGui::Separator();
		ImGui::Text("AABB1");
		ImGui::DragFloat3("AABB1 Min", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("AABB1 Max", &aabb1.max.x, 0.01f);

		ImGui::Text("AABB2");
		ImGui::DragFloat3("AABB2 Min", &aabb2.min.x, 0.01f);
		ImGui::DragFloat3("AABB2 Max", &aabb2.max.x, 0.01f);

		ImGui::End(); // ←これも忘れずに
		AABB fixedAABB1 = FixAABB(aabb1);
		AABB fixedAABB2 = FixAABB(aabb2);
		if ( MatrixMath::IsCollision(aabb1, aabb2) ) {
			aabbColor1 = RED;      // aabb1 を赤く
			aabbColor2 = WHITE;    // aabb2 は白のまま
		} else {
			aabbColor1 = WHITE;    // 衝突していないなら両方白
			aabbColor2 = WHITE;
		}

		MatrixMath::DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, aabbColor1);
		MatrixMath::DrawAABB(aabb2, worldViewProjectionMatrix, viewportMatrix, aabbColor2);

		

		DrawGrid(worldViewProjectionMatrix, viewportMatrix, 0.0f);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if ( preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0 ) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}