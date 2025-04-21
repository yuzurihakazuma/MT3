#pragma once
#include "Vector3.h"


struct Matrix4x4 {
	float m;
};

namespace MatrixMath {

	// 平行移動行列
	Matrix4x4 MakeTranslate(const Vector3& translate);
	// 拡大縮小行列
	Matrix4x4 MakeScale(const Vector3& scale);

	// 3次元アフィン変換行列
	Matrix4x4 MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

}