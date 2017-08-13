#include "BGO.hh"
#include "G4Cons.hh"
#include "G4IntersectionSolid.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4VisAttributes.hh"
#include <string>

BGO::BGO(const _type type, const G4String name)
{

    G4double nose_length = 4.2 * cm;
    G4double cone_length = 4.4 * cm;
    G4double zyl_length = 12. * cm;

    full_length = nose_length + cone_length + zyl_length;
    overlap_length = (nose_length + cone_length) / 2.;

    G4double nose_front_inner_diameter = 0;
    G4double nose_front_outer_diameter = 0;
    switch (type) {
    case tSMALLNOSE:
        nose_front_inner_diameter = 2 * cm;
        nose_front_outer_diameter = 5.5 * cm;
        break;
    case tLARGENOSE:
        nose_front_inner_diameter = 3.2 * cm;
        nose_front_outer_diameter = 5. * cm;
        break;
    default:
        G4Exception("BGO::BGO()", "Unknown nose type", FatalException, ("BGO " + name + " has an unknown type.").c_str());
        break;
    }

    G4double cone_back_inner_diameter = 10. * cm;
    G4double cone_back_outer_diameter = 13.5 * cm;

    G4double nose_back_inner_diameter = 4.5 * cm;
    G4double nose_back_outer_diameter = 9.2 * cm;

    G4double cone_front_inner_diameter = nose_back_inner_diameter;
    G4double cone_front_outer_diameter = nose_back_outer_diameter;

    G4double zyl_inner_diameter = cone_back_inner_diameter;
    G4double zyl_outer_diameter = cone_back_outer_diameter;

    // Logical Mother Volume
    G4Tubs* mother_zyl_s = new G4Tubs("BGO_" + name + "_mother_zyl_solid", zyl_inner_diameter / 2., zyl_outer_diameter / 2., zyl_length / 2., 0. * deg, 360. * deg);
    G4Cons* mother_cons_s = new G4Cons("BGO_" + name + "_mother_cons_solid", nose_front_inner_diameter / 2., nose_front_outer_diameter / 2., cone_back_inner_diameter / 2., cone_back_outer_diameter / 2., (nose_length + cone_length) / 2., 0. * deg, 360. * deg);
    G4UnionSolid* mother_s = new G4UnionSolid("BGO_" + name + "_mother_solid", mother_zyl_s, mother_cons_s, 0, G4ThreeVector(0., 0., -full_length / 2.));
    G4Material* mother_mat = G4Material::GetMaterial("Galactic");

    mother_lv = new G4LogicalVolume(mother_s, mother_mat, "BGO_" + name + "_mother_lv", 0, 0, 0);
    mother_lv->SetVisAttributes(G4VisAttributes::Invisible);

    // Lead nose
    G4Cons* nose_s = new G4Cons("BGO_" + name + "_nose_solid", nose_front_inner_diameter / 2., nose_front_outer_diameter / 2., nose_back_inner_diameter / 2., nose_back_outer_diameter / 2., nose_length / 2, 0. * deg, 360. * deg);
    G4Material* nose_mat = G4Material::GetMaterial("G4_Pb");
    G4VisAttributes* nose_vis = new G4VisAttributes(G4Color(0.3, 0.3, 0.3));
    nose_vis->SetForceSolid(true);

    G4LogicalVolume* nose_lv = new G4LogicalVolume(nose_s, nose_mat, "BGO_" + name + "_nose_lv", 0, 0, 0);
    nose_lv->SetVisAttributes(nose_vis);
    new G4PVPlacement(0, G4ThreeVector(0., 0., -(full_length / 2. + cone_length / 2.)), nose_lv, "BGO_" + name + "_nose", mother_lv, false, 0);

    // BGO-Crystal
    G4Tubs* bgo_zyl_s = new G4Tubs("BGO_" + name + "_bgo_zyl_solid", zyl_inner_diameter / 2., zyl_outer_diameter / 2., zyl_length / 2., 0. * deg, 360. * deg);
    G4Cons* bgo_cons_s = new G4Cons("BGO_" + name + "_bgo_cons_solid", cone_front_inner_diameter / 2., cone_front_outer_diameter / 2., cone_back_inner_diameter / 2., cone_back_outer_diameter / 2., cone_length / 2., 0. * deg, 360. * deg);
    G4UnionSolid* bgo_s = new G4UnionSolid("BGO_" + name + "_bgo_solid", bgo_zyl_s, bgo_cons_s, 0, G4ThreeVector(0., 0., -(zyl_length + cone_length) / 2.));
    G4Material* bgo_mat = G4Material::GetMaterial("BGO");
    G4VisAttributes* bgo_vis = new G4VisAttributes(G4Color(0.8, 0., 0.1));
    bgo_vis->SetForceSolid(true);

    G4LogicalVolume* bgo_lv = new G4LogicalVolume(bgo_s, bgo_mat, "BGO_" + name + "_bgo_lv", 0, 0, 0);
    bgo_lv->SetVisAttributes(bgo_vis);
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), bgo_lv, "BGO_" + name + "_bgo", mother_lv, false, 0);
}

BGO::~BGO()
{
}
