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
    
    ofVec2f vel = myDestination - myTransform.position;
    float degrees = AI::AngleUtils::Vec2ToAngleInDegrees(vel.x, vel.y);
    float rot = AI::AngleUtils::AngleDiff(degrees, myTransform.orientation);
    
    if (vel.length() > 5.f)
        SetVelocity(vel.getNormalized() * 500.f);
    else
        SetVelocity(ofVec2f::zero());
    if (fabs(rot) > 5.f && vel.length() > 5.f)
        SetRotation(rot > 0.f ? 600.f : -600.f);
    else
        SetRotation(0);
}

void Boid::SetDestination(const ofVec2f & aVector){
    myDestination = aVector;
}
