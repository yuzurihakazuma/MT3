#pragma once

struct Matrix4x4 {
	float m[4][4];
};

namespace MatrixMath {
	// X軸の回転行列
	Matrix4x4 MakeRotateX(float radian);
	// Y軸の回転行列
	Matrix4x4 MakeRotateY(float radian);
	// Z軸の回転行列
	Matrix4x4 MakeRotateZ(float radian);

	// 行列の積
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
}
