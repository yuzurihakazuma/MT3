#define NOMINMAX
#include <algorithm> 
#define _USE_MATH_DEFINES 
#include "Grid.h"
#include <cmath>
#include <math.h>
#include <assert.h>
#include <vector>
#include <Novice.h>

using namespace MatrixMath;

void DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfwidth = 2.0f; // グリッドの半分の幅
	const uint32_t kSubdivision = 10;  // 分割数
	const float kGridEvery =
		(kGridHalfwidth * 2.0f) / float(kSubdivision); // 一つ分の長さ

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float x = -kGridHalfwidth + kGridEvery * xIndex;

		// ワールド座標系の支点と終点
		Vector3 start = { x, 0.0f, -kGridHalfwidth };
		Vector3 end = { x, 0.0f, kGridHalfwidth };

		// 変換（ワールド→スクリーン）
		Vector3 startScreen = Transform(start, worldViewProjectionMatrix);
		startScreen = Transform(startScreen, viewportMatrix);

		Vector3 endScreen = Transform(end, worldViewProjectionMatrix);
		endScreen = Transform(endScreen, viewportMatrix);

		// 色を決める（原点の線は黒、それ以外は薄い灰色）
		uint32_t color = (x == 0.0f) ? 0x000000FF : 0xAAAAAAFF;

		// 線を引く
		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x),
			int(endScreen.y), color);
	}

	// 左から右への線を順々に引いていく
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
	float dot = v1.Dot(v2);            // v1とv2の内積
	float lenSq = v2.Dot(v2);          // v2の長さの2乗
	if (lenSq == 0.0f) {
		return Vector3{ 0.0f, 0.0f, 0.0f }; // v2がゼロベクトルなら射影は0
	}
	float scale = dot / lenSq;
	return Vector3{
		v2.x * scale,
		v2.y * scale,
		v2.z * scale
	};
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 ab = segment.end - segment.start;
	Vector3 ap = point - segment.start;

	float abLengthSq = ab.Dot(ab);
	if (abLengthSq == 0.0f) {
		// 線分が1点（startとendが同じ）ならstartを返す
		return segment.start;
	}

	float t = ap.Dot(ab) / abLengthSq;
	t = std::max(0.0f, std::min(1.0f, t)); // 線分の範囲にクランプ

	return segment.start + ab * t;
}