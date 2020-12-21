#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup the canvas
  ofSetBackgroundAuto(false);
  ofSetFrameRate(6000);
  ofSetCircleResolution(72);
  const ofColor bg_color(245, 242, 235);
  ofBackground(bg_color);

  const float spacing = 11.f;
  for (int i{0}; i < 13; i++) {
    Layer layer;
    layer.spirograph_.AddNode({0, 0, 0}, -1.f);
    layer.spirograph_.AddNode({144 - spacing * i, 0, 0}, 3.f, true);
    layer.spirograph_.AddNode({96, 0, 0}, 0, true);
    layers_.push_back(layer);

    layers_.back().draw_ = [](const Layer& layer) {
      ofSetColor(0);
      ofSetLineWidth(2);
      ofDrawLine(layer.previous_brush_position_,
                 layer.spirograph_.brush_position());
    };
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  //  soo::SaveFrame(ofGetFrameNum());

  // Process the layers in order, from the inner to the outer one
  // - If the current layer is already closed, remove it from the list
  // - Then, rotate the spirograph nodes accordingly
  if (!layers_.empty()) {
    if (layers_.back().spirograph_.IsCicleStart() && !init_cicle_) {
      layers_.pop_back();
      init_cicle_ = true;
    } else {
      init_cicle_ = false;
    }
  }

  if (!layers_.empty()) {
    auto& layer = layers_.back();
    layer.previous_brush_position_ = layer.spirograph_.brush_position();

    auto& nodes = layer.spirograph_.nodes_mutable();
    std::for_each(nodes.begin(), --nodes.end(),
                  [](auto& node) { node->RotateZ(); });
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (!layers_.empty()) {
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateZDeg(30.f);
    layers_.back().draw();
    ofPopMatrix();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  //  if (key == 's') {
  //    soo::SaveFrame();
  //  }
}
