#include "HPGeCoaxial.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

//#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"

#include <vector>
#include <string>

const G4double HPGe::Coaxial::MAX_VOLUME_DIFFERENCE = 0.5*cm3;


HPGe::Coaxial::Coaxial(const _spec &spec, const std::string &name, const G4double &filter_thickness){
  G4Material* filter_material  = G4Material::GetMaterial("G4_Cu");
  G4Material* hull_material    = G4Material::GetMaterial("G4_Al");
  G4Material* crystal_material = G4Material::GetMaterial("G4_Ge");
  G4Material* vacuum_material  = G4Material::GetMaterial("Galactic");

  G4double hull_innerer_radius = spec.crystal.diameter/2. + spec.hull.padding;
  G4double hull_radius = spec.crystal.diameter/2. + spec.hull.padding + spec.hull.thickness;
  G4double filter_radius = hull_radius;

  full_length = filter_thickness + spec.hull.thickness + spec.hull.padding + spec.hull.length;

  // Detector: container for all detector parts
  G4Tubs* detector_solid = new G4Tubs("HPGe_" + name + "_solid", 0, hull_radius, full_length/2, 0.*deg, 360.*deg);
  detector_logical = new G4LogicalVolume(detector_solid, vacuum_material, "HPGe_" + name + "_Logical");
  detector_logical->SetVisAttributes(G4VisAttributes::Invisible);

  // copper filter
  if(filter_thickness > 0.*mm){
    G4Tubs* filter_solid = new G4Tubs("HPGe_" + name + "_filter_solid", 0, filter_radius, filter_thickness/2, 0.*deg, 360.*deg);
    G4LogicalVolume* filter_logical = new G4LogicalVolume(filter_solid, filter_material, "HPGe_" + name + "_filter_logical");
    G4VisAttributes* filter_vis = new G4VisAttributes(G4Color(1.,0.5,0));
    filter_vis->SetForceSolid(true);
    filter_logical->SetVisAttributes(filter_vis);
    new G4PVPlacement(0, G4ThreeVector(0,0, -(full_length/2 - filter_thickness/2)), filter_logical, "HPGe_" + name + "_filter", detector_logical, false, 0);
  }
  
  // hull front (endcap)
  G4Tubs* hull_front_solid = new G4Tubs("HPGe_" + name + "_hull_front_solid", 0, hull_innerer_radius, spec.hull.thickness/2, 0.*deg, 360.*deg);
  G4LogicalVolume* hull_front_logical = new G4LogicalVolume(hull_front_solid, hull_material, "HPGe_" + name + "_hull_front_logical", 0, 0, 0);
  G4VisAttributes* hull_front_vis = new G4VisAttributes(G4Color(0.2,0.3,0.2,0.5));
  hull_front_vis->SetForceSolid(true);
  hull_front_logical->SetVisAttributes(hull_front_vis);
  new G4PVPlacement(0, G4ThreeVector(0, 0, -(full_length/2 - filter_thickness - spec.hull.thickness/2)), hull_front_logical, "HPGe_" + name + "_hull_front", detector_logical, false, 0);

  // hull
  G4Tubs* hull_solid = new G4Tubs("HPGe_" + name + "_hull_solid", hull_innerer_radius, hull_radius, spec.hull.length/2, 0.*deg, 360.*deg);
  G4LogicalVolume* hull_logical = new G4LogicalVolume(hull_solid, hull_material, "HPGe_" + name + "_hull_logical", 0, 0, 0);
  G4VisAttributes* hull_vis = new G4VisAttributes(G4Color(0.2,0.3,0.2,0.5));
  hull_vis->SetForceSolid(true);
  hull_logical->SetVisAttributes(hull_vis);
  new G4PVPlacement(0, G4ThreeVector(0, 0, -(full_length/2 - filter_thickness - spec.hull.length/2)), hull_logical, "HPGe_" + name + "_hull", detector_logical, false, 0);

  // Germanium crystal and hole
  G4Tubs* coax_hole_solid = new G4Tubs("HPGe_" + name + "_crystal_hole_solid", 0.*cm, spec.crystal.hole_diameter/2, spec.crystal.hole_length/2, 0.*deg, 360.*deg);
  G4Tubs* crystal_solid   = new G4Tubs("HPGe_" + name + "_crystal_solid", 0.*cm, spec.crystal.diameter/2., spec.crystal.length/2., 0.*deg, 360.*deg);
  G4VSolid* crystal_solid_with_hole = new G4SubtractionSolid("HPGe_" + name + "_crystal_solid_with_hole", crystal_solid, coax_hole_solid, 0, G4ThreeVector(0,0,spec.crystal.length/2-spec.crystal.hole_length/2));
  G4LogicalVolume* crystal_logical = new G4LogicalVolume(crystal_solid_with_hole, crystal_material, "HPGe_" + name + "_crystal_logical", 0, 0, 0);
  G4VisAttributes* crystal_vis = new G4VisAttributes(G4Color(0,0.5,1));
  crystal_vis->SetForceSolid(true);
  crystal_logical->SetVisAttributes(crystal_vis);
  new G4PVPlacement(0,G4ThreeVector(0, 0, -(full_length/2 - filter_thickness - spec.hull.thickness - spec.hull.padding - spec.crystal.length/2)), crystal_logical, "HPGe_" + name + "_crystal", detector_logical, false, 0);



  G4cout << "Id: " << spec.id << " - hole " << coax_hole_solid->GetCubicVolume()/cm3 << "cm3" << G4endl;
  G4cout << "Id: " << spec.id << " - without hole " << crystal_solid->GetCubicVolume()/cm3 << "cm3" << G4endl;
  G4cout << "Id: " << spec.id << " - crystal volume: " << crystal_solid_with_hole->GetCubicVolume()/cm3 << "cm3" << G4endl;
  G4cout << "Id: " << spec.id << " - expected volume: " << spec.crystal.volume/cm3 << "cm3" << G4endl;

  if( fabs(crystal_solid_with_hole->GetCubicVolume()/cm3 - spec.crystal.volume/cm3)*cm3 > MAX_VOLUME_DIFFERENCE ){
    G4Exception("HPGe::Coaxial::Coaxial()", "Horus", JustWarning, ("Volume of detector " + spec.id + " does not match!").c_str() );
  }

}


HPGe::Coaxial::~Coaxial()
{}
