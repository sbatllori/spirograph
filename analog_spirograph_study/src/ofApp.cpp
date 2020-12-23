#include "ofApp.h"

namespace {
std::string ConfigPath(const int id) {
  return "config/config_" + std::to_string(id) + ".xml";
}
}  // namespace

void ofApp::ResetModel() {
  // Load the config
  const std::string path = ConfigPath(config_id_);
  std::cout << "[INFO] Loading config: " << path << std::endl;
  config_ = soo::Config(path);

  // Reset the model with the loaded config data
  model_.clear();
  for (const auto& set : config_.model_.sets_) {
    SpirographSet spirograph_set;
    for (const auto& brush : set.brushes_) {
      spirograph_set.emplace_back(set.ring_, set.wheel_, brush, [set, brush]() {
        ofRotateZDeg(set.static_rotation_ +
                     3.f * set.dynamic_rotation_ * brush);
        ofSetColor(set.color_);
      });
    }
    model_.push_back(spirograph_set);
  }

  // Reset the active set
  active_set_ = &(model_.back());

  // Reset the background
  ofBackground(bg_color_);
}

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(6000);
  ofSetCircleResolution(72);
  ofSetBackgroundAuto(false);

  config_id_ = 1;
  bg_color_ = ofColor(245, 242, 235);

  ResetModel();
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
  if (!model_.empty()) {
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2.f, ofGetHeight() / 3.f);
    ofSetLineWidth(2);
    for (auto& spirograph : *active_set_) spirograph.Draw();
    ofPopMatrix();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    glReadBuffer(GL_FRONT);
    ofSaveScreen("screenshot_" + ofGetTimestampString() + ".png");
  }
  if (key == 'n') {
    config_id_++;
    ResetModel();
  }
  if (key == 'p') {
    config_id_--;
    ResetModel();
  }
}
