#include <Novice.h>
#include "Matrix4x4.h"
#include "Grid.h"
#include <imgui.h>

using namespace MatrixMath;

const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	
	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 camaraRotate{ 0.26f,0.0f,0.0f };
	Vector3 cameraPos{ 0.0f,2.0f,10.0f };

	Segment segmet{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	// pointを養分に射影したベクトル。今回は正しく計算できているかを確認するためだけに使う
	Vector3 point{ -1.5f,0.6f,0.6f };
	// この値が線分上の点を表す
	Vector3 closestPoint = ClosestPoint(point, segmet);

	

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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
		
			// ワールド行列
		Matrix4x4 cameraMatrix = MakeAffine({ 1.0f,1.0f,1.0f }, camaraRotate, cameraTranslate);
		// ビュー行列はカメラ行列の逆行列
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		// 透視投影行列
		Matrix4x4 projectionMatrix = PerspectiveFov(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		// W→V→Pの順番でかけ合わせる
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		// ビューポート行列
		Matrix4x4 viewportMatrix = Viewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		Sphere pointSphere{ point,0.01f };// 1cmの球描画
		Sphere closestPointSphere{ closestPoint,0.01f };

		DrawSphere(pointSphere, viewportMatrix, viewMatrix, RED);
		DrawSphere(closestPointSphere, viewportMatrix, viewMatrix, BLACK);




#ifdef _DEBUG
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &camaraRotate.x, 0.01f);
		ImGui::End();
#endif // _DEBUG



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Vector3 start = Transform(Transform(segmet.start, viewProjectionMatrix), viewportMatrix);
		//start = Transform(start, viewportMatrix);

		Vector3 end = Transform(Transform(segmet.end, viewProjectionMatrix),viewportMatrix);
		//end = Transform(end, viewportMatrix);

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		Novice::DrawLine(
			static_cast<int>(start.x), static_cast<int>(start.y),
			static_cast<int>(end.x), static_cast<int>(end.y),
			0xFFFFFFFF
		);

		

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


