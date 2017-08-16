#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

extern const std::vector<std::string> detectors;

class DetectorConstruction : public G4VUserDetectorConstruction {
  public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

  private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    G4bool fCheckOverlaps;
};

#endif //DETECTORCONSTRUCTION_HH
