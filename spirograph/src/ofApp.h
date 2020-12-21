#pragma once

#include "Spirograph.h"
#include "ofMain.h"

struct Layer {
  soo::Spirograph spirograph_;
  ofVec3f previous_brush_position_{0, 0, 0};
  std::function<void(const Layer&)> draw_ = [](const Layer&) {};

  void draw() const { draw_(*this); }
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  bool init_cicle_ = true;
  std::vector<Layer> layers_;
};
