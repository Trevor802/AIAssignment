//
//  LeaderBoid.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 3/2/21.
//

#pragma once
#include "Boid.hpp"
class LeaderBoid final : public Boid{
public:
    LeaderBoid(float x, float y, float orient);
    enum MoveState : unsigned char{
        Wander = 0,
        Arrive = 1
    };
    void SetMoveState(MoveState aState);
protected:
    void UpdateMovement(struct kinematicOutput& output) override;
private:
    MoveState myMoveState;
};
