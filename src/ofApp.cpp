#include "ofApp.h"
#include "math.h"
//--------------------------------------------------------------
void ofApp::setup(){

  //* setup gui
  gui.setup();
  gui.add(incSlider.setup("x/y increase", 0.25, 0.0001, 0.5));
  gui.add(zincSlider.setup("z increase", 0.0003, 0.00001, 0.5));
  gui.add(drawField.setup("Draw Field", false));
  gui.add(bgAlpha.setup("bg alpha", 1, 0, 255));
  gui.add(fgAlpha.setup("fg alpha", 25, 0, 255));
  gui.add(forceSlider.setup("force", 4, 1, 10));

  int width = ofGetWindowWidth();
  int height = ofGetWindowHeight();

  cols = floor(width / scl);
  rows = floor(height / scl);

  particles.reserve(NUM_PARTICLES);
  flowfield.reserve(cols * rows);

  ofLog(OF_LOG_NOTICE, "cols " + ofToString(cols));
  ofLog(OF_LOG_NOTICE, "rows " + ofToString(rows));

  for (int i = 0; i < NUM_PARTICLES; i++) {
    particles.push_back(Particle(scl, cols));
  }
  for (int i = 0; i < (cols * rows); i++) {
    ofVec2f v;
    flowfield.push_back(v);
  }
  ofLog(OF_LOG_NOTICE, "flowfield has " + ofToString(flowfield.size()) + " vectors");
  ofBackground(0);
  ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
  inc = incSlider;
  float yoff = 0;
  for (int y = 0; y < rows; y++) {
    float xoff = 0;
    for (int x = 0; x < cols; x++) {
      int index = x + y * cols;
      float a = ofNoise(xoff, yoff, zoff) * TWO_PI * forceSlider;
      ofVec2f v1(cos(a) - sin(a), sin(a) + cos(a));
      ofVec2f v = v1.getNormalized();
      flowfield[index] = v;
      xoff += inc;
    }
    yoff += inc;
  }
  zoff += zincSlider;

  for (int i = 0; i < particles.size(); i++) {
    particles[i].follow(flowfield);
    particles[i].update();
    particles[i].edges();
  }
  if(doSaveScreen)
  {
    ofSaveScreen(ofToString(ofGetFrameNum())+".png");
    doSaveScreen = false;
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofFill();
  ofSetColor(3, 3, 3, bgAlpha);
  ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
  if (drawField) {
    for (int y = 0; y < rows; y++) {
      for (int x = 0; x < cols; x++) {
        int index = x + y * cols;
        try {
          ofVec2f zero(1, 0);
          ofVec2f v = flowfield.at(index);
          ofPushMatrix();
          ofTranslate(x * scl, y * scl);
          ofRotate(zero.angle(v));
          ofNoFill();
          ofSetColor(255, 0, 255, fgAlpha);
          ofDrawLine(0, 0, scl, 0);
          ofPopMatrix();
        } catch (const std::out_of_range& e) {

        }
      }
    }
  }


  for (int i = 0; i < particles.size(); i++) {
    particles.at(i).show(fgAlpha);
  }

  gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  doSaveScreen = true;
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
