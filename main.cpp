#include <Novice.h>
#include "Matrix4x4.h"
#include <cstdint>
#include "imgui.h"
const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

using namespace MatrixMath;

static const int kColumnWidth = 60;
static const int kRowHeight = 40;
const int kWindowWidth = 1280;
const int kWindowHeight = 720;
//const float kW = 1.0f; // 適切な値に調整してください
// x座標 y座標 z座標　関数を綺麗に並べるための関数
void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.02f", vector.x); //ｘのフォーマット 
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.02f", vector.y);//yのフォーマット
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.02f", vector.z);//zのフォーマット
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label); //関数の名前
}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	Vector3 kLocalVertices[3] = {
	{-1.0f, -1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{1.0f, -1.0f, 0.0f}
	};


	// クロス積確認用
	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };
	Vector3 cameraPos{ 0.0f,0.0f,-10.0f };


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
		// 右に移動
		if (keys[DIK_A]) {
			
			translate.x -= 0.5f;
		}
		// 左に移動
		if (keys[DIK_D]) {
			translate.x += 0.5f;
		}
		// 奥に移動
		if (keys[DIK_W]) {
			translate.z += 0.5f;
		}
		// 手前に移動
		if (keys[DIK_S]) {
			translate.z -= 0.5f;
		}

		rotate.y += 0.25f;

		


		// クロス積のデバック表示
		VectorScreenPrintf(0, 0, cross, "Cross");
		// ワールド行列
		Matrix4x4 worldMatrix = MakeAffine({ 1.0f,1.0f,1.0f }, rotate, translate);
		// カメラのワールド行列
		Matrix4x4 cameraMatrix = MakeAffine({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPos);
		// ビュー行列はカメラ行列の逆行列
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		// 透視投影行列
		Matrix4x4 projectionMatrix = PerspectiveFov(0.45f, float(kWindowWidth)/float(kWindowHeight),0.1f,100.0f);
		// W→V→Pの順番でかけ合わせる
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		// ビューポート行列
		Matrix4x4 viewportMatrix = Viewport(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		// 描くローカル頂点をスクリーン座標に変換
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			// W→V→P(NDC座標)
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			// NDC→スクリーン座標変換
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
#ifdef _DEBUG
		ImGui::Begin("debug");
		ImGui::DragFloat3("cameraPos", &translate.z, 0.1f);
		ImGui::End();
#endif // _DEBUG


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawTriangle(
			static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
			static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
			static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
			RED, kFillModeSolid
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


