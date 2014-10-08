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
  G4Material* filter_material  = G4Material::GetMaterial("G4_Cu");
  G4Material* hull_material    = G4Material::GetMaterial("G4_Al");
  G4Material* crystal_material = G4Material::GetMaterial("G4_Ge");
  G4Material* vacuum_material  = G4Material::GetMaterial("Galactic");

  G4double hull_inner_radius = spec.hull.diameter/2. - spec.hull.thickness;
  G4double filter_radius = spec.hull.diameter/2.;

  full_length = filter_thickness + spec.hull.thickness + spec.hull.padding + spec.hull.length;

  // Detector: container for all detector parts
  G4Tubs* detector_solid = new G4Tubs("HPGe_" + name + "_solid", 0, spec.hull.diameter/2., full_length/2., 0.*deg, 360.*deg);
  detector_logical = new G4LogicalVolume(detector_solid, vacuum_material, "HPGe_" + name + "_Logical");
  detector_logical->SetVisAttributes(G4VisAttributes::Invisible);

  // copper filter
  if(filter_thickness > 0.*mm){
    G4Tubs* filter_solid = new G4Tubs("HPGe_" + name + "_filter_solid", 0, filter_radius, filter_thickness/2., 0.*deg, 360.*deg);
    G4LogicalVolume* filter_logical = new G4LogicalVolume(filter_solid, filter_material, "HPGe_" + name + "_filter_logical");
    G4VisAttributes* filter_vis = new G4VisAttributes(G4Color(1.,0.5,0));
    filter_vis->SetForceSolid(true);
    filter_logical->SetVisAttributes(filter_vis);
    new G4PVPlacement(0, G4ThreeVector(0,0, -(full_length/2 - filter_thickness/2.)), filter_logical, "HPGe_" + name + "_filter", detector_logical, false, 0);
  }

  // hull front (endcap)
  G4Tubs* hull_front_solid = new G4Tubs("HPGe_" + name + "_hull_front_solid", 0, hull_inner_radius, spec.hull.thickness/2., 0.*deg, 360.*deg);
  G4LogicalVolume* hull_front_logical = new G4LogicalVolume(hull_front_solid, hull_material, "HPGe_" + name + "_hull_front_logical", 0, 0, 0);
  G4VisAttributes* hull_front_vis = new G4VisAttributes(G4Color(0.2,0.3,0.2,0.3));
  hull_front_vis->SetForceSolid(true);
  hull_front_logical->SetVisAttributes(hull_front_vis);
  new G4PVPlacement(0, G4ThreeVector(0, 0, -(full_length/2 - filter_thickness - spec.hull.thickness/2)), hull_front_logical, "HPGe_" + name + "_hull_front", detector_logical, false, 0);

  // hull
  G4Tubs* hull_solid = new G4Tubs("HPGe_" + name + "_hull_solid", hull_inner_radius, spec.hull.diameter/2., spec.hull.length/2., 0.*deg, 360.*deg);
  G4LogicalVolume* hull_logical = new G4LogicalVolume(hull_solid, hull_material, "HPGe_" + name + "_hull_logical", 0, 0, 0);
  G4VisAttributes* hull_vis = new G4VisAttributes(G4Color(0.2,0.3,0.2,0.3));
  hull_vis->SetForceSolid(true);
  hull_logical->SetVisAttributes(hull_vis);
  new G4PVPlacement(0, G4ThreeVector(0, 0, -(full_length/2 - filter_thickness - spec.hull.length/2)), hull_logical, "HPGe_" + name + "_hull", detector_logical, false, 0);


  // these values should be the same for all encapsulated detectors
  G4int nSides=6;
  G4int nZPlanes=2;

  G4double capsule_thickness = 0.7*mm; // Diss. Dirk Werner Weißhaar, Page 10
  G4double capsule_padding   = 0.7*mm; // Diss. Dirk Werner Weißhaar, Page 10

  G4double crystal_length[2]       = { + spec.crystal.length/2, - spec.crystal.length/2 };
  G4double capsule_inner_length[2] = { + (spec.crystal.length/2 + capsule_padding), - (spec.crystal.length/2 + capsule_padding) };
  G4double capsule_full_length[2]  = { + (spec.crystal.length/2 + capsule_padding + capsule_thickness), - (spec.crystal.length/2 + capsule_padding + capsule_thickness) };
  G4double capsule_length = capsule_full_length[0]*2.;

  G4double null_radius[2] = {0.*mm, 0.*mm};
  G4double crystal_radius[2] = { 59.*mm/2., 70.*mm/2. }; // Diss. Dirk Werner Weißhaar, Page 9
  G4double capsule_inner_radius[2] = { crystal_radius[0] + capsule_padding, crystal_radius[1] + capsule_padding };
  G4double capsule_outer_radius[2] = { capsule_inner_radius[0] + capsule_thickness, capsule_inner_radius[1] + capsule_thickness };

  G4double crystal_intersection_radius = crystal_radius[1];

  // Capsule (additional hull around the crystal) is build by subtracting a smaller (~> hull thickness) solid from the full solid
  G4Polyhedra* capsule_full_solid   = new G4Polyhedra("HPGe_" + name + "_capsule_full_solid",  0.*deg, 360.*deg, nSides, nZPlanes, capsule_full_length,  null_radius, capsule_outer_radius);
  G4Polyhedra* capsule_inner_solid  = new G4Polyhedra("HPGe_" + name + "_capsule_inner_solid", 0.*deg, 360.*deg, nSides, nZPlanes, capsule_inner_length, null_radius, capsule_inner_radius);
  G4VSolid*    capsule_solid = new G4SubtractionSolid("HPGe_" + name + "_capsule_solid", capsule_full_solid, capsule_inner_solid, 0, G4ThreeVector(0,0,0));
  G4LogicalVolume* capsule_logical = new G4LogicalVolume(capsule_solid, hull_material, "HPGe_" + name + "_capsule_logical", 0, 0, 0);
  capsule_logical->SetVisAttributes(hull_vis);
  G4RotationMatrix *rm = new G4RotationMatrix;
  rm->rotateX(180.*deg);
  new G4PVPlacement(rm, G4ThreeVector(0,0,-(full_length/2 - filter_thickness - spec.hull.thickness - spec.hull.padding - capsule_length/2)), capsule_logical, "Kapsel", detector_logical, false, 0);

  // Germanium Dead layer
  G4double dead_layer_arr[2]    = { + spec.crystal.dead_layer/2, - spec.crystal.dead_layer/2 };
  G4double dead_layer_radius[2] = { crystal_radius[0], crystal_radius[0] };
  G4Polyhedra*      crystal_dead_layer_solid   = new G4Polyhedra("HPGe_" + name + "_crystal_dead_layer_solid", 0.*deg, 360.*deg, nSides, nZPlanes, dead_layer_arr, null_radius, dead_layer_radius);
  G4LogicalVolume*  crystal_dead_layer_logical = new G4LogicalVolume(crystal_dead_layer_solid, crystal_material, "HPGe_" + name + "_crystal_dead_layer_logical", 0, 0, 0);
  G4VisAttributes*  crystal_dead_layer_vis     = new G4VisAttributes(G4Color(1,0.5,1));
                    crystal_dead_layer_vis->SetForceSolid(true);
                    crystal_dead_layer_logical->SetVisAttributes(crystal_dead_layer_vis);
  new G4PVPlacement(0,G4ThreeVector(0, 0, -(full_length/2 - filter_thickness - spec.hull.thickness - spec.hull.padding - capsule_thickness - capsule_padding - spec.crystal.dead_layer/2)), crystal_dead_layer_logical, "HPGe_" + name + "_crystal_dead_layer", detector_logical, false, 0);

  // Germanium crystal
  G4Tubs*      crystal_solid_tubs = new G4Tubs("HPGe_" + name + "_crystal_solid_tubs", 0.*cm, crystal_intersection_radius, spec.crystal.length/2., 0.*deg, 360.*deg);
  G4Polyhedra* crystal_solid_poly = new G4Polyhedra("HPGe_" + name + "_crystal_solid_poly", 0.*deg, 360.*deg, nSides, nZPlanes, crystal_length, null_radius, crystal_radius);
  G4VSolid*    crystal_solid_wo_hole = new G4IntersectionSolid("HPGe_" + name + "_crystal_solid", crystal_solid_tubs, crystal_solid_poly, 0, G4ThreeVector(0,0,0));

  G4Tubs*   crystal_hole_solid = new G4Tubs("HPGe_" + name + "_crystal_hole_solid", 0.*cm, spec.crystal.hole_diameter/2., spec.crystal.hole_length/2., 0.*deg, 360.*deg);
  G4VSolid* crystal_solid = new G4SubtractionSolid("HPGe_" + name + "_crystal_solid_with_hole", crystal_solid_wo_hole, crystal_hole_solid, 0, G4ThreeVector(0,0,-(spec.crystal.length/2.-spec.crystal.hole_length/2.)));


  G4LogicalVolume* crystal_logical = new G4LogicalVolume(crystal_solid, crystal_material, "HPGe_" + name + "_crystal_logical", 0, 0, 0);
  G4VisAttributes* crystal_vis = new G4VisAttributes(G4Color(0,0.5,1,0.5));
  crystal_vis->SetForceSolid(true);
  crystal_logical->SetVisAttributes(crystal_vis);
  new G4PVPlacement(rm, G4ThreeVector(0,0,-(full_length/2 - filter_thickness - spec.hull.thickness - spec.hull.padding - capsule_thickness - capsule_padding - spec.crystal.dead_layer - spec.crystal.length/2)), crystal_logical, "HPGe_" + name + "_crystal", detector_logical, false, 0);

  G4cout << "Id: " << spec.id << " - crystal volume: " << (crystal_solid->GetCubicVolume()/cm3 + crystal_dead_layer_solid->GetCubicVolume()/cm3) << "cm3 = " << crystal_solid->GetCubicVolume()*crystal_material->GetDensity()/g << "g" << G4endl;
  G4cout << "Id: " << spec.id << " - expected volume: " << spec.crystal.volume/cm3 << "cm3 = " << spec.crystal.volume*crystal_material->GetDensity()/g << "g" << G4endl;

  if( fabs((crystal_solid->GetCubicVolume()/cm3 + crystal_dead_layer_solid->GetCubicVolume()/cm3)/spec.crystal.volume - 1) > MAX_VOLUME_DIFFERENCE ){
    G4Exception("HPGe::Hexagonal::Hexagonal()", "Horus", JustWarning, ("Volume of detector " + spec.id + " does not match!").c_str() );
  }

}


HPGe::Hexagonal::~Hexagonal()
{}
