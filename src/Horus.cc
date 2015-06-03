#include "Horus.hh"

#include "HPGe.hh"
#include "HPGeCoaxial.hh"
#include "HPGeHexagonal.hh"

#include "G4PhysicalConstants.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

const std::map<std::string, coordinate> Horus::positions = {
  { "Ge00", { 90.*deg,  0      } },
  { "Ge01", { 90.*deg, 55.*deg } },
  { "Ge02", { 90.*deg, 125.*deg } },
  { "Ge03", { 90.*deg, 180.*deg } },
  { "Ge04", { 90.*deg, 235.*deg } },
  { "Ge05", { 90.*deg, 305.*deg } },
  { "Ge06", {135.*deg, 270.*deg } },
  { "Ge07", { 45.*deg, 270.*deg } },
  { "Ge08", { 45.*deg, 90.*deg } },
  { "Ge09", {135.*deg, 90.*deg } },
  { "Ge10", {145.*deg,  0      } },
  { "Ge11", {145.*deg, 180.*deg } },
  { "Ge12", { 35.*deg, 180.*deg } },
  { "Ge13", { 35.*deg,  0      } }
};


Horus::Horus(G4LogicalVolume *theMother)
{
  MotherLV = theMother;
  detector_library = new DetectorLibrary();
}


Horus::~Horus()
{}


void Horus::PlaceHPGe(const std::string &id, const std::string &position, const G4double &distance, const G4double &filter, BGO *const thebgo)
{
  // Place BGO
  new G4PVPlacement(  *GetTransform(CoordinateForPosition(position), distance + thebgo->GetLength() / 2 - thebgo->GetOverlapLength() ), // position and rotation, distance is to front of detector, but to center is expected
                      thebgo->GetLogical(), // its logical volume
                      (id + "_BGO").c_str(), // its name
                      MotherLV,  // its mother  volume
                      false, // no boolean operation
                      0, // copy number
                      true); // checking overlaps

  // and then continue to place detector
  Horus::PlaceHPGe(id, position, distance, filter);
}


void Horus::PlaceHPGe(const std::string &id, const std::string &position, const G4double &distance, const G4double &filter)
{
  // Place Detector
  const auto thedet = detector_library->GetDetector(id, position, filter);
  new G4PVPlacement(  *GetTransform(CoordinateForPosition(position), distance + thedet->GetLength() / 2 ), // position and rotation, distance is to front of detector, but to center is expected
                      thedet->GetLogical(), // its logical volume
                      id, // its name
                      MotherLV,  // its mother  volume
                      false, // no boolean operation
                      0, // copy number
                      true); // checking overlaps
}


const coordinate Horus::CoordinateForPosition(const std::string &position)
{
  auto _pos = positions.find(position);
  if ( _pos == positions.end() ) {
    G4Exception("Horus::PlaceHPGe", "Unknown position", FatalException, ("Position " + position + " is not a valid position in Horus").c_str() );
  }
  return _pos->second;
}


G4Transform3D *Horus::GetTransform(const coordinate &pos, const G4double &distance)
{
  G4ThreeVector *moveto = new G4ThreeVector(); moveto->setRThetaPhi(distance, pos.theta, pos.phi);

  G4ThreeVector *rotation_axis = new G4ThreeVector(0, 0, -1);
  *rotation_axis = rotation_axis->cross(*moveto);
  *rotation_axis = rotation_axis->unit();

  G4double rotation_angle = acos( G4ThreeVector(0, 0, -1).dot(*moveto) / moveto->mag() ) + pi;

  G4RotationMatrix *rm = new G4RotationMatrix();
  rm->rotate(rotation_angle, rotation_axis);

  return new G4Transform3D(*rm, *moveto);
}
