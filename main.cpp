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


	Vector3 controlPoints[3] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
	};


	Vector3 cameraPosition = { 0.0f,0.0f,-1.0f };

	Vector3 cameraTranslate { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate { 0.26f,0.0f,0.0f };


	


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





		// ビュー・プロジェクション・ビューポート行列作成
		Matrix4x4 cameraMatrix = MakeAffine({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = MatrixMath::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = PerspectiveFov(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldMatrix = MakeIdentity4x4();
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);
		Matrix4x4 viewportMatrix = Viewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);





		///																							
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		// ImGui UI
		ImGui::SetNextWindowPos(ImVec2(980, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(280, 230), ImGuiCond_Once);
		ImGui::Begin("Debug");
		ImGui::Text("Camera Debug");
		ImGui::DragFloat3("Camera Position", &cameraTranslate.x, 0.05f);
		ImGui::DragFloat3("Camera Rotation", &cameraRotate.x, 0.01f);
		ImGui::Separator();
		ImGui::Text("Bezier Control Points");
		ImGui::DragFloat3("p0", &controlPoints[0].x, 0.01f);
		ImGui::DragFloat3("p1", &controlPoints[1].x, 0.01f);
		ImGui::DragFloat3("p2", &controlPoints[2].x, 0.01f);
		ImGui::End();
		
		

		// ベジェ曲線描画
		MatrixMath::DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], worldViewProjectionMatrix, viewportMatrix, GREEN);

		// グリッド描画
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