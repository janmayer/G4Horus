#include "Horus.hh"

#include "BGO.hh"

#include "G4PhysicalConstants.hh"
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
  specs["73954"].crystal.diameter      = 74.*mm;
  specs["73954"].crystal.length        = (72.-2.)*mm;
  specs["73954"].crystal.dead_layer    = 2.*mm;
  specs["73954"].crystal.volume        = 304.*cm3;
  specs["73954"].crystal.hole_diameter = 5.8*mm * 2.;  // guess
  specs["73954"].crystal.hole_length   = 52.*mm; //guess
  specs["73954"].hull.diameter  = 80.*mm;
  specs["73954"].hull.padding   = 3.*mm;
  specs["73954"].hull.thickness = 1.*mm;
  specs["73954"].hull.length    = 16.*cm;


  specs["73959"].id = "73959";
  specs["73959"].type = HPGe::tCOAXIAL;
  specs["73959"].crystal.diameter      = 74.*mm;
  specs["73959"].crystal.length        = (72.-2.)*mm;
  specs["73959"].crystal.dead_layer    = 2.*mm;
  specs["73959"].crystal.volume        = 306.*cm3;
  specs["73959"].crystal.hole_diameter = 5.*mm * 2.; //guess
  specs["73959"].crystal.hole_length   = 46.6*mm; //guess
  specs["73959"].hull.diameter  = 80.*mm;
  specs["73959"].hull.padding   = 3.*mm;
  specs["73959"].hull.thickness = 1.*mm;
  specs["73959"].hull.length    = 16.*cm;


  specs["elek"].id = "elek";
  specs["elek"].type = HPGe::tCOAXIAL;
  specs["elek"].crystal.diameter      = 60.*mm; //guess
  specs["elek"].crystal.length        = (72.-2.)*mm; //guess
  specs["elek"].crystal.dead_layer    = 2.*mm;
  specs["elek"].crystal.volume        = 0.*cm3;
  specs["elek"].crystal.hole_diameter = 5.*mm * 2.; //guess
  specs["elek"].crystal.hole_length   = 46.6*mm; //guess
  specs["elek"].hull.diameter  = 80.*mm;
  specs["elek"].hull.padding   = 3.*mm;
  specs["elek"].hull.thickness = 1.*mm;
  specs["elek"].hull.length    = 16.*cm;


  specs["609502"].id = "609502";
  specs["609502"].type = HPGe::tCOAXIAL;
  specs["609502"].crystal.diameter      = 75.*mm; //guess
  specs["609502"].crystal.length        = (72.-1.)*mm; //guess
  specs["609502"].crystal.dead_layer    = 2.*mm;
  specs["609502"].crystal.volume        = 306.*cm3;
  specs["609502"].crystal.hole_diameter = 5.*mm * 2.; //guess
  specs["609502"].crystal.hole_length   = 46.6*mm; //guess
  specs["609502"].hull.diameter  = 80.*mm;
  specs["609502"].hull.padding   = 3.*mm;
  specs["609502"].hull.thickness = 1.*mm;
  specs["609502"].hull.length    = 16.*cm;


  specs["37N31120A"].id = "37N31120A";
  specs["37N31120A"].type = HPGe::tCOAXIAL;
  specs["37N31120A"].crystal.diameter      = 75.*mm;
  specs["37N31120A"].crystal.length        = 92.*mm-1.*um;
  specs["37N31120A"].crystal.dead_layer    = 1.*um;
  specs["37N31120A"].crystal.volume        = 400.*cm3;
  specs["37N31120A"].crystal.hole_diameter = 5.8*mm * 2.; //guess
  specs["37N31120A"].crystal.hole_length   = 60.*mm; //guess
  specs["37N31120A"].hull.diameter  = 85.*mm;
  specs["37N31120A"].hull.padding   = 5.*mm;
  specs["37N31120A"].hull.thickness = 1.*mm;
  specs["37N31120A"].hull.length    = 16.*cm;


  specs["25N1546B"].id = "25N1546B";
  specs["25N1546B"].type = HPGe::tCOAXIAL;
  specs["25N1546B"].crystal.diameter      = 55.9*mm;
  specs["25N1546B"].crystal.length        = 55.4*mm - 1.*um;
  specs["25N1546B"].crystal.dead_layer    = 1.*um;
  specs["25N1546B"].crystal.volume        = 135.*cm3; //guess
  specs["25N1546B"].crystal.hole_diameter = 3.*mm * 2.; //guess
  specs["25N1546B"].crystal.hole_length   = 25.*mm; //guess
  specs["25N1546B"].hull.diameter  = 65.*mm;
  specs["25N1546B"].hull.padding   = 4.*mm;
  specs["25N1546B"].hull.thickness = 1.*mm;
  specs["25N1546B"].hull.length    = 16.*cm;


  specs["miniball_capsule"].id = "miniball_capsule";
  specs["miniball_capsule"].type = HPGe::tHEXAGONAL;
  specs["miniball_capsule"].crystal.diameter   = 59.*mm;
  //specs["miniball_capsule"].crystal.diameter   = 55.*mm;
  specs["miniball_capsule"].crystal.length     = 78.*mm;
  //specs["miniball_capsule"].crystal.length     = 65.*mm;
  specs["miniball_capsule"].crystal.dead_layer = 0.5*um;
  //specs["miniball_capsule"].crystal.dead_layer = 2.mm;
  specs["miniball_capsule"].crystal.volume   = 0.*g/(5.323*g/cm3);
  specs["miniball_capsule"].crystal.hole_diameter = 10.*mm;
  specs["miniball_capsule"].crystal.hole_length   = specs["miniball_capsule"].crystal.length-15.*mm;
  specs["miniball_capsule"].hull.diameter  = 85.*mm;
  specs["miniball_capsule"].hull.padding   = 3.*mm;
  specs["miniball_capsule"].hull.thickness = 1.*mm;
  specs["miniball_capsule"].hull.length    = 12.*cm;


  specs["adjusted_capsule"].id = "adjusted_capsule";
  specs["adjusted_capsule"].type = HPGe::tHEXAGONAL;
  specs["adjusted_capsule"].crystal.diameter   = 55.*mm;
  specs["adjusted_capsule"].crystal.length     = 65.*mm;
  specs["adjusted_capsule"].crystal.dead_layer = 0.5*um;
  //specs["adjusted_capsule"].crystal.dead_layer = 2.mm;
  specs["adjusted_capsule"].crystal.volume   = 0.*g/(5.323*g/cm3);
  specs["adjusted_capsule"].crystal.hole_diameter = 10.*mm;
  specs["adjusted_capsule"].crystal.hole_length   = specs["adjusted_capsule"].crystal.length-15.*mm;
  specs["adjusted_capsule"].hull.diameter  = 85.*mm;
  specs["adjusted_capsule"].hull.padding   = 3.*mm;
  specs["adjusted_capsule"].hull.thickness = 1.*mm;
  specs["adjusted_capsule"].hull.length    = 12.*cm;


  specs["72309"] = specs["miniball_capsule"];
  specs["72309"].id = "72309";
  specs["72309"].crystal.length   = 76.5*mm; // from datasheet
  specs["72309"].crystal.volume   = 1578.*g/(5.323*g/cm3); // from datasheet
  specs["72309"].crystal.hole_length   = specs["72309"].crystal.length-15.*mm;

  specs["72341"] = specs["miniball_capsule"];
  specs["72341"].id = "72341";
  specs["72341"].crystal.length   = 78.*mm; // from datasheet
  specs["72341"].crystal.volume   = 1600.*g/(5.323*g/cm3); // from datasheet
  specs["72341"].crystal.hole_length   = specs["72341"].crystal.length-15.*mm;

  specs["72397"] = specs["miniball_capsule"];
  specs["72397"].id = "72397";
  specs["72397"].crystal.length   = 78.1*mm; // from datasheet
  specs["72397"].crystal.volume   = 1621.*g/(5.323*g/cm3); // from datasheet
  specs["72397"].crystal.hole_length   = specs["72397"].crystal.length-15.*mm;

  specs["72442"] = specs["miniball_capsule"];
  specs["72442"].id = "72442";
  specs["72442"].crystal.length   = 78.*mm; // from datasheet
  specs["72442"].crystal.volume   = 1628.*g/(5.323*g/cm3); // from datasheet
  specs["72442"].crystal.hole_length   = specs["72442"].crystal.length-15.*mm;

  specs["72802"] = specs["miniball_capsule"];
  specs["72802"].id = "72802";
  specs["72802"].crystal.length   = 77.9*mm; // from datasheet
  specs["72802"].crystal.volume   = 1585.*g/(5.323*g/cm3); // from datasheet
  specs["72802"].crystal.hole_length   = specs["72802"].crystal.length-15.*mm;

  specs["72811"] = specs["miniball_capsule"];
  specs["72811"].id = "72811";
  specs["72811"].crystal.length   = 78.*mm; // from datasheet
  specs["72811"].crystal.volume   = 1590.*g/(5.323*g/cm3); // from datasheet
  specs["72811"].crystal.hole_length   = specs["72811"].crystal.length-15.*mm;

  specs["72812"] = specs["miniball_capsule"];
  specs["72812"].id = "72812";
  specs["72812"].crystal.length   = 78.*mm; // from datasheet
  specs["72812"].crystal.volume   = 1587.*g/(5.323*g/cm3); // from datasheet
  specs["72812"].crystal.hole_length   = specs["72812"].crystal.length-15.*mm;

  specs["72827"] = specs["miniball_capsule"];
  specs["72827"].id = "72827";
  specs["72827"].crystal.length   = 78.*mm; // from datasheet
  specs["72827"].crystal.volume   = 1596.7*g/(5.323*g/cm3); // from datasheet
  specs["72827"].crystal.hole_length   = specs["72827"].crystal.length-15.*mm;

  specs["72890"] = specs["miniball_capsule"];
  specs["72890"].id = "72890";
  specs["72890"].crystal.length   = 77.9*mm; // from datasheet
  specs["72890"].crystal.volume   = 1521.*g/(5.323*g/cm3); // from datasheet
  specs["72890"].crystal.hole_length   = specs["72890"].crystal.length-15.*mm;

  specs["73002"] = specs["miniball_capsule"];
  specs["73002"].id = "73002";
  specs["73002"].crystal.length   = 78.2*mm; // from datasheet
  specs["73002"].crystal.volume   = 1531.*g/(5.323*g/cm3); // from datasheet
  specs["73002"].crystal.hole_length   = specs["73002"].crystal.length-15.*mm;

  specs["73209"] = specs["miniball_capsule"];
  specs["73209"].id = "73209";
  specs["73209"].crystal.length   = 77.*mm; // from datasheet
  specs["73209"].crystal.volume   = 1594.*g/(5.323*g/cm3); // from datasheet
  specs["73209"].crystal.hole_length   = specs["73209"].crystal.length-15.*mm;

  specs["73211"] = specs["miniball_capsule"];
  specs["73211"].id = "73211";
  specs["73211"].crystal.length   = 77.9*mm; // from datasheet
  specs["73211"].crystal.volume   = 1584.7*g/(5.323*g/cm3); // from datasheet
  specs["73211"].crystal.hole_length   = specs["73211"].crystal.length-15.*mm;

  return specs;
}

const std::unordered_map<std::string,HPGe::_spec> Horus::specifications = BuildSpecs();


Horus::Horus(G4LogicalVolume* theMother)
{
	MotherLV = theMother;
}


Horus::~Horus()
{}


void Horus::PlaceHPGe(const std::string& id, const std::string& position, const G4double& distance, const G4double& filter, BGO* const thebgo)
{
  // Place BGO
  new G4PVPlacement(  *GetTransform(CoordinateForPosition(position), distance + thebgo->GetLength()/2 - thebgo->GetOverlapLength() ), // position and rotation, distance is to front of detector, but to center is expected
                      thebgo->GetLogical(), // its logical volume
                      (id + "_BGO").c_str(), // its name
                      MotherLV,  // its mother  volume
                      false, // no boolean operation
                      0, // copy number
                      true); // checking overlaps

  // and then continue to place detector
  Horus::PlaceHPGe(id, position, distance, filter);
}


void Horus::PlaceHPGe(const std::string& id, const std::string& position, const G4double& distance, const G4double& filter)
{
  // Place Detector
  const auto thedet = GetDetector(id, position, filter);
  new G4PVPlacement(  *GetTransform(CoordinateForPosition(position), distance + thedet->GetLength()/2 ), // position and rotation, distance is to front of detector, but to center is expected
                      thedet->GetLogical(), // its logical volume
                      id, // its name
                      MotherLV,  // its mother  volume
                      false, // no boolean operation
                      0, // copy number
                      true); // checking overlaps
}


const coordinate Horus::CoordinateForPosition(const std::string& position)
{
  auto _pos = positions.find(position);
  if ( _pos == positions.end() ){
    G4Exception("Horus::PlaceHPGe", "Unknown position", FatalException, ("Position " + position + " is not a valid position in Horus").c_str() );
  }
  return _pos->second;
}


G4Transform3D* Horus::GetTransform(const coordinate &pos, const G4double &distance)
{
	G4ThreeVector* moveto = new G4ThreeVector(); moveto->setRThetaPhi(distance, pos.theta, pos.phi);

  G4ThreeVector* rotation_axis = new G4ThreeVector(0,0,-1);
                 *rotation_axis = rotation_axis->cross(*moveto);
                 *rotation_axis = rotation_axis->unit();

  G4double rotation_angle = acos( G4ThreeVector(0,0,-1).dot(*moveto)/moveto->mag() ) + pi;

  G4RotationMatrix* rm = new G4RotationMatrix();
  rm->rotate(rotation_angle,rotation_axis);

  return new G4Transform3D(*rm,*moveto);
}


HPGe::HPGe* Horus::GetDetector(const std::string &id, const std::string &position, const G4double filter)
{
  // Find spec
  auto _s = specifications.find(id);
  if ( _s == specifications.end() ){
    G4Exception("Horus::GetDetector", "Unknown detector", FatalException, ("Detector " + id + " has no specification.").c_str() );
  }
  const HPGe::_spec spec = _s->second;

  HPGe::HPGe* thedet = nullptr;
  switch (spec.type)
  {
    case HPGe::tCOAXIAL:
      thedet = new HPGe::Coaxial(spec, position, filter);
      break;
    case HPGe::tHEXAGONAL:
      thedet = new HPGe::Hexagonal(spec, position, filter);
      break;
    default:
      G4Exception("Horus::GetDetector", "Unknown detector type", FatalException, ("Detector " + id + " has an unknown type.").c_str() );
      break;
  }

  return thedet;
}
