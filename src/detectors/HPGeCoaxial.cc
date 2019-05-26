#include "HPGeCoaxial.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "Randomize.hh"
#include <numeric>

HPGe::Coaxial::Coaxial(const _spec& spec, const std::string& name)
    : HPGe(spec, name)
{
    // hull front (endcap)
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -(fLength / 2 - fSpec.hull.endcap_thickness / 2)), this->BuildHullFront(), "HPGe_" + name + "_hull_front", fDetectorLV, false, 0, fSpec.check_overlaps);

    // hull
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -(fLength / 2 - fSpec.hull.length / 2)), this->BuildHull(), "HPGe_" + name + "_hull", fDetectorLV, false, 0, fSpec.check_overlaps);

    // Germanium Dead layer
    auto crystal_dead_layer_solid = new G4Tubs("HPGe_" + name + "_crystal_dead_layer_solid", 0. * cm, spec.crystal.diameter / 2., spec.crystal.dead_layer / 2, 0. * deg, 360. * deg);
    auto crystal_dead_layer_logical = new G4LogicalVolume(crystal_dead_layer_solid, G4Material::GetMaterial("G4_Ge"), "HPGe_" + name + "_crystal_dead_layer_logical");
    auto crystal_dead_layer_vis = G4VisAttributes(G4Color(1, 0.5, 1));
    crystal_dead_layer_vis.SetForceSolid(true);
    crystal_dead_layer_logical->SetVisAttributes(crystal_dead_layer_vis);
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -(fLength / 2 - spec.hull.thickness - spec.hull.padding - spec.crystal.dead_layer / 2)), crystal_dead_layer_logical, "HPGe_" + name + "_crystal_dead_layer", fDetectorLV, false, 0, spec.check_overlaps);

    // Germanium crystal and hole
    auto coax_hole_solid = new G4Tubs("HPGe_" + name + "_crystal_hole_solid", 0. * cm, spec.crystal.hole_diameter / 2., spec.crystal.hole_length / 2., 0. * deg, 360. * deg);
    auto crystal_solid = new G4Tubs("HPGe_" + name + "_crystal_solid", 0. * cm, spec.crystal.diameter / 2., spec.crystal.length / 2., 0. * deg, 360. * deg);
    auto crystal_solid_with_hole = new G4SubtractionSolid("HPGe_" + name + "_crystal_solid_with_hole", crystal_solid, coax_hole_solid,
                                                          nullptr, G4ThreeVector(0, 0, spec.crystal.length / 2 - spec.crystal.hole_length / 2));
    auto crystal_logical = new G4LogicalVolume(crystal_solid_with_hole, G4Material::GetMaterial("G4_Ge"), "HPGe_" + name + "_crystal_logical");
    auto crystal_vis = G4VisAttributes(G4Color(0, 0.5, 1));
    crystal_vis.SetForceSolid(true);
    crystal_logical->SetVisAttributes(crystal_vis);
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -(fLength / 2 - spec.hull.thickness - spec.hull.padding - spec.crystal.dead_layer - spec.crystal.length / 2)), crystal_logical, "HPGe_" + name + "_crystal", fDetectorLV, false, 0, spec.check_overlaps);

    G4cout << "Id: " << spec.id << " - crystal volume: " << crystal_solid_with_hole->GetCubicVolume() / cm3 + crystal_dead_layer_solid->GetCubicVolume() / cm3 << "cm3" << G4endl;
    G4cout << "Id: " << spec.id << " - expected volume: " << spec.crystal.volume / cm3 << "cm3" << G4endl;

    // cryo finger?
    auto cryo_solid = new G4Tubs("HPGe_" + name + "_cryo_solid", 0. * cm, spec.crystal.hole_diameter / 2. - 0.5 * mm, spec.crystal.hole_length / 2, 0. * deg, 360. * deg);
    auto cryo_logical = new G4LogicalVolume(cryo_solid, G4Material::GetMaterial("G4_Al"), "HPGe_" + name + "_cryo_logical");
    auto cryo_vis = G4VisAttributes(G4Color(1., 0.5, 0));
    cryo_vis.SetForceSolid(true);
    cryo_logical->SetVisAttributes(cryo_vis);
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -(fLength / 2. - spec.hull.thickness - spec.hull.padding - spec.crystal.dead_layer - (spec.crystal.length - spec.crystal.hole_length) - spec.crystal.hole_length / 2)), cryo_logical, "HPGe_" + name + "_cryo", fDetectorLV, false, 0, spec.check_overlaps);
}
