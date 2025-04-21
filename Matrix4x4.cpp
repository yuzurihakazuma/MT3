#include "Matrix4x4.h"
#include <math.h>
#include <cassert>

// 4x4s—ñ‚ÌÏ
Matrix4x4 MatrixMath::Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.m[row][col] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[row][col] += m1.m[row][k] * m2.m[k][col];
            }
        }
    }

    return result;
}

Matrix4x4 MatrixMath::MakeTranslate(const Vector3& translate) {
	return Matrix4x4();
}

Matrix4x4 MatrixMath::MakeScale(const Vector3& scale) {
	return Matrix4x4();
}

Matrix4x4 MatrixMath::MakeRotateX(float radian) {
	return Matrix4x4();
}

Matrix4x4 MatrixMath::MakeRotateY(float radian) {
	return Matrix4x4();
}

Matrix4x4 MatrixMath::MakeRotateZ(float radian) {
	return Matrix4x4();
}

Matrix4x4 MatrixMath::MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	return Matrix4x4();
}
