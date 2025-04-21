#include <Novice.h>
#include "Matrix4x4.h"
const char kWindowTitle[] = "LE2C_28_ユズリハ_カズマ";

static const int kColumnWidth = 60;
static const int kRowHeight = 40;
// Matrixを綺麗に並べるための関数
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix , const char* label) {
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]
			);
		}
	}
	Novice::ScreenPrintf(x, y-20, "%s", label);// 関数の名前
}

// x座標 y座標 z座標　関数を綺麗に並べるための関数
void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.02f", vector.x); //ｘのフォーマット 
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.02f", vector.y);//yのフォーマット
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.02f", vector.z);//zのフォーマット
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label); //関数の名前
}





// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// 平行移動ベクトル
	Vector3 translate{ 4.1f, 2.6f, 0.8f };
	// 拡大縮小ベクトル
	Vector3 scale{ 1.5f,5.2f,7.3f };
	// 座標変換
	Vector3 point{ 2.3f,3.8f,1.4f };

	Matrix4x4 transformMatrix = {
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
	};

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
		// 平行移動
		Matrix4x4 translateMatrix = MatrixMath::MakeTranslate(translate);
		// 拡大縮小
		Matrix4x4 scaleMatrix = MatrixMath::MakeScale(scale);
		// 座標変換
		Vector3 transformed = MatrixMath::Transform(point, transformMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, transformed, "transformed");

		MatrixScreenPrintf(0, kRowHeight, translateMatrix, "translateMatrix");

		MatrixScreenPrintf(0, kRowHeight * 5, scaleMatrix, "scaleMatrix");

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


