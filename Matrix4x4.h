#pragma once
#include "Vector3.h"
#include "KamataEngine.h"




namespace MatrixMath {

	// 加算
	Vector3 Add(const Vector3& v1, const Vector3& v2);
	// 行列の加法
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
	// 行列の減法
	Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
	// 行列の積
	Matrix4x4 Multipty(const Matrix4x4& m1, const Matrix4x4& m2);
	// 減算
	Vector3 Subtract(const Vector3& v1, const Vector3& v2);
	
	// 内積
	float Dot(const Vector3& v1, const Vector3& v2);
	// 外積
	Vector3 Cross(const Vector3& a, const Vector3& b);
	
	
	// 行列とベクトルの乗算（行ベクトル×列行列）例
	Vector4 Multiply(const Matrix4x4& mat, const Vector4& vec);

	// 長さ(ノルム)
	float Length(const Vector3& v);
	
	Vector3 ScreenTransform(const Vector3& v, const Matrix4x4& vp, const Matrix4x4& viewport);
	
	// 正規化
	Vector3 Normalize(const Vector3& v);

	// スカラー倍
	Vector3 Multiply(float scalar, const Vector3& v);

	// 行列の積
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	// 平行移動行列
	Matrix4x4 MakeTranslate(const Vector3& translate);
	// 拡大縮小行列
	Matrix4x4 MakeScale(const Vector3& scale);

	// X軸の回転行列
	Matrix4x4 MakeRotateX(float radian);
	// Y軸の回転行列
	Matrix4x4 MakeRotateY(float radian);
	// Z軸の回転行列
	Matrix4x4 MakeRotateZ(float radian);

	// 3次元アフィン変換行列
	Matrix4x4 MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
	// 逆行列
	Matrix4x4 Inverse(const Matrix4x4& m);

	// 単位行列の作成
	Matrix4x4 MakeIdentity4x4();

	// 座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
	// 正射影行列
	Matrix4x4 Orthographic(float left, float top, float right, float bottom, float nearClip, float farClip);
	// 透視投影行列
	Matrix4x4 PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip);
	// ビューポート変換行列
	Matrix4x4 Viewport(float left, float top, float width, float height, float minDepth, float maxDepth);

	
	Vector3 Perpendicular(const Vector3& normal);

	// 球
	void DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t coler);

	// グリッド
	void DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& Viewport, float yOffset);

	void DrawSegment(const Segment& seg, const Matrix4x4& vp, const Matrix4x4& viewport, uint32_t color);
	


	// 平面
	void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	// 三角形
	void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewportMatrix,uint32_t color);

	// AABBの描画
	void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	AABB FixAABB(const AABB& aabb);


	bool IsCollision(const AABB& aabb1,const AABB& aabb2);
	
	bool IsCollision(const   AABB& aabb, const Sphere& sphere);

	bool IsCollision(const AABB& aabb, const Segment& segment);

	Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

	void DrawBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewport, uint32_t color);

	void UpdateWorldMatrices(std::array<Matrix4x4, 3>& worldMatrices, const std::array<Vector3, 3>& translate, const std::array<Vector3, 3>& rotate, const std::array<Vector3, 3>& scale);

	// Vector3（二項）
	Vector3 operator+(const Vector3& v1, const Vector3& v2);
	Vector3 operator-(const Vector3& v1, const Vector3& v2);
	Vector3 operator*(float s, const Vector3& v);
	Vector3 operator*(const Vector3& v, float s);
	Vector3 operator/(const Vector3& v, float s);

	// Vector3（単項）
	Vector3 operator-(const Vector3& v);
	Vector3 operator+(const Vector3& v);

	// Matrix4x4（二項）
	Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
	Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
	Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

}


