#pragma once

struct Vector3 {

	float x;
	float y;
	float z;
};

struct Sphere {
	Vector3 center; //中心点
	float radius; // 半径
};

struct Plane {
	Vector3 normal; // 平面の法線ベクトル(単位ベクトル)
	float distance; // 原点から平面までの距（b）
};

struct Matrix4x4 {
	float m[4][4];
};