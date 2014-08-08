#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "Horus.hh"
#include "BGO.hh"

extern const std::vector<std::string> detectors = {/*"Ge00", "Ge01", "Ge02", "Ge03", "Ge04", "Ge05", "Ge06", "Ge07", "Ge08", "Ge09", "Ge10", "Ge11", "Ge12", "Ge13"*/};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
  fCheckOverlaps = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  DefineMaterials();
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_Cu");
  nistManager->FindOrBuildMaterial("G4_Al");
  nistManager->FindOrBuildMaterial("G4_Ge");

  G4Element*  O = nistManager->FindOrBuildElement("O");
  G4Element* Bi = nistManager->FindOrBuildElement("Bi");
  G4Element* Ge = nistManager->FindOrBuildElement("Ge");
  G4Material* BGO_Material = new G4Material("BGO", 7.13*g/cm3, 3);
  BGO_Material->AddElement(O,12);
  BGO_Material->AddElement(Bi,4);
  BGO_Material->AddElement(Ge,3);


  new G4Material("Galactic", 1, 1.01*g/mole, universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);
  new G4Material("Nothing", 1, 0, universe_mean_density, kStateUndefined, 0, 0);

  //G4cout << *(G4Material::GetMaterialTable()) << G4endl; // Print materials
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // World
  G4double worldSizeXYZ = 1.*m/2;
  G4Material* worldMaterial = G4Material::GetMaterial("Nothing");

  G4VSolid*           worldS  = new G4Box("World", worldSizeXYZ, worldSizeXYZ, worldSizeXYZ);
  G4LogicalVolume*    worldLV = new G4LogicalVolume(worldS, worldMaterial, "World");
                      worldLV->SetVisAttributes (G4VisAttributes::Invisible);
  G4VPhysicalVolume*  worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0, fCheckOverlaps);


  auto horus = new Horus(worldLV);
  // ID, Position, Distance to endcap / filter, BGO
  horus->PlaceHPGe("72442", "Ge00", 13.*cm, 2.*mm, true);
  horus->PlaceHPGe("73959", "Ge01", 10.*cm, 2.*mm);
  horus->PlaceHPGe("72341", "Ge02", 18.5*cm, 2.*mm, true);
  horus->PlaceHPGe("72309", "Ge03", 13.5*cm, 2.*mm, true);
  horus->PlaceHPGe("73954", "Ge04", 8.5*cm, 2.*mm);
  horus->PlaceHPGe("72980", "Ge05", 9.5*cm, 2.*mm);
  //horus->PlaceHPGe("73002", "Ge06", 10.*cm);
  horus->PlaceHPGe("73209", "Ge07", 18.*cm, 2.*mm, true);
  horus->PlaceHPGe("73211", "Ge08", 17.*cm, 2.*mm, true);
  horus->PlaceHPGe("72827", "Ge09", 16.*cm, 2.*mm, true);
  horus->PlaceHPGe("72812", "Ge10", 12.3*cm, 2.*mm);
  horus->PlaceHPGe("72811", "Ge11", 10.5*cm, 1.*mm);
  horus->PlaceHPGe("72802", "Ge12", 14.*cm, 2.*mm);
  horus->PlaceHPGe("72397", "Ge13", 12.5*cm, 2.*mm);

  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  for( auto &det : detectors ) {
    G4MultiFunctionalDetector* cryst = new G4MultiFunctionalDetector(det);
    G4VPrimitiveScorer* primitiv = new G4PSEnergyDeposit("edep");
    cryst->RegisterPrimitive(primitiv);
    SetSensitiveDetector("HPGe_" + det + "_crystal_logical",cryst);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
