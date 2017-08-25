#include "Setup.hh"
#include "G4PhysicalConstants.hh"

Setup::Setup(G4LogicalVolume *theMother, const std::map<std::string, coordinate> &positions)
    : fPositions(positions)
    , fMotherLV(theMother)
    , fDetDB(DetectorLibrary())
{
}

void Setup::PlaceDetector(const std::string &id, const std::string &position, const G4double &distance, const std::pair<BGO::_type, G4String> &bgo, const std::vector<Detector::_filter> &filters)
{
    // Place BGO
    auto thebgo = new BGO(bgo.first, bgo.second, filters);
    new G4PVPlacement(GetTransform(CoordinateForPosition(position), distance + thebgo->GetLength() / 2 - thebgo->GetOverlapLength()), // position and rotation, distance is to front of detector, but to center is expected
                      thebgo->GetLogical(), // its logical volume
                      (id + "_BGO").c_str(), // its name
                      fMotherLV, // its mother  volume
                      false, // no boolean operation
                      0, // copy number
                      true); // checking overlaps

    // and then continue to place detector
    PlaceDetector(id, position, distance);
}

void Setup::PlaceDetector(const std::string &id, const std::string &position, const G4double &distance, const std::vector<Detector::_filter> &filters)
{
    // Place HPGe
    const auto thedet = fDetDB.GetDetector(id, position, filters);
    new G4PVPlacement(GetTransform(CoordinateForPosition(position), distance + thedet->GetLength() / 2), // position and rotation, distance is to front of detector, but to center is expected
                      thedet->GetLogical(), // its logical volume
                      id, // its name
                      fMotherLV, // its mother  volume
                      false, // no boolean operation
                      0, // copy number
                      true); // checking overlaps
}

const Setup::coordinate Setup::CoordinateForPosition(const std::string &position) const
{
    auto _pos = fPositions.find(position);
    if (_pos == fPositions.end()) {
        G4Exception("Horus::PlaceHPGe", "Unknown position", FatalException, ("Position " + position + " is not a valid position").c_str());
    }
    return _pos->second;
}

G4Transform3D Setup::GetTransform(const coordinate &pos, const G4double &distance) const
{
    G4ThreeVector moveto;
    moveto.setRThetaPhi(distance, pos.theta, pos.phi);

    const auto rotation_axis = G4ThreeVector(0, 0, -1).cross(moveto).unit();
    const G4double rotation_angle = acos(G4ThreeVector(0, 0, -1).dot(moveto) / moveto.mag()) + pi;
    const G4RotationMatrix rm(rotation_axis, rotation_angle);

    return G4Transform3D(rm, moveto);
}
