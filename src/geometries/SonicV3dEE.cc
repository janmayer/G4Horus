#include "SonicV3dEE.hh"
#include "CADElement.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4AssemblyVolume.hh"
#include "G4Color.hh"
#include "G4INCLThreeVector.hh"
#include "G4IntersectionSolid.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4Polyhedra.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4VisAttributes.hh"

// clang-format off
SonicV3dEE::SonicV3dEE(G4LogicalVolume* worldLV, bool hasTaShield)
    : Setup(worldLV, {{"Si00", {145. * deg,  45. * deg}},
                      {"Si01", {145. * deg, 135. * deg}},
                      {"Si02", {145. * deg, 225. * deg}},
                      {"Si03", {145. * deg, 315. * deg}},
                      {"Si04", {123. * deg,   0. * deg}},
                      {"Si05", {123. * deg,  90. * deg}},
                      {"Si06", {123. * deg, 180. * deg}},
                      {"Si07", {123. * deg, 270. * deg}},
                      {"Si08", {107. * deg,  45. * deg}},
                      {"Si09", {107. * deg, 135. * deg}},
                      {"Si10", {107. * deg, 225. * deg}},
                      {"Si11", {107. * deg, 315. * deg}},
                     })
// clang-format on
{
    auto rot = new G4RotationMatrix();
    rot->rotateX(180. * deg);

    const std::vector<CADElement> elements = {
        {"SonicV3dEE-Al-Chamber", "G4_Al", G4Color(0.517, 0.529, 0.537)},
        {"SonicV3dEE-Al-ChamberCap", "G4_Al", G4Color(0.517, 0.529, 0.537)},
        {"SonicV3dEE-Al-Base", "G4_Al", G4Color(0.517, 0.529, 0.537)},
        // {"SonicV3dEE-Plastic-Detectormount", "G4_POLYCARBONATE", G4Color(1, 1, 1)}
    };

    for (const auto& element : elements) {
        element.Place(worldLV, rot);
    }

    // place tantalum shield here
    if (hasTaShield) {
        const G4double delta = 0.09875; //correction value to prevent overlap with cad modell
        const G4double Ta_thickness = 0.2 * mm; //measured
        const G4double Ta_long_tube_length = 120.1 * mm; //measured
        const G4double Ta_long_tube_diameter = (32.0 - delta) * mm; //measured
        const G4double Ta_small_ring_radius = 3.25 * mm; //measured
        const G4double Ta_medium_ring_diameter = 75.3 * mm; //measured
        const G4double Ta_large_ring_diameter = 111.6 * mm; //measured
        const G4double distFromMidpoint = (200 / 8 - 1.5) * mm; //correction value to place shield adjacent to and touching SONIC Backplate/ChamberCap

        auto tantal = G4Material::GetMaterial("G4_Ta");
        G4RotationMatrix* rm = new G4RotationMatrix();
        auto Sonic_Ta_Long_Tube = new G4Tubs("SonicV3dEE-Ta-Long_Tube", Ta_long_tube_diameter / 2. - Ta_thickness, Ta_long_tube_diameter / 2., Ta_long_tube_length / 2., 0.0 * deg, 360.0 * deg);
        auto Sonic_Ta_Small_Ring = new G4Tubs("SonicVdEE-Ta-Small_Ring", Ta_long_tube_diameter / 2. - Ta_thickness, Ta_long_tube_diameter / 2. - Ta_thickness + Ta_small_ring_radius, Ta_thickness / 2., 0.0 * deg, 360.0 * deg);
        auto Sonic_Ta_Medium_Ring = new G4Tubs("SonicV3dEE-Ta-Medium_Ring", Ta_long_tube_diameter / 2., Ta_medium_ring_diameter / 2., Ta_thickness / 2., 0.0 * deg, 360.0 * deg);
        auto Sonic_Ta_Large_Ring = new G4Tubs("SonicV3dEE-Ta-Large_Ring", Ta_long_tube_diameter / 2., Ta_large_ring_diameter / 2., Ta_thickness / 2., 0.0 * deg, 360.0 * deg);
        auto Sonic_Ta_Shield = new G4UnionSolid("SonicV3dEE-Ta-Shield", Sonic_Ta_Small_Ring, Sonic_Ta_Long_Tube, rm, G4ThreeVector(0.0, 0.0, Ta_long_tube_length / 2. + Ta_thickness / 2.));
        Sonic_Ta_Shield = new G4UnionSolid("SonicV3dEE-Ta-Shield", Sonic_Ta_Shield, Sonic_Ta_Medium_Ring, rm, G4ThreeVector(0.0, 0.0, Ta_thickness));
        Sonic_Ta_Shield = new G4UnionSolid("SonicV3dEE-Ta-Shield", Sonic_Ta_Shield, Sonic_Ta_Large_Ring, rm, G4ThreeVector(0.0, 0.0, Ta_thickness * 2.));
        auto Sonic_Ta_Shield_logical = new G4LogicalVolume(Sonic_Ta_Shield, tantal, "SonicV3dEE_Shield_Logical");

        auto shield_vis = G4VisAttributes(G4Color(1.0, 1.0, 1.0, 0.8));
        shield_vis.SetForceSolid(true);
        Sonic_Ta_Shield_logical->SetVisAttributes(shield_vis);
        new G4PVPlacement(rm, G4ThreeVector(0.0, 0.0, distFromMidpoint), Sonic_Ta_Shield_logical, "SonicV3dEE-Ta-Shield_pV", worldLV, false, 0, true);
    }
}
