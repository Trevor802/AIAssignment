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
    void KinematicSeek(float speed, float stopDistance);
    void KinematicFlee(float speed);
    void Arrive(float maxSpeed, float slowDistancce, float stopDistance, float maxRotation, float stopAngle);
    void DynamicFlee(float acceleration, float rotation);
    void DynamicSeek(float acceleration, float rotation, float accStopDistance);
    
private:
    constexpr static const float kBoidRadius = 20.f;
    ofVec2f myDestination;
    bool hasWrapped = false;
    void WrapAround();
    void ClampSpeed(float maxSpeed);
};

#endif /* Boid_hpp */
