//
//  PhysicsBehavior.cpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/3/21.
//

#include "PhysicsBehavior.hpp"
#include "AngleUtils-inl.hpp"

namespace AI{

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
