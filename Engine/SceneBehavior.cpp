//
//  Entity.cpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/3/21.
//

#include "SceneBehavior.hpp"
#include "AngleUtils-inl.hpp"

namespace AI{

void SceneBehavior::Draw(){
    ofPushMatrix();
    ofTranslate(myTransform.position.x, myTransform.position.y);
    ofRotateDeg(myTransform.orientation);
    DrawImplementation();
    ofPopMatrix();
}

void SceneBehavior::SetOrientation(float orient){
    AngleUtils::WrapDegrees(orient);
    myTransform.orientation = orient;
}

}
