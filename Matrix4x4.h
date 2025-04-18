#pragma once
#include "Vector3.h"

struct Matrix4x4 {
	float m[4][4];
};

namespace MatrixMath {
	// ���s�ړ��s��
	Matrix4x4 MakeTranslate(const Vector3& translate);
	// �g��k���s��
	Matrix4x4 MakeScale(const Vector3& scale);
	// ���W�ϊ�
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

}