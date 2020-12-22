#pragma once

#include "AnalogSpirograph.h"
#include "ofMain.h"
#include "ofxXmlSettings.h"

using SpirographSet = std::vector<soo::analog::Spirograph>;

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  SpirographSet* active_set_;
  std::vector<SpirographSet> model_;
};
