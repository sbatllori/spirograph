#include "ofApp.h"
#include "soo_export.h"

namespace {
std::string ConfigPath(const int id) {
  return "config/config_" + std::to_string(id) + ".xml";
}
}  // namespace

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(6000);
  ofSetCircleResolution(72);
  ofSetBackgroundAuto(render_mechanics_);

  config_id_ = 0;
  bg_color_ = ofColor(245, 242, 235);
  font_.load("Batang.ttf", 18, true, true, true);

  Reset();
}

//--------------------------------------------------------------
void ofApp::update() {
  if (!model_.empty()) {
    //    soo::SaveFrame(ofGetFrameNum());

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
    DrawModel();
    DrawParamsText();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
  if (key == 'n') {
    config_id_++;
    Reset();
  }
  if (key == 'p') {
    config_id_--;
    Reset();
  }
}

void ofApp::ResetConfig() {
  const std::string path = ConfigPath(config_id_);
  std::cout << "[INFO] Loading config: " << path << std::endl;
  config_ = soo::Config(path);
}

void ofApp::ResetModel() {
  model_.clear();

  // Parse the config to get the relevant parameters for the model generation,
  // i.e. parameters for each spirograph set
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

void ofApp::ResetParamsText() {
  params_texts_.clear();

  // Parse the config to get the relevant parameters for the text generation
  // - string holding the parameters of a set
  // - color of the set to display the text with
  // - bounding box of the string to place the text accordingly
  for (const auto& set : config_.model_.sets_) {
    std::string str = "";
    str += std::to_string(int(set.ring_)) + "\t";
    str += std::to_string(int(set.wheel_)) + "\t";

    for (const auto& brush : set.brushes_) {
      str += std::to_string(int(brush)) + "-";
    }
    str.pop_back();

    str += ", R " + std::to_string(int(set.static_rotation_));
    str += ":" + std::to_string(int(set.dynamic_rotation_));

    params_texts_.emplace_back(str, set.color_,
                               font_.getStringBoundingBox(str, 0, 0));
  }

  // Define the box enclosing the parameters text
  box_.x = std::min_element(params_texts_.begin(), params_texts_.end(),
                            [](const auto& left, const auto& right) {
                              return left.bbox_.x < right.bbox_.x;
                            })
               ->bbox_.x;

  box_.y = std::min_element(params_texts_.begin(), params_texts_.end(),
                            [](const auto& left, const auto& right) {
                              return left.bbox_.y < right.bbox_.y;
                            })
               ->bbox_.y;

  box_.width = std::max_element(params_texts_.begin(), params_texts_.end(),
                                [](const auto& left, const auto& right) {
                                  return left.bbox_.width < right.bbox_.width;
                                })
                   ->bbox_.width;

  box_.height = 0;
  std::for_each(params_texts_.begin(), params_texts_.end(),
                [this](const auto& params_text) {
                  box_.height += params_text.bbox_.height;
                });

  box_.y -= kBoxOuterMargin_;
  box_.width += 2 * kBoxOuterMargin_;
  box_.height += 2 * kBoxOuterMargin_;
  box_.height += (params_texts_.size() - 1) * kBoxInnerMargin_;
}

void ofApp::DrawModel() {
  ofPushMatrix();
  {
    ofTranslate(ofGetWidth() / 2.f, 2.f * ofGetHeight() / 5.f);
    ofScale(1.5);

    ofSetLineWidth(2);
    for (auto& spirograph : *active_set_)
      render_mechanics_ ? spirograph.DrawDisks() : spirograph.Draw();
  }
  ofPopMatrix();
}

void ofApp::DrawParamsText() {
  ofPushMatrix();
  {
    ofTranslate(ofGetWidth() / 2.f, 6.f * ofGetHeight() / 7.f);

    ofPushMatrix();
    {
      ofTranslate(-box_.width / 2, -box_.height / 2);
      // Draw the box
      ofNoFill();
      ofSetColor(0);
      ofSetLineWidth(2);
      ofDrawRectangle(box_);

      // Draw the parameters inside the box
      for (unsigned long i{0}; i < params_texts_.size(); i++) {
        const auto& params_text = params_texts_[i];
        ofSetColor(params_text.color_);
        font_.drawString(params_text.str_, kBoxOuterMargin_,
                         i * (params_text.bbox_.height + kBoxInnerMargin_));
      }
    }
    ofPopMatrix();
  }
  ofPopMatrix();
}
