#include "Matrix4x4.h"
#include <cmath>
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
    result.m[0][0] = std::cos(radian) ; // X�����̉�]
    result.m[0][1] = std::sin(radian);  // Y�����ւ̉e��  
    result.m[1][0] = -std::sin(radian); // X�����ւ̉e��
    result.m[1][1] = std::cos(radian);  // Y�����̉�]
    result.m[2][2] = 1.0f;// Z���͌Œ�
    result.m[3][3] = 1.0f;// �������W�n��w����(�Œ�l1)

    return result;// Z���̉�]�s���Ԃ�
}
