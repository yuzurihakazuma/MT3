#include "Matrix4x4.h"
#include <math.h>
#include <cassert>

// 4x4�s��̐�
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

// ���s�ړ��s��
Matrix4x4 MatrixMath::MakeTranslate(const Vector3& translate) {

	Matrix4x4 result = {};
	// �P�ʍs��̍쐬
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	// ���s�ړ��̐���
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;// �����������s�ړ���Ԃ�
}
// �g��k���s��
Matrix4x4 MatrixMath::MakeScale(const Vector3& scale) {

	Matrix4x4 result = {};
	// �g�嗦�̐ݒ�
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	return result;// �g��(�X�P�\�����N)�s���Ԃ�
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
