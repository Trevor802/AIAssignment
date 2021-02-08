#include "ofApp.h"

ofApp::~ofApp() noexcept {
    delete myBoid;
}

//--------------------------------------------------------------
void ofApp::setup(){
    float centerX = ourWidth * 0.5f, centerY = ourHeight * 0.5f;
    float orient = 90.f;
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
