#define _USE_MATH_DEFINES 
#include "Sphere.h"
#include <cmath>
#include <math.h>
#include <assert.h>
#include <vector>
#include <Novice.h>

using namespace MatrixMath;


void DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t coler) {

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



void DrawaGrid(const Matrix4x4& PerspectiveFov, const Matrix4x4& Viewport) {

	const float kGridHalfWidth = 2.0f; // Gridの半分の幅
	const uint32_t kSubdivision = 10;  // 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); // 一つ分の長さ

	// 奥から手前への線を隅々に引いていく
	for (uint32_t xIndex = 0; xIndex < kSubdivision; ++xIndex) {
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		float x = -kGridHalfWidth + xIndex * kGridEvery;

		// Z方向に奥から手前
		Vector3 start = { x,0.0f,-kGridHalfWidth };
		Vector3 end = { x,0.0f,kGridHalfWidth };

		// スクリーン座標系の変換をかける
		Vector3 startScreen = Transform(Transform(start, PerspectiveFov), Viewport);
		Vector3 endScreen = Transform(Transform(end, PerspectiveFov), Viewport);

		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF),原点は黒ぐらいがいいが、何でもいい
		uint32_t color = (x == 0) ? 0x000000FF : 0xAAAAAAAFF; //原点は黒、それ以外は灰色

		Novice::DrawLine(float(startScreen.x), float(startScreen.y),
			float(endScreen.x), float(endScreen.y), color);
	}

	// 左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float z = -kGridHalfWidth + zIndex * kGridEvery;

		// 左から右方向に引くグリッド線の始点と終点（XZ平面）
		Vector3 start = { -kGridHalfWidth, 0.0f, z };
		Vector3 end = { kGridHalfWidth, 0.0f, z };

		// 変換（ワールド座標 → クリップ座標 → スクリーン座標）
		Vector3 startScreen = Transform(Transform(start, PerspectiveFov), Viewport);
		Vector3 endScreen = Transform(Transform(end, PerspectiveFov), Viewport);

		uint32_t color = (z == 0.0f) ? 0x000000FF : 0xAAAAAAFF;
		Novice::DrawLine(int(startScreen.x), int(startScreen.y),
			int(endScreen.x), int(endScreen.y), color);
	}


}