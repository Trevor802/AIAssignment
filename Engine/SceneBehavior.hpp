//
//  Entity.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/3/21.
//

#pragma once
#include "Types.h"
namespace AI{

class SceneBehavior{
public:
    SceneBehavior() = default;
    virtual ~SceneBehavior(){}
    void Draw();
    virtual void Update(float){}
    
    inline void SetPosition(const ofVec2f& pos) { myTransform.position = pos; }
    void SetOrientation(float orient);
    
    inline ofVec2f GetPosition() const { return myTransform.position; }
    inline float GetOrientation() const { return myTransform.orientation; }
protected:
    virtual void DrawImplementation(){};
    transform myTransform;
};

}

