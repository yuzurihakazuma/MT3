#pragma once
#include "Matrix4x4.h"
#include "KamataEngine.h"

struct Segment {
	Vector3 start;  // 線分の始点
	Vector3 end;    // 線分の終点
};

// グリッド
void DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& Viewport);

Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& sement);