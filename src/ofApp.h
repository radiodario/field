#pragma once

#include "ofMain.h"
#include "particle.h"
#include "ofxGui.h"
#include "ofxSyphon.h"

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
    float inc = 0.3;
    int scl = 30;
    float zoff = 0;
    int rows;
    int cols;
    vector<Particle> particles;
    vector<ofVec2f> flowfield;

    ofEasyCam camera;

    const int NUM_PARTICLES = 20000;
    bool doSaveScreen = false;

    ofFbo buffer;
    ofImage imageSaver;
    ofTexture tex;

    // gui
    ofxPanel gui;
    ofxFloatSlider incSlider;
    ofxFloatSlider zincSlider;
    ofxToggle drawField;
    ofxToggle onSphere;
    ofxToggle sendToSyphon;

    ofxIntSlider bgAlpha;
    ofxIntSlider fgAlpha;
    ofxIntSlider forceSlider;
    ofxIntSlider maxSpeedSlider;

    ofxSyphonServer send;
};
