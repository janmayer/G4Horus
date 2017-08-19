#include "HPGe.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include <numeric>

namespace HPGe {

HPGe::HPGe(const _spec& spec, const std::string& name, const std::vector<Detector::_filter>& filters)
    : Detector(name)
    , fSpec(spec)
    , fFilterLength(std::accumulate(filters.begin(), filters.end(), G4double(0.), [](const G4double sum, const Detector::_filter& f) { return sum + f.thickness; }))
{
    fLength = fFilterLength + fSpec.hull.thickness + fSpec.hull.length;

    // container for all detector parts
    auto sV = new G4Tubs("HPGe_" + name + "_solid", 0, fSpec.hull.diameter / 2., fLength / 2., 0. * deg, 360. * deg);
    fDetectorLV = new G4LogicalVolume(sV, G4Material::GetMaterial("Galactic"), "HPGe_" + name + "_Logical");
    fDetectorLV->SetVisAttributes(G4VisAttributes::Invisible);

    // filter
    for (auto ifilter = filters.begin(); ifilter != filters.end(); ifilter++) {
        auto cur_thickness = std::accumulate(ifilter, filters.end(), G4double(0.), [](const G4double sum, const Detector::_filter& f) { return sum + f.thickness; });
        new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -(fLength / 2 - cur_thickness + (*ifilter).thickness / 2.)), BuildFilter(*ifilter, fSpec.hull.diameter), "HPGe_" + name + "_filter" + (*ifilter).material, fDetectorLV, false, 0, fSpec.check_overlaps);
    }

    // hull front (endcap)
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -(fLength / 2 - fFilterLength - fSpec.hull.thickness / 2)), BuildHullFront(), "HPGe_" + name + "_hull_front", fDetectorLV, false, 0, fSpec.check_overlaps);

    // hull
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -(fLength / 2 - fFilterLength - fSpec.hull.length / 2)), BuildHull(), "HPGe_" + name + "_hull", fDetectorLV, false, 0, fSpec.check_overlaps);
}

G4LogicalVolume* HPGe::BuildHull()
{
    auto sV = new G4Tubs("HPGe_" + fName + "_hull_solid", fSpec.hull.diameter / 2. - fSpec.hull.thickness, fSpec.hull.diameter / 2., fSpec.hull.length / 2., 0. * deg, 360. * deg);
    auto lV = new G4LogicalVolume(sV, G4Material::GetMaterial("G4_Al"), "HPGe_" + fName + "_hull_logical");

    auto vis = G4VisAttributes(G4Color(0.2, 0.3, 0.2, 0.8));
    vis.SetForceSolid(true);
    lV->SetVisAttributes(vis);

    return lV;
}

G4LogicalVolume* HPGe::BuildHullFront()
{
    auto sV = new G4Tubs("HPGe_" + fName + "_hull_front_solid", 0, fSpec.hull.diameter / 2. - fSpec.hull.thickness, fSpec.hull.thickness / 2., 0. * deg, 360. * deg);
    auto lV = new G4LogicalVolume(sV, G4Material::GetMaterial("G4_Al"), "HPGe_" + fName + "_hull_front_logical");

    auto vis = G4VisAttributes(G4Color(0.2, 0.3, 0.2, 0.8));
    vis.SetForceSolid(true);
    lV->SetVisAttributes(vis);

    return lV;
}

} // namespace HPGe
