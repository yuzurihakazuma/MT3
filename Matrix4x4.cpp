#include "Matrix4x4.h"
#include <math.h>
#include <cassert>

// 4x4行列の積
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
