#include "ofApp.h"
#include "math.h"
//--------------------------------------------------------------
void ofApp::setup(){
  receive.setup(12345);
  ofSetFrameRate(60);
  buffer.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA);
  imageSaver.allocate(ofGetWindowWidth(), ofGetWindowHeight(), OF_IMAGE_COLOR_ALPHA);
  send.setName("Field");
  //* setup gui
  gui.setup();
  gui.add(incSlider.set("x/y increase", 0.25, 0.0001, 0.5));
  gui.add(zincSlider.set("z increase", 0.0003, 0.00001, 0.02));
  gui.add(drawField.setup("Draw Field", false));
  gui.add(onSphere.setup("Draw Sphere", true));
  gui.add(bgAlpha.set("bg alpha", 1, 0, 255));
  gui.add(fgAlpha.set("fg alpha", 25, 0, 255));
  gui.add(forceSlider.set("force", 4, 1, 10));
  gui.add(maxSpeedSlider.set("max speed", 4, 1, 10));
  gui.add(red.set("red", 255, 0, 255));
  gui.add(green.set("green", 255, 0, 255));
  gui.add(blue.set("blue", 255, 0, 255));
  gui.add(randomicity.set("randomicity", 1, 0, 1));

  gui.add(sendToSyphon.setup("Send to Syphon", true));

  int width = ofGetWindowWidth();
  int height = ofGetWindowHeight();

  cols = floor(width / scl)+1;
  rows = floor(height / scl)+1;

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
  while (receive.hasWaitingMessages()) {
    ofxOscMessage m;
    receive.getNextMessage(&m);
    string msgAddress = m.getAddress();

    ofLog(OF_LOG_NOTICE, msgAddress + " " + ofToString(m.getArgAsFloat(0)));
    if (msgAddress == "/2/fader1") {
        red =((int) (m.getArgAsFloat(0) * 255));
    }

    if (msgAddress == "/2/fader2") {
        green = ((int) (m.getArgAsFloat(0) * 255));
    }
    if (msgAddress == "/2/fader3") {
        blue = ((int) (m.getArgAsFloat(0) * 255));
    }

    if (msgAddress == "/2/fader8") {
      randomicity = m.getArgAsFloat(0);
    }

    if (msgAddress == "/2/fader4") {
      fgAlpha = ((int) (m.getArgAsFloat(0) * 255));
    }
    if (msgAddress == "/2/fader5") {
      bgAlpha = ((int) (m.getArgAsFloat(0) * 255));
    }

    if (msgAddress == "/1/xy") {
      incSlider = m.getArgAsFloat(0) * 0.5;
      zincSlider = m.getArgAsFloat(1) * 0.02;
    }

    if (msgAddress == "/1/fader1") {
      forceSlider = (int) (m.getArgAsFloat(0) * 10);
    }
    if (msgAddress == "/1/fader2") {
      maxSpeedSlider = (int) (m.getArgAsFloat(0) * 10);
    }
  }
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
    ofPixels pixels;
    buffer.readToPixels(pixels);
    imageSaver.setFromPixels(pixels, ofGetWindowWidth(), ofGetWindowHeight(), OF_IMAGE_COLOR_ALPHA, true);
    imageSaver.save(ofToString(ofGetFrameNum())+".png");
    doSaveScreen = false;
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  buffer.begin();
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

  if (onSphere) {
    camera.begin();
    for (int i = 0; i < particles.size(); i++) {
      particles.at(i).show3d(fgAlpha);
    }
    camera.end();
  }
  else {
    for (int i = 0; i < particles.size(); i++) {
      particles.at(i).show(fgAlpha);
    }
  }
  buffer.end();

  buffer.draw(0, 0);
  if (sendToSyphon) {
    tex = buffer.getTexture();
    send.publishTexture(&tex);
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
void ofApp::mouseMoved(int x, int y){

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
