#include "Matrix4x4.h"

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