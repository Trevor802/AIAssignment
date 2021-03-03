//
//  FollowerBoid.cpp
//  AIAssignment
//
//  Created by Trevor Zhang on 3/3/21.
//

#include "FollowerBoid.hpp"
#include "GameTypes.h"
#include "ofApp.h"
#include "AngleUtils-inl.hpp"

void FollowerBoid::UpdateMovement(struct kinematicOutput &output){
    output.velocity += Separation(GetAroundBoids(100.f), 100.f, 10.f).velocity * 0.8f;
    output.velocity += Arrive(myWorld->GetLeader()->GetPosition(), 200.f, 100.f, 5.f).velocity * 0.5f;
    output.velocity += Cohesion(GetAroundBoids(200.f), 100.f).velocity * 0.2f;
    ofVec2f directLeader = myWorld->GetLeader()->GetPosition() - GetPosition();
    float orientLeader = AI::AngleUtils::Vec2ToAngleInDegrees(directLeader.x, directLeader.y);
    output.rotation += Turn(orientLeader, 180.f, 40.f, 5.f).rotation * 0.5f;
    output.rotation += Alignment(GetAroundBoids(80.f), 180.f).rotation * 0.25f;
}
