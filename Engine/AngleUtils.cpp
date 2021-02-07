//
//  AngleUtils.cpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/6/21.
//

#include "AngleUtils.hpp"

namespace AI{

namespace AngleUtils{

void WrapDegrees(float& angle) {
    angle = fmodf(angle + 180.f, 360.f);
    if (angle < 0)
        angle += 360.f;
    angle -= 180.f;
}

float AngleDiff(float dest, float src){
    float result = fmodf(dest - src + 180.f, 360.f);
    if (result < 0)
        result += 360.f;
    return result - 180.f;
}

}

}
