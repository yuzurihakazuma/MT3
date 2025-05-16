#include "Sphere.h"
#include <vector>
#include <cmath> 
#include <Novice.h>

using namespace MatrixMath;


void DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t coler) {

	const uint32_t kSubdivsion = 16;
	const float kLonEvery = 2.0f * float(M_PI) / float(kSubdivsion);
	const float kLatEvery = float(M_PI) / float(kSubdivsion);
	// �y�x�̕����ɕ���


}



void DrawaGrid(const Matrix4x4& PerspectiveFov, const Matrix4x4& Viewport) {

	const float kGridHalfWidth = 2.0f; // Grid�̔����̕�
	const uint32_t kSubdivision = 10;  // ������
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); // ����̒���

	// �������O�ւ̐������X�Ɉ����Ă���
	for (uint32_t xIndex = 0; xIndex < kSubdivision; ++xIndex) {
		// ��̏����g���ă��[���h���W�n��̎n�_�ƏI�_�����߂�
		float x = -kGridHalfWidth + xIndex * kGridEvery;

		// Z�����ɉ������O
		Vector3 start = { x,0.0f,-kGridHalfWidth };
		Vector3 end = { x,0.0f,kGridHalfWidth };

		// �X�N���[�����W�n�̕ϊ���������
		Vector3 startScreen = Transform(Transform(start, PerspectiveFov), Viewport);
		Vector3 endScreen = Transform(Transform(end, PerspectiveFov), Viewport);

		// �ϊ��������W���g���ĕ\���B�F�͔����D�F(0xAAAAAAFF),���_�͍����炢���������A���ł�����
		uint32_t color = (x == 0) ? 0x000000FF : 0xAAAAAAAFF; //���_�͍��A����ȊO�͊D�F

		Novice::DrawLine(float(startScreen.x), float(startScreen.y),
			float(endScreen.x), float(endScreen.y), color);
	}

	// ������E�������悤�ɏ��X�Ɉ����Ă���
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float z = -kGridHalfWidth + zIndex * kGridEvery;

		// ������E�����Ɉ����O���b�h���̎n�_�ƏI�_�iXZ���ʁj
		Vector3 start = { -kGridHalfWidth, 0.0f, z };
		Vector3 end = { kGridHalfWidth, 0.0f, z };

		// �ϊ��i���[���h���W �� �N���b�v���W �� �X�N���[�����W�j
		Vector3 startScreen = Transform(Transform(start, PerspectiveFov), Viewport);
		Vector3 endScreen = Transform(Transform(end, PerspectiveFov), Viewport);

		uint32_t color = (z == 0.0f) ? 0x000000FF : 0xAAAAAAFF;
		Novice::DrawLine(float(startScreen.x), float(startScreen.y),
			float(endScreen.x), float(endScreen.y), color);
	}


}