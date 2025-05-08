#include "Matrix4x4.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>
#include <cmath>


// 4x4�s��̐�
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




// ���s�ړ��s��
Matrix4x4 MatrixMath::MakeTranslate(const Vector3& translate) {

    Matrix4x4 result = {};
    // �P�ʍs��̍쐬
    result.m[0][0] = 1.0f;
    result.m[1][1] = 1.0f;
    result.m[2][2] = 1.0f;
    result.m[3][3] = 1.0f;
    // ���s�ړ��̐���
    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;

    return result;// �����������s�ړ���Ԃ�
}
// �g��k���s��
Matrix4x4 MatrixMath::MakeScale(const Vector3& scale) {

    Matrix4x4 result = {};
    // �g�嗦�̐ݒ�
    result.m[0][0] = scale.x;
    result.m[1][1] = scale.y;
    result.m[2][2] = scale.z;
    result.m[3][3] = 1.0f;

    return result;// �g��(�X�P�\�����N)�s���Ԃ�
}

#pragma region ��]�s��

//X���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateX(float radian) {

    Matrix4x4 result = {};
    // 3������X������̉�]�s��
    result.m[0][0] = 1.0f;// X�������̃x�N�g���ω����Ȃ�
    result.m[1][1] = std::cos(radian); // Y�����̉�]
    result.m[1][2] = std::sin(radian); // Z�����ւ̉e��
    result.m[2][1] = -std::sin(radian);// Y�����ւ̉e��  
    result.m[2][2] = std::cos(radian); // Z�����̉�]
    result.m[3][3] = 1.0f;// �����n���w����(�Œ�l1)

    return result;// X���̉�]�s���Ԃ�
}
// Y���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateY(float radian) {

    Matrix4x4 result = {};
    // 3������Y������̉�]�s��
    result.m[0][0] = std::cos(radian); // X�����̉�]
    result.m[0][2] = -std::sin(radian);// Z�����ւ̉e��
    result.m[1][1] = 1.0f;// Y���͌Œ�
    result.m[2][0] = std::sin(radian); // X�����ւ̉e��
    result.m[2][2] = std::cos(radian); // Z�����̉�]
    result.m[3][3] = 1.0f;// �������W�n��w����(�Œ�l1)

    return result;// Y���̉�]�s���Ԃ�
}
// Z���̉�]�s��
Matrix4x4 MatrixMath::MakeRotateZ(float radian) {

    Matrix4x4 result = {};
    // 3������Z������̉�]�s��
    result.m[0][0] = std::cos(radian); // X�����̉�]
    result.m[0][1] = std::sin(radian);  // Y�����ւ̉e��  
    result.m[1][0] = -std::sin(radian); // X�����ւ̉e��
    result.m[1][1] = std::cos(radian);  // Y�����̉�]
    result.m[2][2] = 1.0f;// Z���͌Œ�
    result.m[3][3] = 1.0f;// �������W�n��w����(�Œ�l1)

    return result;// Z���̉�]�s���Ԃ�
}
#pragma endregion

// 3�����A�t�B���ϊ��s��
Matrix4x4 MatrixMath::MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

    Matrix4x4 result = {};
    // �g��k���𐶐�
    Matrix4x4 scaleMatrix = MatrixMath::MakeScale(scale);

    // X���̉�]�s��𐶐�
    Matrix4x4 rotateXMatrix = MatrixMath::MakeRotateX(rotate.x);
    // Y���̉�]�s��𐶐�
    Matrix4x4 rotateYMatrix = MatrixMath::MakeRotateY(rotate.y);
    // Z���̉�]�s��𐶐�
    Matrix4x4 rotateZMatrix = MatrixMath::MakeRotateZ(rotate.z);
    // X���AY���AZ���̏��ɉ�]������
    Matrix4x4 rotateXYZMatrix = MatrixMath::Multiply(MatrixMath::Multiply(rotateXMatrix, rotateYMatrix), rotateZMatrix);

    // ���s�ړ��𐶐�
    Matrix4x4 translateMatrix = MatrixMath::MakeTranslate(translate);

    // �ŏI�I�ȃA�t�B���ϊ��s��F T * R * S
    result = MatrixMath::Multiply(MatrixMath::Multiply(scaleMatrix, rotateXYZMatrix), translateMatrix);



    return result;
}

// 4x4�s��̋t�s��
Matrix4x4 MatrixMath::Inverse(const Matrix4x4& m) {
    float aug[4][8] = {};
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            aug[row][col] = m.m[row][col];
        }
    }
    // �P�ʍs��̒ǉ�
    aug[0][4] = 1.0f;
    aug[1][5] = 1.0f;
    aug[2][6] = 1.0f;
    aug[3][7] = 1.0f;

    for (int i = 0; i < 4; i++) {
        // �s�{�b�g��0�̏ꍇ���̍s�Ɠ���ւ���
        if (aug[i][i] == 0.0f) {
            for (int j = i + 1; j < 4; j++) {
                if (aug[j][i] != 0.0f) {
                    // �s����������
                    for (int k = 0; k < 8; k++) { // ��
                        float copyNum = aug[i][k]; //���Ƃ��Ƃ̏�̍s����
                        aug[i][k] = aug[j][k]; //��̍s
                        aug[j][k] = copyNum; //���̍s
                    }
                    break;
                }
            }
        }

        // �s�{�b�g��1�ɂ���
        float pivot = aug[i][i];
        for (int k = 0; k < 8; k++) {
            aug[i][k] /= pivot;
        }

        //i��ڂ̃s�{�b�g�ȊO��0�ɂ���
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

// ���ˉe�s��
Matrix4x4 MatrixMath::Orthographic(float left, float top, float right, float bottom, float nearClip, float farClip) {

    Matrix4x4 result = {};

    result.m[0][0] = 2.0f / (right - left);
    result.m[1][1] = 2.0f / (top - bottom);
    result.m[2][2] = 1.0f / (farClip - nearClip);
    result.m[3][0] = (left + right) / (left - right);
    result.m[3][1] = (top + bottom) / (bottom - top);
    result.m[3][2] = nearClip / (nearClip - farClip);
    result.m[3][3] = 1.0f;


    return result;
}
// �������e�s��
Matrix4x4 MatrixMath::PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip) {

    Matrix4x4 result = {};

    // �R�^���W�F���g(fovY/2)
    float f = 1.0f / std::tan(fovY / 2.0f);

    // �������e�s��̊e�v�f�ݒ�
    result.m[0][0] = f / aspectRatio;
    result.m[1][1] = f;
    result.m[2][2] = farClip / (farClip - nearClip);
    result.m[2][3] = 1.0f;
    result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

    return result;
}
// �r���[�|�[�g�ϊ��s��
Matrix4x4 MatrixMath::Viewport(float left, float top, float width, float height, float minDepth, float maxDepth) {

    Matrix4x4 result = {};

    result.m[0][0] = width / 2.0f;
    result.m[1][1] = -height / 2.0f;
    result.m[2][2] = maxDepth - minDepth;
    result.m[3][0] = left + (width / 2.0f);
    result.m[3][1] = top + (height / 2.0f);
    result.m[3][2] = minDepth;
    result.m[3][3] = 1.0f;

    return result;
}

