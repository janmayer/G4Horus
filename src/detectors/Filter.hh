#pragma once

#include "Detector.hh"

class Filter : public Detector {
  public:
    struct _filter {
        std::string material;
        G4double length;
    };

    explicit Filter(const Filter::_filter&, G4double width);
    Filter(const std::string& material, G4double length, G4double diameter);
};
