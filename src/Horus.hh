#ifndef HORUS_HH
#define HORUS_HH

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "BGO.hh"
#include "DetectorLibrary.hh"
#include "HPGe.hh"

#include <map>

class Horus {
  public:
    struct coordinate {
        double theta;
        double phi;
    };

    explicit Horus(G4LogicalVolume *theMother);
    void PlaceHPGe(const std::string &id, const std::string &position, const G4double &distance, const std::vector<Detector::_filter> &filters = {});
    void PlaceHPGe(const std::string &id, const std::string &position, const G4double &distance, const std::pair<BGO::_type, G4String> &bgo, const std::vector<Detector::_filter> &filters = {});
    G4Transform3D GetTransform(const coordinate &pos, const G4double &distance) const;

    static const std::map<std::string, coordinate> positions;

  private:
    const coordinate CoordinateForPosition(const std::string &position) const;
    G4LogicalVolume *MotherLV; // non-owning
    const DetectorLibrary detDB;
};

#endif //HORUS_HH
