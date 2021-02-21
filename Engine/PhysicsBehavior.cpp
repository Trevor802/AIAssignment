//
//  PhysicsBehavior.cpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/3/21.
//

#include "PhysicsBehavior.hpp"
#include "AngleUtils-inl.hpp"

namespace AI{

PhysicsBehavior::PhysicsBehavior(){
    myRigidbody.rotation = 0;
    myRigidbody.angularAcceleration = 0;
    myRigidbody.velocity = std::move(ofVec2f::zero());
    myRigidbody.acceleration = std::move(ofVec2f::zero());
}

void PhysicsBehavior::Update(float deltaTime) {
    Super::Update(deltaTime);
    myTransform.position += myRigidbody.velocity * deltaTime;
    myRigidbody.velocity += myRigidbody.acceleration * deltaTime;
    float newOrient = myTransform.orientation + myRigidbody.rotation * deltaTime;
    AngleUtils::WrapDegrees(newOrient);
    myTransform.orientation = newOrient;
    myRigidbody.rotation += myRigidbody.angularAcceleration * deltaTime;
}

}
