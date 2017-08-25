#include "DummyChamber.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

DummyChamber::DummyChamber(G4LogicalVolume* worldLV)
{
    auto sV = new G4Sphere("DummyChamber_solid", 60. * mm - 2. * mm, 60. * mm, 0. * deg, 360. * deg, 0. * deg, 360. * deg);

    auto aluminum = G4Material::GetMaterial("G4_Al");
    auto lV = new G4LogicalVolume(sV, aluminum, "DummyChamber_logical");
    auto vis = G4VisAttributes(G4Color(0.5, 0.5, 0.5, 1));
    vis.SetForceSolid(true);
    lV->SetVisAttributes(vis);

    new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), lV, "DummyChamber", worldLV, false, 0);
}
