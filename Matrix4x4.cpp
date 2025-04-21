#include "Matrix4x4.h"

// 平行移動行列
Matrix4x4 MatrixMath::MakeTranslate(const Vector3& translate) {

	Matrix4x4 result = {};
	// 単位行列の作成
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	// 平行移動の成分
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;// 完成した平行移動を返す
}
// 拡大縮小行列
Matrix4x4 MatrixMath::MakeScale(const Vector3& scale) {

	Matrix4x4 result = {};
	// 拡大率の設定
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	return result;// 拡大(スケ―リンク)行列を返す
}