//
//  GameTypes.h
//  AIAssignment
//
//  Created by Trevor Zhang on 2/4/21.
//

#ifndef GameTypes_h
#define GameTypes_h

#include "ofMain.h"

struct kinematicOutput{
    ofVec2f velocity = ofVec2f::zero();
    float orientation = 0;
    
    inline kinematicOutput operator+=(const kinematicOutput& other){
        this->velocity += other.velocity;
        this->orientation += other.orientation;
        return *this;
    }
    
    inline kinematicOutput operator*=(const float& weight){
        this->velocity *= weight;
        this->orientation *= weight;
        return *this;
    }
};

struct dynamicOutput{
    ofVec2f acceleration = ofVec2f::zero();
    float rotation = 0;
    
    inline dynamicOutput operator+=(const dynamicOutput& other){
        this->rotation += other.rotation;
        this->acceleration += other.acceleration;
        return *this;
    }
    
    inline dynamicOutput operator*=(const float& weight){
        this->rotation *= weight;
        this->acceleration *= weight;
        return *this;
    }
};

#endif /* GameTypes_h */
