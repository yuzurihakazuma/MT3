#pragma once
#include "Vector3.h"


struct Matrix4x4 {
	float m[4][4];
};

namespace MatrixMath {

	// 座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
	// 正射影行列
	Matrix4x4 Orthographic(float left, float top, float right, float bottom, float nearClip, float farClip);
	// 透視投影行列
	Matrix4x4 PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip);
	// ビューポート変換行列
	Matrix4x4 Viewport(float left, float top, float width, float height, float minDepth, float maxDepth);

	

	

}


