#define _USE_MATH_DEFINES 
#include <algorithm> 
#include "Grid.h"
#include <cmath>
#include <math.h>
#include <assert.h>
#include <vector>
#include <Novice.h>

using namespace MatrixMath;

void DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfwidth = 2.0f; // �O���b�h�̔����̕�
	const uint32_t kSubdivision = 10;  // ������
	const float kGridEvery =
		(kGridHalfwidth * 2.0f) / float(kSubdivision); // ����̒���

	// �������O�ւ̐������X�Ɉ����Ă���
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float x = -kGridHalfwidth + kGridEvery * xIndex;

		// ���[���h���W�n�̎x�_�ƏI�_
		Vector3 start = { x, 0.0f, -kGridHalfwidth };
		Vector3 end = { x, 0.0f, kGridHalfwidth };

		// �ϊ��i���[���h���X�N���[���j
		Vector3 startScreen = Transform(start, worldViewProjectionMatrix);
		startScreen = Transform(startScreen, viewportMatrix);

		Vector3 endScreen = Transform(end, worldViewProjectionMatrix);
		endScreen = Transform(endScreen, viewportMatrix);

		// �F�����߂�i���_�̐��͍��A����ȊO�͔����D�F�j
		uint32_t color = (x == 0.0f) ? 0x000000FF : 0xAAAAAAFF;

		// ��������
		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x),
			int(endScreen.y), color);
	}

	// ������E�ւ̐������X�Ɉ����Ă���
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float z = -kGridHalfwidth + kGridEvery * zIndex;

		Vector3 start = { -kGridHalfwidth, 0.0f, z };
		Vector3 end = { kGridHalfwidth, 0.0f, z };

		Vector3 startScreen = Transform(start, worldViewProjectionMatrix);
		startScreen = Transform(startScreen, viewportMatrix);

		Vector3 endScreen = Transform(end, worldViewProjectionMatrix);
		endScreen = Transform(endScreen, viewportMatrix);

		uint32_t color = (z == 0.0f) ? 0x000000FF : 0xAAAAAAFF;

		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x),
			int(endScreen.y), color);
	}
}

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	return Vector3();
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 ab = segment.end - segment.start;
	Vector3 ap = point - segment.start;

	float abLengthSq = ab.Dot(ab);
	if (abLengthSq == 0.0f) {
		// ������1�_�istart��end�������j�Ȃ�start��Ԃ�
		return segment.start;
	}

	float t = ap.Dot(ab) / abLengthSq;
	t = std::max(0.0f, std::min(1.0f, t)); // �����͈̔͂ɃN�����v

	return segment.start + ab * t;
}