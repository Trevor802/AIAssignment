//
//  Boid.cpp
//  AIAssignment
//
//  Created by Trevor Zhang on 2/2/21.
//

#include "Boid.hpp"
#include "ofMain.h"

Boid::Boid(){
    myRB = {.pos = ofVec2f(0, 0), .orientation = 0};
}

Boid::Boid(float anX, float aY, float anOrient){
    myRB = {.pos = ofVec2f(anX, aY), .orientation = anOrient};
}

void Boid::Draw(){
    ofDrawCircle(myRB.pos.x, myRB.pos.y, kBoidRadius);
    float halfRadius = kBoidRadius * 0.5f, length = halfRadius * sqrt(3);
    ofDrawTriangle(myRB.pos.x + halfRadius, myRB.pos.y - length, myRB.pos.x + kBoidRadius * 2.f, myRB.pos.y, myRB.pos.x + halfRadius, myRB.pos.y + length);
}
