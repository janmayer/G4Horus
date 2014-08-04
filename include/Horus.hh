#ifndef HORUS_HH
#define HORUS_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "HPGeCoaxial.hh"

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
  HPGe::Coaxial* GetDetector(const std::string &id, const std::string &position);

  G4LogicalVolume* MotherLV;
  static const std::unordered_map<std::string,HPGe::Coaxial::_spec> specifications;
  static const std::unordered_map<std::string,coordinate> positions;

};

#endif //HORUS_HH
