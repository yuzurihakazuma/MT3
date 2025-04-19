#pragma once

struct Matrix4x4 {
	float m[4][4];
};

namespace MatrixMath {
	// X²‚Ì‰ñ“]s—ñ
	Matrix4x4 MakeRotateX(float radian);
	// Y²‚Ì‰ñ“]s—ñ
	Matrix4x4 MakeRotateY(float radian);
	// Z²‚Ì‰ñ“]s—ñ
	Matrix4x4 MakeRotateZ(float radian);


}
