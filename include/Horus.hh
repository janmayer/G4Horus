#ifndef HORUS_HH
#define HORUS_HH

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"


#include "HPGe.hh"
#include "HPGeCoaxial.hh"
#include "HPGeHexagonal.hh"
#include "BGO.hh"

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
  void PlaceHPGe(const std::string& id, const std::string& position, const G4double& distance, const G4double& filter);
  void PlaceHPGe(const std::string& id, const std::string& position, const G4double& distance, const G4double& filter, BGO* const thebgo);
  G4Transform3D* GetTransform(const coordinate &pos, const G4double &distance);

  static const std::unordered_map<std::string,HPGe::_spec> specifications;
  static const std::unordered_map<std::string,coordinate> positions;

private:
  const coordinate CoordinateForPosition(const std::string& position);
  HPGe::HPGe* GetDetector(const std::string &id, const std::string &position, const G4double filter);

  G4LogicalVolume* MotherLV;

};

#endif //HORUS_HH
