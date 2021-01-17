#pragma once

#include "AnalogSpirograph.h"
#include "Config.h"
#include "ofMain.h"

using SpirographSet = std::vector<soo::analog::Spirograph>;

struct ParamsText {
  std::string str_;
  ofColor color_;
  ofRectangle bbox_;

  ParamsText() = default;
  ParamsText(const std::string& str, const ofColor& color,
             const ofRectangle& bbox)
      : str_(str), color_(color), bbox_(bbox) {}
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  void Reset() {
    ResetConfig();
    ResetModel();
    ResetParamsText();
  }

  void ResetConfig();
  void ResetModel();
  void ResetParamsText();

  void DrawModel();
  void DrawParamsText();

 private:
  const bool render_mechanics_ = false;

  ofColor bg_color_;

  int config_id_;
  soo::Config config_;

  SpirographSet* active_set_;
  std::vector<SpirographSet> model_;

  ofTrueTypeFont font_;
  std::vector<ParamsText> params_texts_;
  float const kBoxOuterMargin_ = 10.f;
  float const kBoxInnerMargin_ = 10.f;
  ofRectangle box_;
};
