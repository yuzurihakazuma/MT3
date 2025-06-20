#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "KamataEngine.h"






// 球
void DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t coler);

// グリッド
void DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& Viewport);

// 平面
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewportMatrix, uint32_t color);