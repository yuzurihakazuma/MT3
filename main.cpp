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






	// 階層構造の初期化[0]は肩[1]は肘[2]は手
	Vector3 translate[3] = { 
		{0.2f, 1.0f, 0.0f}, 
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f}
	};
	Vector3 rotate[3] = {
	{0.0f, 0.0f, -6.8f},
	{0.0f, 0.0f, -1.4f},
	{0.0f, 0.0f, 0.0f}
	};
	Vector3 scale[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f}
	};
	Matrix4x4 worldMatrix[3]; // ワールド行列（肩・肘・手）



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





		// ビュー行列などの生成
		Matrix4x4 cameraMatrix = MakeAffine({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = PerspectiveFov(0.45f, float(kWindowWidth) / kWindowHeight, 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = Viewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		// 階層構造のワールド行列計算
		worldMatrix[0] = MakeAffine(scale[0], rotate[0], translate[0]);                           // 肩
		worldMatrix[1] = Multiply(MakeAffine(scale[1], rotate[1], translate[1]), worldMatrix[0]); // 肘
		worldMatrix[2] = Multiply(MakeAffine(scale[2], rotate[2], translate[2]), worldMatrix[1]); // 手


		///																							
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		   // ImGui UI 表示
		ImGui::SetNextWindowPos(ImVec2(980, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(280, 250), ImGuiCond_Once);
		ImGui::Begin("Debug");

		ImGui::Text("Camera Debug");
		ImGui::DragFloat3("Camera Position", &cameraTranslate.x, 0.05f);
		ImGui::DragFloat3("Camera Rotation", &cameraRotate.x, 0.01f);

		ImGui::Separator();
		ImGui::Text("Joint Transforms");
		for ( int i = 0; i < 3; i++ ) {
			std::string labelT = "translate[" + std::to_string(i) + "]";
			std::string labelR = "rotate[" + std::to_string(i) + "]";
			std::string labelS = "scale[" + std::to_string(i) + "]";
			ImGui::DragFloat3(labelT.c_str(), &translate[i].x, 0.01f);
			ImGui::DragFloat3(labelR.c_str(), &rotate[i].x, 0.01f);
			ImGui::DragFloat3(labelS.c_str(), &scale[i].x, 0.01f);
		}
		ImGui::End();

		// 関節の位置を計算
		Vector3 shoulderPos = Transform({ 0, 0, 0 }, worldMatrix[0]);
		Vector3 elbowPos = Transform({ 0, 0, 0 }, worldMatrix[1]);
		Vector3 wristPos = Transform({ 0, 0, 0 }, worldMatrix[2]);

		DrawSphere({ shoulderPos, 0.05f * scale[0].x }, viewProjectionMatrix, viewportMatrix, RED);
		DrawSphere({ elbowPos,    0.05f * scale[1].x }, viewProjectionMatrix, viewportMatrix, GREEN);
		DrawSphere({ wristPos,    0.05f * scale[2].x }, viewProjectionMatrix, viewportMatrix, BLUE);

		// 関節を結ぶ線を描画
		DrawSegment({ shoulderPos, elbowPos }, viewProjectionMatrix, viewportMatrix, WHITE);
		DrawSegment({ elbowPos, wristPos }, viewProjectionMatrix, viewportMatrix, WHITE);

		// グリッドを描画
		Matrix4x4 worldViewProjectionMatrix = Multiply(MakeIdentity4x4(), viewProjectionMatrix);
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