//
//  Boid.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/2/21.
//

#ifndef Boid_hpp
#define Boid_hpp

#include "PhysicsBehavior.hpp"
using namespace AI;

class Boid : public PhysicsBehavior{
    typedef PhysicsBehavior Super;
public:
    Boid(float, float, float);
    void Update(float) override;
    
protected:
    void DrawImplementation() override;
    
private:
    constexpr static const float kBoidRadius = 20.f;
};

#endif /* Boid_hpp */
