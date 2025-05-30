#define _USE_MATH_DEFINES
#include "Matrix4x4.h"
#include <math.h>
#include <cassert>
#include <cmath>

using namespace MatrixMath;

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
Matrix4x4 MatrixMath::MakeScale(const Vector3& scale) {}

#pragma region ��]�s��

//X���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateX(float radian) {}
// Y���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateY(float radian) {}
// Z���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateZ(float radian) {}
#pragma endregion

// 3�����A�t�B���ϊ��s��
Matrix4x4 MatrixMath::MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {}

// 4x4�s��̋t�s��
Matrix4x4 MatrixMath::Inverse(const Matrix4x4& m) {}


// ���W�ϊ�
Vector3 MatrixMath::Transform(const Vector3& vector, const Matrix4x4& matrix) {}

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
// �������e�s��
Matrix4x4 MatrixMath::PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip) {

	Matrix4x4 result = {};

	// �R�^���W�F���g(fovY/2)
	float f = 1.0f / std::tan(fovY / 2.0f);

	// �������e�s��̊e�v�f�ݒ�
	result.m[0][0] = f / aspectRatio;
	result.m[1][1] = f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

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