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
    SetRotation(0);
}

void Boid::DrawImplementation(){
    ofDrawCircle(0, 0, kBoidRadius);
    float halfRadius = kBoidRadius * 0.5f, length = halfRadius * sqrt(3);
    ofDrawTriangle(halfRadius, -length, kBoidRadius * 2.f, 0, halfRadius, length);
}

void Boid::Update(float deltaTime){
    Super::Update(deltaTime);
    if (!hasWrapped){
//        Arrive(500.f, 200.f, 5.f, 300.f, 5.f);
//        DynamicFlee(1000.f, 300.f);
        DynamicSeek(500.f, 300.f, 100.f);
    }
    ClampSpeed(100.f);
    // Wrap around world
    WrapAround();
}

void Boid::SetDestination(const ofVec2f & aVector){
    myDestination = aVector;
    hasWrapped = false;
}

void Boid::KinematicSeek(float speed, float stopDistance){
    ofVec2f vel = myDestination - myTransform.position;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(vel.x, vel.y);
    if (vel.length() > stopDistance){
        SetVelocity(vel.getNormalized() * speed);
        SetOrientation(degrees);
    }
    else{
        SetVelocity(ofVec2f::zero());
    }
}

void Boid::KinematicFlee(float aSpeed){
    ofVec2f vel = myTransform.position - myDestination;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(vel.x, vel.y);
    SetVelocity(vel.getNormalized() * aSpeed);
    SetOrientation(degrees);
}

void Boid::WrapAround(){
    ofVec2f pos = GetPosition();
    if (ofApp::TryWrapAround(pos)){
        hasWrapped = true;
        SetRotation(0);
    }
    SetPosition(pos);
}

void Boid::Arrive(float maxSpeed, float slowDistancce, float stopDistance, float rotation, float stopAngle){
    assert(slowDistancce > stopDistance);
    ofVec2f vel = myDestination - myTransform.position;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(vel.x, vel.y);
    float rot = AI::AngleUtils::AngleDiff(degrees, myTransform.orientation);
    float distance = vel.length();
    
    if (distance > slowDistancce){
        SetVelocity(vel.getNormalized() * maxSpeed);
    }
    else if (distance > stopDistance){
        float ratio = (distance - stopDistance) / (slowDistancce - stopDistance);
        SetVelocity(vel.getNormalized() * maxSpeed * ratio);
    }
    else{
        SetVelocity(ofVec2f::zero());
    }
    
    if (fabsf(rot) > stopAngle && distance > stopDistance)
        SetRotation(rot > 0.f ? rotation : -rotation);
    else
        SetRotation(0);
}

void Boid::DynamicFlee(float acceleration, float rotation){
    ofVec2f direction = myTransform.position - myDestination;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(direction.x, direction.y);
    float rot = AI::AngleUtils::AngleDiff(degrees, myTransform.orientation);
    rotation *= rot > 0.f ? 1.f : -1.f;
    if (fabsf(rot) > 5.f)
        SetRotation(rotation);
    else
        SetRotation(0);
    float orientation = GetOrientation();
    AI::AngleUtils::AngleToVec2(orientation, direction.x, direction.y);
    SetAcceleration(direction * acceleration);
}

void Boid::ClampSpeed(float maxSpeed){
    ofVec2f velocity = GetVelocity();
    if (velocity.length() > maxSpeed){
        SetVelocity(velocity.getNormalized() * maxSpeed);
        SetAcceleration(ofVec2f::zero());
    }
}

void Boid::DynamicSeek(float acceleration, float rotation, float accStopDistance){
    ofVec2f direction = myDestination - myTransform.position;
    bool canAccelerate = direction.length() > accStopDistance;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(direction.x, direction.y);
    float rot = AI::AngleUtils::AngleDiff(degrees, myTransform.orientation);
    rotation *= rot > 0.f ? 1.f : -1.f;
    if (fabsf(rot) > 5.f)
        SetRotation(rotation);
    else
        SetRotation(0);
    float orientation = GetOrientation();
    AI::AngleUtils::AngleToVec2(orientation, direction.x, direction.y);
    if (canAccelerate)
        SetAcceleration(direction * acceleration);
    else
        SetAcceleration(ofVec2f::zero());
}
