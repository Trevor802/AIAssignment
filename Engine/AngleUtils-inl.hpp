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

}

}
