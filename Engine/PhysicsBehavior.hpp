//
//  PhysicsBehavior.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/3/21.
//
#pragma once

#include "SceneBehavior.hpp"
#include "Types.h"

namespace AI{

class PhysicsBehavior : public SceneBehavior{
    typedef SceneBehavior Super;
public:
    PhysicsBehavior();
    void Update(float) override;
    inline void SetAcceleration(const ofVec2f& acc) { myRigidbody.acceleration = acc; }
    inline void SetAngularAcc(const float& angularAcc) { myRigidbody.angularAcceleration = angularAcc; }
    inline void SetVelocity(const ofVec2f& aVec) { myRigidbody.velocity = aVec; }
    inline void SetRotation(const float& rot) { myRigidbody.rotation = rot; }
    inline ofVec2f GetVelocity() const { return myRigidbody.velocity; }
    inline float GetRotation() const { return myRigidbody.rotation; }
    inline ofVec2f GetAcceleration() const { return myRigidbody.acceleration; }
    inline float GetAngularAcc() const { return myRigidbody.angularAcceleration; }
private:
    rigidbody myRigidbody;
};

}

