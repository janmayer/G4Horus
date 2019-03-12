#pragma once

#include "G4Color.hh"
#include "G4PVPlacement.hh"

class CADElement {
  public:
    CADElement(std::string filename, const std::string& material, const G4Color& color);
    void Place(G4LogicalVolume* worldLV, G4RotationMatrix* rot = nullptr, const G4ThreeVector& trans = {0, 0, 0}, const bool checkOverlaps = false) const;

  private:
    char* GetCadFile(const std::string& filename) const;

    const std::string fFilename;
    G4LogicalVolume* fLV;
};
