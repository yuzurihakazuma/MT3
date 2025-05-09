#include <Novice.h>
#include "Matrix4x4.h"
const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

using namespace MatrixMath;

// x座標 y座標 z座標　関数を綺麗に並べるための関数
void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.02f", vector.x); //ｘのフォーマット 
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.02f", vector.y);//yのフォーマット
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.02f", vector.z);//zのフォーマット
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label); //関数の名前
}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);



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
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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


