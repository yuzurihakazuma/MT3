#include "Matrix4x4.h"
#include <math.h>
#include <cassert>
#include <cmath>
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

//X���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateX(float radian) {

    Matrix4x4 result = {};
    // 3������X������̉�]�s��
    result.m[0][0] = 1.0f;// X�������̃x�N�g���ω����Ȃ�
    result.m[1][1] = std::cos(radian); // Y�����̉�]
    result.m[1][2] = std::sin(radian); // Z�����ւ̉e��
    result.m[2][1] = -std::sin(radian);// Y�����ւ̉e��  
    result.m[2][2] = std::cos(radian); // Z�����̉�]
    result.m[3][3] = 1.0f;// �����n���w����(�Œ�l1)

    return result;// X���̉�]�s���Ԃ�
}
// Y���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateY(float radian) {

    Matrix4x4 result = {};
    // 3������Y������̉�]�s��
    result.m[0][0] = std::cos(radian); // X�����̉�]
    result.m[0][2] = -std::sin(radian);// Z�����ւ̉e��
    result.m[1][1] = 1.0f;// Y���͌Œ�
    result.m[2][0] = std::sin(radian); // X�����ւ̉e��
    result.m[2][2] = std::cos(radian); // Z�����̉�]
    result.m[3][3] = 1.0f;// �������W�n��w����(�Œ�l1)

    return result;// Y���̉�]�s���Ԃ�
}
// Z���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateZ(float radian) {

    Matrix4x4 result = {};
    // 3������Z������̉�]�s��
    result.m[0][0] = std::cos(radian); // X�����̉�]
    result.m[0][1] = std::sin(radian);  // Y�����ւ̉e��  
    result.m[1][0] = -std::sin(radian); // X�����ւ̉e��
    result.m[1][1] = std::cos(radian);  // Y�����̉�]
    result.m[2][2] = 1.0f;// Z���͌Œ�
    result.m[3][3] = 1.0f;// �������W�n��w����(�Œ�l1)

    return result;// Z���̉�]�s���Ԃ�
}
// 3�����A�t�B���ϊ��s��
Matrix4x4 MatrixMath::MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	
    Matrix4x4 result = {};
    // �g��k���𐶐�
    Matrix4x4 scaleMatrix = MatrixMath::MakeScale(scale);
    // X���̉�]�s��𐶐�
    Matrix4x4 rotateXMatrix = MatrixMath::MakeRotateX(rotate.x);
    // Y���̉�]�s��𐶐�
    Matrix4x4 rotateYMatrix = MatrixMath::MakeRotateY(rotate.y);
    // Z���̉�]�s��𐶐�
    Matrix4x4 rotateZMatrix = MatrixMath::MakeRotateZ(rotate.z);
    // Z���AY���AX���̏��ɉ�]������
    Matrix4x4 rotateXYZMatrix = MatrixMath::Multiply(rotateXMatrix, MatrixMath::Multiply(rotateYMatrix, rotateZMatrix));
    // ���s�ړ��𐶐�
    Matrix4x4 translateMatrix = MatrixMath::MakeTranslate(translate);
    
    result = MatrixMath::Multiply(translateMatrix, MatrixMath::Multiply(rotateXYZMatrix, scaleMatrix));

    return result;
}
