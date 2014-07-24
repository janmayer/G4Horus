#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    G4bool  fCheckOverlaps;
};

#endif //DETECTORCONSTRUCTION_HH
