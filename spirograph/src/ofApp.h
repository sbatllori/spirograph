#pragma once

#include "ofMain.h"

class Spirograph {
 public:
  Spirograph(const float ring_radius, const float wheel_radius,
             const int num_corners,
             const std::function<void()>& drawing_settings)
      : num_corners_(num_corners), drawing_settings_(drawing_settings) {
    root_.setGlobalPosition({0, 0, 0});

    ring_.setParent(root_);
    ring_.setPosition({ring_radius, 0, 0});

    wheel_.setParent(ring_);
    wheel_.setPosition({wheel_radius, 0, 0});
  }

  void update() {
    previous_brush_position_ = wheel_.getGlobalPosition();
    root_.rotateDeg(-1.f, {0, 0, 1});
    ring_.rotateDeg(num_corners_, {0, 0, 1});
  }

  void draw() const {
    drawing_settings_();
    ofDrawLine(previous_brush_position_, wheel_.getGlobalPosition());
  }

 private:
  int num_corners_;
  ofNode root_;
  ofNode ring_;
  ofNode wheel_;
  ofVec3f previous_brush_position_;
  std::function<void()> drawing_settings_;
};

using SpirographPtr = std::unique_ptr<Spirograph>;
inline SpirographPtr MakeSpirographPtr(
    const float ring_radius, const float wheel_radius, const int num_corners,
    const std::function<void()>& drawing_settings) {
  return std::make_unique<Spirograph>(ring_radius, wheel_radius, num_corners,
                                      drawing_settings);
}

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  std::vector<SpirographPtr> model_;
};
