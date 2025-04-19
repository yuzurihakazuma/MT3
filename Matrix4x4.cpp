#include "Matrix4x4.h"
#include <cmath>
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
    result.m[0][0] = std::cos(radian) ; // X成分の回転
    result.m[0][1] = std::sin(radian);  // Y成分への影響  
    result.m[1][0] = -std::sin(radian); // X成分への影響
    result.m[1][1] = std::cos(radian);  // Y成分の回転
    result.m[2][2] = 1.0f;// Z軸は固定
    result.m[3][3] = 1.0f;// 同時座標系のw成分(固定値1)

    return result;// Z軸の回転行列を返す
}

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

