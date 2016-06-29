#include "particle.h"
#include "math.h"

Particle::Particle(int scl, int cols) {
  pos = ofVec2f(ofRandom(0, ofWidth), ofRandom(0, ofHeight));
  prevPos = pos;
  this.scl = scl;
  this.cols = cols;
}

void Particle::update() {
  vel += acc;
  vel.limit(maxSpeed);
  pos += vel;
  acc *= 0;
}

void Particle::follow(vector<ofVec2f> vectors) {
  int x = floor(pos.x / scl);
  int y = floor(pos.y / scl);
  int index = x + y * cols;
  ofVec2f force = vectors[index];
  applyForce(force);
}

void Particle::applyForce(ofVec2f force) {
  acc += force;
}

void Particle::show() {
  ofNoFill();
  ofSetColor(h, 255, 255, 25);
  h = (h + 1) % 255;
  ofSetLineWidth(1);
  ofDrawLine(pos.x, pos.y, prevPos.x, prevPos.y);
  updatePrev();
}

void Particle::updatePrev() {
  prevPos.set(pos);
}

void Particle::edges() {
  int width = ofGetWindowWidth();
  int height = ofGetWindowHeight();
  if (pos.x > width) {
    pos.x = 0;
    updatePrev();
  }
  if (pos.x < 0) {
    pos.x = width;
    updatePrev();
  }
  if (pos.y > height) {
    pos.y = 0;
    updatePrev();
  }
  if (pos.y < 0) {
    pos.y = height;
    updatePrev();
  }
}
