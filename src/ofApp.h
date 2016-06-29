#pragma once

#include "ofMain.h"
#include "particle.h"

class ofApp : public ofBaseApp{

  public:
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
    float inc = 0.01;
    int scl = 10;
    float zoff = 0;
    int rows;
    int cols;
    vector<Particle> particles;
    vector<ofVec2f> flowfield;
    const int NUM_PARTICLES = 2000;
};
