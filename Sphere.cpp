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


// グリット
void MathSphere::DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& viewportMatrix) {
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


void MathSphere::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = MultiplyScalar(plane.distance, plane.normal);

	// 平面上の直交ベクトルを2つ生成
	Vector3 axisX = Normalize(Perpendicular(plane.normal));
	Vector3 axisY = Normalize(Cross(plane.normal, axisX));

	// 4頂点を作成（±方向に拡張）
	float size = 2.0f; // 平面の可視範囲（任意）
	Vector3 corners[4];
	corners[0] = Add(center, Add(MultiplyScalar(size, axisX), MultiplyScalar(size, axisY)));  // +X +Y
	corners[1] = Add(center, Add(MultiplyScalar(-size, axisX), MultiplyScalar(size, axisY))); // -X +Y
	corners[2] = Add(center, Add(MultiplyScalar(-size, axisX), MultiplyScalar(-size, axisY))); // -X -Y
	corners[3] = Add(center, Add(MultiplyScalar(size, axisX), MultiplyScalar(-size, axisY))); // +X -Y

	// 変換（ViewProjection → Viewport）
	for (int i = 0; i < 4; i++) {
		corners[i] = Transform(Transform(corners[i], viewProjectionMatrix), viewportMatrix);
	}

	// 線を描画（四角形として接続）
	for (int i = 0; i < 4; i++) {
		int next = (i + 1) % 4;
		Novice::DrawLine(
			static_cast<int>(corners[i].x),
			static_cast<int>(corners[i].y),
			static_cast<int>(corners[next].x),
			static_cast<int>(corners[next].y),
			color
		);
	}
}

bool MathSphere::IsCollision(const Sphere& sphere, const Plane& plane) {
	// 球の中心と平面の距離 = dot(plane.normal, sphere.center) - plane.distance
	float distance = Dot(plane.normal, sphere.center) - plane.distance;

	// 絶対値を取る（裏側も考慮）
	distance = std::fabs(distance);

	// 距離が半径以下なら衝突
	return distance <= sphere.radius;
}

