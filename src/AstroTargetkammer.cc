#include "AstroTargetkammer.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4VisAttributes.hh"

AstroTargetkammer::AstroTargetkammer(G4LogicalVolume* mother_l)
{
    G4bool check_overlaps = true;

    G4Material* pet = G4Material::GetMaterial("PET");
    G4VisAttributes* pet_va = new G4VisAttributes(G4Color(1, 1, 1, 1));
    pet_va->SetForceSolid(true);

    G4Material* aluminum = G4Material::GetMaterial("G4_Al");
    G4VisAttributes* aluminum_va = new G4VisAttributes(G4Color(0.5, 0.5, 0.5, 1));
    aluminum_va->SetForceSolid(true);

    G4Material* lead = G4Material::GetMaterial("G4_Pb");
    G4VisAttributes* lead_va = new G4VisAttributes(G4Color(0.2, 0.2, 0.2, 1));
    lead_va->SetForceSolid(true);

    G4Material* tantalum = G4Material::GetMaterial("G4_Ta");
    G4VisAttributes* tantalum_va = new G4VisAttributes(G4Color(0., 0.5, 0.5, 1));
    tantalum_va->SetForceSolid(true);

    G4Material* brass = G4Material::GetMaterial("Brass");
    G4VisAttributes* brass_va = new G4VisAttributes(G4Color(0.82, 0.71, 0.28, 1));
    brass_va->SetForceSolid(true);

    G4Material* copper = G4Material::GetMaterial("G4_Cu");
    G4VisAttributes* copper_va = new G4VisAttributes(G4Color(0.50, 0.24, 0.09, 1));
    copper_va->SetForceSolid(true);

    G4RotationMatrix* rm90x = new G4RotationMatrix();
    rm90x->rotateX(90. * deg);
    G4RotationMatrix* rm90y = new G4RotationMatrix();
    rm90y->rotateY(90. * deg);
    G4RotationMatrix* rm90z = new G4RotationMatrix();
    rm90z->rotateZ(90. * deg);
    G4RotationMatrix* rmrbs = new G4RotationMatrix();
    rmrbs->rotateY(-90. * deg);
    rmrbs->rotateX(132. * deg);
    G4RotationMatrix* rm90y180z = new G4RotationMatrix();
    rm90y180z->rotateY(-90. * deg);
    rm90y180z->rotateZ(180. * deg);

    // Aluminum main corpus and tantalum coating
    G4double chamber_corpus_radius[2] = {55. * mm / 2., 65. * mm / 2.};
    G4double chamber_corpus_width[2] = {40. * mm / 2., 44. * mm / 2.};
    G4double chamber_coating_radius[2] = {51. * mm / 2., 51.5 * mm / 2.};
    G4double chamber_coating_width[2] = {39. * mm / 2., 39.5 * mm / 2.};
    G4double chamber_corpus_b1_d3[3] = {34. * mm / 2, 72. * mm / 2, 34. * mm / 2};
    G4double chamber_corpus_b2_d3[3] = {68. * mm / 4., 42. * mm / 2, 34. * mm / 2};

    G4Tubs* chamber_corpus_full_tubs_s = new G4Tubs("chamber_corpus_full_tubs_s", 0, chamber_corpus_radius[1], chamber_corpus_width[1], 0. * deg, 360. * deg);
    G4Box* chamber_corpus_b1_s = new G4Box("chamber_corpus_b1_s", chamber_corpus_b1_d3[0], chamber_corpus_b1_d3[1], chamber_corpus_b1_d3[2]);
    G4Box* chamber_corpus_b2_s = new G4Box("chamber_corpus_b2_s", chamber_corpus_b2_d3[0], chamber_corpus_b2_d3[1], chamber_corpus_b2_d3[2]);
    G4UnionSolid* chamber_corpus_b1b2_s = new G4UnionSolid("chamber_corpus_b1b2_s", chamber_corpus_b1_s, chamber_corpus_b2_s, 0, G4ThreeVector(chamber_corpus_b2_d3[0], 0, 0));
    G4UnionSolid* chamber_corpus_full_s = new G4UnionSolid("chamber_corpus_full_s", chamber_corpus_full_tubs_s, chamber_corpus_b1b2_s);

    G4Tubs* chamber_coating_full_s = new G4Tubs("chamber_coating_full_s", 0, chamber_coating_radius[1], chamber_coating_width[1], 0. * deg, 360. * deg);

    // inner "cave"
    G4Tubs* chamber_corpus_sub_s0 = new G4Tubs("chamber_corpus_sub_s0", 0, chamber_corpus_radius[0], chamber_corpus_width[0], 0. * deg, 360. * deg);
    G4Tubs* chamber_coating_sub_s0 = new G4Tubs("chamber_coating_sub_s0", 0, chamber_coating_radius[0], chamber_coating_width[0], 0. * deg, 360. * deg);
    // beam pipe
    G4double chamber_pipe_hole_radius = 1.1 * cm;
    G4Tubs* chamber_pipe_front_sub_s = new G4Tubs("chamber_pipe_front_sub_s", 0, chamber_pipe_hole_radius, chamber_corpus_radius[1] * 1.2, 0. * deg, 360. * deg);
    G4UnionSolid* chamber_corpus_sub_s1 = new G4UnionSolid("chamber_corpus_sub_s1", chamber_corpus_sub_s0, chamber_pipe_front_sub_s, rm90y, G4ThreeVector());
    G4UnionSolid* chamber_coating_sub_s1 = new G4UnionSolid("chamber_coating_sub_s1", chamber_coating_sub_s0, chamber_pipe_front_sub_s, rm90y, G4ThreeVector());
    // rbs pipe
    G4double rbs_pipe_hole_radius = 18. * mm / 2.;
    G4Tubs* rbs_pipe_sub_s = new G4Tubs("rbs_pipe_sub_s", 0, rbs_pipe_hole_radius, chamber_corpus_radius[1], 0. * deg, 360. * deg);
    G4UnionSolid* chamber_corpus_sub_s2 = new G4UnionSolid("chamber_corpus_sub_s2", chamber_corpus_sub_s1, rbs_pipe_sub_s, rmrbs, G4ThreeVector(-1 * cm, 1 * cm, 0));
    G4UnionSolid* chamber_coating_sub_s2 = new G4UnionSolid("chamber_coating_sub_s2", chamber_coating_sub_s1, rbs_pipe_sub_s, rmrbs, G4ThreeVector(-1 * cm, 1 * cm, 0));
    // top % bottom hole
    G4double topbottom_hole_radius = 20. * mm / 2.;
    G4Tubs* topbottom_sub_s = new G4Tubs("rbs_pipe_sub_s", 0, topbottom_hole_radius, chamber_corpus_radius[1] * 1.2, 0. * deg, 360. * deg);
    G4UnionSolid* chamber_corpus_sub_s3 = new G4UnionSolid("chamber_corpus_sub_s3", chamber_corpus_sub_s2, topbottom_sub_s, rm90x, G4ThreeVector());
    G4UnionSolid* chamber_coating_sub_s3 = new G4UnionSolid("chamber_coating_sub_s3", chamber_coating_sub_s2, topbottom_sub_s, rm90x, G4ThreeVector());

    G4SubtractionSolid* chamber_corpus_s = new G4SubtractionSolid("chamber_corpus_s", chamber_corpus_full_s, chamber_corpus_sub_s3);
    G4SubtractionSolid* chamber_coating_s = new G4SubtractionSolid("chamber_coating_s", chamber_coating_full_s, chamber_coating_sub_s3);

    G4LogicalVolume* chamber_corpus_l = new G4LogicalVolume(chamber_corpus_s, aluminum, "chamber_corpus_l");
    chamber_corpus_l->SetVisAttributes(aluminum_va);
    G4LogicalVolume* chamber_coating_l = new G4LogicalVolume(chamber_coating_s, tantalum, "chamber_coating_l");
    chamber_coating_l->SetVisAttributes(tantalum_va);

    new G4PVPlacement(rm90y180z, G4ThreeVector(), chamber_corpus_l, "chamber_corpus", mother_l, false, 0, check_overlaps);
    new G4PVPlacement(rm90y180z, G4ThreeVector(), chamber_coating_l, "chamber_coating", mother_l, false, 0, check_overlaps);

    // Cooling finger
    G4double cooling_finger_radius[2] = {13. * mm / 2., 15. * mm / 2.};
    G4double cooling_finger_length = 80. * mm / 2;
    G4double cooling_finger_offset = 10. * mm;
    G4double cooling_finger_hole_radius = 5. * mm;

    G4Tubs* cooling_finger_full_s = new G4Tubs("cooling_finger_full_s", cooling_finger_radius[0], cooling_finger_radius[1], cooling_finger_length, 0. * deg, 360. * deg);
    G4Tubs* cooling_finger_sub_s = new G4Tubs("cooling_finger_sub_s", 0, cooling_finger_hole_radius, cooling_finger_radius[1] * 1.2, 0. * deg, 360. * deg);
    G4SubtractionSolid* cooling_finger_s = new G4SubtractionSolid("cooling_finger_s", cooling_finger_full_s, cooling_finger_sub_s, rm90x, G4ThreeVector(0, 0, -(cooling_finger_length - cooling_finger_offset)));
    G4LogicalVolume* cooling_finger_l = new G4LogicalVolume(cooling_finger_s, copper, "cooling_finger_l");
    cooling_finger_l->SetVisAttributes(copper_va);

    new G4PVPlacement(rm90x, G4ThreeVector(0, (cooling_finger_length - cooling_finger_offset), 0), cooling_finger_l, "cooling_finger", mother_l, false, 0, check_overlaps);

    // Beampipe front
    G4double pipe_front_radius[2] = {1. * cm, 1.1 * cm};
    G4double pipe_front_length = 40. * cm / 2;
    G4double pipe_front_distance = pipe_front_length + chamber_corpus_radius[1] + 2. * mm;

    G4Tubs* pipe_front_s = new G4Tubs("pipe_front_s", pipe_front_radius[0], pipe_front_radius[1], pipe_front_length, 0. * deg, 360. * deg);
    G4LogicalVolume* pipe_front_l = new G4LogicalVolume(pipe_front_s, aluminum, "pipe_front_l");
    pipe_front_l->SetVisAttributes(aluminum_va);

    new G4PVPlacement(0, G4ThreeVector(0, 0, -pipe_front_distance), pipe_front_l, "pipe_front", mother_l, false, 0, check_overlaps);

    //Beam Pipe Front Connector
    G4double pipe_front_connector_radius[2] = {22. * mm / 2., 32. * mm / 2.};
    G4double pipe_front_connector_length = 32. * mm / 2.;

    G4Tubs* pipe_front_connector_s = new G4Tubs("pipe_front_connector_s", pipe_front_connector_radius[0], pipe_front_connector_radius[1], pipe_front_connector_length, 0. * deg, 360. * deg);
    G4LogicalVolume* pipe_front_connector_l = new G4LogicalVolume(pipe_front_connector_s, pet, "pipe_front_l");
    pipe_front_connector_l->SetVisAttributes(pet_va);

    new G4PVPlacement(0, G4ThreeVector(0, 0, -(pipe_front_connector_length + chamber_corpus_radius[1])), pipe_front_connector_l, "pipe_front_connector", mother_l, false, 0, check_overlaps);

    // beam entry shield
    G4double entry_shield_radius[3] = {32. * mm / 2., 52. * mm / 2., 59. * mm / 2.};
    G4double entry_shield_length = {100. * mm / 2.};
    G4double entry_shield_distance = chamber_corpus_radius[1] + 20. * mm;

    G4Tubs* entry_shield_lead_tubs_s = new G4Tubs("entry_shield_lead_tubs_s", entry_shield_radius[0], entry_shield_radius[1], entry_shield_length, 0. * deg, 360. * deg);
    G4Tubs* entry_shield_brass_tubs_s = new G4Tubs("entry_shield_brass_tubs_s", entry_shield_radius[1], entry_shield_radius[2], entry_shield_length, 0. * deg, 360. * deg);

    G4LogicalVolume* entry_shield_lead_tubs_l = new G4LogicalVolume(entry_shield_lead_tubs_s, lead, "entry_shield_lead_tubs_l");
    entry_shield_lead_tubs_l->SetVisAttributes(lead_va);
    G4LogicalVolume* entry_shield_brass_tubs_l = new G4LogicalVolume(entry_shield_brass_tubs_s, brass, "entry_shield_brass_tubs_l");
    entry_shield_brass_tubs_l->SetVisAttributes(brass_va);

    new G4PVPlacement(0, G4ThreeVector(0, 0, -(entry_shield_distance + entry_shield_length)), entry_shield_lead_tubs_l, "entry_shield_lead_tubs", mother_l, false, 0, check_overlaps);
    new G4PVPlacement(0, G4ThreeVector(0, 0, -(entry_shield_distance + entry_shield_length)), entry_shield_brass_tubs_l, "entry_shield_brass_tubs", mother_l, false, 0, check_overlaps);

    // beam exit shield
    // FIXME: Is a cone, not a tubs
    //G4double exit_shield_radius[3] = {37.*mm/2., 57*mm/2., 64.*mm/2.};
    G4double exit_shield_radius[3] = {37. * mm / 2. * .9, 57 * mm / 2. * .9, 64. * mm / 2. * .9};
    G4double exit_shield_length = {97. * mm / 2.};
    G4double exit_shield_distance = chamber_corpus_radius[1] + 2. * mm;

    G4Tubs* exit_shield_lead_tubs_s = new G4Tubs("exit_shield_lead_tubs_s", exit_shield_radius[0], exit_shield_radius[1], exit_shield_length, 0. * deg, 360. * deg);
    G4Tubs* exit_shield_brass_tubs_s = new G4Tubs("exit_shield_brass_tubs_s", exit_shield_radius[1], exit_shield_radius[2], exit_shield_length, 0. * deg, 360. * deg);

    G4LogicalVolume* exit_shield_lead_tubs_l = new G4LogicalVolume(exit_shield_lead_tubs_s, lead, "exit_shield_lead_tubs_l");
    exit_shield_lead_tubs_l->SetVisAttributes(lead_va);
    G4LogicalVolume* exit_shield_brass_tubs_l = new G4LogicalVolume(exit_shield_brass_tubs_s, brass, "exit_shield_brass_tubs_l");
    exit_shield_brass_tubs_l->SetVisAttributes(brass_va);

    new G4PVPlacement(0, G4ThreeVector(0, 0, +(exit_shield_distance + exit_shield_length)), exit_shield_lead_tubs_l, "exit_shield_lead_tubs", mother_l, false, 0, check_overlaps);
    new G4PVPlacement(0, G4ThreeVector(0, 0, +(exit_shield_distance + exit_shield_length)), exit_shield_brass_tubs_l, "exit_shield_brass_tubs", mother_l, false, 0, check_overlaps);

    //Target Pipe
    G4double target_pipe_radius[2] = {7. * mm, 10. * mm};
    G4double target_pipe_length = 100. * mm;

    G4Tubs* target_pipe_s = new G4Tubs("target_pipe_s", target_pipe_radius[0], target_pipe_radius[1], target_pipe_length / 2, 0. * deg, 360. * deg);
    G4LogicalVolume* target_pipe_l = new G4LogicalVolume(target_pipe_s, aluminum, "target_pipe_l");
    target_pipe_l->SetVisAttributes(aluminum_va);

    new G4PVPlacement(rm90x, G4ThreeVector(0. * cm, -(target_pipe_length / 2 + chamber_corpus_radius[1]), 0. * cm), target_pipe_l, "target_pipe", mother_l, false, 0, check_overlaps);
    new G4PVPlacement(rm90x, G4ThreeVector(0. * cm, +(target_pipe_length / 2 + chamber_corpus_radius[1]), 0. * cm), target_pipe_l, "target_pipe", mother_l, false, 0, check_overlaps);

    /*


G4double pipe_front_z = - (pipe_front_length/2 + chamber_corpus_radius+17.*mm);

G4double rbs_pipe_radius = 6.*mm;
G4double rbs_pipe_thickness = 3.5*mm;
G4double rbs_pipe_length = 19.*mm;
G4double rbs_pipe_angle = ;
G4double rbs_pipe_z = rbs_pipe_length/2 + chamber_corpus_radius-1.*mm;

G4double Pipe_Conus_Radius_1 = 13.5*mm;
G4double Pipe_Conus_Radius_2 = 20.*mm;
G4double Pipe_Conus_Thickness = 1.*mm;
G4double Pipe_Conus_Length = 115.*mm;
G4double Pipe_Conus_z = (Pipe_Conus_Length/2+chamber_corpus_radius-5.*mm);

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
G4double Pipe_Bottom_z = -(Pipe_Bottom_Length/2+chamber_corpus_radius-5.*mm);

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

G4double rbs_pipe_radius = 6.*mm;
G4double rbs_pipe_thickness = 3.5*mm;
G4double rbs_pipe_length = 19.*mm;
G4double rbs_pipe_angle = 132.*deg;
G4double rbs_pipe_z = rbs_pipe_length/2+chamber_corpus_radius-1.*mm;


G4Tubs* rbs_pipe_sub_s = new G4Tubs("rbs_pipe_sub_s",
				    0,
				    rbs_pipe_radius+rbs_pipe_thickness,
				    rbs_pipe_length/2,
				    0.*deg,
				    360.*deg);

  G4RotationMatrix* RBS_Pipe_rm = new G4RotationMatrix();
  RBS_Pipe_rm->rotateX(rbs_pipe_angle);
  G4ThreeVector RBS_Pipe_Vector = G4ThreeVector(0.,rbs_pipe_z*sin(rbs_pipe_angle),rbs_pipe_z*cos(rbs_pipe_angle));


  G4SubtractionSolid* Chamber_Corpus_Solid_5 = new G4SubtractionSolid("Chamber_Corpus_Solid_5",
							   Chamber_Corpus_Solid_4,
							   rbs_pipe_sub_s,
							   RBS_Pipe_rm,
							   RBS_Pipe_Vector);

G4LogicalVolume* Chamber_Corpus_Logical = new G4LogicalVolume(
								  TargetChamber,
									//Chamber_Corpus_Solid_5,
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
		    mother_l,
		    false, 0);

//Tantal Auskleidung der Targetkammer



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
		    mother_l,
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
		    mother_l,
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
		    mother_l,
		    false, 0);

//RBS Pipe
  G4Tubs* RBS_Pipe_Solid = new G4Tubs("RBS_Pipe_Solid",
				     rbs_pipe_radius,
				     rbs_pipe_radius+rbs_pipe_thickness,
				     rbs_pipe_length/2,
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
			mother_l,
			false, 0);

//RBS Housing

  G4double RBS_Housing_Radius = 16.5*mm;
  G4double RBS_Housing_Thickness = 6.*mm;
  G4double RBS_Housing_Length = 150.*mm;
  //G4double RBS_Housing_Angle = rbs_pipe_angle;
  G4double RBS_Housing_z = RBS_Housing_Length/2+rbs_pipe_z+rbs_pipe_length/2;

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

  G4ThreeVector RBS_Housing_Vector = G4ThreeVector(0.,RBS_Housing_z*sin(rbs_pipe_angle),RBS_Housing_z*cos(rbs_pipe_angle));

   new G4PVPlacement(RBS_Pipe_rm,
			RBS_Housing_Vector,
			RBS_Housing_Logical,
			"RBS_Housing",
			mother_l,
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
			mother_l,
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
			mother_l,
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
			mother_l,
			false, 0);

*/
}
