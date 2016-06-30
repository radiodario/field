#include "particle.h"
#include "math.h"
#include "ofMath.h"
#include "ofApp.h"

Particle::Particle(int scl, int cols) {
  pos = ofVec2f(ofRandom(0, 1) * ofGetWindowWidth(), ofRandom(0, 1) * ofGetWindowHeight());

  prevPos = pos;
  this->scl = scl;
  this->cols = cols;
  color = ofColor(
      ofRandom(0, 1) > 0.9 ? 200 : 0,
      ofRandom(0, 1) > 0.9 ? 200 : 0,
      ofRandom(0, 1) > 0.0 ? 255 : 0,
      25
      );
}

void Particle::update() {
  vel += acc;
  maxSpeed = ((ofApp*) ofGetAppPtr())->maxSpeedSlider;
  vel.limit(maxSpeed);
  pos += vel;
  acc *= 0;
  if (((ofApp*) ofGetAppPtr())->onSphere) {
    update3d();
  }
}

void Particle::update3d() {
  float lon = ofMap(pos.x, 0, ofGetWindowWidth(), 0, PI);
  float lat = ofMap(pos.y, 0, ofGetWindowHeight(), 0, TWO_PI);
  pos3d.set(
      radius * sin(lon) * cos(lat),
      radius * sin(lon) * sin(lat),
      radius * cos(lon)
      );
}

void Particle::follow(vector<ofVec2f> forces) {
  int x = floor(pos.x / scl);
  int y = floor(pos.y / scl);
  int index = x + y * cols;
  try {
    ofVec2f force = forces.at(index);
    applyForce(force);
  } catch (const std::out_of_range& e) {

  }
}

void Particle::applyForce(ofVec2f force) {
  acc += force;
}

void Particle::show(int alpha) {
  ofNoFill();
  ofSetColor(color.r, color.g, color.b, alpha);

  ofSetLineWidth(1);
  ofDrawLine(pos.x, pos.y, prevPos.x, prevPos.y);
  updatePrev();
}


void Particle::show3d(int alpha) {
  ofNoFill();
  ofSetColor(color.r, color.g, color.b, alpha);

  ofSetLineWidth(1);
  ofBeginShape();
  ofVertex(prevPos3d);
  ofVertex(pos3d);
  ofEndShape(false);
  updatePrev();
}

void Particle::updatePrev() {
  prevPos.set(pos);
  prevPos3d.set(pos3d);
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
