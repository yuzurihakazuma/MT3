#pragma once
#include "Matrix4x4.h"
#include "KamataEngine.h"

struct Sphere {
	Vector3 center; //中心点
	float radius; // 半径
};



// 球
void DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t coler);

// グリッド
void DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& Viewport);
