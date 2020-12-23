#pragma once

#include "ofMain.h"

namespace soo {
namespace analog {

struct Disk;
using DiskPtr = std::shared_ptr<Disk>;
inline DiskPtr MakeDiskPtr() { return std::make_shared<Disk>(); }

struct Disk {
  float radius_;
  float rotation_deg_;
  ofNode node_;

  void Rotate() { node_.rotateDeg(rotation_deg_, {0, 0, 1}); }
  void Draw() {
    node_.draw();
    ofDrawCircle(node_.getGlobalPosition(), radius_);
  }
};

class Spirograph {
 public:
  Spirograph() = default;
  Spirograph(float ring_perimeter, float wheel_perimeter, float brush_radius,
             const std::function<void()>& drawing_settings)
      : drawing_settings_(drawing_settings) {
    // Scale the input parameters accordingly
    const float scale_factor = 15.f;
    ring_perimeter *= scale_factor;
    wheel_perimeter *= scale_factor;
    brush_radius = scale_factor / 3.2f * (brush_radius + 5);

    // Initialize disk smart pointers
    ring_ = MakeDiskPtr();
    wheel_ = MakeDiskPtr();
    brush_ = MakeDiskPtr();

    // Setup/define disk geometric parameters
    // - radius
    // - rotation angle in degrees
    // - initial center {x, 0, 0} (local position, relative to its parent)
    ring_->radius_ = ring_perimeter / TWO_PI;
    ring_->rotation_deg_ = -360.f / ring_perimeter;
    const float ring_init_center_x_ = 0;

    wheel_->radius_ = wheel_perimeter / TWO_PI;
    wheel_->rotation_deg_ = 360.f / wheel_perimeter;
    const float wheel_init_center_x_ = ring_->radius_ - wheel_->radius_;

    brush_->radius_ = brush_radius;
    brush_->rotation_deg_ = 0;
    const float brush_init_center_x_ = wheel_->radius_ - brush_->radius_;

    // Setup disk nodes
    // - hierarchy
    // - initial relative position
    wheel_->node_.setParent(ring_->node_);
    brush_->node_.setParent(wheel_->node_);

    ring_->node_.setGlobalPosition({ring_init_center_x_, 0, 0});
    wheel_->node_.setPosition({wheel_init_center_x_, 0, 0});
    brush_->node_.setPosition({brush_init_center_x_, 0, 0});

    // Setup global geometric spirograph parameters
    center_ = ring_->node_.getGlobalPosition();
    brush_origin_ = brush_->node_.getGlobalPosition();
    previous_brush_position_ = brush_origin_;
  }

  void Update() {
    if (!done_) {
      previous_brush_position_ = brush_->node_.getGlobalPosition();
      ring_->Rotate();
      wheel_->Rotate();

      done_ = brush_origin_.squareDistance(brush_->node_.getGlobalPosition()) <
                      0.0001f
                  ? true
                  : false;
    }
  }

  void Draw() const {
    if (!done_) {
      ofPushMatrix();
      drawing_settings_();
      ofDrawLine(previous_brush_position_, brush_->node_.getGlobalPosition());
      ofPopMatrix();
    }
  }

  void DrawDisks() {
    const auto& brush_position = brush_->node_.getGlobalPosition();

    ofPushMatrix();
    drawing_settings_();
    mechanics_path_.curveTo(brush_position);
    mechanics_path_.setFilled(false);
    mechanics_path_.setStrokeColor(ofColor::orange);
    mechanics_path_.setStrokeWidth(5);
    mechanics_path_.draw();
    ofPopMatrix();

    ofNoFill();
    ofPushMatrix();
    drawing_settings_();
    ring_->Draw();
    wheel_->Draw();
    brush_->Draw();

    ofFill();
    ofSetColor(ofColor::orange);
    ofDrawCircle(brush_position, 5.f);
    ofPopMatrix();
  }

  const auto& done() const { return done_; }

 private:
  DiskPtr ring_;
  DiskPtr wheel_;
  DiskPtr brush_;

  ofVec3f center_;
  ofVec3f brush_origin_;
  ofVec3f previous_brush_position_;
  std::function<void()> drawing_settings_;

  bool done_ = false;

  ofPath mechanics_path_;
};

}  // namespace analog
}  // namespace soo
