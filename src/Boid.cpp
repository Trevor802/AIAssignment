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
#include "ofApp.h"

Boid::Boid(float x, float y, float degress){
    SetPosition(ofVec2f(x, y));
    SetOrientation(degress);
    myDestination = myTransform.position;
    myTargetOrientation = 0;
    SetRotation(0);
}

void Boid::DrawImplementation(){
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
//    kinematicOutput output;
    dynamicOutput output;
    if (!hasWrapped){
//        output += Arrive(500.f, 200.f, 5.f) *= 1.f;
//        output += KinematicFlee(100.f) *= 1.f;
//        output += KinematicSeek(300.f, 5.f) *= 1.f;
//        output += DynamicFlee(1000.f) *= 1.f;
        output += DynamicSeek(3.f, 100.f) *= 1.f;
//        output += Align(90.f) *= 1.f;
//        output += Turn(180.f, 40.f, 5.f);
    }
//    ApplyKinematic(output);
    ApplyDynamic(output);
    ClampSpeed(300.f);
    // Wrap around world
    WrapAround();
}

void Boid::SetDestination(const ofVec2f & aVector){
    myDestination = aVector;
    hasWrapped = false;
}

void Boid::SetTargetOrientation(float orientation){
    myTargetOrientation = orientation;
}

kinematicOutput Boid::KinematicSeek(float speed, float stopDistance){
    kinematicOutput output;
    ofVec2f vel = myDestination - myTransform.position;
    if (vel.length() > stopDistance){
        output.velocity = vel.getNormalized() * speed;
    }
    else{
        output.velocity = ofVec2f::zero();
    }
    return output;
}

kinematicOutput Boid::KinematicFlee(float aSpeed){
    kinematicOutput output;
    ofVec2f vel = myTransform.position - myDestination;
    output.velocity = vel.getNormalized() * aSpeed;
    return output;
}

kinematicOutput Boid::Arrive(float maxSpeed, float slowDistancce, float stopDistance){
    assert(slowDistancce > stopDistance);
    kinematicOutput output;
    ofVec2f vel = myDestination - myTransform.position;
    float distance = vel.length();
    
    if (distance > slowDistancce){
        output.velocity = vel.getNormalized() * maxSpeed;
    }
    else if (distance > stopDistance){
        float ratio = (distance - stopDistance) / (slowDistancce - stopDistance);
        output.velocity = vel.getNormalized() * maxSpeed * ratio;
    }
    else{
        output.velocity = ofVec2f::zero();
    }
    return output;
}

dynamicOutput Boid::DynamicFlee(float acceleration){
    dynamicOutput output;
    ofVec2f direction = myTransform.position - myDestination;
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

dynamicOutput Boid::DynamicSeek(float timeLeft, float accStopDistance){
    assert(timeLeft > 0);
    dynamicOutput output;
    ofVec2f direction = myDestination - myTransform.position;
    bool canAccelerate = direction.length() > accStopDistance;
    output.acceleration = canAccelerate ? direction / timeLeft : ofVec2f::zero();
    return output;
}

kinematicOutput Boid::Align(float rotation){
    kinematicOutput output;
    float rot = AI::AngleUtils::AngleDiff(myTargetOrientation, myTransform.orientation);
    rotation *= rot > 0.f ? 1.f : -1.f;
    output.rotation = fabsf(rot) > 5.f ? rotation : 0;
    return output;
}

kinematicOutput Boid::Turn(float maxRotation, float slowAngleDiff, float stopAngleDiff){
    assert(slowAngleDiff > stopAngleDiff);
    kinematicOutput output;
    float rot = AI::AngleUtils::AngleDiff(myTargetOrientation, myTransform.orientation);
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

void Boid::WrapAround(){
    ofVec2f pos = GetPosition();
    if (ofApp::TryWrapAround(pos)){
        hasWrapped = true;
        SetRotation(0);
    }
    SetPosition(pos);
}
