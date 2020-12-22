#pragma once

#include "AnalogSpirograph.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  std::vector<soo::analog::Spirograph> model_;
};
