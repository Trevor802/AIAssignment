//
//  Boid.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/2/21.
//

#ifndef Boid_hpp
#define Boid_hpp

#include <stdio.h>
#include "Types.h"
class Boid{
public:
    Boid();
    Boid(float, float, float);
    void Draw();
private:
    Rigidbody myRB;
    constexpr static const float kBoidRadius = 20.f;
};
#endif /* Boid_hpp */
