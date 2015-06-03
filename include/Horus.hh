#ifndef HORUS_HH
#define HORUS_HH

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "BGO.hh"
#include "DetectorLibrary.hh"

#include <map>

struct coordinate {
  double theta;
  double phi;
};

class Horus
{
public:
  Horus(G4LogicalVolume* theMother);
  ~Horus();
  void PlaceHPGe(const std::string &id, const std::string &position, const G4double &distance, const G4double &filter);
  void PlaceHPGe(const std::string &id, const std::string &position, const G4double &distance, const G4double &filter, BGO* const thebgo);
  G4Transform3D* GetTransform(const coordinate &pos, const G4double &distance);

  static const std::map<std::string, coordinate> positions;

private:
  const coordinate CoordinateForPosition(const std::string &position);
  G4LogicalVolume* MotherLV;
  DetectorLibrary* detector_library;
};

#endif //HORUS_HH
