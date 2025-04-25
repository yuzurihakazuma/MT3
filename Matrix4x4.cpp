#include "Matrix4x4.h"
#define _USE_MATH_DEFINES 
#include <cmath>

// �������e�s��
Matrix4x4 MatrixMath::PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip) {
	
	Matrix4x4 result = {};
	
	// �x���@���烉�W�A���ɕϊ�
	float fovY_rad = fovY * (M_PI / 180.0f);

	// �R�^���W�F���g(fovY/2)
	float f = 1.0f / tanf(fovY_rad / 2.0f);

	// �������e�s��̊e�v�f�ݒ�
	result.m[0][0] = f / aspectRatio;
	result.m[1][1] = f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = (-nearClip * farClip) / (-farClip - nearClip);
	
	return result;
}
// ���ˉe�s��
Matrix4x4 MatrixMath::Orthographic(float left, float top, float right, float bottom, float nearClip, float farClip) {
	
	Matrix4x4 result = {};
	
	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	
	return result;
}
// �r���[�|�[�g�ϊ��s��
Matrix4x4 MatrixMath::Viewport(float left, float top, float width, float height, float minDepth, float maxDepth) {
	
	Matrix4x4 result = {};

	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + (width / 2.0f);
	result.m[3][1] = top + (height / 2.0f);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}
