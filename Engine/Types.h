//
//  Types.h
//  AIAssignment
//
//  Created by Trevor Zhang on 2/2/21.
//

#ifndef Types_h
#define Types_h

#include "ofMain.h"
namespace AI{

struct transform{
    ofVec2f position;
    float orientation;
};

struct rigidbody{
    ofVec2f velocity;
    ofVec2f acceleration;
    float rotation;
    float angularAcceleration;
};

}
#endif /* Types_h */
