//
//  Boid.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/2/21.
//

#ifndef Boid_hpp
#define Boid_hpp

#include "PhysicsBehavior.hpp"
#include <vector>
#include <functional>

using namespace AI;
typedef std::vector<class Boid*> Boids;

class Boid : public PhysicsBehavior{
    typedef PhysicsBehavior Super;
public:
    Boid(float, float, float);
    void Update(float) final;
    void SetDestination(const ofVec2f&);
    void SetWorld(class ofApp* theWorld);
    void SetColor(const ofColor& aColor);
    static void GetBoidRect(const class Boid&, float&, float&, float&, float&);
    
protected:
    class ofApp* myWorld;
    ofVec2f myClickedPosition;
    virtual void UpdateMovement(struct kinematicOutput& output) = 0;
    void DrawImplementation() override;
    Boids GetAroundBoids(float radius);
    struct dynamicOutput DynamicFlee(const ofVec2f& destination, float acceleration);
    struct kinematicOutput KinematicSeek(const ofVec2f& destination, float speed, float stopDistance); // Arrive method 1
    struct kinematicOutput KinematicFlee(const ofVec2f& destination, float speed);
    struct kinematicOutput Arrive(const ofVec2f& destination, float maxSpeed, float slowDistancce, float stopDistance); // Arrive method 2, better, realistic
    struct kinematicOutput Align(float targetOrientation, float rotation); // Orientation method 1
    struct kinematicOutput Turn(float targetOrientation, float maxRotation, float slowAngleDiff, float stopAngleDiff); // Orientation method 2, better, smoother
    struct kinematicOutput Wander(float maxSpeed, float maxRotation);
    struct kinematicOutput Separation(const Boids& someBoids, float radius, float maxRepulsion);
    struct kinematicOutput Alignment(const Boids& someBoids, float maxRotation);
    struct kinematicOutput Cohesion(const Boids& someBoids, float maxSpeed);
    std::function<void()> ArrivedCallback;
    
private:
    constexpr static const float kBoidRadius = 20.f;
    bool myHasWrapped = false;
    void WrapAround();
    void ClampSpeed(float maxSpeed);
    void ApplyKinematic(const struct kinematicOutput& output);
    void ApplyDynamic(const struct dynamicOutput& output);
    ofColor myColor;
};

#endif /* Boid_hpp */
