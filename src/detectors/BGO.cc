#include "BGO.hh"
#include "G4Cons.hh"
#include "G4IntersectionSolid.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4VisAttributes.hh"
#include <numeric>
#include <utility>

BGO::BGO(const _type& type, std::string name)
    : Detector(std::move(name))
{
    G4double nose_length = 4.2 * cm;
    G4double cone_length = 4.4 * cm;
    G4double zyl_length = 12. * cm;

    fLength = nose_length + cone_length + zyl_length;
    fOverlap = (nose_length + cone_length) / 2.;
    fOffset = nose_length + cone_length + zyl_length / 2.;

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
        G4Exception("BGO::BGO()", "Unknown nose type", FatalException, ("BGO " + fName + " has an unknown type.").c_str());
        break;
    }

    fWidth = nose_front_outer_diameter;

    G4double cone_back_inner_diameter = 10. * cm;
    G4double cone_back_outer_diameter = 13.5 * cm;

    G4double nose_back_inner_diameter = 4.5 * cm;
    G4double nose_back_outer_diameter = 9.2 * cm;

    G4double cone_front_inner_diameter = nose_back_inner_diameter;
    G4double cone_front_outer_diameter = nose_back_outer_diameter;

    G4double zyl_inner_diameter = cone_back_inner_diameter;
    G4double zyl_outer_diameter = cone_back_outer_diameter;

    // Logical Mother Volume
    auto mother_zyl_s = new G4Tubs("BGO_" + fName + "_mother_zyl_solid", zyl_inner_diameter / 2., zyl_outer_diameter / 2., zyl_length / 2., 0. * deg, 360. * deg);
    auto mother_cons_s = new G4Cons("BGO_" + fName + "_mother_cons_solid", cone_front_inner_diameter / 2., cone_front_outer_diameter / 2., cone_back_inner_diameter / 2., cone_back_outer_diameter / 2., cone_length / 2., 0. * deg, 360. * deg);
    auto mother_s1 = new G4UnionSolid("BGO_" + fName + "_mother1_solid", mother_zyl_s, mother_cons_s, nullptr, G4ThreeVector(0., 0., -(zyl_length + cone_length) / 2.));

    auto mother_nose_s = new G4Cons("BGO_" + fName + "_mother_nose_solid", nose_front_inner_diameter / 2., nose_front_outer_diameter / 2., nose_back_inner_diameter / 2., nose_back_outer_diameter / 2., nose_length / 2, 0. * deg, 360. * deg);
    auto mother_s = new G4UnionSolid("BGO_" + fName + "_mother_solid", mother_s1, mother_nose_s, nullptr, G4ThreeVector(0., 0., -(zyl_length + cone_length) / 2. - nose_length));

    auto mother_mat = G4Material::GetMaterial("Galactic");

    fDetectorLV = new G4LogicalVolume(mother_s, mother_mat, "BGO_" + fName + "_mother_lv");
    auto vis = G4VisAttributes(G4Color(0.1, 0.1, 0.1, 0.1));
    vis.SetForceSolid(true);
    fDetectorLV->SetVisAttributes(vis);

    // Lead nose
    auto nose_s = new G4Cons("BGO_" + fName + "_nose_solid", nose_front_inner_diameter / 2., nose_front_outer_diameter / 2., nose_back_inner_diameter / 2., nose_back_outer_diameter / 2., nose_length / 2, 0. * deg, 360. * deg);
    auto nose_mat = G4Material::GetMaterial("G4_Pb");
    auto nose_vis = new G4VisAttributes(G4Color(0.3, 0.3, 0.3));
    nose_vis->SetForceSolid(true);

    auto nose_lv = new G4LogicalVolume(nose_s, nose_mat, "BGO_" + fName + "_nose_lv");
    nose_lv->SetVisAttributes(nose_vis);
    new G4PVPlacement(nullptr, G4ThreeVector(0., 0., -(fLength / 2. + cone_length / 2.)), nose_lv, "BGO_" + fName + "_nose", fDetectorLV, false, 0);

    // BGO-Crystal
    auto bgo_zyl_s = new G4Tubs("BGO_" + fName + "_bgo_zyl_solid", zyl_inner_diameter / 2., zyl_outer_diameter / 2., zyl_length / 2., 0. * deg, 360. * deg);
    auto bgo_cons_s = new G4Cons("BGO_" + fName + "_bgo_cons_solid", cone_front_inner_diameter / 2., cone_front_outer_diameter / 2., cone_back_inner_diameter / 2., cone_back_outer_diameter / 2., cone_length / 2., 0. * deg, 360. * deg);
    auto bgo_s = new G4UnionSolid("BGO_" + fName + "_bgo_solid", bgo_zyl_s, bgo_cons_s, nullptr, G4ThreeVector(0., 0., -(zyl_length + cone_length) / 2.));
    auto bgo_mat = G4Material::GetMaterial("BGO");
    auto bgo_vis = new G4VisAttributes(G4Color(0.8, 0., 0.1));
    bgo_vis->SetForceSolid(true);

    auto bgo_lv = new G4LogicalVolume(bgo_s, bgo_mat, "BGO_" + fName + "_bgo_lv");
    bgo_lv->SetVisAttributes(bgo_vis);
    new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), bgo_lv, "BGO_" + fName + "_bgo", fDetectorLV, false, 0, false);
}
