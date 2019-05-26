#include "Setup.hh"
#include "G4PhysicalConstants.hh"
#include <numeric>
#include <utility>

Setup::Setup(G4LogicalVolume* theMother, std::map<std::string, coordinate> positions)
    : fPositions(std::move(positions))
    , fMotherLV(theMother)
    , fDetDB(DetectorLibrary())
{
}

void Setup::Place(G4LogicalVolume* logicalVolume, const std::string& name, const std::string& position, const G4double distance)
{
    const auto transform = GetTransform(CoordinateForPosition(position), distance);
    new G4PVPlacement(transform, logicalVolume, name, fMotherLV, false, 0, true);
}

void Setup::PlaceDetector(const std::string& id, const std::string& position, G4double distance, const std::vector<Filter::_filter>& filters)
{
    // Place HPGe
    const auto thedet = fDetDB.GetDetector(id, position);

    for (const auto& f : filters) {
        const Filter filter {f, thedet->GetWidth()};
        Place(filter.GetLogical(), position + "_filter_" + f.material, position, distance + filter.GetOffset());
        distance += f.length;
    }

    Place(thedet->GetLogical(), position, position, distance + thedet->GetOffset());
}

void Setup::PlaceDetector(const BGO::_type& bgo, const std::string& position, G4double distance, const std::vector<Filter::_filter>& filters)
{
    // Place BGO
    const auto thebgo = new BGO(bgo, position);

    for (const auto& f : filters) {
        const Filter filter {f, thebgo->GetWidth()};
        Place(filter.GetLogical(), position + "_BGO_filter_" + f.material, position, distance + filter.GetOffset());
        distance += f.length;
    }

    Place(thebgo->GetLogical(), position, position, distance + thebgo->GetOffset());
}

const Setup::coordinate Setup::CoordinateForPosition(const std::string& position) const
{
    auto _pos = fPositions.find(position);
    if (_pos == fPositions.end()) {
        G4Exception("Setup::PlaceDetector", "Unknown position", FatalException, ("Position " + position + " is not a valid position").c_str());
    }
    return _pos->second;
}

G4Transform3D Setup::GetTransform(const coordinate& pos, const G4double& distance) const
{
    G4ThreeVector moveto;
    moveto.setRThetaPhi(distance, pos.theta, pos.phi);

    const auto rotation_axis = G4ThreeVector(0, 0, -1).cross(moveto).unit();
    const G4double rotation_angle = acos(G4ThreeVector(0, 0, -1).dot(moveto) / moveto.mag()) + pi;
    const G4RotationMatrix rm(rotation_axis, rotation_angle);

    return G4Transform3D(rm, moveto);
}
