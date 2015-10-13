#include "HPGeHexagonal.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4Tubs.hh"
#include "G4Polyhedra.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"

#include <vector>
#include <string>

HPGe::Hexagonal::Hexagonal(const _spec &spec, const std::string &name, const G4double &filter_thickness){
  G4Material* hull_material    = G4Material::GetMaterial("G4_Al");
  G4VisAttributes* hull_vis    = new G4VisAttributes(G4Color( 0.2, 0.3, 0.2, 0.8 )); hull_vis->SetForceSolid(true);

  G4Material* filter_material  = G4Material::GetMaterial("G4_Cu");
  G4VisAttributes* filter_vis  = new G4VisAttributes(G4Color( 1. , 0.5, 0  , 0   )); filter_vis->SetForceSolid(true);

  G4Material* crystal_material = G4Material::GetMaterial("G4_Ge");
  G4VisAttributes* crystal_vis = new G4VisAttributes(G4Color( 0  , 0.5, 1  , 0.7 )); crystal_vis->SetForceSolid(true);
  G4VisAttributes* crystal_dead_layer_vis = new G4VisAttributes(G4Color(1,0.5,1,0.7)); crystal_dead_layer_vis->SetForceSolid(true);

  G4Material* vacuum_material  = G4Material::GetMaterial("Galactic");

  G4RotationMatrix *rm = new G4RotationMatrix;
  rm->rotateX(180.*deg);


  G4double capsule_length = 91.*mm;
  G4double capsule_base_radius = 62.7*mm/2.;
  G4double capsule_thickness = 0.7*mm;
  G4double capsule_padding   = 0.7*mm;

  full_length = filter_thickness + spec.hull.thickness + spec.hull.padding + spec.hull.length;


  // Detector: container for all detector parts
  G4Tubs* detector_solid = new G4Tubs("HPGe_" + name + "_solid", 0, spec.hull.diameter/2., full_length/2., 0.*deg, 360.*deg);
  detector_logical = new G4LogicalVolume(detector_solid, vacuum_material, "HPGe_" + name + "_Logical");
  detector_logical->SetVisAttributes(G4VisAttributes::Invisible);

  // copper filter
  if(filter_thickness > 0.*mm){
    G4Tubs* filter_solid = new G4Tubs("HPGe_" + name + "_filter_solid", 0, spec.hull.diameter/2., filter_thickness/2., 0.*deg, 360.*deg);
    G4LogicalVolume* filter_logical = new G4LogicalVolume(filter_solid, filter_material, "HPGe_" + name + "_filter_logical");
    filter_logical->SetVisAttributes(filter_vis);
    new G4PVPlacement(0, G4ThreeVector(0,0, -(full_length/2. - filter_thickness/2.)), filter_logical, "HPGe_" + name + "_filter", detector_logical, false, 0, spec.check_overlaps);
  }

  // hull front (endcap)
  G4Tubs* hull_front_solid = new G4Tubs("HPGe_" + name + "_hull_front_solid", 0, spec.hull.diameter/2.-spec.hull.thickness, spec.hull.thickness/2., 0.*deg, 360.*deg);
  G4LogicalVolume* hull_front_logical = new G4LogicalVolume(hull_front_solid, hull_material, "HPGe_" + name + "_hull_front_logical", 0, 0, 0);
  hull_front_logical->SetVisAttributes(hull_vis);
  new G4PVPlacement(0, G4ThreeVector(0, 0, -(full_length/2. - filter_thickness - spec.hull.thickness/2.)), hull_front_logical, "HPGe_" + name + "_hull_front", detector_logical, false, 0, spec.check_overlaps);

  // hull
  G4Tubs* hull_solid = new G4Tubs("HPGe_" + name + "_hull_solid", spec.hull.diameter/2.-spec.hull.thickness, spec.hull.diameter/2., spec.hull.length/2., 0.*deg, 360.*deg);
  G4LogicalVolume* hull_logical = new G4LogicalVolume(hull_solid, hull_material, "HPGe_" + name + "_hull_logical", 0, 0, 0);
  hull_logical->SetVisAttributes(hull_vis);
  new G4PVPlacement(0, G4ThreeVector(0, 0, -(full_length/2. - filter_thickness - spec.hull.length/2.)), hull_logical, "HPGe_" + name + "_hull", detector_logical, false, 0, spec.check_overlaps);

  // Capsule (additional hull around the crystal) is build by subtracting a smaller (~> hull thickness) solid from the full solid
  G4VSolid* capsule_full_solid  = HexShape("HPGe_" + name + "_capsule_full",  capsule_base_radius, capsule_length/2.);
  G4VSolid* capsule_inner_solid = HexShape("HPGe_" + name + "_capsule_inner", capsule_base_radius - capsule_thickness, capsule_length/2. - capsule_thickness);
  G4VSolid* capsule_solid = new G4SubtractionSolid("HPGe_" + name + "_capsule_solid", capsule_full_solid, capsule_inner_solid, 0, G4ThreeVector());
  G4LogicalVolume* capsule_logical = new G4LogicalVolume(capsule_solid, hull_material, "HPGe_" + name + "_capsule_logical", 0, 0, 0);
  capsule_logical->SetVisAttributes(hull_vis);
  new G4PVPlacement(rm, G4ThreeVector(0, 0, -(full_length/2. - filter_thickness - spec.hull.thickness - spec.hull.padding - capsule_length/2.)), capsule_logical, "HPGe_" + name + "_capsule", detector_logical, false, 0, spec.check_overlaps);

  // Germanium Dead layer
  G4double gdl_l[2]  = {spec.crystal.dead_layer/2.,-spec.crystal.dead_layer/2.};
  G4double gdl_r1[2] = {0, 0};
  G4double gdl_r2[2] = {spec.crystal.diameter/2., spec.crystal.diameter/2.};
  G4Polyhedra* crystal_dead_layer_solid = new G4Polyhedra(name + "_poly_S", 0.*deg, 360.*deg, 6, 2, gdl_l, gdl_r1, gdl_r2);
  G4LogicalVolume*  crystal_dead_layer_logical = new G4LogicalVolume(crystal_dead_layer_solid, crystal_material, "HPGe_" + name + "_crystal_dead_layer_logical", 0, 0, 0);
                    crystal_dead_layer_logical->SetVisAttributes(crystal_dead_layer_vis);
  new G4PVPlacement(rm, G4ThreeVector(0, 0, -(full_length/2. - filter_thickness - spec.hull.thickness - spec.hull.padding - capsule_thickness - capsule_padding - spec.crystal.dead_layer/2.)), crystal_dead_layer_logical, "HPGe_" + name + "_crystal_dead_layer", detector_logical, false, 0, spec.check_overlaps);

  // Germanium crystal
  G4VSolid* crystal_solid_wo_hole = HexShape("HPGe_" + name + "_crystal", spec.crystal.diameter/2., spec.crystal.length/2.);
  G4Tubs*   crystal_hole_solid = new G4Tubs("HPGe_" + name + "_crystal_hole_solid", 0.*cm, spec.crystal.hole_diameter/2., spec.crystal.hole_length/2., 0.*deg, 360.*deg);
  G4VSolid* crystal_solid = new G4SubtractionSolid("HPGe_" + name + "_crystal_solid_with_hole", crystal_solid_wo_hole, crystal_hole_solid, 0, G4ThreeVector(0,0,-(spec.crystal.length/2.-spec.crystal.hole_length/2.)));
  G4LogicalVolume* crystal_logical = new G4LogicalVolume(crystal_solid, crystal_material, "HPGe_" + name + "_crystal_logical", 0, 0, 0);
  crystal_logical->SetVisAttributes(crystal_vis);
  new G4PVPlacement(rm, G4ThreeVector(0, 0, -(full_length/2. - filter_thickness - spec.hull.thickness - spec.hull.padding - capsule_thickness - capsule_padding - spec.crystal.dead_layer - spec.crystal.length/2.)), crystal_logical, "HPGe_" + name + "_crystal", detector_logical, false, 0, spec.check_overlaps);


  // Germanium Volume check
  G4double volume = crystal_solid->GetCubicVolume() + crystal_dead_layer_solid->GetCubicVolume();
  G4cout << "HPGe: " << name << " with Id: " << spec.id << " - crystal volume:  " << volume/cm3 << "cm3 = " << volume*crystal_material->GetDensity()/g << "g" << G4endl;
  G4cout << "HPGe: " << name << " with Id: " << spec.id << " - expected volume: " << spec.crystal.volume/cm3 << "cm3 = " << spec.crystal.volume*crystal_material->GetDensity()/g << "g" << G4endl;
  G4cout << "HPGe: " << name << " with Id: " << spec.id << " - capsule mass:  " << capsule_solid->GetCubicVolume()*hull_material->GetDensity()/g << "g" << G4endl;
  /*if( fabs(volume/spec.crystal.volume - 1) > MAX_VOLUME_DIFFERENCE ){
    G4Exception("HPGe::Hexagonal::Hexagonal()", "Horus", JustWarning, ("Volume of detector " + spec.id + " does not match!").c_str() );
  }*/

  //cryo finger
  G4Tubs*   cryo_solid = new G4Tubs("HPGe_" + name + "_cryo_solid", 0.*cm, spec.crystal.hole_diameter/2. - 0.5*mm, spec.crystal.hole_length/2, 0.*deg, 360.*deg);
  G4LogicalVolume* cryo_logical = new G4LogicalVolume(cryo_solid, hull_material, "HPGe_" + name + "_cryo_logical", 0, 0, 0);
  cryo_logical->SetVisAttributes(hull_vis);
  new G4PVPlacement(0, G4ThreeVector(0,0,-(full_length/2. - filter_thickness - spec.hull.thickness - spec.hull.padding - capsule_thickness - capsule_padding - spec.crystal.dead_layer - (spec.crystal.length-spec.crystal.hole_length) - spec.crystal.hole_length/2 )), cryo_logical, "HPGe_" + name + "_cryo", detector_logical, false, 0, spec.check_overlaps);
}


G4VSolid* HPGe::Hexagonal::HexShape(const std::string &name, const G4double &base_radius, const G4double &half_length){
  const G4double angle = 4.125*deg;

  G4double top_radius = base_radius + tan(angle)*(half_length*2.);

  G4double poly_r1[2] = { 0, 0 };
  G4double poly_r2[2] = { base_radius, top_radius };
  G4double poly_l[2]  = { half_length, -half_length };

  return new G4IntersectionSolid(
    name + "_is_S",
    new G4Tubs(name + "_tubs_S", 0, top_radius, half_length, 0.*deg, 360.*deg),
    new G4Polyhedra(name + "_poly_S", 0.*deg, 360.*deg, 6, 2, poly_l, poly_r1, poly_r2),
    0,
    G4ThreeVector()
  );

}


HPGe::Hexagonal::~Hexagonal()
{}
