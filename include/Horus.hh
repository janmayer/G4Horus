#ifndef HORUS_HH
#define HORUS_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "HPGe.hh"
#include "HPGeCoaxial.hh"
#include "HPGeHexagonal.hh"

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
  void PlaceHPGe(std::string id, std::string position, G4double distance, G4double filter=0.*cm, G4bool BGO_installed=false);

  static const std::unordered_map<std::string,HPGe::_spec> specifications;
  static const std::unordered_map<std::string,coordinate> positions;


private:
  G4Transform3D* GetTransform(const coordinate &pos, const G4double &distance);
  HPGe::HPGe* GetDetector(const std::string &id, const std::string &position, const G4double filter);

  G4LogicalVolume* MotherLV;

};

#endif //HORUS_HH
