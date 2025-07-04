#define _USE_MATH_DEFINES 
#include "Sphere.h"
#include <cmath>
#include <math.h>
#include <assert.h>
#include <vector>
#include <Novice.h>

using namespace MatrixMath;
using namespace MathSphere;


Vector3 MathSphere::Perpendicular(const Vector3& vector) {
	// 法線の絶対値の小さい成分を避けて直交ベクトルを作成
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}
// 球
void MathSphere::DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t color) {

	const uint32_t kSubdivsion = 16; // 分割数
	const float kLonEvery = 2.0f * float(M_PI) / float(kSubdivsion); // 経度分割一つ分の角度
	const float kLatEvery = float(M_PI) / float(kSubdivsion); // 緯度分割一つ分の角度
	// 緯度の方向に分割 -π/2-π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivsion; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + latIndex * kLatEvery; // 現在の緯度
		// 経度の方向に分割 0-2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivsion; ++lonIndex) {
			float lon = lonIndex * kLonEvery;// 現在の経度
			// world座標系でのa,b,cを求める
			Vector3 a = {
				sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon),
				sphere.center.y + sphere.radius * std::sin(lat),
				sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon),
			};

			float nextLat = lat + kLatEvery;
			float nextLon = lon + kLonEvery;

			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(lon)
			};

			Vector3 c = {
			   sphere.center.x + sphere.radius * cosf(lat) * cosf(nextLon),
			   sphere.center.y + sphere.radius * sinf(lat),
			   sphere.center.z + sphere.radius * cosf(lat) * sinf(nextLon)
			};


			// a,b,cをScreen座標系まで変換

			Vector3 screenA = Transform(Transform(a, viewProjection), viewport);
			Vector3 screenB = Transform(Transform(b, viewProjection), viewport);
			Vector3 screenC = Transform(Transform(c, viewProjection), viewport);




			// ab,bcで線を引く
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);

		}

	}


}


void MathSphere::DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& viewportMatrix, float yOffset) {
	const float kGridHalfwidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfwidth * 2.0f) / float(kSubdivision);

	// Z軸方向のグリッド
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float x = -kGridHalfwidth + kGridEvery * xIndex;

		Vector3 start = { x, yOffset, -kGridHalfwidth };
		Vector3 end = { x, yOffset, kGridHalfwidth };

		Vector3 startScreen = Transform(Transform(start, worldViewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, worldViewProjectionMatrix), viewportMatrix);

		uint32_t color = (x == 0.0f) ? 0x000000FF : 0xAAAAAAFF;
		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), color);
	}

	// X軸方向のグリッド
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float z = -kGridHalfwidth + kGridEvery * zIndex;

		Vector3 start = { -kGridHalfwidth, yOffset, z };
		Vector3 end = { kGridHalfwidth, yOffset, z };

		Vector3 startScreen = Transform(Transform(start, worldViewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, worldViewProjectionMatrix), viewportMatrix);

		uint32_t color = (z == 0.0f) ? 0x000000FF : 0xAAAAAAFF;
		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), color);
	}
}

//void MathSphere::DrawSegment(const Segment& seg, const Matrix4x4& vp, const Matrix4x4& viewport, uint32_t color) {
//	Vector2 a = Project(seg.origin, vp, viewport);
//	Vector2 b = Project(Add(seg.origin, seg.diff), vp, viewport);
//	Novice::DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, color);
//}

void MathSphere::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	// 平面の中心点（法線ベクトルに距離を掛けたもの）
	Vector3 center = MultiplyScalar(plane.distance, plane.normal);

	// 平面に垂直な2つの単位ベクトルを作成（平面上の軸）
	Vector3 u = MatrixMath::Normalize(Perpendicular(plane.normal)); // 法線と垂直な任意のベクトル
	Vector3 v = MatrixMath::Normalize(Cross(plane.normal, u));                // uと法線に垂直なもう一つのベクトル

	float size = 2.0f; // 平面を描画する正方形の一辺の半分の長さ

	// 平面の四隅の座標を計算（正方形の4頂点）
	Vector3 corners[4] = {
		Add(center, Add(MultiplyScalar(size, u), MultiplyScalar(size, v))),   // +u +v方向の頂点
		Add(center, Add(MultiplyScalar(size, u), MultiplyScalar(-size, v))),  // +u -v方向の頂点
		Add(center, Add(MultiplyScalar(-size, u), MultiplyScalar(-size, v))), // -u -v方向の頂点
		Add(center, Add(MultiplyScalar(-size, u), MultiplyScalar(size, v)))   // -u +v方向の頂点
	};

	// 4つの頂点をスクリーン座標に変換して線で繋ぐ
	// viewProjectionMatrix と viewportMatrix をかけ合わせて変換行列を作成
	Matrix4x4 transform = Multiply(viewProjectionMatrix, viewportMatrix);

	for (int i = 0; i < 4; ++i) {
		Vector3 screen0 = Transform(corners[i], transform);                 // 頂点iを変換
		Vector3 screen1 = Transform(corners[(i + 1) % 4], transform);       // 次の頂点を変換
		Novice::DrawLine(
			static_cast<int>(screen0.x), static_cast<int>(screen0.y),       // 頂点iのスクリーン座標
			static_cast<int>(screen1.x), static_cast<int>(screen1.y),       // 頂点i+1のスクリーン座標
			color                                                           // 線の色
		);
	}
}
// SegmentとPlaneの交差判定
bool MathSphere::IsCollision(const Segment& segment, const Plane& plane) {
	Vector3 startToPlane = segment.start;
	Vector3 endToPlane = segment.end;

	// 各点の平面との距離を求める
	float d1 = Dot(plane.normal, startToPlane) - plane.distance;
	float d2 = Dot(plane.normal, endToPlane) - plane.distance;

	// どちらかが正、どちらかが負なら交差している
	return d1 * d2 <= 0.0f;
}

