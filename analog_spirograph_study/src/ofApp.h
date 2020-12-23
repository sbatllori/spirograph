#pragma once

#include "AnalogSpirograph.h"
#include "Config.h"
#include "ofMain.h"

using SpirographSet = std::vector<soo::analog::Spirograph>;

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  void ResetModel();

 private:
  ofColor bg_color_;

  int config_id_;
  soo::Config config_;

  SpirographSet* active_set_;
  std::vector<SpirographSet> model_;
};
