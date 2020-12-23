#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

namespace soo {

struct Set {
  float ring_;
  float wheel_;
  ofColor color_;
  float static_rotation_;
  int dynamic_rotation_;
  std::vector<float> brushes_;
};

struct Model {
  std::vector<Set> sets_;
};

struct Config {
  Model model_;

  Config() = default;
  Config(const std::string& path) {
    ofxXmlSettings xml_config;
    if (xml_config.loadFile(path)) {
      xml_config.pushTag("model");
      {
        // Parse multiple sets for one model
        const int num_sets = xml_config.getNumTags("set");
        for (int set_idx{0}; set_idx < num_sets; set_idx++) {
          xml_config.pushTag("set", set_idx);
          {
            Set set;
            set.ring_ = xml_config.getValue("ring", 0.f);
            set.wheel_ = xml_config.getValue("wheel", 0.f);

            xml_config.pushTag("rotation");
            {
              set.static_rotation_ = xml_config.getValue("static", 0.f);
              set.dynamic_rotation_ = xml_config.getValue("dynamic", 0.f);
            }
            xml_config.popTag();  // rotation

            xml_config.pushTag("color");
            {
              set.color_.r = xml_config.getValue("r", 0);
              set.color_.g = xml_config.getValue("g", 0);
              set.color_.b = xml_config.getValue("b", 0);
              set.color_.a = xml_config.getValue("a", 255);
            }
            xml_config.popTag();  // color

            // Parse multiple brushes for one set
            const int num_brushes = xml_config.getNumTags("brush");
            for (int i{0}; i < num_brushes; i++) {
              xml_config.pushTag("brush", i);
              set.brushes_.push_back(xml_config.getValue("radius", 1.f));
              xml_config.popTag();  // brush
            }
            // Add set to model
            model_.sets_.push_back(set);
          }
          xml_config.popTag();  // set
        }
        xml_config.popTag();  // model
      }
    }
  }
};

}  // namespace soo
