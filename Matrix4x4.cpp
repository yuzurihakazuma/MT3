#include "Matrix4x4.h"
#include <math.h>
#include <cassert>
#include <cmath>
// 4x4s—ñ‚ÌÏ
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

// •½sˆÚ“®s—ñ
Matrix4x4 MatrixMath::MakeTranslate(const Vector3& translate) {

	Matrix4x4 result = {};
	// ’PˆÊs—ñ‚Ìì¬
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	// •½sˆÚ“®‚Ì¬•ª
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;// Š®¬‚µ‚½•½sˆÚ“®‚ğ•Ô‚·
}
// Šg‘åk¬s—ñ
Matrix4x4 MatrixMath::MakeScale(const Vector3& scale) {

	Matrix4x4 result = {};
	// Šg‘å—¦‚Ìİ’è
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	return result;// Šg‘å(ƒXƒP\ƒŠƒ“ƒN)s—ñ‚ğ•Ô‚·
}

//X²‚Ì‰ñ“]s—ñ
Matrix4x4 MatrixMath::MakeRotateX(float radian) {

    Matrix4x4 result = {};
    // 3ŸŒ³‚ÌX²ü‚è‚Ì‰ñ“]s—ñ
    result.m[0][0] = 1.0f;// X²•ûŒü‚ÌƒxƒNƒgƒ‹•Ï‰»‚µ‚È‚¢
    result.m[1][1] = std::cos(radian); // Y¬•ª‚Ì‰ñ“]
    result.m[1][2] = std::sin(radian); // Z¬•ª‚Ö‚Ì‰e‹¿
    result.m[2][1] = -std::sin(radian);// Y¬•ª‚Ö‚Ì‰e‹¿  
    result.m[2][2] = std::cos(radian); // Z¬•ª‚Ì‰ñ“]
    result.m[3][3] = 1.0f;// “¯Œn—ñ‚Ìw¬•ª(ŒÅ’è’l1)

    return result;// X²‚Ì‰ñ“]s—ñ‚ğ•Ô‚·
}
// Y²‚Ì‰ñ“]s—ñ
Matrix4x4 MatrixMath::MakeRotateY(float radian) {

    Matrix4x4 result = {};
    // 3ŸŒ³‚ÌY²ü‚è‚Ì‰ñ“]s—ñ
    result.m[0][0] = std::cos(radian); // X¬•ª‚Ì‰ñ“]
    result.m[0][2] = -std::sin(radian);// Z¬•ª‚Ö‚Ì‰e‹¿
    result.m[1][1] = 1.0f;// Y²‚ÍŒÅ’è
    result.m[2][0] = std::sin(radian); // X¬•ª‚Ö‚Ì‰e‹¿
    result.m[2][2] = std::cos(radian); // Z¬•ª‚Ì‰ñ“]
    result.m[3][3] = 1.0f;// “¯ŸÀ•WŒn‚Ìw¬•ª(ŒÅ’è’l1)

    return result;// Y²‚Ì‰ñ“]s—ñ‚ğ•Ô‚·
}
// Z²‚Ì‰ñ“]s—ñ
Matrix4x4 MatrixMath::MakeRotateZ(float radian) {

    Matrix4x4 result = {};
    // 3ŸŒ³‚ÌZ²ü‚è‚Ì‰ñ“]s—ñ
    result.m[0][0] = std::cos(radian); // X¬•ª‚Ì‰ñ“]
    result.m[0][1] = std::sin(radian);  // Y¬•ª‚Ö‚Ì‰e‹¿  
    result.m[1][0] = -std::sin(radian); // X¬•ª‚Ö‚Ì‰e‹¿
    result.m[1][1] = std::cos(radian);  // Y¬•ª‚Ì‰ñ“]
    result.m[2][2] = 1.0f;// Z²‚ÍŒÅ’è
    result.m[3][3] = 1.0f;// “¯À•WŒn‚Ìw¬•ª(ŒÅ’è’l1)

    return result;// Z²‚Ì‰ñ“]s—ñ‚ğ•Ô‚·
}
// 3ŸŒ³ƒAƒtƒBƒ“•ÏŠ·s—ñ
Matrix4x4 MatrixMath::MakeAffine(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	
    Matrix4x4 result = {};
    // Šg‘åk¬‚ğ¶¬
    Matrix4x4 scaleMatrix = MatrixMath::MakeScale(scale);
    // X²‚Ì‰ñ“]s—ñ‚ğ¶¬
    Matrix4x4 rotateXMatrix = MatrixMath::MakeRotateX(rotate.x);
    // Y²‚Ì‰ñ“]s—ñ‚ğ¶¬
    Matrix4x4 rotateYMatrix = MatrixMath::MakeRotateY(rotate.y);
    // Z²‚Ì‰ñ“]s—ñ‚ğ¶¬
    Matrix4x4 rotateZMatrix = MatrixMath::MakeRotateZ(rotate.z);
    // Z²AY²AX²‚Ì‡‚É‰ñ“]‚ğ‡¬
    Matrix4x4 rotateXYZMatrix = MatrixMath::Multiply(rotateXMatrix, MatrixMath::Multiply(rotateYMatrix, rotateZMatrix));
    // •½sˆÚ“®‚ğ¶¬
    Matrix4x4 translateMatrix = MatrixMath::MakeTranslate(translate);
    
    result = MatrixMath::Multiply(translateMatrix, MatrixMath::Multiply(rotateXYZMatrix, scaleMatrix));

    return result;
}
