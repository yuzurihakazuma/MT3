#pragma once
#include "Vector3.h"


struct Matrix4x4 {
	float m;
};

namespace MatrixMath {

	// 行列の積
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	// 平行移動行列
	Matrix4x4 MakeTranslate(const Vector3& translate);
	// 拡大縮小行列
	Matrix4x4 MakeScale(const Vector3& scale);

	// X軸の回転行列
	Matrix4x4 MakeRotateX(float radian);
	// Y軸の回転行列
	Matrix4x4 MakeRotateY(float radian);
	// Z軸の回転行列
	Matrix4x4 MakeRotateZ(float radian);

	// 3次元アフィン変換行列
	Matrix4x4 MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

}