#ifndef HORUS_HH
#define HORUS_HH

#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include <string>
#include <unordered_map>

struct coordinate
{
  double theta;
  double phi;
};

class Horus
{

public:
  Horus(G4LogicalVolume* theMother);
  ~Horus();
  void PlaceHPGe(std::string id, std::string position, G4double distance);

private:
  G4Transform3D* GetTransform(const coordinate &pos, const G4double &distance);

  G4LogicalVolume* MotherLV;
  static std::unordered_map<std::string,coordinate> positions;

};

#endif //HORUS_HH
