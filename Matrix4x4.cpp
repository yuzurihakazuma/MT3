#include "Matrix4x4.h"
#include <cmath>
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
    result.m[0][0] = std::cos(radian) ; // X¬•ª‚Ì‰ñ“]
    result.m[0][1] = std::sin(radian);  // Y¬•ª‚Ö‚Ì‰e‹¿  
    result.m[1][0] = -std::sin(radian); // X¬•ª‚Ö‚Ì‰e‹¿
    result.m[1][1] = std::cos(radian);  // Y¬•ª‚Ì‰ñ“]
    result.m[2][2] = 1.0f;// Z²‚ÍŒÅ’è
    result.m[3][3] = 1.0f;// “¯À•WŒn‚Ìw¬•ª(ŒÅ’è’l1)

    return result;// Z²‚Ì‰ñ“]s—ñ‚ğ•Ô‚·
}
