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






	// --- ベクトル演算テスト ---
	Vector3 a { 0.2f, 1.0f, 0.0f };
	Vector3 b { 2.4f, 3.1f, 1.2f };

	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 rotate { 0.4f,1.43f,-0.8f };
	
	// 行列演算テスト（回転Zの合成など）
	Vector3 rotate0 { 0.4f, 0.0f, 0.0f };
	Vector3 rotate1 { 1.43f, 0.0f, 0.8f };

	Matrix4x4 rotateMatrix1 = MakeRotateX(rotate.x);
	Matrix4x4 rotateMatrix2 = MakeRotateY(rotate.y);
	Matrix4x4 rotateMatrix3 = MakeRotateZ(rotate.z);
	Matrix4x4 rotateMatrix = rotateMatrix1 * rotateMatrix2 * rotateMatrix3;


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
		Matrix4x4 worldMatrixRoot = MakeIdentity4x4();
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrixRoot, viewProjectionMatrix);
		Matrix4x4 viewportMatrix = Viewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		///																						
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

	// --- ImGui 表示 ---
		ImGui::Begin("Debug");
		ImGui::Text("Camera Debug");
		ImGui::DragFloat3("Camera Position", &cameraTranslate.x, 0.05f);
		ImGui::DragFloat3("Camera Rotation", &cameraRotate.x, 0.01f);


		ImGui::Text("c: %f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d: %f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e: %f, %f, %f", e.x, e.y, e.z);

		ImGui::Text(
			"matrix:\n"
			"%f, %f, %f, %f\n"
			"%f, %f, %f, %f\n"
			"%f, %f, %f, %f\n"
			"%f, %f, %f, %f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]
		);

		ImGui::End();
		


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