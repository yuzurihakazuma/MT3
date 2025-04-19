#include "Matrix4x4.h"
// 行列の加法
Matrix4x4 MatrixMath::Add(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.m[row][col] = m1.m[row][col] + m2.m[row][col];
        }
    }

    return result;
}
// 行列の減法
Matrix4x4 MatrixMath::Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.m[row][col] = m1.m[row][col] - m2.m[row][col];
        }
    }
    return result;
}
// 4x4行列の積
Matrix4x4 MatrixMath::Multipty(const Matrix4x4& m1, const Matrix4x4& m2) {
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
// 4x4行列の逆行列
Matrix4x4 MatrixMath::Inverse(const Matrix4x4& m) {
    float aug[4][8] = {};
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            aug[row][col] = m.m[row][col];
        }
    }
    // 単位行列の追加
    aug[0][4] = 1.0f;
    aug[1][5] = 1.0f;
    aug[2][6] = 1.0f;
    aug[3][7] = 1.0f;

    for (int i = 0; i < 4; i++) {
        // ピボットが0の場合下の行と入れ替える
        if (aug[i][i] == 0.0f) {
            for (int j = i + 1; j < 4; j++) {
                if (aug[j][i] != 0.0f) {
                    // 行を交換する
                    for (int k = 0; k < 8; k++) { // 列
                        float copyNum = aug[i][k]; //もともとの上の行を代入
                        aug[i][k] = aug[j][k]; //上の行
                        aug[j][k] = copyNum; //下の行
                    }
                    break;
                }
            }
        }

        // ピボットを1にする
        float pivot = aug[i][i];
        for (int k = 0; k < 8; k++) {
            aug[i][k] /= pivot;
        }

        //i列目のピボット以外を0にする
        for (int j = 0; j < 4; j++) {
            if (j != i) {
                float factor = aug[j][i];
                for (int k = 0; k < 8; k++) {
                    aug[j][k] -= factor * aug[i][k];
                }
            }
        }

    }

    Matrix4x4 result = {};
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.m[row][col] = aug[row][col + 4];
        }
    }

    return result;
}
// 転置行列
Matrix4x4 MatrixMath::Transpoce(const Matrix4x4& m) {
    Matrix4x4 result = {};

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.m[row][col] = m.m[col][row];
        }
    }

    return result;
}
// 単位行列の作成
Matrix4x4 MatrixMath::MakeIdentity4x4() {
    Matrix4x4 result = {};

    for (int i = 0; i < 4; ++i) {
        result.m[i][i] = 1.0f;
    }
    return result;
}
