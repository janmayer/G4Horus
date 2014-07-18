#include "HPGe_73954.hh"

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

#include <vector>
#include <string>

HPGe_73954::HPGe_73954(std::string DetectorName, G4bool BGO_is_Used, G4double Filter_Dicke){

  G4Material* Filter_Material    = G4Material::GetMaterial("G4_Cu");
  G4Material* AluHuelle_Material = G4Material::GetMaterial("G4_Al");
  G4Material* Kristall_Material  = G4Material::GetMaterial("G4_Ge");
  G4Material* Vakuum_Material    = G4Material::GetMaterial("Galactic");


  G4double Kristall_Radius   = 74.*mm/2;
  G4double Kristall_Laenge   = 72.*mm;
  G4double Abstand_von_Kappe = 3.*mm;
  G4double AluHuelle_Dicke   = 1.*mm;

  G4double AluHuelle_Innerer_Radius  = Kristall_Radius + Abstand_von_Kappe;
  G4double AluHuelle_Radius  = Kristall_Radius + Abstand_von_Kappe + AluHuelle_Dicke;
  G4double AluHuelle_Laenge  = 16.*cm;

  G4double Filter_Radius     = AluHuelle_Radius;

  Gesammt_Laenge    = Filter_Dicke + AluHuelle_Dicke + Abstand_von_Kappe + AluHuelle_Laenge;

  // Detektor Box
  G4Tubs* HPGe_73954_Box = new G4Tubs("HPGe_" + DetectorName + "_Box", 0, 1.*AluHuelle_Radius, Gesammt_Laenge/2, 0.*deg, 360.*deg);
  //G4Box* HPGe_73954_Box = new G4Box("HPGe_" + DetectorName + "_Box", 1.2*AluHuelle_Radius, 1.2*AluHuelle_Radius, Gesammt_Laenge/2);
  HPGe_73954_Logical    = new G4LogicalVolume(HPGe_73954_Box, Vakuum_Material, "HPGe_" + DetectorName + "_Logical");
  //G4VisAttributes* HPGe_73954VisAtt = new G4VisAttributes(G4Color(1,1,1));
  //HPGe_73954_Logical->SetVisAttributes(HPGe_73954VisAtt);
  //HPGe_73954_Logical->SetVisAttributes (G4VisAttributes::Invisible);

  // Kupfer Filter
  G4Tubs* Filter_Solid = new G4Tubs("HPGe_" + DetectorName + "_Filter_Solid", 0, Filter_Radius, Filter_Dicke/2, 0.*deg, 360.*deg);
  G4LogicalVolume* Filter_Logical=new G4LogicalVolume(Filter_Solid, Filter_Material,"HPGe_" + DetectorName + "_Filter_Logical");
  G4VisAttributes* Filter_Vis = new G4VisAttributes(G4Color(1.,0.5,0));
  Filter_Vis->SetForceSolid(true);
  Filter_Logical->SetVisAttributes(Filter_Vis);
  new G4PVPlacement(0,G4ThreeVector( 0,0,-(Gesammt_Laenge/2-Filter_Dicke/2) ), Filter_Logical, "HPGe_" + DetectorName + "_Filter_Phys", HPGe_73954_Logical, false, 0);

  // Alu Hülle Front
  G4Tubs* AluHuelleF_Solid = new G4Tubs("HPGe_" + DetectorName + "_AluHuelleF_Solid", 0, AluHuelle_Innerer_Radius, AluHuelle_Dicke/2, 0.*deg, 360.*deg);
  G4LogicalVolume* AluHuelleF_Logical = new G4LogicalVolume(AluHuelleF_Solid, AluHuelle_Material,"HPGe_" + DetectorName + "_AluHuelleF_Logical", 0, 0, 0);
  G4VisAttributes* AluHuelleF_Vis = new G4VisAttributes(G4Color(0.2,0.3,0.2,0.5));
  AluHuelleF_Vis->SetForceSolid(true);
  AluHuelleF_Logical->SetVisAttributes(AluHuelleF_Vis);
  new G4PVPlacement(0,G4ThreeVector( 0,0,-(Gesammt_Laenge/2-Filter_Dicke-AluHuelle_Dicke/2)), AluHuelleF_Logical, "HPGe_" + DetectorName + "_AluHuelleF", HPGe_73954_Logical, false,0);

  // Alu Hülle
  G4Tubs* AluHuelle_Solid=new G4Tubs("HPGe_" + DetectorName + "_AluHuelle_Solid", AluHuelle_Innerer_Radius, AluHuelle_Radius, AluHuelle_Laenge/2, 0.*deg, 360.*deg);
  G4LogicalVolume* AluHuelle_Logical=new G4LogicalVolume(AluHuelle_Solid, AluHuelle_Material,"HPGe_" + DetectorName + "_AluHuelle_Logical", 0, 0, 0);
  G4VisAttributes* AluHuelle_Vis = new G4VisAttributes(G4Color(0.2,0.3,0.2,0.5));
  AluHuelle_Vis->SetForceSolid(true);
  AluHuelle_Logical->SetVisAttributes(AluHuelle_Vis);
  new G4PVPlacement(0,G4ThreeVector( 0,0,-(Gesammt_Laenge/2-Filter_Dicke-AluHuelle_Laenge/2)), AluHuelle_Logical, "HPGe_" + DetectorName + "_AluHuelle", HPGe_73954_Logical, false,0);

  // Germanium Kristall
  G4Tubs* Kristall_Solid=new G4Tubs("HPGe_" + DetectorName + "_Kristall1_Solid", 0.*cm, Kristall_Radius, Kristall_Laenge/2, 0.*deg, 360.*deg);
  G4LogicalVolume* Kristall_Logical=new G4LogicalVolume(Kristall_Solid, Kristall_Material,"HPGe_" + DetectorName + "_Kristall_Logical", 0, 0, 0);
  G4VisAttributes* Kristall_Vis = new G4VisAttributes(G4Color(0,0.5,1));
  Kristall_Vis->SetForceSolid(true);
  Kristall_Logical->SetVisAttributes(Kristall_Vis);
  new G4PVPlacement(0,G4ThreeVector(0,0,-(Gesammt_Laenge/2-Filter_Dicke-AluHuelle_Dicke-Abstand_von_Kappe-Kristall_Laenge/2)), Kristall_Logical, "HPGe_" + DetectorName + "_Kristall", HPGe_73954_Logical, false,0);

  G4cout << DetectorName << " gebaut. Kristallvolumen: " << Kristall_Solid->GetCubicVolume()/cm3 << "cm3" << G4endl;
}

HPGe_73954::~HPGe_73954(){
  ;
}
