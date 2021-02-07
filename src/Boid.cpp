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
#include "AngleUtils.hpp"
#include "ofApp.h"

Boid::Boid(float x, float y, float degress){
    SetPosition(ofVec2f(x, y));
    SetOrientation(degress);
}

void Boid::DrawImplementation(){
    ofDrawCircle(0, 0, kBoidRadius);
    float halfRadius = kBoidRadius * 0.5f, length = halfRadius * sqrt(3);
    ofDrawTriangle(halfRadius, -length, kBoidRadius * 2.f, 0, halfRadius, length);
}

void Boid::Update(float deltaTime){
    Super::Update(deltaTime);
    
    ofVec2f targetPos(ofApp::ourWidth * 0.5f, ofApp::ourHeight * 0.5f);
    float targetOrient = 0;
    ofVec2f vel = targetPos - myTransform.position;
    float rot = AI::AngleUtils::AngleDiff(targetOrient, myTransform.orientation);
    kinematicOutput output{vel, rot};
    
    SetVelocity(output.velocity.getNormalized() * 100.f);
    SetRotation(rot > 0.f ? 15.f : -15.f);
}
