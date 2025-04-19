#pragma once

struct Matrix4x4 {
	float m[4][4];
};

namespace MatrixMath {
	// X���̉�]�s��
	Matrix4x4 MakeRotateX(float radian);
	// Y���̉�]�s��
	Matrix4x4 MakeRotateY(float radian);
	// Z���̉�]�s��
	Matrix4x4 MakeRotateZ(float radian);


}
