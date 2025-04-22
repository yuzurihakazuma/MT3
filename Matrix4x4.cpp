#include "Matrix4x4.h"
#include <math.h>
#include <cassert>
#include <cmath>
// 4x4行列の積
Matrix4x4 MatrixMath::Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.m[row][col] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[row][col] += m1.m[row][k] * m2.m[k][col];
            }
        }
    }

    return result;
}

// 平行移動行列
Matrix4x4 MatrixMath::MakeTranslate(const Vector3& translate) {

	Matrix4x4 result = {};
	// 単位行列の作成
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	// 平行移動の成分
	result.m[0][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;// 完成した平行移動を返す
}
// 拡大縮小行列
Matrix4x4 MatrixMath::MakeScale(const Vector3& scale) {

	Matrix4x4 result = {};
	// 拡大率の設定
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	return result;// 拡大(スケ―リンク)行列を返す
}

//X軸の回転行列
Matrix4x4 MatrixMath::MakeRotateX(float radian) {

    Matrix4x4 result = {};
    // 3次元のX軸周りの回転行列
    result.m[0][0] = 1.0f;// X軸方向のベクトル変化しない
    result.m[1][1] = std::cos(radian); // Y成分の回転
    result.m[1][2] = std::sin(radian); // Z成分への影響
    result.m[2][1] = -std::sin(radian);// Y成分への影響  
    result.m[2][2] = std::cos(radian); // Z成分の回転
    result.m[3][3] = 1.0f;// 同時系列のw成分(固定値1)

    return result;// X軸の回転行列を返す
}
// Y軸の回転行列
Matrix4x4 MatrixMath::MakeRotateY(float radian) {

    Matrix4x4 result = {};
    // 3次元のY軸周りの回転行列
    result.m[0][0] = std::cos(radian); // X成分の回転
    result.m[0][2] = -std::sin(radian);// Z成分への影響
    result.m[1][1] = 1.0f;// Y軸は固定
    result.m[2][0] = std::sin(radian); // X成分への影響
    result.m[2][2] = std::cos(radian); // Z成分の回転
    result.m[3][3] = 1.0f;// 同次座標系のw成分(固定値1)

    return result;// Y軸の回転行列を返す
}
// Z軸の回転行列
Matrix4x4 MatrixMath::MakeRotateZ(float radian) {

    Matrix4x4 result = {};
    // 3次元のZ軸周りの回転行列
    result.m[0][0] = std::cos(radian); // X成分の回転
    result.m[0][1] = std::sin(radian);  // Y成分への影響  
    result.m[1][0] = -std::sin(radian); // X成分への影響
    result.m[1][1] = std::cos(radian);  // Y成分の回転
    result.m[2][2] = 1.0f;// Z軸は固定
    result.m[3][3] = 1.0f;// 同時座標系のw成分(固定値1)

    return result;// Z軸の回転行列を返す
}
// 3次元アフィン変換行列
Matrix4x4 MatrixMath::MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	
    Matrix4x4 result = {};
    // 拡大縮小を生成
    Matrix4x4 scaleMatrix = MatrixMath::MakeScale(scale);
 
    // X軸の回転行列を生成
    Matrix4x4 rotateXMatrix = MatrixMath::MakeRotateX(rotate.x);
    // Y軸の回転行列を生成
    Matrix4x4 rotateYMatrix = MatrixMath::MakeRotateY(rotate.y);
    // Z軸の回転行列を生成
    Matrix4x4 rotateZMatrix = MatrixMath::MakeRotateZ(rotate.z);
    // Z軸、Y軸、X軸の順に回転を合成
    Matrix4x4 rotateXYZMatrix = MatrixMath::Multiply(rotateXMatrix, MatrixMath::Multiply(rotateYMatrix, rotateZMatrix));
    
    // 平行移動を生成
    Matrix4x4 translateMatrix = MatrixMath::MakeTranslate(translate);
    
    result = MatrixMath::Multiply(translateMatrix, MatrixMath::Multiply(rotateXYZMatrix, scaleMatrix));

    return result;
}
