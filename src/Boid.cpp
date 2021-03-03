//
//  Boid.cpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/2/21.
//

#include "Boid.hpp"
#include "SceneBehavior.hpp"
#include "ofMain.h"
#include "GameTypes.h"
#include "AngleUtils-inl.hpp"
#include "FloatUtils-inl.hpp"
#include "ofApp.h"

Boid::Boid(float x, float y, float degress){
    SetPosition(ofVec2f(x, y));
    SetOrientation(degress);
    myClickedPosition = myTransform.position;
    SetRotation(0);
}

void Boid::DrawImplementation(){
    ofSetColor(myColor);
    ofDrawCircle(0, 0, kBoidRadius);
    float halfRadius = kBoidRadius * 0.5f, length = halfRadius * sqrt(3);
    ofDrawTriangle(halfRadius, -length, kBoidRadius * 2.f, 0, halfRadius, length);
}

void Boid::ApplyKinematic(const struct kinematicOutput &output){
    SetVelocity(output.velocity);
    SetRotation(output.rotation);
}

void Boid::ApplyDynamic(const struct dynamicOutput &output){
    SetAngularAcc(output.angularAcceleration);
    SetAcceleration(output.acceleration);
}

void Boid::Update(float deltaTime){
    Super::Update(deltaTime);
    if (!myHasWrapped){
        kinematicOutput output;
        UpdateMovement(output);
        ApplyKinematic(output);
    }
    ClampSpeed(500.f);
    // Wrap around world
    WrapAround();
}

void Boid::SetDestination(const ofVec2f & aVector){
    myClickedPosition = aVector;
    myHasWrapped = false;
}

kinematicOutput Boid::KinematicSeek(const ofVec2f& destination, float speed, float stopDistance){
    kinematicOutput output;
    ofVec2f vel = destination - myTransform.position;
    if (vel.length() > stopDistance){
        output.velocity = vel.getNormalized() * speed;
    }
    else{
        output.velocity = ofVec2f::zero();
    }
    return output;
}

kinematicOutput Boid::KinematicFlee(const ofVec2f& destination, float aSpeed){
    kinematicOutput output;
    ofVec2f vel = myTransform.position - destination;
    output.velocity = vel.getNormalized() * aSpeed;
    return output;
}

kinematicOutput Boid::Arrive(const ofVec2f& destination, float maxSpeed, float slowDistancce, float stopDistance){
    assert(slowDistancce > stopDistance);
    kinematicOutput output;
    ofVec2f vel = destination - myTransform.position;
    float distance = vel.length();
    const float extraDist = 1.f;
    
    if (distance > slowDistancce){
        output.velocity = vel.getNormalized() * maxSpeed;
    }
    else if (distance > stopDistance){
        float ratio = (distance - stopDistance + extraDist) / (slowDistancce - stopDistance);
        output.velocity = vel.getNormalized() * maxSpeed * ratio;
    }
    else{
        output.velocity = ofVec2f::zero();
        if (ArrivedCallback)
            ArrivedCallback();
    }
    return output;
}

dynamicOutput Boid::DynamicFlee(const ofVec2f& destination, float acceleration){
    dynamicOutput output;
    ofVec2f direction = myTransform.position - destination;
    output.acceleration = direction.getNormalized() * acceleration;
    return output;
}

void Boid::ClampSpeed(float maxSpeed){
    ofVec2f velocity = GetVelocity();
    ofVec2f acceleration = GetAcceleration();
    if (velocity.length() > maxSpeed && velocity.dot(acceleration) > 0){
        SetVelocity(velocity.getNormalized() * maxSpeed);
        SetAcceleration(ofVec2f::zero());
    }
}

kinematicOutput Boid::Align(float targetOrientation, float rotation){
    kinematicOutput output;
    float rot = AI::AngleUtils::AngleDiff(targetOrientation, myTransform.orientation);
    rotation *= rot > 0.f ? 1.f : -1.f;
    output.rotation = fabsf(rot) > 5.f ? rotation : 0;
    return output;
}

kinematicOutput Boid::Turn(float targetOrientation, float maxRotation, float slowAngleDiff, float stopAngleDiff){
    assert(slowAngleDiff > stopAngleDiff);
    kinematicOutput output;
    float rot = AI::AngleUtils::AngleDiff(targetOrientation, myTransform.orientation);
    float rotation = rot > 0.f ? maxRotation : -maxRotation;
    if (fabsf(rot) < slowAngleDiff && fabsf(rot) >= stopAngleDiff){
        float ratio = (fabsf(rot) - stopAngleDiff) / (slowAngleDiff - stopAngleDiff);
        rotation *= ratio;
    }
    else if (fabsf(rot) < stopAngleDiff)
        rotation = 0;
    output.rotation = rotation;
    return output;
}

kinematicOutput Boid::Wander(float maxSpeed, float maxRotation){
    kinematicOutput output;
    ofVec2f velocity;
    AI::AngleUtils::AngleToVec2(GetOrientation(), velocity.x, velocity.y);
    output.velocity = velocity * maxSpeed;
    float r = AI::FloatUtils::randomBinomial();
    output.rotation = r * maxRotation;
    return output;
}

void Boid::WrapAround(){
    ofVec2f pos = GetPosition();
    myHasWrapped = ofApp::TryWrapAround(pos);
    SetPosition(pos);
}

Boids Boid::GetAroundBoids(float radius){
    Boids results;
    Boids boids = myWorld->GetBoids();
    for(auto& it : boids){
        if (this == it)
            continue;
        float dist = (GetPosition() - it->GetPosition()).length();
        if (dist < radius)
            results.push_back(it);
    }
    return results;
}

kinematicOutput Boid::Separation(const Boids &someBoids, float radius, float maxRepulsion){
    kinematicOutput output;
    if (1 == someBoids.size())
        return output;
    ofVec2f repulsion;
    for(auto& it : someBoids){
        assert(this != it);
        ofVec2f direction = GetPosition() - it->GetPosition();
        float ratio = direction.length() / radius;
        assert(ratio < 1.f);
        repulsion += (maxRepulsion / (ratio * ratio)) * direction.normalize();
    }
    repulsion /= (float)someBoids.size();
    output.velocity = repulsion;
    return output;
}

kinematicOutput Boid::Alignment(const Boids& someBoids, float maxRotation){
    kinematicOutput output;
    if (1 == someBoids.size())
        return output;
    float alignment;
    for(auto& it : someBoids){
        assert(this != it);
        alignment += it->GetOrientation();
    }
    alignment /= (float)someBoids.size();
    output = Turn(alignment, maxRotation, 15.f, 1.f);
    return output;
}

kinematicOutput Boid::Cohesion(const Boids &someBoids, float maxSpeed){
    kinematicOutput output;
    if (1 == someBoids.size())
        return output;
    ofVec2f cohesion;
    for(auto& it : someBoids){
        assert(this != it);
        cohesion += it->GetPosition();
    }
    cohesion /= (float)someBoids.size();
    output = Arrive(cohesion, 100.f, 10.f, 5.f);
    return output;
}

void Boid::SetWorld(class ofApp *theWorld){
    myWorld = theWorld;
}

void Boid::SetColor(const ofColor& aColor){
    myColor = aColor;
}
