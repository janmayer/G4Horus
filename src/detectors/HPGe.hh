#pragma once

#include "Detector.hh"

namespace HPGe {

enum _type { HPGeCoaxial,
             HPGeHexagonal,
             HPGeClover
};

struct _crystal {
    G4double diameter;
    G4double length;
    G4double volume;
    G4double hole_diameter;
    G4double hole_length;
    G4double dead_layer;
};

struct _hull {
    G4double diameter;
    G4double thickness;
    G4double endcap_thickness;
    G4double padding;
    G4double length;
};

struct _spec {
    std::string id;
    _type type;
    struct _crystal crystal;
    struct _hull hull;
    bool check_overlaps;
};

class HPGe : public Detector {
  public:
    HPGe(_spec spec, std::string name);

  protected:
    _spec fSpec;

    const G4double MAX_VOLUME_DIFFERENCE = 0.01; // relative

    virtual G4LogicalVolume* BuildHull();
    virtual G4LogicalVolume* BuildHullFront();
};

} //namespace HPGe
