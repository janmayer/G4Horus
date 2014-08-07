#include "Horus.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDManager.hh"

const std::unordered_map<std::string,coordinate> Horus::positions = {
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


std::unordered_map<std::string,HPGe::_spec> BuildSpecs(){
  std::unordered_map<std::string,HPGe::_spec> specs;

  specs["73954"].id = "73954";
  specs["73954"].type = HPGe::tCOAXIAL;
  specs["73954"].crystal.diameter = 74.*mm;
  specs["73954"].crystal.length   = 72.*mm;
  specs["73954"].crystal.volume   = 304.*cm3;
  specs["73954"].crystal.hole_diameter = 5.8*mm * 2.;  // guess
  specs["73954"].crystal.hole_length   = 52.*mm; //guess
  specs["73954"].hull.diameter   = 80.*mm;
  specs["73954"].hull.padding   = 3.*mm;
  specs["73954"].hull.thickness = 1.*mm;
  specs["73954"].hull.length    = 16.*cm;


  specs["73959"].id = "73959";
  specs["73959"].type = HPGe::tCOAXIAL;
  specs["73959"].crystal.diameter = 74.*mm;
  specs["73959"].crystal.length   = 72.*mm;
  specs["73959"].crystal.volume   = 306.*cm3;
  specs["73959"].crystal.hole_diameter = 5.*mm * 2.; //guess
  specs["73959"].crystal.hole_length   = 46.6*mm; //guess
  specs["73959"].hull.diameter  = 80.*mm;
  specs["73959"].hull.padding   = 3.*mm;
  specs["73959"].hull.thickness = 1.*mm;
  specs["73959"].hull.length    = 16.*cm;


  specs["37N31120A"].id = "37N31120A";
  specs["37N31120A"].type = HPGe::tCOAXIAL;
  specs["37N31120A"].crystal.diameter = 75.*mm;
  specs["37N31120A"].crystal.length   = 92.*mm;
  specs["37N31120A"].crystal.volume   = 400.*cm3;
  specs["37N31120A"].crystal.hole_diameter = 5.8*mm * 2.; //guess
  specs["37N31120A"].crystal.hole_length   = 60.*mm; //guess
  specs["37N31120A"].hull.diameter  = 85.*mm;
  specs["37N31120A"].hull.padding   = 5.*mm;
  specs["37N31120A"].hull.thickness = 1.*mm;
  specs["37N31120A"].hull.length    = 16.*cm;


  specs["25N1546B"].id = "25N1546B";
  specs["25N1546B"].type = HPGe::tCOAXIAL;
  specs["25N1546B"].crystal.diameter = 55.9*mm;
  specs["25N1546B"].crystal.length   = 55.4*mm;
  specs["25N1546B"].crystal.volume   = 135.*cm3; //guess
  specs["25N1546B"].crystal.hole_diameter = 3.*mm * 2.; //guess
  specs["25N1546B"].crystal.hole_length   = 25.*mm; //guess
  specs["25N1546B"].hull.diameter  = 65.*mm;
  specs["25N1546B"].hull.padding   = 4.*mm;
  specs["25N1546B"].hull.thickness = 1.*mm;
  specs["25N1546B"].hull.length    = 16.*cm;


  specs["generic_hex"].type = HPGe::tHEXAGONAL;
  specs["generic_hex"].hull.diameter  = 85.*mm;
  specs["generic_hex"].hull.padding   = 3.*mm;
  specs["generic_hex"].hull.thickness = 1.*mm;
  specs["generic_hex"].hull.length    = 16.*cm;

  specs["72309"] = specs["generic_hex"];
  specs["72309"].id = "72309";
  specs["72309"].crystal.diameter = 42.*mm*2.; // guessed to match weight
  specs["72309"].crystal.length   = 76.5*mm; // from datasheet
  specs["72309"].crystal.volume   = 1578.*g/(5.323*g/cm3); // from datasheet

  specs["72341"] = specs["generic_hex"];
  specs["72341"].id = "72341";
  specs["72341"].crystal.diameter = 42.*mm*2.; // guessed to match weight
  specs["72341"].crystal.length   = 78.*mm; // from datasheet
  specs["72341"].crystal.volume   = 1600.*g/(5.323*g/cm3); // from datasheet

  specs["72397"] = specs["generic_hex"];
  specs["72397"].id = "72397";
  specs["72397"].crystal.diameter = 42.*mm*2.; // guessed to match weight
  specs["72397"].crystal.length   = 78.1*mm; // from datasheet
  specs["72397"].crystal.volume   = 1621.*g/(5.323*g/cm3); // from datasheet

  specs["72442"] = specs["generic_hex"];
  specs["72442"].id = "72442";
  specs["72442"].crystal.diameter = 42.1*mm*2.; // guessed to match weight
  specs["72442"].crystal.length   = 78.*mm; // from datasheet
  specs["72442"].crystal.volume   = 1628.*g/(5.323*g/cm3); // from datasheet

  specs["72802"] = specs["generic_hex"];
  specs["72802"].id = "72802";
  specs["72802"].crystal.diameter = 41.8*mm*2.; // guessed to match weight
  specs["72802"].crystal.length   = 77.9*mm; // from datasheet
  specs["72802"].crystal.volume   = 1585.*g/(5.323*g/cm3); // from datasheet

  specs["72811"] = specs["generic_hex"];
  specs["72811"].id = "72811";
  specs["72811"].crystal.diameter = 42.*mm*2.; // guessed to match weight
  specs["72811"].crystal.length   = 78.*mm; // from datasheet
  specs["72811"].crystal.volume   = 1590.*g/(5.323*g/cm3); // from datasheet

  specs["72812"] = specs["generic_hex"];
  specs["72812"].id = "72812";
  specs["72812"].crystal.diameter = 41.8*mm*2.; // guessed to match weight
  specs["72812"].crystal.length   = 78.*mm; // from datasheet
  specs["72812"].crystal.volume   = 1587.*g/(5.323*g/cm3); // from datasheet

  specs["72827"] = specs["generic_hex"];
  specs["72827"].id = "72827";
  specs["72827"].crystal.diameter = 42.*mm*2.; // guessed to match weight
  specs["72827"].crystal.length   = 78.*mm; // from datasheet
  specs["72827"].crystal.volume   = 1596.7*g/(5.323*g/cm3); // from datasheet

  specs["72980"] = specs["generic_hex"];
  specs["72980"].id = "72980";
  specs["72980"].crystal.diameter = 41.*mm*2.; // guessed to match weight
  specs["72980"].crystal.length   = 77.9*mm; // from datasheet
  specs["72980"].crystal.volume   = 1521.*g/(5.323*g/cm3); // from datasheet

  specs["73002"] = specs["generic_hex"];
  specs["73002"].id = "73002";
  specs["73002"].crystal.diameter = 40.8*mm*2.; // guessed to match weight
  specs["73002"].crystal.length   = 78.2*mm; // from datasheet
  specs["73002"].crystal.volume   = 1531.*g/(5.323*g/cm3); // from datasheet

  specs["73209"] = specs["generic_hex"];
  specs["73209"].id = "73209";
  specs["73209"].crystal.diameter = 42.*mm*2.; // guessed to match weight
  specs["73209"].crystal.length   = 77.*mm; // from datasheet
  specs["73209"].crystal.volume   = 1594.*g/(5.323*g/cm3); // from datasheet

  specs["73211"] = specs["generic_hex"];
  specs["73211"].id = "73211";
  specs["73211"].crystal.diameter = 41.8*mm*2.; // guessed to match weight
  specs["73211"].crystal.length   = 77.9*mm; // from datasheet
  specs["73211"].crystal.volume   = 1584.7*g/(5.323*g/cm3); // from datasheet

  return specs;
}

const std::unordered_map<std::string,HPGe::_spec> Horus::specifications = BuildSpecs();



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

  auto thedet = GetDetector(id, position);

  // Place Detector
  new G4PVPlacement(  *GetTransform(pos, distance + thedet->GetLength()/2 ), // position and rotation, distance is to front of detector, but to center is expected
                      thedet->GetLogical(), // its logical volume
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


HPGe::HPGe* Horus::GetDetector(const std::string &id, const std::string &position)
{
  // Find spec
  auto _s = specifications.find(id);
  if ( _s == specifications.end() ){
    G4Exception("Horus::GetDetector", "Unknown detector", FatalException, ("Detector " + id + " has no specification.").c_str() );
  }
  const HPGe::_spec spec = _s->second;

  HPGe::HPGe* thedet;
  switch (spec.type)
  {
    case HPGe::tCOAXIAL:
      thedet = new HPGe::Coaxial(spec, position, 2.*mm);
      break;
    case HPGe::tHEXAGONAL:
      thedet = new HPGe::Hexagonal(spec, position, 2.*mm);
      break;
    default:
      G4Exception("Horus::GetDetector", "Unknown detector type", FatalException, ("Detector " + id + " has an unknown type.").c_str() );
      break;
  }

  return thedet;
}
