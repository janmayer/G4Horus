#include "PIPS.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include <utility>

PIPS::PIPS(const std::string& name)
    : Detector(name)
{
    G4Material* vacuum_material = G4Material::GetMaterial("Galactic");

    G4Material* hull_material = G4Material::GetMaterial("G4_Al");
    G4VisAttributes* hull_vis = new G4VisAttributes(G4Color(0.5, 0.5, 0.5));
    hull_vis->SetForceSolid(true);

    G4Material* active_material = G4Material::GetMaterial("G4_Si"); //TODO change Back to Sili
    G4VisAttributes* active_vis = new G4VisAttributes(G4Color(1, 0, 0));
    active_vis->SetForceSolid(true);

    G4bool fCheckOverlaps = true;

    G4double front_thick = 1. * mm;
    G4double front_inner = 6.9 * mm;
    G4double front_outer = 13.1 * mm;
    fWidth = front_outer;

    G4double side_thick = 9. * mm - front_thick * 2.;
    G4double side_inner = front_outer - 3. * mm;
    G4double side_outer = front_outer;

    G4double back_thick = front_thick;
    G4double back_inner = front_inner;
    G4double back_outer = front_outer;

    G4double active_thick = 1500.0 * um;
    G4double active_outer = front_inner;

    G4double dead_front_outer = front_inner;
    G4double dead_front_thick = 50.0 * nm;

    G4double dead_back_outer = back_inner;
    G4double dead_back_thick = 160.0 * nm;

    fLength = front_thick + side_thick + back_thick;

    // Container for all detector parts
    G4Tubs* envS = new G4Tubs("PIPS_" + name + "_envelope_solid", 0, front_outer, fLength / 2., 0. * deg, 360. * deg);
    fDetectorLV = new G4LogicalVolume(envS, vacuum_material, "PIPS_" + name + "_envelope_logical");
    fDetectorLV->SetVisAttributes(G4VisAttributes::Invisible);

    // Front
    G4ThreeVector front_pos = G4ThreeVector(0, 0, -fLength / 2. + front_thick / 2.);
    G4Tubs* frontS = new G4Tubs("PIPS_" + name + "_front_solid", front_inner, front_outer, front_thick / 2., 0. * deg, 360. * deg);
    G4LogicalVolume* frontLV = new G4LogicalVolume(frontS, hull_material, "PIPS_" + name + "_front_logical");
    frontLV->SetVisAttributes(hull_vis);
    new G4PVPlacement(nullptr, front_pos, frontLV, "PIPS_" + name + "_front", fDetectorLV, false, 0, fCheckOverlaps);

    // Side
    G4ThreeVector side_pos = G4ThreeVector(0, 0, -fLength / 2. + front_thick + side_thick / 2.);
    G4Tubs* sideS = new G4Tubs("PIPS_" + name + "_side_solid", side_inner, side_outer, side_thick / 2., 0. * deg, 360. * deg);
    G4LogicalVolume* sideLV = new G4LogicalVolume(sideS, hull_material, "PIPS_" + name + "_side_logical");
    sideLV->SetVisAttributes(hull_vis);
    new G4PVPlacement(nullptr, side_pos, sideLV, "PIPS_" + name + "_side", fDetectorLV, false, 0, fCheckOverlaps);

    // Back
    G4ThreeVector back_pos = G4ThreeVector(0, 0, -fLength / 2. + front_thick + side_thick + back_thick / 2.);
    G4Tubs* backS = new G4Tubs("PIPS_" + name + "_back_solid", back_inner, back_outer, back_thick / 2., 0. * deg, 360. * deg);
    G4LogicalVolume* backLV = new G4LogicalVolume(backS, hull_material, "PIPS_" + name + "_back_logical");
    backLV->SetVisAttributes(hull_vis);
    new G4PVPlacement(nullptr, back_pos, backLV, "PIPS_" + name + "_back", fDetectorLV, false, 0, fCheckOverlaps);

    // Active
    G4ThreeVector active_pos = G4ThreeVector(0, 0, -fLength / 2. + front_thick + active_thick / 2.);
    G4Tubs* activeS = new G4Tubs("PIPS_" + name + "_active_solid", 0, active_outer, active_thick / 2., 0. * deg, 360. * deg);
    G4LogicalVolume* activeLV = new G4LogicalVolume(activeS, active_material, "PIPS_" + name + "_active_logical");
    activeLV->SetVisAttributes(active_vis);
    new G4PVPlacement(nullptr, active_pos, activeLV, "PIPS_" + name + "_active", fDetectorLV, false, 0, fCheckOverlaps);

    // Deadlayer front
    G4ThreeVector dead_front_pos = G4ThreeVector(0, 0, -fLength / 2. + front_thick - dead_front_thick / 2.);
    G4Tubs* dead_frontS = new G4Tubs("PIPS_" + name + "_dead_front_solid", 0, dead_front_outer, dead_front_thick / 2., 0. * deg, 360. * deg);
    G4LogicalVolume* dead_frontLV = new G4LogicalVolume(dead_frontS, active_material, "PIPS_" + name + "_dead_front_logical");
    dead_frontLV->SetVisAttributes(G4VisAttributes::Invisible);
    new G4PVPlacement(nullptr, dead_front_pos, dead_frontLV, "Dead_front", fDetectorLV, false, 0, fCheckOverlaps);

    // Deadlayer back
    G4ThreeVector dead_back_pos = G4ThreeVector(0, 0, -fLength / 2. + front_thick + active_thick + dead_back_thick / 2.);
    G4Tubs* dead_backS = new G4Tubs("PIPS_" + name + "_dead_back_solid", 0, dead_back_outer, dead_back_thick / 2., 0. * deg, 360. * deg);
    G4LogicalVolume* dead_backLV = new G4LogicalVolume(dead_backS, active_material, "PIPS_" + name + "_dead_back_logical");
    dead_backLV->SetVisAttributes(G4VisAttributes::Invisible);
    new G4PVPlacement(nullptr, dead_back_pos, dead_backLV, "PIPS_" + name + "_dead_back", fDetectorLV, false, 0, fCheckOverlaps);
}
