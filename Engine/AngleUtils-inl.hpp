//
//  AngleUtils.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/6/21.
//

#pragma once
#include <math.h>

namespace AI{

namespace AngleUtils{

#define PI 3.14159265358979323846
const float PIf = (float)PI;
const float D2R = PIf / 180.f;
const float R2D = 180.f / PIf;

inline float RadiansToDegrees(float radians){
    return radians * R2D;
}

inline float DegreesToRadians(float degrees){
    return degrees * D2R;
}

inline void WrapDegrees(float& angle) {
    angle = fmodf(angle + 180.f, 360.f);
    if (angle < 0)
        angle += 360.f;
    angle -= 180.f;
}

inline float AngleDiff(float dest, float src){
    float result = fmodf(dest - src + 180.f, 360.f);
    if (result < 0)
        result += 360.f;
    return result - 180.f;
}

inline float Vec2ToAngleInDegrees(float x, float y){
    float radians = 0;
    if (0 == y){
        radians = x >= 0 ? 0 : -AI::AngleUtils::PIf;
    }
    else{
        radians = atan2f(y, x);
    }
    return RadiansToDegrees(radians);
}

inline float Q_rsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//    y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

inline void AngleToVec2(float someDegrees, float& x, float& y){
    WrapDegrees(someDegrees);
    if (someDegrees == 90.f){
        x = 0;
        y = 1.f;
    }
    else if (someDegrees == -90.f){
        x = 0;
        y = -1.f;
    }
    else if (someDegrees == -180.f){
        x = -1.f;
        y = 0;
    }
    else if (someDegrees == 0.f){
        x = 1.f;
        y = 0;
    }
    else{
        x = fabsf(someDegrees) > 90.f ? -1.f : 1.f;
        y = x * tan(DegreesToRadians(someDegrees));
        float sq = Q_rsqrt(x * x + y * y);
        x *= sq;
        y *= sq;
    }
}

}

}
