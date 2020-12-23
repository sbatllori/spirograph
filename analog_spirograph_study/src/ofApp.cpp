#include "ofApp.h"

void ofApp::InitSpirographFromConfig() {
  model_.clear();
  ofBackground(245, 242, 235);

  ofxXmlSettings config;
  if (config.loadFile("config/config_" + std::to_string(config_id_) + ".xml")) {
    config.pushTag("model");
    {
      // Load multiple sets for one model
      const int num_sets = config.getNumTags("set");
      for (int k{0}; k < num_sets; k++) {
        config.pushTag("set", k);
        {
          // Load set parameters
          float ring = config.getValue("ring", 0);
          float wheel = config.getValue("wheel", 0);
          const float rotation = config.getValue("rotation", 30);
          const float move = config.getValue("move", 0);
          const float scale = config.getValue("scale", 20);

          ofColor color;
          config.pushTag("color");
          {
            color.r = config.getValue("r", 0);
            color.g = config.getValue("g", 0);
            color.b = config.getValue("b", 0);
            color.a = config.getValue("a", 255);
          }
          config.popTag();

          SpirographSet set;
          // Load multiple brushes for one set
          const int num_brushes = config.getNumTags("brush");
          for (int i{0}; i < num_brushes; i++) {
            config.pushTag("brush", i);
            {
              // Load brush parameters
              float brush = config.getValue("radius", 1);

              // Add brush to set
              set.emplace_back(
                  ring, wheel, brush, scale, [brush, color, rotation, move]() {
                    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
                    ofRotateZDeg(rotation + 3.f * move * brush);

                    ofSetColor(color);
                    ofSetLineWidth(2);
                  });
            }
            config.popTag();
          }
          // Add set to model
          model_.push_back(set);
        }
        config.popTag();
      }
    }
    config.popTag();
  }

  active_set_ = &(model_.back());
}

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(6000);
  ofSetCircleResolution(72);
  InitSpirographFromConfig();
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
  if (key == 'n') {
    config_id_++;
    InitSpirographFromConfig();
  }
  if (key == 'p') {
    config_id_--;
    InitSpirographFromConfig();
  }
}
