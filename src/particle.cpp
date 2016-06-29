#include "particle.h"
#include "math.h"
#include "ofMath.h"

Particle::Particle(int scl, int cols) {
  pos = ofVec2f(ofRandom(0, 1) * ofGetWindowWidth(), ofRandom(0, 1) * ofGetWindowHeight());
  prevPos = pos;
  this->scl = scl;
  this->cols = cols;
  color = ofColor(
      ofRandom(0, 1) > 0.5 ? 255 : 0,
      ofRandom(0, 1) > 0.5 ? 255 : 0,
      ofRandom(0, 1) > 0.5 ? 255 : 0,
      25
      );
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
  try {
    ofVec2f force = vectors.at(index);
    applyForce(force);
  } catch (const std::out_of_range& e) {

  }
}

void Particle::applyForce(ofVec2f force) {
  acc += force;
}

void Particle::show(int alpha) {
  ofFill();
  ofSetColor(color.r, color.g, color.b, alpha);

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
