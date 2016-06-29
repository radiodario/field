#pragma once

#include "ofMain.h"

class Particle {
  private:
    ofVec2f pos;
    ofVec2f prevPos;
    ofVec2f vel;
    ofVec2f acc;
    const int maxSpeed = 4;
    int h = 0;
    int cols;
    int scl;
    ofColor color;

  public:
    void update();
    void follow(vector<ofVec2f> vectors);
    void applyForce(ofVec2f forcd);
    void show(int alpha);
    void updatePrev();
    void edges();

    Particle(int scl, int cols);
};
