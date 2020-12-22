#pragma once

#include "ofMain.h"

// class Spirograph {
// public:
//  Spirograph(const float ring_radius, const float wheel_radius,
//             const float num_corners,
//             const std::function<void()>& drawing_settings)
//      : num_corners_(num_corners), drawing_settings_(drawing_settings) {
//    root_.setGlobalPosition({0, 0, 0});

//    ring_.setParent(root_);
//    ring_.setPosition({ring_radius, 0, 0});

//    wheel_.setParent(ring_);
//    wheel_.setPosition({wheel_radius, 0, 0});

//    origin_ = wheel_.getGlobalPosition();
//  }

//  void update() {
//    if (!done_) {
//      previous_brush_position = wheel_.getGlobalPosition();
//      root_.rotateDeg(-1.f, {0, 0, 1});
//      ring_.rotateDeg(num_corners_, {0, 0, 1});

//      if (origin_.distance(wheel_.getGlobalPosition()) < 0.00001f) done_ =
//      true;
//    }
//  }

//  void draw() {
//    ofPushMatrix();
//    drawing_settings_();
//    ofDrawLine(previous_brush_position, wheel_.getGlobalPosition());
//    ofPopMatrix();
//  }

// private:
//  ofNode root_;
//  ofNode ring_;
//  ofNode wheel_;
//  float num_corners_;

//  ofVec3f origin_;
//  bool done_ = false;

//  ofVec3f previous_brush_position;
//  std::function<void()> drawing_settings_;
//};

struct Disk {
  float radius_;
  float center_x_;
  float angle_deg_;
  ofNode node_;

  void Rotate() { node_.rotateDeg(angle_deg_, {0, 0, 1}); }
  void Draw() {
    node_.draw();
    ofDrawCircle(node_.getGlobalPosition(), radius_);
  }
};

using DiskPtr = std::shared_ptr<Disk>;
inline DiskPtr MakeDiskPtr() { return std::make_shared<Disk>(); }

struct Spirograph {
  DiskPtr ring_;
  DiskPtr wheel_;
  DiskPtr brush_;
  ofVec3f previous_brush_position_;

  Spirograph() = default;
  Spirograph(const float ring_perimeter, const float wheel_perimeter,
             const float brush_radius) {
    // Initialize smart pointers
    ring_ = MakeDiskPtr();
    wheel_ = MakeDiskPtr();
    brush_ = MakeDiskPtr();

    // Setup geometric parameters
    // - radius
    // - rotation angle in degrees
    // - initial local center {x, 0, 0}
    ring_->radius_ = ring_perimeter / TWO_PI;
    ring_->angle_deg_ = -360.f / ring_perimeter;
    ring_->center_x_ = 0;

    wheel_->radius_ = wheel_perimeter / TWO_PI;
    wheel_->angle_deg_ = 360.f / wheel_perimeter;
    wheel_->center_x_ = ring_->radius_ - wheel_->radius_;

    brush_->radius_ = brush_radius;
    brush_->angle_deg_ = 0;
    brush_->center_x_ = wheel_->radius_ - brush_radius;

    // Setup nodes
    // - initial reltive position
    // - hierarchy
    ring_->node_.setGlobalPosition({ring_->center_x_, 0, 0});
    wheel_->node_.setPosition({wheel_->center_x_, 0, 0});
    brush_->node_.setPosition({brush_->center_x_, 0, 0});

    wheel_->node_.setParent(ring_->node_);
    brush_->node_.setParent(wheel_->node_);

    //    origin_ = brush_.node_.boom(getGlobalPosition();
  }
};

// using SpirographPtr = std::unique_ptr<Spirograph>;
// inline SpirographPtr MakeDiskPtr(const Spirograph& spirograph) {
//  return std::make_unique<Spirograph>(spirograph);
//}
// inline SpirographPtr MakeSpirographPtr(
//    const float ring_radius, const float wheel_radius, const float
//    num_corners, const std::function<void()>& drawing_settings) {
//  return std::make_unique<Spirograph>(ring_radius, wheel_radius, num_corners,
//                                      drawing_settings);
//}

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  Spirograph mechanics_;
  //  std::vector<SpirographPtr> model_;
};
