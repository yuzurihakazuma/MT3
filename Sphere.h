#pragma once
#include "Matrix4x4.h"
#include "KamataEngine.h"

struct Sphere {
	Vector3 center;
	float radius;
};


// ‹…
void DrawSphere(const Sphere& sphere, Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t coler);

// ƒOƒŠƒbƒh
void DrawaGrid(const Matrix4x4& PerspectiveFov, const Matrix4x4& Viewport);
