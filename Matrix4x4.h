#pragma once
#include "Vector3.h"


struct Matrix4x4 {
	float m[4][4];
};

namespace MatrixMath {

	// ���W�ϊ�
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
	// ���ˉe�s��
	Matrix4x4 Orthographic(float left, float top, float right, float bottom, float nearClip, float farClip);
	// �������e�s��
	Matrix4x4 PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip);
	// �r���[�|�[�g�ϊ��s��
	Matrix4x4 Viewport(float left, float top, float width, float height, float minDepth, float maxDepth);

	

	

}


