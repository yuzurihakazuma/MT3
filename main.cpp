#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
const char kWindowTitle[] = "LE2C_27_ユズリハ_カズマ";
// 3次元ベクトル
typedef struct Vector3 {
	float x;
	float y;
	float z;
}Vector3;
// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {

	Vector3 result = {};

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;

}
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {

	Vector3 result = {};

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {

	Vector3 result = {};

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;
}
// 内積
float Dot(const Vector3& v1, const Vector3& v2) {

	float result = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);


	return result;

}
// 長さ(ノルム)
float Length(const Vector3& v) {

	float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	return result;
}
// 正規化
Vector3 Normalize(const Vector3& v) {

	Vector3 result = {};

	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);

	return result;
}
// xの幅
static const int kColumnWindth = 60;
 // x座標 y座標 z座標　関数を綺麗に並べるための関数
void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.02f", vector.x); //ｘのフォーマット 
	Novice::ScreenPrintf(x + kColumnWindth, y, "%0.02f", vector.y);//yのフォーマット
	Novice::ScreenPrintf(x + kColumnWindth * 2, y, "%0.02f", vector.z);//zのフォーマット
	Novice::ScreenPrintf(x + kColumnWindth * 3, y, "%s", label); //関数の名前


}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	Vector3 v1 = {
		1.0f,3.0f,-5.0f
	};
	Vector3 v2 = {
		4.0f,-1.0f,2.0f
	};
	// スカラー
	float k = 4.0f;

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
		
		// 加算
		Vector3 resultAdd = Add(v1, v2);
		// 減算
		Vector3 resultSubtract = Subtract(v1, v2);
		// スカラー倍
		Vector3 resultMultiply = Multiply(k, v1);
		// 内積
		float resultDot =	Dot(v1, v2);
		// 長さ(ノルく)
		float resultLength = Length(v1);
		// 正規化
		Vector3 resultNormalize = Normalize(v2);





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, resultAdd, " :Add");
		VectorScreenPrintf(0, 15, resultSubtract, " :Subtract");
		VectorScreenPrintf(0, 30, resultMultiply, " :Multiply");
		Novice::ScreenPrintf(0, 45, "%0.02f  :Dot", resultDot);
		Novice::ScreenPrintf(0, 60, "%0.02f  :Length", resultLength);
		VectorScreenPrintf(0, 75, resultNormalize, " :Normalize");




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


