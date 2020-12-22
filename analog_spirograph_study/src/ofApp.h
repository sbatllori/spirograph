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
  void InitSpirographFromConfig();

 private:
  int config_id_ = 1;
  SpirographSet* active_set_;
  std::vector<SpirographSet> model_;
};
