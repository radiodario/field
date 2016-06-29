#pragma once

#include "ofMain.h"

class Particle {
  private:
    ofVec2f pos;
    ofVec3f pos3d;
    ofVec2f prevPos;
    ofVec3f prevPos3d;
    ofVec2f vel;
    ofVec2f acc;
    int maxSpeed = 4;
    int h = 0;
    int cols;
    int scl;
    ofColor color;
    int radius = 500;

  public:
    void update();
    void update3d();
    void follow(vector<ofVec2f> vectors);
    void applyForce(ofVec2f forcd);
    void show(int alpha);
    void updatePrev();
    void edges();
    void show3d(int alpha);
    Particle(int scl, int cols);
};
