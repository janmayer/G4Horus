#include "AstroTargetkammer.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include <vector>
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


AstroTargetkammer::AstroTargetkammer(G4LogicalVolume* expHall_log)
{

  //G4Material* Vacuum = G4Material::GetMaterial("Galactic");
  G4Material* Aluminium = G4Material::GetMaterial("G4_Al");
  //G4Material* Germanium = G4Material::GetMaterial("G4_Ge");
  //G4Material* Blei = G4Material::GetMaterial("G4_Pb");
  G4Material* Tantalum = G4Material::GetMaterial("G4_Ta");
  G4Material* PET = G4Material::GetMaterial("PET");


// Einbinden der Astro-Targetkammer

G4double Chamber_Corpus_Radius = 55./2*mm;
G4double Chamber_Corpus_Thickness = 1.*mm;
G4double Chamber_Corpus_Height = 40.*mm;

G4RotationMatrix* Chamber_rm = new G4RotationMatrix();
Chamber_rm->rotateY(90.*deg);

G4Tubs* TargetChamber = new G4Tubs("TargetChamber", Chamber_Corpus_Radius, Chamber_Corpus_Radius+Chamber_Corpus_Thickness, Chamber_Corpus_Height/2., 0.*deg, 360.*deg);


//Subtraction Volumes for Beam Pipes

G4double Pipe_Front_Radius = 1.*cm;
G4double Pipe_Front_Thickness = 1.*mm;
G4double Pipe_Front_Length = 42.5*cm;
G4double Pipe_Front_z = -(Pipe_Front_Length/2+Chamber_Corpus_Radius+17.*mm);

G4Tubs* Pipe_Front_Sub_Solid = new G4Tubs("Pipe_Front_Sub_Solid",0, Pipe_Front_Radius+Pipe_Front_Thickness, Chamber_Corpus_Radius+Chamber_Corpus_Thickness, 0.*deg, 360.*deg);
G4RotationMatrix* Pipe_Front_rm = new G4RotationMatrix();
Pipe_Front_rm->rotateY(90.*deg);


G4SubtractionSolid* Chamber_Corpus_Solid_1 = new G4SubtractionSolid("Chamber_Corpus_Solid_1", TargetChamber, Pipe_Front_Sub_Solid, Pipe_Front_rm,G4ThreeVector(0.,0.,0.));

G4double Pipe_Conus_Radius_1 = 13.5*mm;
G4double Pipe_Conus_Radius_2 = 20.*mm;
G4double Pipe_Conus_Thickness = 1.*mm;
G4double Pipe_Conus_Length = 115.*mm;
G4double Pipe_Conus_z = (Pipe_Conus_Length/2+Chamber_Corpus_Radius-5.*mm);

G4Cons* Conus_Sub_Solid = new G4Cons("Pipe_Conus_Sub_Solid",
				    Pipe_Conus_Radius_1,
				    Pipe_Conus_Radius_1+Pipe_Conus_Thickness,
				    Pipe_Conus_Radius_2,
				    Pipe_Conus_Radius_2+Pipe_Conus_Thickness,
				    Pipe_Conus_Length/2,
				    0.*deg,
				    360.*deg);

G4RotationMatrix* Conus_rm = new G4RotationMatrix();
  Conus_rm->rotateY(90.*deg);

  G4SubtractionSolid* Chamber_Corpus_Solid_2 = new G4SubtractionSolid("Chamber_Corpus_Solid_2",
							   Chamber_Corpus_Solid_1,
							   Conus_Sub_Solid,
							   Conus_rm,
							   G4ThreeVector(0.,Pipe_Conus_z,0.));

G4double Pipe_Bottom_Radius = 8.*mm;
G4double Pipe_Bottom_Thickness = 8.*mm;
G4double Pipe_Bottom_Length = 100.*mm;
G4double Pipe_Bottom_z = -(Pipe_Bottom_Length/2+Chamber_Corpus_Radius-5.*mm);

G4Tubs* Pipe_Bottom_Sub_Solid = new G4Tubs("Pipe_Bottom_Sub_Solid",
				    0,
				    Pipe_Bottom_Radius+Pipe_Bottom_Thickness,
				    Pipe_Bottom_Length/2,
				    0.*deg,
				    360.*deg);

G4RotationMatrix* Pipe_Bottom_rm = new G4RotationMatrix();
  Pipe_Bottom_rm->rotateX(90.*deg);

  G4SubtractionSolid* Chamber_Corpus_Solid_3 = new G4SubtractionSolid("Chamber_Corpus_Solid_3",
							   Chamber_Corpus_Solid_2,
							   Pipe_Bottom_Sub_Solid,
							   Pipe_Bottom_rm,
							   G4ThreeVector(0.,Pipe_Bottom_z,0.));

G4double Target_Pipe_Radius = 7.*mm;
G4double Target_Pipe_Thickness = 3.*mm;
G4double Target_Pipe_Length = 100.*mm;
G4double Target_Pipe_z = (Target_Pipe_Length/2+Chamber_Corpus_Radius-1.*mm);



G4Tubs* Target_Pipe_Sub_Solid = new G4Tubs("Target_Pipe_Sub_Solid",
				    0,
				    Target_Pipe_Radius+Target_Pipe_Thickness,
				    Target_Pipe_Length/2,
				    0.*deg,
				    360.*deg);

  G4RotationMatrix* Target_Pipe_rm = new G4RotationMatrix();
  Target_Pipe_rm->rotateX(90.*deg);

  G4SubtractionSolid* Chamber_Corpus_Solid_4 = new G4SubtractionSolid("Chamber_Corpus_Solid_4",
							   Chamber_Corpus_Solid_3,
							   Target_Pipe_Sub_Solid,
							   Target_Pipe_rm,
							   G4ThreeVector(0.,Target_Pipe_z,0.));

G4double RBS_Pipe_Radius = 6.*mm;
G4double RBS_Pipe_Thickness = 3.5*mm;
G4double RBS_Pipe_Length = 19.*mm;
G4double RBS_Pipe_Angle = 132.*deg;
G4double RBS_Pipe_z = RBS_Pipe_Length/2+Chamber_Corpus_Radius-1.*mm;


G4Tubs* RBS_Pipe_Sub_Solid = new G4Tubs("RBS_Pipe_Sub_Solid",
				    0,
				    RBS_Pipe_Radius+RBS_Pipe_Thickness,
				    RBS_Pipe_Length/2,
				    0.*deg,
				    360.*deg);

  G4RotationMatrix* RBS_Pipe_rm = new G4RotationMatrix();
  RBS_Pipe_rm->rotateX(RBS_Pipe_Angle);
  G4ThreeVector RBS_Pipe_Vector = G4ThreeVector(0.,RBS_Pipe_z*sin(RBS_Pipe_Angle),RBS_Pipe_z*cos(RBS_Pipe_Angle));


  G4SubtractionSolid* Chamber_Corpus_Solid_5 = new G4SubtractionSolid("Chamber_Corpus_Solid_5",
							   Chamber_Corpus_Solid_4,
							   RBS_Pipe_Sub_Solid,
							   RBS_Pipe_rm,
							   RBS_Pipe_Vector);

G4LogicalVolume* Chamber_Corpus_Logical = new G4LogicalVolume(Chamber_Corpus_Solid_5,
							      Aluminium,
							      "Chamber_Corpus_Logical",
							      0, 0, 0);

  G4VisAttributes* Chamber_Corpus_VisAtt = new G4VisAttributes(G4Color(0.5,0.5,0.5,0.5));
  Chamber_Corpus_VisAtt->SetForceSolid(true);
  Chamber_Corpus_Logical->SetVisAttributes(Chamber_Corpus_VisAtt);

  new G4PVPlacement(Chamber_rm,
		    G4ThreeVector(0.*cm, 0.*cm, 0.*cm),
		    Chamber_Corpus_Logical,
		    "Chamber",
		    expHall_log,
		    false, 0);

//Einbinden der Seitenteile für Astro-Targetkammer

G4Tubs* Chamber_Cover_Solid = new G4Tubs("Chamber_Cover_Solid",
					 0,
					 Chamber_Corpus_Radius,
					 Chamber_Corpus_Thickness/2.,
					 0.*deg,
					 360.*deg);

  G4LogicalVolume* Chamber_Cover_Logical = new G4LogicalVolume(Chamber_Cover_Solid,
							      Aluminium,
							      "Chamber_Cover_Logical",
							      0, 0, 0);

  G4VisAttributes* Chamber_Cover_VisAtt = new G4VisAttributes(G4Color(0.5,0.5,0.5,0.5));
  Chamber_Cover_VisAtt->SetForceSolid(true);
  Chamber_Cover_Logical->SetVisAttributes(Chamber_Cover_VisAtt);

      new G4PVPlacement(Chamber_rm,
		    G4ThreeVector(Chamber_Corpus_Height/2+Chamber_Corpus_Thickness/2, 0.*cm, 0.*cm),
		    Chamber_Cover_Logical,
		    "Chamber_Cover1",
		    expHall_log,
		    false, 0);

      new G4PVPlacement(Chamber_rm,
		    G4ThreeVector(-(Chamber_Corpus_Height/2+Chamber_Corpus_Thickness/2), 0.*cm, 0.*cm),
		    Chamber_Cover_Logical,
		    "Chamber_Cover2",
		    expHall_log,
		    false, 0);




//Tantal Auskleidung der Targetkammer

G4RotationMatrix* Chamber_Coating_rm = new G4RotationMatrix();
Chamber_Coating_rm->rotateY(90.*deg);

G4double Chamber_Coating_Corpus_Radius = 55./2*mm;
G4double Chamber_Coating_Corpus_Height = 40.*mm;
G4double Chamber_Coating_Corpus_Thickness = 1.*mm;

G4Tubs* Chamber_Coating_Corpus_Full_Solid = new G4Tubs("Chamber_Coating_Corpus_Full_Solid",
					    Chamber_Coating_Corpus_Radius,
					  Chamber_Coating_Corpus_Radius+Chamber_Coating_Corpus_Thickness,
					  Chamber_Coating_Corpus_Height/2.,
					    0.*deg,
					    360.*deg);

//Subtraction Volumes for Beam Pipes

G4Tubs* Pipe_Front_Coating_Sub_Solid = new G4Tubs("Pipe_Front_Coating_Sub_Solid",
						0,
						Pipe_Front_Radius+Pipe_Front_Thickness,
						Chamber_Coating_Corpus_Radius+Chamber_Coating_Corpus_Thickness,
						0.*deg,
						360.*deg);

G4RotationMatrix* Pipe_Front_Coating_rm = new G4RotationMatrix();
Pipe_Front_Coating_rm->rotateY(90.*deg);

G4SubtractionSolid* Chamber_Coating_Corpus_Solid_1 = new G4SubtractionSolid("Chamber_Coating_Corpus_Solid_1",
									  Chamber_Coating_Corpus_Full_Solid,
									  Pipe_Front_Coating_Sub_Solid,
									  Pipe_Front_Coating_rm,
									  G4ThreeVector(0.,0.,0.));

G4Cons* Conus_Coating_Sub_Solid = new G4Cons("Pipe_Conus_Coating_Sub_Solid",
					   Pipe_Conus_Radius_1,
					   Pipe_Conus_Radius_1+Pipe_Conus_Thickness,
					   Pipe_Conus_Radius_2,
					   Pipe_Conus_Radius_2+Pipe_Conus_Thickness,
					   Pipe_Conus_Length/2,
					   0.*deg,
					   360.*deg);

G4RotationMatrix* Conus_Coating_rm = new G4RotationMatrix();
Conus_Coating_rm->rotateY(90.*deg);

G4SubtractionSolid* Chamber_Coating_Corpus_Solid_2 = new G4SubtractionSolid("Chamber_Coating_Corpus_Solid_2",
									  Chamber_Coating_Corpus_Solid_1,
									  Conus_Coating_Sub_Solid,
									  Conus_Coating_rm,
									  G4ThreeVector(0.,Pipe_Conus_z,0.));

G4Tubs* Pipe_Bottom_Coating_Sub_Solid = new G4Tubs("Pipe_Bottom_Coating_Sub_Solid",
						 0,
						 Pipe_Bottom_Radius+Pipe_Bottom_Thickness,
						 Pipe_Bottom_Length/2,
						 0.*deg,
						 360.*deg);

G4RotationMatrix* Pipe_Bottom_Coating_rm = new G4RotationMatrix();
Pipe_Bottom_Coating_rm->rotateX(90.*deg);

G4SubtractionSolid* Chamber_Coating_Corpus_Solid_3 = new G4SubtractionSolid("Chamber_Coating_Corpus_Solid_3",
							   Chamber_Coating_Corpus_Solid_2,
							   Pipe_Bottom_Coating_Sub_Solid,
							   Pipe_Bottom_Coating_rm,
							   G4ThreeVector(0.,Pipe_Bottom_z,0.));

G4Tubs* Target_Pipe_Coating_Sub_Solid = new G4Tubs("Target_Pipe_Coating_Sub_Solid",
				    0,
				    Target_Pipe_Radius+Target_Pipe_Thickness,
				    Target_Pipe_Length/2,
				    0.*deg,
				    360.*deg);

  G4RotationMatrix* Target_Pipe_Coating_rm = new G4RotationMatrix();
  Target_Pipe_Coating_rm->rotateX(90.*deg);

  G4SubtractionSolid* Chamber_Coating_Corpus_Solid_4 = new G4SubtractionSolid("Chamber_Coating_Corpus_Solid_4",
							   Chamber_Coating_Corpus_Solid_3,
							   Target_Pipe_Coating_Sub_Solid,
							   Target_Pipe_Coating_rm,
							   G4ThreeVector(0.,Target_Pipe_z,0.));


 G4Tubs* RBS_Pipe_Coating_Sub_Solid = new G4Tubs("RBS_Pipe_Coating_Sub_Solid",
				    0,
				    RBS_Pipe_Radius+RBS_Pipe_Thickness,
				    RBS_Pipe_Length/2,
				    0.*deg,
				    360.*deg);

  G4RotationMatrix* RBS_Pipe_Coating_rm = new G4RotationMatrix();
  RBS_Pipe_Coating_rm->rotateX(RBS_Pipe_Angle);
  G4ThreeVector RBS_Pipe_Coating_Vector = G4ThreeVector(0.,RBS_Pipe_z*sin(RBS_Pipe_Angle),RBS_Pipe_z*cos(RBS_Pipe_Angle));


  G4SubtractionSolid* Chamber_Coating_Corpus_Solid_5 = new G4SubtractionSolid("Chamber_Coating_Corpus_Solid_5",
							   Chamber_Coating_Corpus_Solid_4,
							   RBS_Pipe_Coating_Sub_Solid,
							   RBS_Pipe_Coating_rm,
							   RBS_Pipe_Coating_Vector);

  G4LogicalVolume* Chamber_Coating_Corpus_Logical = new G4LogicalVolume(Chamber_Coating_Corpus_Solid_5,
							      Tantalum,
							      "Chamber_Coating_Corpus_Logical",
							      0, 0, 0);

  G4VisAttributes* Chamber_Coating_Corpus_VisAtt = new G4VisAttributes(G4Color(0.,1.,1.));
  Chamber_Coating_Corpus_VisAtt->SetForceSolid(true);
  Chamber_Coating_Corpus_Logical->SetVisAttributes(Chamber_Coating_Corpus_VisAtt);

  new G4PVPlacement(Chamber_Coating_rm,
		    G4ThreeVector(0.*cm, 0.*cm, 0.*cm),
		    Chamber_Coating_Corpus_Logical,
		    "Chamber_Coating",
		    expHall_log,
		    false, 0);

//Tantalauskleidung der Seitenteile

G4Tubs* Chamber_Coating_Cover_Solid = new G4Tubs("Chamber_Coating_Cover_Solid",
					 0,
					 Chamber_Coating_Corpus_Radius,
					 Chamber_Coating_Corpus_Thickness/2.,
					 0.*deg,
					 360.*deg);

  G4LogicalVolume* Chamber_Coating_Cover_Logical = new G4LogicalVolume(Chamber_Coating_Cover_Solid,
							      Tantalum,
							      "Chamber_Coating_Cover_Logical",
							      0, 0, 0);

new G4PVPlacement(Chamber_Coating_rm,
		    G4ThreeVector(Chamber_Coating_Corpus_Height/2+Chamber_Coating_Corpus_Thickness/2, 0.*cm, 0.*cm),
		    Chamber_Coating_Cover_Logical,
		    "Chamber_Coating_Cover1",
		    expHall_log,
		    false, 0);

      new G4PVPlacement(Chamber_Coating_rm,
		    G4ThreeVector(-(Chamber_Coating_Corpus_Height/2+Chamber_Coating_Corpus_Thickness/2), 0.*cm, 0.*cm),
		    Chamber_Coating_Cover_Logical,
		    "Chamber_Coating_Cover2",
		    expHall_log,
		    false, 0);

  G4VisAttributes* Chamber_Coating_Cover_VisAtt = new G4VisAttributes(G4Color(0.,1.,0.));
  Chamber_Coating_Cover_VisAtt->SetForceSolid(true);
  Chamber_Coating_Cover_Logical->SetVisAttributes(Chamber_Coating_Cover_VisAtt);

//Beampipe Front

G4Tubs* Pipe_Front_Solid = new G4Tubs("Pipe_Front_Solid",
				    Pipe_Front_Radius,
				    Pipe_Front_Radius+Pipe_Front_Thickness,
				    Pipe_Front_Length/2.,
				    0.*deg,
				    360.*deg);

G4LogicalVolume* Pipe_Front_Logical = new G4LogicalVolume(Pipe_Front_Solid,
							Aluminium,
							"Pipe_Front_Logical",0 ,0 ,0);

G4VisAttributes* Pipe_Front_VisAtt = new G4VisAttributes(G4Color(1.,0.,0.,0.5));
Pipe_Front_VisAtt->SetForceSolid(true);
Pipe_Front_Logical->SetVisAttributes(Pipe_Front_VisAtt);

new G4PVPlacement(0,
		  G4ThreeVector(0.*cm,0.*cm,Pipe_Front_z),
		  Pipe_Front_Logical,
		  "Pipe_Front",
		  expHall_log,
		  false, 0);

//Beam Pipe Front Connector

G4double Pipe_Front_Connector_Radius = Pipe_Front_Radius+Pipe_Front_Thickness;
G4double Pipe_Front_Connector_Thickness = 6.*mm;
G4double Pipe_Front_Connector_Length = 32.*mm;
G4double Pipe_Front_Connector_z = -(Pipe_Front_Connector_Length/2+Chamber_Corpus_Radius+Chamber_Corpus_Thickness);

G4Tubs* Pipe_Front_Connector_Solid = new G4Tubs("Pipe_Front_Connector_Solid",
					      Pipe_Front_Connector_Radius,
					      Pipe_Front_Connector_Radius+Pipe_Front_Connector_Thickness,
					      Pipe_Front_Connector_Length/2.,
					      0.*deg,
					      360.*deg);

G4LogicalVolume* Pipe_Front_Connector_Logical = new G4LogicalVolume(Pipe_Front_Connector_Solid,
								    PET,
								    "Pipe_Front_Logical",
								    0, 0, 0);

G4VisAttributes* Pipe_Front_Connector_VisAtt = new G4VisAttributes(G4Color(0.5,0.5,0.,0.5));
Pipe_Front_Connector_VisAtt->SetForceSolid(true);
Pipe_Front_Connector_Logical->SetVisAttributes(Pipe_Front_Connector_VisAtt);

new G4PVPlacement(0,
		    G4ThreeVector(0.*cm, 0.*cm, Pipe_Front_Connector_z),
		    Pipe_Front_Connector_Logical,
		    "Pipe_Front_Connector",
		    expHall_log,
		    false, 0);

//Beam Pipe Conus

 G4Cons* Pipe_Conus_Solid = new G4Cons("Pipe_Conus_Sub_Solid",
				    Pipe_Conus_Radius_1,
				    Pipe_Conus_Radius_1+Pipe_Conus_Thickness,
				    Pipe_Conus_Radius_2,
				    Pipe_Conus_Radius_2+Pipe_Conus_Thickness,
				    Pipe_Conus_Length/2,
				    0.*deg,
				    360.*deg);

  G4LogicalVolume* Pipe_Conus_Logical = new G4LogicalVolume(Pipe_Conus_Solid,
								    Aluminium,
								    "Pipe_Conus_Logical",
								    0, 0, 0);

  G4VisAttributes* Pipe_Conus_VisAtt = new G4VisAttributes(G4Color(0.5,0.5,0.5,0.5));
  Pipe_Conus_VisAtt->SetForceSolid(true);
  Pipe_Conus_Logical->SetVisAttributes(Pipe_Conus_VisAtt);

new G4PVPlacement(0,
		    G4ThreeVector(0.*cm, 0.*cm, Pipe_Conus_z),
		    Pipe_Conus_Logical,
		    "Pipe_Conus_Connector",
		    expHall_log,
		    false, 0);

//Beam Pipe Bottom

G4Tubs* Pipe_Bottom_Solid = new G4Tubs("Pipe_Bottom_Solid",
				    Pipe_Bottom_Radius,
				    Pipe_Bottom_Radius+Pipe_Bottom_Thickness,
				    Pipe_Bottom_Length/2,
				    0.*deg,
				    360.*deg);

  G4LogicalVolume* Pipe_Bottom_Logical = new G4LogicalVolume(Pipe_Bottom_Solid,
							  Aluminium,
							  "Pipe_Bottom_Logical", 0, 0, 0);

  G4VisAttributes* Pipe_Bottom_VisAtt = new G4VisAttributes(G4Color(0.5,0.5,0.5));
  Pipe_Bottom_VisAtt->SetForceSolid(true);
  Pipe_Bottom_Logical->SetVisAttributes(Pipe_Front_VisAtt);

  new G4PVPlacement(Pipe_Bottom_rm,
		    G4ThreeVector(0.*cm, Pipe_Bottom_z, 0.*cm),
		    Pipe_Bottom_Logical,
		    "Pipe_Bottom",
		    expHall_log,
		    false, 0);

//Target Pipe
  G4Tubs* Target_Pipe_Solid = new G4Tubs("Target_Pipe_Solid",
				    Target_Pipe_Radius,
				    Target_Pipe_Radius+Target_Pipe_Thickness,
				    Target_Pipe_Length/2,
				    0.*deg,
				    360.*deg);

  G4LogicalVolume* Target_Pipe_Logical = new G4LogicalVolume(Target_Pipe_Solid,
							  Aluminium,
							  "Target_Pipe_Logical", 0, 0, 0);

  G4VisAttributes* Target_Pipe_VisAtt = new G4VisAttributes(G4Color(1.,0.,0.));
  Target_Pipe_VisAtt->SetForceSolid(true);
  Target_Pipe_Logical->SetVisAttributes(Target_Pipe_VisAtt);

  new G4PVPlacement(Target_Pipe_rm,
		    G4ThreeVector(0.*cm, Target_Pipe_z, 0.*cm),
		    Target_Pipe_Logical,
		    "Target_Pipe",
		    expHall_log,
		    false, 0);

//RBS Pipe
  G4Tubs* RBS_Pipe_Solid = new G4Tubs("RBS_Pipe_Solid",
				     RBS_Pipe_Radius,
				     RBS_Pipe_Radius+RBS_Pipe_Thickness,
				     RBS_Pipe_Length/2,
				     0.*deg,
				     360.*deg);

  G4LogicalVolume* RBS_Pipe_Logical = new G4LogicalVolume(RBS_Pipe_Solid,
							Aluminium,
							"RBS_Pipe_Logical",
							0, 0, 0);


  G4VisAttributes* RBS_Pipe_VisAtt = new G4VisAttributes(G4Color(0.5,0.5,0.5,0.5));
  RBS_Pipe_VisAtt->SetForceSolid(true);
  RBS_Pipe_Logical->SetVisAttributes(RBS_Pipe_VisAtt);

  new G4PVPlacement(RBS_Pipe_rm,
			RBS_Pipe_Vector,
			RBS_Pipe_Logical,
			"RBS_Pipe",
			expHall_log,
			false, 0);

//RBS Housing

  G4double RBS_Housing_Radius = 16.5*mm;
  G4double RBS_Housing_Thickness = 6.*mm;
  G4double RBS_Housing_Length = 150.*mm;
  //G4double RBS_Housing_Angle = RBS_Pipe_Angle;
  G4double RBS_Housing_z = RBS_Housing_Length/2+RBS_Pipe_z+RBS_Pipe_Length/2;

  G4Tubs* RBS_Housing_Solid = new G4Tubs("RBS_Housing_Solid",
				     RBS_Housing_Radius,
				     RBS_Housing_Radius+RBS_Housing_Thickness,
				     RBS_Housing_Length/2,
				     0.*deg,
				     360.*deg);

  G4LogicalVolume* RBS_Housing_Logical = new G4LogicalVolume(RBS_Housing_Solid,
							Aluminium,
							"RBS_Housing_Logical",
							0, 0, 0);


  G4VisAttributes* RBS_Housing_VisAtt = new G4VisAttributes(G4Color(0.,0.5,0.));
  RBS_Housing_VisAtt->SetForceSolid(true);
  RBS_Housing_Logical->SetVisAttributes(RBS_Housing_VisAtt);

  G4ThreeVector RBS_Housing_Vector = G4ThreeVector(0.,RBS_Housing_z*sin(RBS_Pipe_Angle),RBS_Housing_z*cos(RBS_Pipe_Angle));

   new G4PVPlacement(RBS_Pipe_rm,
			RBS_Housing_Vector,
			RBS_Housing_Logical,
			"RBS_Housing",
			expHall_log,
			false, 0);

//Faraday Box

G4double Faraday_Box_Front_Radius = Pipe_Conus_Radius_2;
G4double Faraday_Box_Front_Thickness = 40.*mm-Pipe_Conus_Radius_2;
G4double Faraday_Box_Front_Length = 20.*mm;
G4double Faraday_Box_Front_z = Faraday_Box_Front_Length/2+Pipe_Conus_z+Pipe_Conus_Length/2;

G4double Faraday_Box_Back_Radius = 25.*mm;
G4double Faraday_Box_Back_Thickness = 22.5*mm;
G4double Faraday_Box_Back_Length = 52.*mm;
G4double Faraday_Box_Back_z = Faraday_Box_Back_Length/2+Faraday_Box_Front_z+Faraday_Box_Front_Length/2;

G4Tubs* Faraday_Box_Front_Solid = new G4Tubs("Faraday_Box_Front_Solid",
				     Faraday_Box_Front_Radius,
				     Faraday_Box_Front_Radius+Faraday_Box_Front_Thickness,
				     Faraday_Box_Front_Length/2,
				     0.*deg,
				     360.*deg);

  G4LogicalVolume* Faraday_Box_Front_Logical = new G4LogicalVolume(Faraday_Box_Front_Solid,
							PET,
							"Faraday_Box_Front_Logical",
							0, 0, 0);

  G4VisAttributes* Faraday_Box_Front_VisAtt = new G4VisAttributes(G4Color(0.,0.5,0.,0.5));
  Faraday_Box_Front_VisAtt->SetForceSolid(true);
  Faraday_Box_Front_Logical->SetVisAttributes(Faraday_Box_Front_VisAtt);

new G4PVPlacement(0,
			G4ThreeVector(0.,0.,Faraday_Box_Front_z),
			Faraday_Box_Front_Logical,
			"Faraday_Box_Front",
			expHall_log,
			false, 0);

G4Tubs* Faraday_Box_Back_Solid = new G4Tubs("Faraday_Box_Back_Solid",
				     Faraday_Box_Back_Radius,
				     Faraday_Box_Back_Radius+Faraday_Box_Back_Thickness,
				     Faraday_Box_Back_Length/2,
				     0.*deg,
				     360.*deg);

  G4LogicalVolume* Faraday_Box_Back_Logical = new G4LogicalVolume(Faraday_Box_Back_Solid,
							PET,
							"Faraday_Box_Back_Logical",
							0, 0, 0);

  G4VisAttributes* Faraday_Box_Back_VisAtt = new G4VisAttributes(G4Color(0.,0.5,0.));
  Faraday_Box_Back_VisAtt->SetForceSolid(true);
  Faraday_Box_Back_Logical->SetVisAttributes(Faraday_Box_Back_VisAtt);

  new G4PVPlacement(0,
			G4ThreeVector(0.,0.,Faraday_Box_Back_z),
			Faraday_Box_Back_Logical,
			"Faraday_Box_Back",
			expHall_log,
			false, 0);

//Faraday Cup

G4double Faraday_Cup_Radius = Pipe_Conus_Radius_2+1.*mm;
G4double Faraday_Cup_Thickness = 1.*mm;
G4double Faraday_Cup_z = Faraday_Box_Front_Length/2+Faraday_Box_Front_z+Faraday_Cup_Thickness/2+2.*mm;

G4Tubs* Faraday_Cup_Solid = new G4Tubs("Faraday_Cup_Solid",
				     0,
				     Faraday_Cup_Radius,
				     Faraday_Cup_Thickness/2,
				     0.*deg,
				     360.*deg);

  G4LogicalVolume* Faraday_Cup_Logical = new G4LogicalVolume(Faraday_Cup_Solid,
							Tantalum,
							"Faraday_Cup_Logical",
							0, 0, 0);

  G4VisAttributes* Faraday_Cup_VisAtt = new G4VisAttributes(G4Color(0.,0.,0.5));
  Faraday_Cup_VisAtt->SetForceSolid(true);
  Faraday_Cup_Logical->SetVisAttributes(Faraday_Cup_VisAtt);

  new G4PVPlacement(0,
			G4ThreeVector(0.,0.,Faraday_Cup_z),
			Faraday_Cup_Logical,
			"Faraday_Cup",
			expHall_log,
			false, 0);

}

AstroTargetkammer::~AstroTargetkammer()
{}