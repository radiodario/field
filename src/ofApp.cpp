#include "ofApp.h"
#include "math.h"
//--------------------------------------------------------------
void ofApp::setup(){
  int width = ofGetWindowWidth();
  int height = ofGetWindowHeight();

  cols = floor(width / scl);
  rows = floor(height / scl);

  particles.reserve(300);
  flowfield.reserve(cols * rows);

  for (int i = 0; i < 300; i++) {
    particles.push_back(Particle(scl, cols));
  }
  ofBackground(51);
}

//--------------------------------------------------------------
void ofApp::update(){
  float yoff = 0;
  for (int y = 0; y < rows; y++) {
    float xoff = 0;
    for (int x = 0; x < cols; x++) {
      int index = x + y * cols;
      float a = ofNoise(xoff, yoff, zoff) * TWO_PI * 4;
      ofVec2f v1(cos(a) - sin(a), sin(a) + cos(a));
      ofVec2f v = v1.getNormalized();
      flowfield[index] = v;
      xoff += inc;
    }
    yoff += inc;
    zoff += 0.0003;
  }

  for (int i = 0; i < particles.size(); i++) {
    particles[i].follow(flowfield);
    particles[i].update();
    particles[i].edges();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  for (int i = 0; i < particles.size(); i++) {
    particles[i].show();
  }
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
