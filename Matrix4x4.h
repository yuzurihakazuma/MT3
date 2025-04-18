#pragma once
#include "Vector3.h"

struct Matrix4x4 {
	float m[4][4];
};

namespace MatrixMath {
	// 平行移動行列
	Matrix4x4 MakeTranslate(const Vector3& translate);
	// 拡大縮小行列
	Matrix4x4 MakeScale(const Vector3& scale);
	// 座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

}