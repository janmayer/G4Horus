#ifndef HPGE_HH
#define HPGE_HH

#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

namespace HPGe
{
    enum _type {tNULL, tCOAXIAL, tHEXAGONAL};

    struct _crystal
    {
      G4double diameter;
      G4double length;
      G4double volume;
      G4double hole_diameter;
      G4double hole_length;
      G4double dead_layer;
    };

    struct _hull
    {
      G4double diameter;
      G4double thickness;
      G4double padding;
      G4double length;
    };

    struct _spec
    {
      std::string id;
      _type type;
      struct _crystal crystal;
      struct _hull hull;
    };

  class HPGe {
  public:
    HPGe()
    {};

    ~HPGe()
    {};

    G4LogicalVolume* GetLogical() { return detector_logical; }
    G4double GetLength(){ return full_length; }

  protected:
    G4LogicalVolume* detector_logical;
    G4double full_length;
    const G4double MAX_VOLUME_DIFFERENCE = 0.01; // relative
  };

} //namespace HPGe

#endif //HPGE_HH
