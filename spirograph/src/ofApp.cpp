#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup the canvas
  ofSetFrameRate(300);
  ofSetCircleResolution(72);
  ofSetBackgroundAuto(false);
  ofBackground(245, 242, 235);

  const float spacing = 11.f;
  for (int i{0}; i < 13; i++) {
    model_.push_back(MakeSpirographPtr(144.f - spacing * i, 96.f, 3, []() {
      ofSetColor(0);
      ofSetLineWidth(2);
    }));
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  for (auto& spirograph : model_) {
    spirograph->update();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  ofRotateZDeg(30.f);
  for (const auto& spirograph : model_) {
    spirograph->draw();
  }
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    glReadBuffer(GL_FRONT);
    ofSaveScreen("screenshot_" + ofGetTimestampString() + ".png");
  }
}
