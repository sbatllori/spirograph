#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup the canvas
  ofSetFrameRate(3000);
  ofSetCircleResolution(72);
  ofBackground(245, 242, 235);

  //  for (int i{1}; i <= 25; i += 2) {
  //    model_.emplace_back(96, 64, i, 20, []() {
  //      ofSetColor(0);
  //      ofSetLineWidth(2);

  //      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //      ofRotateZDeg(30.f);
  //    });
  //  }

  //  for (int i{1}; i <= 8; i++) {
  //    model_.emplace_back(96, 84, i, 20, [i]() {
  //      ofSetColor(255, 0, 100);
  //      ofSetLineWidth(2);

  //      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //      ofRotateZDeg(30.f + 3.f * i);
  //    });
  //  }

  for (int i{2}; i <= 6; i++) {
    model_.emplace_back(96, 56, i, 20, []() {
      ofSetColor(255, 0, 100);
      ofSetLineWidth(2);

      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
      ofRotateZDeg(30.f);
    });
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  for (auto& spirograph : model_) spirograph.Update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  for (auto& spirograph : model_) spirograph.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    glReadBuffer(GL_FRONT);
    ofSaveScreen("screenshot_" + ofGetTimestampString() + ".png");
  }
}
