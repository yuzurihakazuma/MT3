#pragma once

struct Vector4{
	float x;
	float y;
	float z;
	float w; // 同次座標系のw成分
};

struct Vector3 {

	float x;
	float y;
	float z;

	// += スカラー
	Vector3& operator+=(float s){
		x += s; y += s; z += s;
		return *this;
	}

	// -= Vector3
	Vector3& operator-=(const Vector3& v){
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	// *= Vector3（要素ごとの積）
	Vector3& operator*=(const Vector3& v){
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	// /= スカラー
	Vector3& operator/=(float s){
		x /= s; y /= s; z /= s;
		return *this;
	}

};
struct Vector2 {

	float x;
	float y;
};

struct Sphere {
	Vector3 center; //中心点
	float radius; // 半径
	int color;
};

struct Plane {
	Vector3 normal; // 平面の法線ベクトル(単位ベクトル)
	float distance; // 原点から平面までの距（b）
};

struct Matrix4x4 {
	float m[4][4];
};
struct Segment {
	Vector3 start; // 線分の始点
	Vector3 end;   // 線分の終点
};

struct Triangle {
	Vector3 vertices[3]; // 原点

};

struct AABB{
	Vector3 min; // AABBの最小点
	Vector3 max; // AABBの最大点
};