#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup the canvas
  ofSetFrameRate(3000);
  ofSetCircleResolution(72);
  ofSetBackgroundAuto(false);
  ofBackground(245, 242, 235);

  //  mechanics_ = Spirograph(7 * 96.f, 7 * 64.f, 10.f);
  mechanics_ = Spirograph(7 * 96.f, 7 * 84.f, 10.f);
}

//--------------------------------------------------------------
void ofApp::update() {
  mechanics_.previous_brush_position_ =
      mechanics_.brush_->node_.getGlobalPosition();
  mechanics_.ring_->Rotate();
  mechanics_.wheel_->Rotate();
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

  ofSetColor(0);
  ofSetLineWidth(2);
  ofNoFill();

  //  mechanics_.ring_->Draw();
  //  mechanics_.wheel_->Draw();
  //  mechanics_.brush_->Draw();
  ofDrawLine(mechanics_.previous_brush_position_,
             mechanics_.brush_->node_.getGlobalPosition());

  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    glReadBuffer(GL_FRONT);
    ofSaveScreen("screenshot_" + ofGetTimestampString() + ".png");
  }
}
