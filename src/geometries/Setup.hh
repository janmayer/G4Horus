#pragma once

#include "BGO.hh"
#include "DetectorLibrary.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include <map>
#include <string>

class Setup {
  public:
    struct coordinate {
        double theta;
        double phi;
    };

    Setup(G4LogicalVolume *theMother, const std::map<std::string, coordinate> &positions);
    void PlaceDetector(const std::string &id, const std::string &position, const G4double &distance, const std::vector<Detector::_filter> &filters = {});
    void PlaceDetector(const std::string &id, const std::string &position, const G4double &distance, const std::pair<BGO::_type, G4String> &bgo, const std::vector<Detector::_filter> &filters = {});

    virtual G4Transform3D GetTransform(const coordinate &pos, const G4double &distance) const;
    const std::map<std::string, coordinate> fPositions;

  private:
    const coordinate CoordinateForPosition(const std::string &position) const;
    G4LogicalVolume *fMotherLV; // non-owning
    const DetectorLibrary fDetDB;
};
