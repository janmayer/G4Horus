#include "Filter.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

Filter::Filter(const Filter::_filter& f, G4double width)
    : Filter(f.material, f.length, width)
{
}

Filter::Filter(const std::string& material, G4double length, G4double diameter)
    : Detector("Filter", length)
{
    fWidth = diameter;

    auto sV = new G4Tubs(fName + "_filter_solid_" + material, 0, diameter / 2., length / 2., 0. * deg, 360. * deg);
    auto lV = new G4LogicalVolume(sV, G4Material::GetMaterial(material), fName + "_filter_logical_" + material);

    auto vis = G4VisAttributes(G4Color(1., 0.5, 0));
    vis.SetForceSolid(true);
    lV->SetVisAttributes(vis);

    fDetectorLV = lV;
}
