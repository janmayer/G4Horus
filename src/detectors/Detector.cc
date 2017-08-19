#include "Detector.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

Detector::Detector(const G4String& name, const G4double& length)
    : fDetectorLV(nullptr)
    , fLength(length)
    , fName(name)
{
}

G4LogicalVolume* Detector::BuildFilter(const _filter& filter, const G4double& diameter)
{
    auto sV = new G4Tubs("Filter_" + fName + "_filter_solid_" + filter.material, 0, diameter / 2., filter.thickness / 2., 0. * deg, 360. * deg);
    auto lV = new G4LogicalVolume(sV, G4Material::GetMaterial(filter.material), "Filter_" + fName + "_filter_logical_" + filter.material);

    auto vis = G4VisAttributes(G4Color(1., 0.5, 0));
    vis.SetForceSolid(true);
    lV->SetVisAttributes(vis);

    return lV;
}
