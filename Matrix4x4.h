#pragma once
#include "Vector3.h"


struct Matrix4x4 {
	float m;
};

namespace MatrixMath {

	// �s��̐�
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	// ���s�ړ��s��
	Matrix4x4 MakeTranslate(const Vector3& translate);
	// �g��k���s��
	Matrix4x4 MakeScale(const Vector3& scale);

	// X���̉�]�s��
	Matrix4x4 MakeRotateX(float radian);
	// Y���̉�]�s��
	Matrix4x4 MakeRotateY(float radian);
	// Z���̉�]�s��
	Matrix4x4 MakeRotateZ(float radian);

	// 3�����A�t�B���ϊ��s��
	Matrix4x4 MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

}