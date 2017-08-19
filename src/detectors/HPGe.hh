#ifndef HPGE_HH
#define HPGE_HH

#include "Detector.hh"
#include "G4LogicalVolume.hh"

namespace HPGe {

enum _type { tCOAXIAL,
             tHEXAGONAL };

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
    HPGe(const _spec& spec, const std::string& name, const std::vector<Detector::_filter>& filters);

  protected:
    _spec fSpec;
    G4double fFilterLength;

    const G4double MAX_VOLUME_DIFFERENCE = 0.01; // relative

    G4LogicalVolume* BuildHull();
    G4LogicalVolume* BuildHullFront();
};

} //namespace HPGe

#endif //HPGE_HH
