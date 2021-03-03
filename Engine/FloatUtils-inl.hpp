//
//  FloatUtils-inl.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 3/2/21.
//

#pragma once
#include <stdlib.h>

namespace AI{
namespace FloatUtils{

inline float random(){
    return (float)rand() / (float)RAND_MAX;
}

inline float randomBinomial(){
    return random() - random();
}

}
}
