#define _USE_MATH_DEFINES
#include "Matrix4x4.h"
#include <math.h>
#include <cassert>
#include <cmath>
#include <Novice.h>
using namespace MatrixMath;
// 加算
Vector3 MatrixMath::Add(const Vector3& v1, const Vector3& v2) {

	Vector3 result = {};

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;

}
// 減算
Vector3 MatrixMath::Subtract(const Vector3& v1, const Vector3& v2) {

	Vector3 result = {};

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}
// 内積
float MatrixMath::Dot(const Vector3& v1, const Vector3& v2) {

	float result = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);


	return result;

}
// 外積
Vector3 MatrixMath::Cross(const Vector3& a, const Vector3& b) {
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}
// 長さ
float MatrixMath::Length(const Vector3& v) {

	float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	return result;
}
Vector3 MatrixMath::ScreenTransform(const Vector3& v, const Matrix4x4& vp, const Matrix4x4& viewport) {
	Vector3 ndc = Transform(v, vp);           // ← ここでもうw除算済み
	return Transform(ndc, viewport);          // ビューポート変換
}
// 正規化
Vector3 MatrixMath::Normalize(const Vector3& v) {

	Vector3 result = {};

	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);

	return result;
}
//スカラー倍
Vector3 MatrixMath::MultiplyScalar(float scalar, const Vector3& v) {

	Vector3 result = {};

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;
}

// 4x4行列の積
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




// 平行移動行列
Matrix4x4 MatrixMath::MakeTranslate(const Vector3& translate) {

	Matrix4x4 result = {};
	// 単位行列の作成
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	// 平行移動の成分
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;// 完成した平行移動を返す
}
// 拡大縮小行列
Matrix4x4 MatrixMath::MakeScale(const Vector3& scale) {

	Matrix4x4 result = {};
	// 拡大率の設定
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	return result;// 拡大(スケ―リンク)行列を返す
}

#pragma region 回転行列

//X軸の回転行列
Matrix4x4 MatrixMath::MakeRotateX(float radian) {

	Matrix4x4 result = {};
	// 3次元のX軸周りの回転行列
	result.m[0][0] = 1.0f;// X軸方向のベクトル変化しない
	result.m[1][1] = std::cos(radian); // Y成分の回転
	result.m[1][2] = std::sin(radian); // Z成分への影響
	result.m[2][1] = -std::sin(radian);// Y成分への影響  
	result.m[2][2] = std::cos(radian); // Z成分の回転
	result.m[3][3] = 1.0f;// 同時系列のw成分(固定値1)

	return result;// X軸の回転行列を返す
}
// Y軸の回転行列
Matrix4x4 MatrixMath::MakeRotateY(float radian) {

	Matrix4x4 result = {};
	// 3次元のY軸周りの回転行列
	result.m[0][0] = std::cos(radian); // X成分の回転
	result.m[0][2] = -std::sin(radian);// Z成分への影響
	result.m[1][1] = 1.0f;// Y軸は固定
	result.m[2][0] = std::sin(radian); // X成分への影響
	result.m[2][2] = std::cos(radian); // Z成分の回転
	result.m[3][3] = 1.0f;// 同次座標系のw成分(固定値1)

	return result;// Y軸の回転行列を返す
}
// Z軸の回転行列
Matrix4x4 MatrixMath::MakeRotateZ(float radian) {

	Matrix4x4 result = {};
	// 3次元のZ軸周りの回転行列
	result.m[0][0] = std::cos(radian); // X成分の回転
	result.m[0][1] = std::sin(radian);  // Y成分への影響  
	result.m[1][0] = -std::sin(radian); // X成分への影響
	result.m[1][1] = std::cos(radian);  // Y成分の回転
	result.m[2][2] = 1.0f;// Z軸は固定
	result.m[3][3] = 1.0f;// 同時座標系のw成分(固定値1)

	return result;// Z軸の回転行列を返す
}
#pragma endregion

// 3次元アフィン変換行列
Matrix4x4 MatrixMath::MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 result = {};
	// 拡大縮小を生成
	Matrix4x4 scaleMatrix = MatrixMath::MakeScale(scale);

	// X軸の回転行列を生成
	Matrix4x4 rotateXMatrix = MatrixMath::MakeRotateX(rotate.x);
	// Y軸の回転行列を生成
	Matrix4x4 rotateYMatrix = MatrixMath::MakeRotateY(rotate.y);
	// Z軸の回転行列を生成
	Matrix4x4 rotateZMatrix = MatrixMath::MakeRotateZ(rotate.z);
	// X軸、Y軸、Z軸の順に回転を合成
	Matrix4x4 rotateXYZMatrix = MatrixMath::Multiply(MatrixMath::Multiply(rotateXMatrix, rotateYMatrix), rotateZMatrix);

	// 平行移動を生成
	Matrix4x4 translateMatrix = MatrixMath::MakeTranslate(translate);

	// 最終的なアフィン変換行列： T * R * S
	result = MatrixMath::Multiply(MatrixMath::Multiply(scaleMatrix, rotateXYZMatrix), translateMatrix);



	return result;
}

// 4x4行列の逆行列
Matrix4x4 MatrixMath::Inverse(const Matrix4x4& m) {
	float aug[4][8] = {};
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			aug[row][col] = m.m[row][col];
		}
	}
	// 単位行列の追加
	aug[0][4] = 1.0f;
	aug[1][5] = 1.0f;
	aug[2][6] = 1.0f;
	aug[3][7] = 1.0f;

	for (int i = 0; i < 4; i++) {
		// ピボットが0の場合下の行と入れ替える
		if (aug[i][i] == 0.0f) {
			for (int j = i + 1; j < 4; j++) {
				if (aug[j][i] != 0.0f) {
					// 行を交換する
					for (int k = 0; k < 8; k++) { // 列
						float copyNum = aug[i][k]; //もともとの上の行を代入
						aug[i][k] = aug[j][k]; //上の行
						aug[j][k] = copyNum; //下の行
					}
					break;
				}
			}
		}

		// ピボットを1にする
		float pivot = aug[i][i];
		for (int k = 0; k < 8; k++) {
			aug[i][k] /= pivot;
		}

		//i列目のピボット以外を0にする
		for (int j = 0; j < 4; j++) {
			if (j != i) {
				float factor = aug[j][i];
				for (int k = 0; k < 8; k++) {
					aug[j][k] -= factor * aug[i][k];
				}
			}
		}

	}

	Matrix4x4 result = {};
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			result.m[row][col] = aug[row][col + 4];
		}
	}

	return result;
}

// 単位行列の作成
Matrix4x4 MatrixMath::MakeIdentity4x4() {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; ++i) {
		result.m[i][i] = 1.0f;
	}
	return result;
}
// 座標変換
Vector3 MatrixMath::Transform(const Vector3& vector, const Matrix4x4& matrix) {

	Vector3 result = {};
	// 座標の変換(行ベクトルx行列の列)
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f); //wが0にならないようにする

	// wで割って通常の3次元空間に戻す
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;// 変換後のベクトルを返す
}

// 正射影行列
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
// 透視投影行列
Matrix4x4 MatrixMath::PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip) {

	Matrix4x4 result = {};

	// コタンジェント(fovY/2)
	float f = 1.0f / std::tan(fovY / 2.0f);

	// 透視投影行列の各要素設定
	result.m[0][0] = f / aspectRatio;
	result.m[1][1] = f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

	return result;
}
// ビューポート変換行列
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


Vector3 MatrixMath::Perpendicular(const Vector3& vector) {
	// 法線の絶対値の小さい成分を避けて直交ベクトルを作成
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}
// 球
void MatrixMath::DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t color) {

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


void MatrixMath::DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& viewportMatrix, float yOffset) {
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

void MatrixMath::DrawSegment(const Segment& seg, const Matrix4x4& vp, const Matrix4x4& viewport, uint32_t color) {
	Vector3 a = ScreenTransform(seg.start, vp, viewport);
	Vector3 b = ScreenTransform(seg.end, vp, viewport);
	Novice::DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, color);
}

void MatrixMath::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

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

void MatrixMath::DrawTriangle(const Triangle& triangle, const Matrix4x4& viewportMatrix, uint32_t color) {
	// 各頂点をビューポート変換（画面座標に変換）
	Vector3 screenA = Transform(triangle.vertices[0], viewportMatrix);
	Vector3 screenB = Transform(triangle.vertices[1], viewportMatrix);
	Vector3 screenC = Transform(triangle.vertices[2], viewportMatrix);

	// 三角形の3辺を描画
	Novice::DrawLine((int)screenA.x, (int)screenA.y, (int)screenB.x, (int)screenB.y, color);
	Novice::DrawLine((int)screenB.x, (int)screenB.y, (int)screenC.x, (int)screenC.y, color);
	Novice::DrawLine((int)screenC.x, (int)screenC.y, (int)screenA.x, (int)screenA.y, color);
}

bool MatrixMath::IsCollision(const Triangle& triangle, const Segment& segment) {
	// Step 1: 平面の法線を求める
	Vector3 edge1 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 edge2 = Subtract(triangle.vertices[2], triangle.vertices[0]);
	Vector3 normal = Normalize(Cross(edge1, edge2));

	// Step 2: 線分と平面の交点を求める
	Vector3 dir = Subtract(segment.end, segment.start);
	float denom = Dot(normal, dir);
	if (fabs(denom) < 1e-6f) return false; // 平行

	float d = Dot(normal, triangle.vertices[0]);
	float t = (d - Dot(normal, segment.start)) / denom;

	if (t < 0.0f || t > 1.0f) return false; // 線分範囲外

	// Step 3: 線分上の交点を求める
	Vector3 p = Add(segment.start, MultiplyScalar(t, dir));

	// Step 4: 三角形の内側かどうかを外積・内積で判定
	Vector3 v0 = triangle.vertices[0];
	Vector3 v1 = triangle.vertices[1];
	Vector3 v2 = triangle.vertices[2];

	Vector3 vp0 = Subtract(p, v0);
	Vector3 vp1 = Subtract(p, v1);
	Vector3 vp2 = Subtract(p, v2);

	Vector3 c1 = Cross(Subtract(v1, v0), vp0);
	Vector3 c2 = Cross(Subtract(v2, v1), vp1);
	Vector3 c3 = Cross(Subtract(v0, v2), vp2);

	if (Dot(c1, normal) >= 0.0f &&
		Dot(c2, normal) >= 0.0f &&
		Dot(c3, normal) >= 0.0f) {
		return true; // 三角形の内側に交差
	}

	return false;
}


