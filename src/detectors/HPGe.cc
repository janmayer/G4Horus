#include "HPGe.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include <numeric>
#include <utility>

namespace HPGe {

HPGe::HPGe(_spec spec, std::string name)
    : Detector(std::move(name))
    , fSpec(std::move(spec))
{
    fLength = fSpec.hull.thickness + fSpec.hull.length;
    fWidth = fSpec.hull.diameter;

    // container for all detector parts
    auto sV = new G4Tubs("HPGe_" + fName + "_solid", 0, fSpec.hull.diameter / 2., fLength / 2., 0. * deg, 360. * deg);
    fDetectorLV = new G4LogicalVolume(sV, G4Material::GetMaterial("Galactic"), "HPGe_" + fName + "_Logical");

    auto vis = G4VisAttributes(G4Color(0.1, 0.1, 0.1, 0.1));
    vis.SetForceSolid(true);
    fDetectorLV->SetVisAttributes(vis);
}

G4LogicalVolume* HPGe::BuildHull()
{
    auto sV = new G4Tubs("HPGe_" + fName + "_hull_solid", fSpec.hull.diameter / 2. - fSpec.hull.thickness, fSpec.hull.diameter / 2., fSpec.hull.length / 2., 0. * deg, 360. * deg);
    auto lV = new G4LogicalVolume(sV, G4Material::GetMaterial("G4_Al"), "HPGe_" + fName + "_hull_logical");

    auto vis = G4VisAttributes(G4Color(0.2, 0.3, 0.2, 0.3));
    vis.SetForceSolid(true);
    lV->SetVisAttributes(vis);

    return lV;
}

G4LogicalVolume* HPGe::BuildHullFront()
{
    auto sV = new G4Tubs("HPGe_" + fName + "_hull_front_solid", 0, fSpec.hull.diameter / 2. - fSpec.hull.thickness, fSpec.hull.endcap_thickness / 2., 0. * deg, 360. * deg);
    auto lV = new G4LogicalVolume(sV, G4Material::GetMaterial("G4_Al"), "HPGe_" + fName + "_hull_front_logical");

    auto vis = G4VisAttributes(G4Color(0.2, 0.3, 0.2, 0.3));
    vis.SetForceSolid(true);
    lV->SetVisAttributes(vis);

    return lV;
}

} // namespace HPGe
