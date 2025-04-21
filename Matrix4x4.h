#pragma once
#include "Vector3.h"


struct Matrix4x4 {
	float m;
};

namespace MatrixMath {



	// 3次元アフィン変換行列
	Matrix4x4 MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

}