#include <Novice.h>
#include "Matrix4x4.h"
const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";


using namespace MatrixMath;

static const int kColumnWidth = 60;
static const int kRowHeight = 30;
// Matrixを綺麗に並べるための関数
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {

	// 通常時：ラベルは上に表示（ただし見切れ防止）
	int labelY = y - 20;
	if (labelY < 0) {
		labelY = 0;
	}
	Novice::ScreenPrintf(x, labelY, "%s", label);

	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, (y + 20) + row * kRowHeight, "%6.02f", matrix.m[row][column]
			);
		}
	}
}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	// 正射影行列
	Matrix4x4 orthographicMatrix =
		Orthographic(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f );
	// 透視投影行列
	Matrix4x4 PerspectiveForMatrix =
		PerspectiveFov(0.63f, 1.33f, 0.1f, 1000.0f);
	// ビューポート変換行列
	Matrix4x4 viewportMatrix =
		Viewport(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);




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

		MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		MatrixScreenPrintf(0, kRowHeight*5, PerspectiveForMatrix, "PerspectiveForMatrix");
		MatrixScreenPrintf(0, kRowHeight*5*2, viewportMatrix, "viewportMatrix");



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


