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
    void SetDestination(const ofVec2f&);
    
protected:
    void DrawImplementation() override;
    
private:
    constexpr static const float kBoidRadius = 20.f;
    ofVec2f myDestination;
};

#endif /* Boid_hpp */
