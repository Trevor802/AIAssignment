//
//  LeaderBoid.cpp
//  AIAssignment
//
//  Created by Trevor Zhang on 3/2/21.
//

#include "LeaderBoid.hpp"
#include "GameTypes.h"
#include "AngleUtils-inl.hpp"
LeaderBoid::LeaderBoid(float x, float y, float orient) : Boid(x, y, orient){
    myMoveState = MoveState::Wander;
}

void LeaderBoid::UpdateMovement(struct kinematicOutput &output){
    switch (myMoveState) {
        case MoveState::Wander:
            output = Boid::Wander(100.f, 180.f);
            ArrivedCallback = nullptr;
            break;
        case MoveState::Arrive:
            output.velocity = Boid::Arrive(myClickedPosition ,500.f, 200.f, 5.f).velocity;
            ofVec2f dir = myClickedPosition - myTransform.position;
            float orient = AI::AngleUtils::Vec2ToAngleInDegrees(dir.x, dir.y);
            output.rotation = Boid::Align(orient, 300.f).rotation;
            ArrivedCallback = [this](){this->SetMoveState(MoveState::Wander);};
            break;
    }
}

void LeaderBoid::SetMoveState(MoveState aState){
    myMoveState = aState;
}
