#define _USE_MATH_DEFINES
#include <algorithm>
#include "Matrix4x4.h"
#include <math.h>
#include <cassert>
#include <cmath>
#include <Novice.h>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif


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
Vector3 MatrixMath::Multiply(float scalar, const Vector3& v) {

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


// 行列とベクトルの乗算
Vector4 MatrixMath::Multiply(const Matrix4x4& mat, const Vector4& vec){
	Vector4 result;
	result.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + vec.w * mat.m[3][0];
	result.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + vec.w * mat.m[3][1];
	result.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + vec.w * mat.m[3][2];
	result.w = vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + vec.w * mat.m[3][3];
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
	Vector3 center = Multiply(plane.distance, plane.normal);

	// 平面に垂直な2つの単位ベクトルを作成（平面上の軸）
	Vector3 u = MatrixMath::Normalize(Perpendicular(plane.normal)); // 法線と垂直な任意のベクトル
	Vector3 v = MatrixMath::Normalize(Cross(plane.normal, u));                // uと法線に垂直なもう一つのベクトル

	float size = 2.0f; // 平面を描画する正方形の一辺の半分の長さ

	// 平面の四隅の座標を計算（正方形の4頂点）
	Vector3 corners[4] = {
		Add(center, Add(Multiply(size, u), Multiply(size, v))),   // +u +v方向の頂点
		Add(center, Add(Multiply(size, u), Multiply(-size, v))),  // +u -v方向の頂点
		Add(center, Add(Multiply(-size, u), Multiply(-size, v))), // -u -v方向の頂点
		Add(center, Add(Multiply(-size, u), Multiply(size, v)))   // -u +v方向の頂点
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

void MatrixMath::DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color){
	// AABBの8頂点を求める
	Vector3 vertices[8] = {
		{aabb.min.x, aabb.min.y, aabb.min.z}, // 0
		{aabb.max.x, aabb.min.y, aabb.min.z}, // 1
		{aabb.min.x, aabb.max.y, aabb.min.z}, // 2
		{aabb.max.x, aabb.max.y, aabb.min.z}, // 3
		{aabb.min.x, aabb.min.y, aabb.max.z}, // 4
		{aabb.max.x, aabb.min.y, aabb.max.z}, // 5
		{aabb.min.x, aabb.max.y, aabb.max.z}, // 6
		{aabb.max.x, aabb.max.y, aabb.max.z}  // 7
	};

	// 各頂点をスクリーン座標に変換
	Vector3 screen[8];
	for ( int i = 0; i < 8; i++ ) {
		Vector4 temp = { vertices[i].x, vertices[i].y, vertices[i].z, 1.0f };
		temp = Multiply(viewProjectionMatrix, temp);
		temp = Multiply(viewportMatrix, temp);
		screen[i] = { temp.x / temp.w, temp.y / temp.w, temp.z / temp.w };
	}

	// AABBのエッジを結ぶ線分（12本）
	int edges[12][2] = {
		{0,1},{1,3},{3,2},{2,0}, // 前面
		{4,5},{5,7},{7,6},{6,4}, // 背面
		{0,4},{1,5},{2,6},{3,7}  // 側面
	};

	for ( int i = 0; i < 12; i++ ) {
		Novice::DrawLine(
			static_cast< int >(screen[edges[i][0]].x),
			static_cast< int >(screen[edges[i][0]].y),
			static_cast< int >(screen[edges[i][1]].x),
			static_cast< int >(screen[edges[i][1]].y),
			color
		);
	}
}

AABB MatrixMath::FixAABB(const AABB& aabb){
	AABB fixed = aabb;

	// x軸
	if ( fixed.min.x > fixed.max.x ) std::swap(fixed.min.x, fixed.max.x);
	// y軸
	if ( fixed.min.y > fixed.max.y ) std::swap(fixed.min.y, fixed.max.y);
	// z軸
	if ( fixed.min.z > fixed.max.z ) std::swap(fixed.min.z, fixed.max.z);

	return fixed;
}

bool MatrixMath::IsCollision(const AABB& aabb1, const AABB& aabb2){
	// 自動でmin/maxを修正（安全対応）
	AABB a = aabb1;
	AABB b = aabb2;

	if ( a.min.x > a.max.x ) std::swap(a.min.x, a.max.x);
	if ( a.min.y > a.max.y ) std::swap(a.min.y, a.max.y);
	if ( a.min.z > a.max.z ) std::swap(a.min.z, a.max.z);

	if ( b.min.x > b.max.x ) std::swap(b.min.x, b.max.x);
	if ( b.min.y > b.max.y ) std::swap(b.min.y, b.max.y);
	if ( b.min.z > b.max.z ) std::swap(b.min.z, b.max.z);

	// 衝突判定
	if ( a.max.x < b.min.x || a.min.x > b.max.x ) return false;
	if ( a.max.y < b.min.y || a.min.y > b.max.y ) return false;
	if ( a.max.z < b.min.z || a.min.z > b.max.z ) return false;

	return true;
}

bool MatrixMath::IsCollision(const AABB& aabb, const Sphere& sphere){
	// 最近接点を求める
	Vector3 closestPoint;

	// 各軸について最近接点をクランプ
	closestPoint.x = std::clamp(sphere.center.x, aabb.min.x, aabb.max.x);
	closestPoint.y = std::clamp(sphere.center.y, aabb.min.y, aabb.max.y);
	closestPoint.z = std::clamp(sphere.center.z, aabb.min.z, aabb.max.z);

	// 球の中心と最近接点との距離の2乗
	Vector3 diff = Subtract(sphere.center, closestPoint);
	float distanceSq = Dot(diff, diff);

	// 衝突しているか：距離² <= 半径²
	return distanceSq <= ( sphere.radius * sphere.radius );
}

bool MatrixMath::IsCollision(const AABB& aabb, const Segment& segment){
	// 線分の方向
	Vector3 dir = Subtract(segment.end, segment.start);

	// tの開始・終了範囲（線分のパラメータ範囲）
	float tMin = 0.0f;
	float tMax = 1.0f;

	// 各軸でスラブ交差判定
	for ( int i = 0; i < 3; i++ ) {
		float start = ( &segment.start.x )[i];
		float delta = ( &dir.x )[i];
		float minVal = ( &aabb.min.x )[i];
		float maxVal = ( &aabb.max.x )[i];

		if ( fabs(delta) < 1e-6f ) {
			// 平行 → AABBのスラブの範囲外なら衝突なし
			if ( start < minVal || start > maxVal ) {
				return false;
			}
		} else {
			float invD = 1.0f / delta;
			float t1 = ( minVal - start ) * invD;
			float t2 = ( maxVal - start ) * invD;

			if ( t1 > t2 ) std::swap(t1, t2);

			tMin = std::max(tMin, t1);
			tMax = std::min(tMax, t2);

			if ( tMin > tMax ) {
				return false;
			}
		}
	}

	return true;
}

Vector3 MatrixMath::Lerp(const Vector3& v1, const Vector3& v2, float t){
	Vector3 result = {};
	result.x = v1.x + ( v2.x - v1.x ) * t;
	result.y = v1.y + ( v2.y - v1.y ) * t;
	result.z = v1.z + ( v2.z - v1.z ) * t;
	return result;
}

void MatrixMath::DrawBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2,
	const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewport,
	uint32_t color){
	const int kSegmentCount = 32; // 曲線を何分割するか
	Vector3 prev = p0;

	for ( int i = 1; i <= kSegmentCount; ++i ) {
		float t = static_cast< float >( i ) / kSegmentCount;

		// 2次ベジェ補間
		Vector3 a = Lerp(p0, p1, t);
		Vector3 b = Lerp(p1, p2, t);
		Vector3 point = Lerp(a, b, t);

		// ワールド → ビュー射影変換 → ビューポート変換
		Vector3 screenPrev = Transform(Transform(prev, viewProjectionMatrix), viewport);
		Vector3 screenCurr = Transform(Transform(point, viewProjectionMatrix), viewport);

		// ライン描画
		Novice::DrawLine(static_cast< int >( screenPrev.x ), static_cast< int >( screenPrev.y ),
			static_cast< int >( screenCurr.x ), static_cast< int >( screenCurr.y ),
			color);

		prev = point;
	}
}

void MatrixMath::UpdateWorldMatrices(std::array<Matrix4x4, 3>& worldMatrices, const std::array<Vector3, 3>& translate, const std::array<Vector3, 3>& rotate, const std::array<Vector3, 3>& scale){


	// 肩（親なし）
	worldMatrices[0] = MakeAffine(scale[0], rotate[0], translate[0]);

	// 肘（肩が親）
	Matrix4x4 localElbow = MakeAffine(scale[1], rotate[1], translate[1]);
	worldMatrices[1] = Multiply(localElbow, worldMatrices[0]);

	// 手（肘が親）
	Matrix4x4 localHand = MakeAffine(scale[2], rotate[2], translate[2]);
	worldMatrices[2] = Multiply(localHand, worldMatrices[1]);



}


