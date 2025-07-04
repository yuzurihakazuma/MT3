#include <Novice.h>
#include "Sphere.h"
#include "Matrix4x4.h"
#include <imgui.h>


using namespace MatrixMath;
using namespace MathSphere;

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

	

	Plane plane = { 0.0f,1.0f,0.0f };
	// 1. 球の代わりに線分を用意
	Segment segment = { {-2.0f, 0.0f, 0.0f}, {2.0f, 2.0f, 0.0f} };
	
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



		//各種行列の計算


		/*Matrix4x4 cameraMatrix = MatrixMath::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);

		Matrix4x4 viewMatrix = MatrixMath::Inverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MatrixMath::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

		Matrix4x4 worldViewProjectionMatrix = MatrixMath::Multiply(cameraMatrix, MatrixMath::Multiply(viewMatrix, projectionMatrix));

		Matrix4x4 viewportMatrix = MatrixMath::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);*/


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



		ImGui::Begin("Window");
		ImGui::DragFloat3("Segment Start", &segment.start.x, 0.01f);
		ImGui::DragFloat("Segment End", &segment.end.x, 0.01f);
		ImGui::DragFloat3("Plane.Normal", &plane.normal.x, 0.01f);
		ImGui::DragFloat("Plane.Distance", &plane.distance, 0.01f);

		plane.normal = MatrixMath::Normalize(plane.normal); // 法線ベクトルを正規化

		// 2. 衝突判定
		if (IsCollision(segment, plane)) {
			color = RED;
		} else {
			color = WHITE;
		}



		// Segment描画
		Vector3 screenStart = Transform(Transform(segment.start, worldViewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(segment.end, worldViewProjectionMatrix), viewportMatrix);
		Novice::DrawLine(
			int(screenStart.x), int(screenStart.y),
			int(screenEnd.x), int(screenEnd.y),
			color
		);
		DrawGrid(worldViewProjectionMatrix, viewportMatrix,-0.6f);

		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);

		/*ImGui::DragFloat3("Point", &point.x, 0.01f);*/
		//ImGui::DragFloat3("segmentOrigin", &segment.origin.x, 0.01f); // ←中心座標
		//ImGui::DragFloat("segmentDiff", &segment.diff.x, 0.01f);     // ←半径
		//ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();
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