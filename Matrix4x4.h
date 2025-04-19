#pragma once
struct Matrix4x4 {

	float m[4][4];
};

namespace MatrixMath {
	// 行列の加法
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
	// 行列の減法
	Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
	// 行列の積
	Matrix4x4 Multipty(const Matrix4x4& m1, const Matrix4x4& m2);
	// 逆行列
	Matrix4x4 Inverse(const Matrix4x4& m);
	// 転置行列
	Matrix4x4 Transpoce(const Matrix4x4& m);
	// 単位行列の作成
	Matrix4x4 MakeIdentity4x4();

}

