#include <Novice.h>
#include "Matrix4x4.h"
const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

static const int kColumnWidth = 40;
static const int kRowHeight = 30;
// Matrixを綺麗に並べるための関数
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]
			);
		}
	}
	Novice::ScreenPrintf(x, y - 20, "%s", label);// 関数の名前
}

struct Vector3 {
	float x;
	float y;
	float z;
};


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	
 Vector3 rotate{ 0.4f,1.43f,-0.8f };

 

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
		
		Matrix4x4 rotateXMatrix = MatrixMath::MakeRotateX(rotate.x);
		Matrix4x4 rotateYMatrix = MatrixMath::MakeRotateX(rotate.y);
		Matrix4x4 rotateZMatrix = MatrixMath::MakeRotateX(rotate.z);
		Matrix4x4 rotateXYZMatrix = MatrixMath::Multiply(rotateXMatrix, MatrixMath::Multiply(rotateYMatrix, rotateZMatrix));

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		MatrixScreenPrintf(0, kRowHeight*5, rotateYMatrix, "rotateYMatrix");
		MatrixScreenPrintf(0, kRowHeight*5*2, rotateZMatrix, "rotateZMatrix");
		MatrixScreenPrintf(0, kRowHeight*5*3, rotateXYZMatrix, "rotateXYZMatrix");



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


