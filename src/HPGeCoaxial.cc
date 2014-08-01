#include "HPGeCoaxial.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"

#include <vector>
#include <string>

HPGe::Coaxial::Coaxial(const _spec spec){
  G4Material* filter_material    = G4Material::GetMaterial("G4_Cu");
  G4Material* aluhuelle_material = G4Material::GetMaterial("G4_Al");
  G4Material* kristall_material  = G4Material::GetMaterial("G4_Ge");
  G4Material* vakuum_material    = G4Material::GetMaterial("Galactic");


  G4double kristall_radius   = 74.*mm/2;
  G4double kristall_laenge   = 72.*mm;

  G4double abstand_von_kappe = 3.*mm;

  G4double aluhuelle_dicke   = 1.*mm;
  G4double aluhuelle_innerer_radius  = kristall_radius + abstand_von_kappe;
  G4double aluhuelle_radius  = kristall_radius + abstand_von_kappe + aluhuelle_dicke;
  G4double aluhuelle_laenge  = 16.*cm;

  G4double loch_radius = 5.8*mm;
  G4double loch_laenge = 52.*mm/2;

  G4double volume = 304.0*cm3;

  const G4double MAX_VOLUME_DIFFERENCE = 0.5*cm3;

  G4double filter_radius     = aluhuelle_radius;

  gesammt_laenge    = spec.filter_thickness + aluhuelle_dicke + abstand_von_kappe + aluhuelle_laenge;

  // Detektor Box
  G4Tubs* HPGeCoaxial_Box = new G4Tubs("HPGe_" + spec.name + "_Box", 0, 1.*aluhuelle_radius, gesammt_laenge/2, 0.*deg, 360.*deg);
  HPGeCoaxial_Logical = new G4LogicalVolume(HPGeCoaxial_Box, vakuum_material, "HPGe_" + spec.name + "_Logical");
  HPGeCoaxial_Logical->SetVisAttributes (G4VisAttributes::Invisible);

  // Kupfer Filter
  G4Tubs* Filter_Solid = new G4Tubs("HPGe_" + spec.name + "_Filter_Solid", 0, filter_radius, spec.filter_thickness/2, 0.*deg, 360.*deg);
  G4LogicalVolume* Filter_Logical=new G4LogicalVolume(Filter_Solid, filter_material,"HPGe_" + spec.name + "_Filter_Logical");
  G4VisAttributes* Filter_Vis = new G4VisAttributes(G4Color(1.,0.5,0));
  Filter_Vis->SetForceSolid(true);
  Filter_Logical->SetVisAttributes(Filter_Vis);
  new G4PVPlacement(0,G4ThreeVector( 0,0,-(gesammt_laenge/2-spec.filter_thickness/2) ), Filter_Logical, "HPGe_" + spec.name + "_Filter_Phys", HPGeCoaxial_Logical, false, 0);

  // Alu Hülle Front
  G4Tubs* AluHuelleF_Solid = new G4Tubs("HPGe_" + spec.name + "_AluHuelleF_Solid", 0, aluhuelle_innerer_radius, aluhuelle_dicke/2, 0.*deg, 360.*deg);
  G4LogicalVolume* AluHuelleF_Logical = new G4LogicalVolume(AluHuelleF_Solid, aluhuelle_material,"HPGe_" + spec.name + "_AluHuelleF_Logical", 0, 0, 0);
  G4VisAttributes* AluHuelleF_Vis = new G4VisAttributes(G4Color(0.2,0.3,0.2,0.5));
  AluHuelleF_Vis->SetForceSolid(true);
  AluHuelleF_Logical->SetVisAttributes(AluHuelleF_Vis);
  new G4PVPlacement(0,G4ThreeVector( 0,0,-(gesammt_laenge/2-spec.filter_thickness-aluhuelle_dicke/2)), AluHuelleF_Logical, "HPGe_" + spec.name + "_AluHuelleF", HPGeCoaxial_Logical, false,0);

  // Alu Hülle
  G4Tubs* AluHuelle_Solid=new G4Tubs("HPGe_" + spec.name + "_AluHuelle_Solid", aluhuelle_innerer_radius, aluhuelle_radius, aluhuelle_laenge/2, 0.*deg, 360.*deg);
  G4LogicalVolume* AluHuelle_Logical=new G4LogicalVolume(AluHuelle_Solid, aluhuelle_material,"HPGe_" + spec.name + "_AluHuelle_Logical", 0, 0, 0);
  G4VisAttributes* AluHuelle_Vis = new G4VisAttributes(G4Color(0.2,0.3,0.2,0.5));
  AluHuelle_Vis->SetForceSolid(true);
  AluHuelle_Logical->SetVisAttributes(AluHuelle_Vis);
  new G4PVPlacement(0,G4ThreeVector( 0,0,-(gesammt_laenge/2-spec.filter_thickness-aluhuelle_laenge/2)), AluHuelle_Logical, "HPGe_" + spec.name + "_AluHuelle", HPGeCoaxial_Logical, false,0);

  // Loch
  G4Tubs* coax_hole_s = new G4Tubs("HPGe_" + spec.name + "_Kristall_Loch_Solid", 0.*cm, loch_radius, loch_laenge, 0.*deg, 360.*deg);
  G4Tubs* Kristall_Solid=new G4Tubs("HPGe_" + spec.name + "_Kristall_Solid", 0.*cm, kristall_radius, kristall_laenge/2, 0.*deg, 360.*deg);
  G4VSolid* Kristall_Solid_mit_Loch = new G4SubtractionSolid("HPGe_" + spec.name + "_Kristall_Solid_mit_Loch", Kristall_Solid, coax_hole_s, 0, G4ThreeVector(0,0,kristall_laenge/2-5.2*cm/2));

  // Germanium Kristall
  G4LogicalVolume* Kristall_Logical=new G4LogicalVolume(Kristall_Solid_mit_Loch, kristall_material,"HPGe_" + spec.name + "_Kristall_Logical", 0, 0, 0);
  G4VisAttributes* Kristall_Vis = new G4VisAttributes(G4Color(0,0.5,1));
  Kristall_Vis->SetForceSolid(true);
  Kristall_Logical->SetVisAttributes(Kristall_Vis);
  new G4PVPlacement(0,G4ThreeVector(0,0,-(gesammt_laenge/2-spec.filter_thickness-aluhuelle_dicke-abstand_von_kappe-kristall_laenge/2)), Kristall_Logical, "HPGe_" + spec.name + "_Kristall", HPGeCoaxial_Logical, false,0);



  G4cout << spec.name << " Loch " << coax_hole_s->GetCubicVolume()/cm3 << "cm3" << G4endl;
  G4cout << spec.name << " ohne Loch " << Kristall_Solid->GetCubicVolume()/cm3 << "cm3" << G4endl;
  G4cout << spec.name << " gebaut. Kristallvolumen: " << Kristall_Solid_mit_Loch->GetCubicVolume()/cm3 << "cm3" << G4endl;
  G4cout << spec.name << " erwartetes Volumen: " << volume/cm3 << "cm3" << G4endl;

  if( fabs(Kristall_Solid_mit_Loch->GetCubicVolume()/cm3 - volume/cm3)*cm3 > MAX_VOLUME_DIFFERENCE ){
    G4ExceptionDescription msg;
    msg << "Volume of Detector " << spec.name << " does not match!" << G4endl;
    G4Exception("HPGe::Coaxial::Coaxial()", "G4Horus", JustWarning, msg);
  }

}


HPGe::Coaxial::~Coaxial()
{}
