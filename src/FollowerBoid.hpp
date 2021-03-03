//
//  FollowerBoid.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 3/3/21.
//

#pragma once
#include "Boid.hpp"

class FollowerBoid final : public Boid{
public:
    FollowerBoid(float x, float y, float orient) : Boid(x, y, orient) {}
protected:
    void UpdateMovement(struct kinematicOutput& output) override;
};
