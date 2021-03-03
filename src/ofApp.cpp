#include "ofApp.h"
#include <time.h>
#include <stdlib.h>

#include "AngleUtils-inl.hpp"
#include "FloatUtils-inl.hpp"

ofApp::~ofApp() noexcept {
    delete myBoidLeader;
    for(int i = 0; i < myBoids.size(); ++i){
        delete myBoids[i];
    }
}

Boids ofApp::GetBoids() const {
    return myBoids;
}

Boid* ofApp::GetLeader() const {
    return myBoidLeader;
}

bool ofApp::TryWrapAround(ofVec2f & aPosition){
    bool isWrapped = false;
    if (aPosition.x > ofApp::ourWidth){
        aPosition.x = 0;
        isWrapped = true;
    }
    else if (aPosition.x < 0){
        aPosition.x = ofApp::ourWidth;
        isWrapped = true;
    }
    if (aPosition.y > ofApp::ourHeight){
        aPosition.y = 0;
        isWrapped = true;
    }
    else if (aPosition.y < 0){
        aPosition.y = ofApp::ourHeight;
        isWrapped = true;
    }
    return isWrapped;
}

//--------------------------------------------------------------
void ofApp::setup(){
    srand(time(NULL));
    const float centerX = ourWidth * 0.5f, centerY = ourHeight * 0.5f;
    const float orient = 72.5f;
    myBoidLeader = new LeaderBoid(centerX, centerY, orient);
    myBoidLeader->SetWorld(this);
    myBoidLeader->SetColor(ofColor(255, 0, 0));
    
    const int numBoids = 3;
    myBoids.resize(numBoids);
    for(int i = 0; i < numBoids; ++i){
        const float x = AI::FloatUtils::random() * centerX;
        const float y = AI::FloatUtils::random() * centerY;
        myBoids[i] = new FollowerBoid(x, y, 0);
        myBoids[i]->SetWorld(this);
        myBoids[i]->SetColor(ofColor(255, 255, 255));
    }
    myBoids.size();
}

//--------------------------------------------------------------
void ofApp::update(){
    myBoidLeader->Update(ofGetLastFrameTime());
    auto targetPos = myBoidLeader->GetPosition();
    for(auto it : myBoids){
        it->Update(ofGetLastFrameTime());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    myBoidLeader->Draw();
    for(auto it : myBoids)
        it->Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    myBoidLeader->SetMoveState(LeaderBoid::MoveState::Arrive);
    myBoidLeader->SetDestination({(float)x, (float)y});
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
