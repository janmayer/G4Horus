#include "Horus.hh"

//#include "HPGe_Hex.hh"
#include "HPGe_73954.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDManager.hh"


std::unordered_map<std::string,coordinate> Horus::positions = {
    { "Ge00", { 90.*deg,  0      } },
    { "Ge01", { 90.*deg, 55.*deg } },
    { "Ge02", { 90.*deg,125.*deg } },
    { "Ge03", { 90.*deg,180.*deg } },
    { "Ge04", { 90.*deg,235.*deg } },
    { "Ge05", { 90.*deg,305.*deg } },
    { "Ge06", {135.*deg,270.*deg } },
    { "Ge07", { 45.*deg,270.*deg } },
    { "Ge08", { 45.*deg, 90.*deg } },
    { "Ge09", {135.*deg, 90.*deg } },
    { "Ge10", {145.*deg,  0      } },
    { "Ge11", {145.*deg,180.*deg } },
    { "Ge12", { 35.*deg,180.*deg } },
    { "Ge13", { 35.*deg,  0      } }
};


Horus::Horus(G4LogicalVolume* theMother)
{
	MotherLV = theMother;
}


Horus::~Horus()
{}


void Horus::PlaceHPGe(std::string id, std::string position, G4double distance){

	// Find position
  auto _pos = positions.find(position);
  if ( _pos == positions.end() ){
    G4Exception("Horus::PlaceHPGe", "Unknown position", FatalException, ("Position " + position + " is not a valid position in Horus").c_str() );
  }
  const coordinate pos = _pos->second;


  // Detectors
  auto thedet = new HPGe_73954(position, false, 2.*mm);
  G4LogicalVolume* HPGeLV = thedet->GetLogical();

  // Place Detector
  new G4PVPlacement(  *GetTransform(pos, distance + thedet->GetLength()/2 ), // position and rotation, distance is to front of detector, but to center is expected
                      HPGeLV, // its logical volume
                      id, // its name
                      MotherLV,  // its mother  volume
                      false, // no boolean operation
                      0, // copy number
                      true); // checking overlaps

}


G4Transform3D* Horus::GetTransform(const coordinate &pos, const G4double &distance)
{
	G4ThreeVector* moveto = new G4ThreeVector(); moveto->setRThetaPhi(distance, pos.theta, pos.phi);

  // TODO: There should be an easier way to do this
  G4ThreeVector* nx = new G4ThreeVector(); nx->setRThetaPhi(1, pos.theta+90.*deg, pos.phi); nx->unit();
  G4ThreeVector* ny = new G4ThreeVector(); ny->setRThetaPhi(1, pos.theta+90.*deg, pos.phi+90.*deg); ny->unit();
  G4ThreeVector* nz = new G4ThreeVector(); nz->setRThetaPhi(1, pos.theta, pos.phi); nz->unit();
  G4RotationMatrix* rm = new G4RotationMatrix(*nx,*ny,*nz);

  return new G4Transform3D(*rm,*moveto);
}