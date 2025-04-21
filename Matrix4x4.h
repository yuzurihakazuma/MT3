#pragma once
#include "Vector3.h"


struct Matrix4x4 {
	float m;
};

namespace MatrixMath {

	// ���s�ړ��s��
	Matrix4x4 MakeTranslate(const Vector3& translate);
	// �g��k���s��
	Matrix4x4 MakeScale(const Vector3& scale);

	// 3�����A�t�B���ϊ��s��
	Matrix4x4 MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

}