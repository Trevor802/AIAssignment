#include "ofApp.h"
#include "AngleUtils-inl.hpp"

ofApp::~ofApp() noexcept {
    delete myBoid;
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
    float centerX = ourWidth * 0.5f, centerY = ourHeight * 0.5f;
    float orient = 72.5f;
    myBoid = new Boid(centerX, centerY, orient);
}

//--------------------------------------------------------------
void ofApp::update(){
    myBoid->Update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw(){
    myBoid->Draw();
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
    myBoid->SetDestination({(float)x, (float)y});
    ofVec2f direction = {x - myBoid->GetPosition().x, y - myBoid->GetPosition().y};
    float orient = AI::AngleUtils::Vec2ToAngleInDegrees((float)x - myBoid->GetPosition().x,
                                                        (float)y - myBoid->GetPosition().y);
    myBoid->SetTargetOrientation(orient);
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
