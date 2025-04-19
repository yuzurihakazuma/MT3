#include <Novice.h>
#include "Matrix4x4.h"
const char kWindowTitle[] = "LE2C_27_ユズリハ_カズマ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
// Matrixを綺麗に並べるための関数
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]
			);
		}
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


	Matrix4x4 m1 = {
		3.2f,0.7f,9.6f,4.4f,
		5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f };

	Matrix4x4 m2 = {
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f };


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

		// 加法
		Matrix4x4 resultAdd = MatrixMath::Add(m1, m2);
		// 減法
		Matrix4x4 resultMultipy = MatrixMath::Multipty(m1, m2);
		// 積
		Matrix4x4 resultSubtract = MatrixMath::Subtract(m1, m2);
		// 逆行列M1
		Matrix4x4 inverseM1 = MatrixMath::Inverse(m1);
		// 逆行列M2
		Matrix4x4 inverseM2 = MatrixMath::Inverse(m2);
		// 転置行列M1
		Matrix4x4 transposeM1 = MatrixMath::Transpoce(m1);
		// 転置行列M2
		Matrix4x4 transposeM2 = MatrixMath::Transpoce(m2);
		// 単位行列
		Matrix4x4 identity = MatrixMath::MakeIdentity4x4();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 15, resultAdd);
		MatrixScreenPrintf(0, 15 + kRowHeight * 5, resultSubtract);
		MatrixScreenPrintf(0, 15 + kRowHeight * 5 * 2, resultMultipy);
		MatrixScreenPrintf(0, 15 + kRowHeight * 5 * 3, inverseM1);
		MatrixScreenPrintf(0, 15 + kRowHeight * 5 * 4, inverseM2);
		MatrixScreenPrintf(kColumnWidth * 5, 15, transposeM1);
		MatrixScreenPrintf(kColumnWidth * 5, 15 + kRowHeight * 5, transposeM2);
		MatrixScreenPrintf(kColumnWidth * 5, 15 + kRowHeight * 5 * 2, identity);

		Novice::ScreenPrintf(0, 0, "Add");
		Novice::ScreenPrintf(0, kRowHeight * 5, "Subtract");
		Novice::ScreenPrintf(0, kRowHeight * 5 * 2, "Multipy");
		Novice::ScreenPrintf(0, kRowHeight * 5 * 3, "inverseM1");
		Novice::ScreenPrintf(0, kRowHeight * 5 * 4, "inverseM2");
		Novice::ScreenPrintf(kColumnWidth * 5, 0, "transposeM1");
		Novice::ScreenPrintf(kColumnWidth * 5, kRowHeight * 5, "transposeM2");
		Novice::ScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, "identity");

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
