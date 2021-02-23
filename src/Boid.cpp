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

void Boid::ApplyKinematic(const struct kinematicOutput &output){
    SetVelocity(output.velocity);
    SetOrientation(output.orientation);
}

void Boid::ApplyDynamic(const struct dynamicOutput &output){
    SetRotation(output.rotation);
    SetAcceleration(output.acceleration);
}

void Boid::Update(float deltaTime){
    Super::Update(deltaTime);
//    kinematicOutput output;
    dynamicOutput output;
    if (!hasWrapped){
//        output += Arrive(500.f, 200.f, 5.f) *= 0.2f;
//        output += KinematicFlee(100.f) *= 0.8f;
//        output += KinematicSeek(300.f, 5.f) *= 0.1f;
        output += DynamicFlee(1000.f, 300.f) *= 0.5f;
        output += DynamicSeek(500.f, 300.f, 100.f) *= 0.3f;
        output += Align(-135.f, 10.f) *= 0.8f;
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

kinematicOutput Boid::KinematicSeek(float speed, float stopDistance){
    kinematicOutput output;
    ofVec2f vel = myDestination - myTransform.position;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(vel.x, vel.y);
    if (vel.length() > stopDistance){
        output.velocity = vel.getNormalized() * speed;
        output.orientation = degrees;
    }
    else{
        output.velocity = ofVec2f::zero();
    }
    return output;
}

kinematicOutput Boid::KinematicFlee(float aSpeed){
    kinematicOutput output;
    ofVec2f vel = myTransform.position - myDestination;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(vel.x, vel.y);
    output.velocity = vel.getNormalized() * aSpeed;
    output.orientation = degrees;
    return output;
}

kinematicOutput Boid::Arrive(float maxSpeed, float slowDistancce, float stopDistance){
    assert(slowDistancce > stopDistance);
    kinematicOutput output;
    ofVec2f vel = myDestination - myTransform.position;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(vel.x, vel.y);
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
    output.orientation = degrees;
    return output;
}

dynamicOutput Boid::DynamicFlee(float acceleration, float rotation){
    dynamicOutput output;
    ofVec2f direction = myTransform.position - myDestination;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(direction.x, direction.y);
    float rot = AI::AngleUtils::AngleDiff(degrees, myTransform.orientation);
    rotation *= rot > 0.f ? 1.f : -1.f;
    output.rotation = fabsf(rot) > 5.f ? rotation : 0;
    float orientation = myTransform.orientation;
    AI::AngleUtils::AngleToVec2(orientation, direction.x, direction.y);
    output.acceleration = direction * acceleration;
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

dynamicOutput Boid::DynamicSeek(float acceleration, float rotation, float accStopDistance){
    dynamicOutput output;
    ofVec2f direction = myDestination - myTransform.position;
    bool canAccelerate = direction.length() > accStopDistance;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(direction.x, direction.y);
    float rot = AI::AngleUtils::AngleDiff(degrees, myTransform.orientation);
    rotation *= rot > 0.f ? 1.f : -1.f;
    output.rotation = fabsf(rot) > 5.f ? rotation : 0;
    float orientation = myTransform.orientation;
    AI::AngleUtils::AngleToVec2(orientation, direction.x, direction.y);
    output.acceleration = canAccelerate ? direction * acceleration : ofVec2f::zero();
    return output;
}

dynamicOutput Boid::Align(float degrees, float rotation){
    dynamicOutput output;
    float rot = AI::AngleUtils::AngleDiff(degrees, myTransform.orientation);
    rotation *= rot > 0.f ? 1.f : -1.f;
    output.rotation = fabsf(rot) > 5.f ? rotation : 0;
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
