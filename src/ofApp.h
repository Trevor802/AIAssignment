#pragma once

#include "ofMain.h"
#include "LeaderBoid.hpp"
#include "FollowerBoid.hpp"
#include "Quadtree.hpp"

using namespace AI;

class ofApp : public ofBaseApp{
public:
    static const int ourWidth = 1024, ourHeight = 768;
    static bool TryWrapAround(ofVec2f&);
    
private:
    LeaderBoid* myBoidLeader;
    Boids myBoids;
    Quadtree<Boid, Boid::GetBoidRect>* myQuadtree;
    
public:
    virtual ~ofApp() noexcept;
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    Boids GetBoids() const;
    Boid* GetLeader() const;
    
    Boids SearchBoidsByAABB(float, float, float, float) const;
};
