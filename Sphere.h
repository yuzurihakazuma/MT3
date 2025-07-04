#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "KamataEngine.h"


namespace MathSphere{

Vector3 Perpendicular(const Vector3& normal);

// 球
void DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t coler);

// グリッド
void DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& Viewport, float yOffset);

// 平面
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

//衝突判定
bool IsCollision(const Sphere& sphere, const Plane& plane);

}
