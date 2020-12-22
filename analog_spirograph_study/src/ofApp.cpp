#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup the canvas
  ofSetFrameRate(3000);
  ofSetCircleResolution(72);
  ofBackground(245, 242, 235);

  ofxXmlSettings config;
  if (config.loadFile("config/config.xml")) {
    config.pushTag("model");

    const int num_sets = config.getNumTags("set");
    for (int k{0}; k < num_sets; k++) {
      config.pushTag("set", k);

      float ring = config.getValue("ring", 0);
      float wheel = config.getValue("wheel", 0);
      const float rotation = config.getValue("rotation", 0);
      const float scale = config.getValue("scale", 20);

      ofColor color;
      config.pushTag("color");
      color.r = config.getValue("r", 0);
      color.g = config.getValue("g", 0);
      color.b = config.getValue("b", 0);
      color.a = config.getValue("a", 255);
      config.popTag();

      SpirographSet set;

      const int num_brushes = config.getNumTags("brush");
      for (int i{0}; i < num_brushes; i++) {
        config.pushTag("brush", i);
        float brush = config.getValue("radius", 1);

        set.emplace_back(ring, wheel, brush, scale, [brush, color, rotation]() {
          ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
          ofRotateZDeg(30.f + rotation * brush);

          ofSetColor(color);
          ofSetLineWidth(2);
        });
        config.popTag();
      }
      model_.push_back(set);

      config.popTag();
    }
    config.popTag();
  }

  //  config.addTag("model");
  //  config.pushTag("model");
  //  for (int i{0}; i < 5; i++) {
  //    config.addValue("blue", i);
  //  }
  //  config.popTag();  // pop model
  //  config.saveFile("config/config.xml");

  //--------------------------------------------------------------
  //  for (int i{1}; i <= 25; i += 2) {
  //    model_1_.emplace_back(96, 64, i, 20, []() {
  //      ofSetColor(0);
  //      ofSetLineWidth(2);

  //      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //      ofRotateZDeg(30.f);
  //    });
  //  }

  //  SpirographSet set_black;
  //  for (int i{1}; i <= 23; i += 2) {
  //    set_black.spirographs_.emplace_back(96, 64, i, 20, []() {
  //      ofSetColor(0);
  //      ofSetLineWidth(2);

  //      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //      ofRotateZDeg(30.f);
  //    });
  //  }
  //  model_.push_back(set_black);

  //  SpirographSet set_red;
  //  set_red.spirographs_.emplace_back(96, 64, 25, 20, []() {
  //    ofSetColor(255, 0, 100);
  //    ofSetLineWidth(2);

  //    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //    ofRotateZDeg(30.f);
  //  });
  //  model_.push_back(set_red);

  //--------------------------------------------------------------

  //--------------------------------------------------------------
  //  for (int i{1}; i <= 8; i++) {
  //    model_1_.emplace_back(96, 84, i, 20, [i]() {
  //      ofSetColor(255, 0, 100);
  //      ofSetLineWidth(2);

  //      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //      ofRotateZDeg(30.f + 3.f * i);
  //    });
  //  }
  //--------------------------------------------------------------

  //--------------------------------------------------------------
  //  model_2_.emplace_back(96, 56, 1, 20, []() {
  //    ofSetColor(0);
  //    ofSetLineWidth(2);

  //    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //    ofRotateZDeg(30.f);
  //  });

  //  for (int i{2}; i <= 6; i++) {
  //    model_1_.emplace_back(96, 56, i, 20, []() {
  //      ofSetColor(255, 0, 100);
  //      ofSetLineWidth(2);

  //      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //      ofRotateZDeg(30.f);
  //    });
  //  }

  //  model_2_.emplace_back(96, 56, 7, 20, []() {
  //    ofSetColor(0);
  //    ofSetLineWidth(2);

  //    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //    ofRotateZDeg(30.f);
  //  });
  //--------------------------------------------------------------

  //--------------------------------------------------------------
  //  for (int i{0}; i <= 15; i += 5) {
  //    model_1_.emplace_back(96, 75, i, 20, []() {
  //      ofSetColor(0);
  //      ofSetLineWidth(2);

  //      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //      ofRotateZDeg(30.f);
  //    });
  //  }
  //--------------------------------------------------------------

  //--------------------------------------------------------------
  //  for (int i{1}; i <= 26; i++) {
  //    model_1_.emplace_back(105, 84, i, 20, [i]() {
  //      ofSetColor(50, 0, 255);
  //      ofSetLineWidth(2);

  //      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  //      ofRotateZDeg(30.f + 6.f * i);
  //    });
  //  }
  //--------------------------------------------------------------

  active_set_ = &(model_.back());
}

//--------------------------------------------------------------
void ofApp::update() {
  if (!model_.empty()) {
    // Remove each done spirograph from the active set of spirographs
    if (!active_set_->empty()) {
      active_set_->erase(
          std::remove_if(
              active_set_->begin(), active_set_->end(),
              [](const auto& spirograph) { return spirograph.done(); }),
          active_set_->end());
    }

    // If the active set of spirographs is empty (i.e. all the spirographs are
    // done), set the next set of spirographs (if any) as the active one
    if (active_set_->empty()) {
      model_.pop_back();
      if (!model_.empty()) active_set_ = &(model_.back());
    }

    // Update all the spirographs of the active set of spirographs
    for (auto& spirograph : *active_set_) spirograph.Update();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (!model_.empty())
    for (auto& spirograph : *active_set_) spirograph.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    glReadBuffer(GL_FRONT);
    ofSaveScreen("screenshot_" + ofGetTimestampString() + ".png");
  }
}
