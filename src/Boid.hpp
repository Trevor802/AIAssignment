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
    struct kinematicOutput KinematicSeek(float speed, float stopDistance);
    struct kinematicOutput KinematicFlee(float speed);
    struct kinematicOutput Arrive(float maxSpeed, float slowDistancce, float stopDistance);
    struct dynamicOutput DynamicFlee(float acceleration, float rotation);
    struct dynamicOutput DynamicSeek(float acceleration, float rotation, float accStopDistance);
    struct dynamicOutput Align(float targetOrientation, float rotation);
    
private:
    constexpr static const float kBoidRadius = 20.f;
    ofVec2f myDestination;
    bool hasWrapped = false;
    void WrapAround();
    void ClampSpeed(float maxSpeed);
    void ApplyKinematic(const struct kinematicOutput& output);
    void ApplyDynamic(const struct dynamicOutput& output);
};

#endif /* Boid_hpp */
