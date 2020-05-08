#include "SONIC.hh"
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
#include "Horus.hh"

SONIC::SONIC(G4LogicalVolume* mother_l)
{
    G4bool fCheckOverlaps = true;
    //Building the SONIC Chamber
    //At first, directly in the world
    G4Material* SONIC_mat = G4Material::GetMaterial("G4_Al");
    //G4Material* beamp_mat = G4Material::GetMaterial("G4_Al");

    auto horus = new Horus(mother_l);

    G4double tubefront = (60. - 15.) * mm;
    G4ThreeVector SONIC_pos = G4ThreeVector();

    //Defining Spheres
    G4double sph_thick = 4. * mm; //2
    G4double sph_outer = 60. * mm, sph_inner = sph_outer - sph_thick; //TODO CHECK OUTER DIAMETER
    //G4ThreeVector sph_pos = G4ThreeVector();
    G4Sphere* sph_fullS = new G4Sphere("sphere_full", 0, sph_outer, 0. * deg, 360. * deg, 0. * deg, 360. * deg);
    G4Sphere* sph_hollS = new G4Sphere("sphere_holl", 0, sph_inner, 0. * deg, 360. * deg, 0. * deg, 360. * deg);
    //G4LogicalVolume* sph_fullLV = new G4LogicalVolume(sph_fullS, SONIC_mat, "Sphere_full",0,0,0);
    //G4LogicalVolume* sph_hollLV = new G4LogicalVolume(sph_hollS, SONIC_mat, "Sphere_holl",0,0,0);

    //new G4PVPlacement(0, sph_pos, sph_fullLV, "Sphere_full", mother_l, false, 0, fCheckOverlaps);
    //sphLV->SetVisAttributes(PEVisAtt);

    //Defining Beam Pipe
    G4double beamp_thick = 4. * mm, beamp_length = 285. * mm; //3,400
    G4double beamp_outer = 20. * mm, beamp_inner = beamp_outer - beamp_thick; //17
    G4Tubs* beamp_fullS = new G4Tubs("beamp_full", 0, beamp_outer, beamp_length / 2.0, 0. * deg, 360. * deg);
    G4Tubs* beamp_hollS = new G4Tubs("beamp_holl", 0, beamp_inner, beamp_length / 2.0 + 0.1 * mm, 0. * deg, 360. * deg);

    //Defining Tubes&pos; tube{s,m,l} for short, medium, long; c for closed > blind flange
    G4double tube_thick = 4. * mm, tubeM_length = 83.5 * mm, tubeS_length = 48. * mm, tubeL_length = 145. * mm; //TODO Check short length
    G4double tubeC_length = 20.5 * mm, blind_thick = 4.0 * mm;
    G4double tube_outer = 20. * mm, tube_inner = tube_outer - tube_thick;
    G4double theta1 = 131 * deg, phi1 = 217. * deg;
    G4double theta2 = 131 * deg, phi2 = 323. * deg;
    G4double theta3 = 122 * deg, phi3 = 123. * deg;
    G4double theta4 = 122 * deg, phi4 = 57. * deg;
    G4double theta5 = 90 * deg, phi5 = 180. * deg;
    G4double theta6 = 90 * deg, phi6 = 0. * deg;
    G4double theta7 = 61 * deg, phi7 = 227. * deg;
    G4double theta8 = 61 * deg, phi8 = 313. * deg;

    G4Tubs* tubeS_fullS = new G4Tubs("tubeS_full", 0, tube_outer, tubeS_length / 2.0, 0. * deg, 360. * deg);
    G4Tubs* tubeS_hollS = new G4Tubs("tubeS_holl", 0, tube_inner, tubeS_length / 2.0 + 0.01 * mm, 0. * deg, 360. * deg);

    G4Tubs* tubeM_fullS = new G4Tubs("tubeM_full", 0, tube_outer, tubeM_length / 2.0, 0. * deg, 360. * deg);
    G4Tubs* tubeM_hollS = new G4Tubs("tubeM_holl", 0, tube_inner, tubeM_length / 2.0 + 0.01 * mm, 0. * deg, 360. * deg);

    G4Tubs* tubeL_fullS = new G4Tubs("tubeL_full", 0, tube_outer, tubeL_length / 2.0, 0. * deg, 360. * deg);
    G4Tubs* tubeL_hollS = new G4Tubs("tubeL_holl", 0, tube_inner, tubeL_length / 2.0 + 0.01 * mm, 0. * deg, 360. * deg);

    G4Tubs* tubeC_fullS = new G4Tubs("tubeC_full", 0, tube_outer, tubeC_length / 2.0, 0. * deg, 360. * deg);
    G4Tubs* tubeC_hollS = new G4Tubs("tubeC_holl", 0, tube_inner, (tubeC_length - blind_thick) / 2. + 0.01 * mm, 0. * deg, 360. * deg);

    //delete inner sphere
    //Building SOLID Sphere+Beampipe
    G4VSolid* SONIC01S = new G4UnionSolid("SONIC01", sph_fullS, beamp_fullS);
    //Carving Sphere+Beampipe
    G4VSolid* SONIC02S = new G4SubtractionSolid("SONIC02", SONIC01S, sph_hollS);
    G4VSolid* SONIC03S = new G4SubtractionSolid("SONIC03", SONIC02S, beamp_hollS);

    //Adding SOLID tube1; Change tubeX_fullS, tubeX_hollS, tubeX_length
    G4UnionSolid* SONIC04S = new G4UnionSolid("SONIC04", SONIC03S, tubeM_fullS, horus->GetTransform({theta1, phi1}, tubeM_length / 2. + tubefront));
    //Carving SOLID tube1
    G4SubtractionSolid* SONIC05S = new G4SubtractionSolid("SONIC05", SONIC04S, tubeM_hollS, horus->GetTransform({theta1, phi1}, tubeM_length / 2. + tubefront));

    //Adding&Carving SOLID tube2
    G4UnionSolid* SONIC06S = new G4UnionSolid("SONIC06", SONIC05S, tubeS_fullS, horus->GetTransform({theta2, phi2}, tubeS_length / 2. + tubefront));
    G4SubtractionSolid* SONIC07S = new G4SubtractionSolid("SONIC07", SONIC06S, tubeS_hollS, horus->GetTransform({theta2, phi2}, tubeS_length / 2. + tubefront));

    //Adding&Carving SOLID tube3
    G4UnionSolid* SONIC08S = new G4UnionSolid("SONIC08", SONIC07S, tubeL_fullS, horus->GetTransform({theta3, phi3}, tubeL_length / 2. + tubefront));
    G4SubtractionSolid* SONIC09S = new G4SubtractionSolid("SONIC09", SONIC08S, tubeL_hollS, horus->GetTransform({theta3, phi3}, tubeL_length / 2. + tubefront));

    //Adding&Carving SOLID tube4
    G4UnionSolid* SONIC10S = new G4UnionSolid("SONIC10", SONIC09S, tubeL_fullS, horus->GetTransform({theta4, phi4}, tubeL_length / 2. + tubefront));
    G4SubtractionSolid* SONIC11S = new G4SubtractionSolid("SONIC11", SONIC10S, tubeL_hollS, horus->GetTransform({theta4, phi4}, tubeL_length / 2. + tubefront));

    //Adding&Carving SOLID tube5 XXXX HERE; closed tubes are added XXX
    G4UnionSolid* SONIC12S = new G4UnionSolid("SONIC12", SONIC11S, tubeC_fullS, horus->GetTransform({theta5, phi5}, tubeC_length / 2. + tubefront));
    G4SubtractionSolid* SONIC13S = new G4SubtractionSolid("SONIC13", SONIC12S, tubeC_hollS, horus->GetTransform({theta5, phi5}, (tubeC_length - blind_thick) / 2. + tubefront));

    //Adding&Carving SOLID tube6 XXXX HERE; closed tubes are added XXX
    G4UnionSolid* SONIC14S = new G4UnionSolid("SONIC14", SONIC13S, tubeC_fullS, horus->GetTransform({theta6, phi6}, tubeC_length / 2. + tubefront));
    G4SubtractionSolid* SONIC15S = new G4SubtractionSolid("SONIC15", SONIC14S, tubeC_hollS, horus->GetTransform({theta6, phi6}, (tubeC_length - blind_thick) / 2. + tubefront));
    //This is for a "normal" tube
    //G4UnionSolid* SONIC14S =  new G4UnionSolid("SONIC14", SONIC13S, tubeS_fullS,horus->GetTransform({theta6, phi6, tubeS_length));
    //G4SubtractionSolid* SONIC15S =  new G4SubtractionSolid("SONIC15", SONIC14S, tubeS_hollS, horus->GetTransform({theta6, phi6, tubeS_length));
    //Adding&Carving SOLID tube7
    G4UnionSolid* SONIC16S = new G4UnionSolid("SONIC16", SONIC15S, tubeL_fullS, horus->GetTransform({theta7, phi7}, tubeL_length / 2. + tubefront));
    G4SubtractionSolid* SONIC17S = new G4SubtractionSolid("SONIC17", SONIC16S, tubeL_hollS, horus->GetTransform({theta7, phi7}, tubeL_length / 2. + tubefront));

    //Adding&Carving SOLID tube8
    G4UnionSolid* SONIC18S = new G4UnionSolid("SONIC18", SONIC17S, tubeL_fullS, horus->GetTransform({theta8, phi8}, tubeL_length / 2. + tubefront));
    G4SubtractionSolid* SONIC19S = new G4SubtractionSolid("SONIC19", SONIC18S, tubeL_hollS, horus->GetTransform({theta8, phi8}, tubeL_length / 2. + tubefront));

    G4LogicalVolume* SONIC19LV = new G4LogicalVolume(SONIC19S, SONIC_mat, "SONIC19", 0, 0, 0);
    //G4VisAttributes* check_vis = new G4VisAttributes(G4Color(1,1,1,0.9));
    //check_vis->SetForceSolid(true);
    //SONIC19LV->SetVisAttributes(check_vis);
    new G4PVPlacement(0, SONIC_pos, SONIC19LV, "SONIC19", mother_l, false, 0, fCheckOverlaps);
    //G4LogicalVolume* SONIC17LV = new G4LogicalVolume(SONIC17S, SONIC_mat, "SONIC",0,0,0);
    //new G4PVPlacement(0, SONIC_pos, SONIC17LV, "SONIC", mother_l, false, 0, fCheckOverlaps);

    //  G4double tubefront= (60.-15.)*mm; //Distance of tube front to center of sphere
    //  G4double distance = length/2. + tubefront;
}
