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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
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
  horus->PlaceHPGe("73950","Ge00",10.*cm);
  horus->PlaceHPGe("73951","Ge01",10.*cm);
  horus->PlaceHPGe("73952","Ge02",10.*cm);
  horus->PlaceHPGe("73953","Ge03",10.*cm);
  horus->PlaceHPGe("73954","Ge04",10.*cm);
  horus->PlaceHPGe("73955","Ge05",10.*cm);
  horus->PlaceHPGe("73956","Ge06",10.*cm);
  horus->PlaceHPGe("73957","Ge07",10.*cm);
  horus->PlaceHPGe("73958","Ge08",10.*cm);
  horus->PlaceHPGe("73959","Ge09",10.*cm);
  horus->PlaceHPGe("73910","Ge10",10.*cm);
  horus->PlaceHPGe("73911","Ge11",10.*cm);
  horus->PlaceHPGe("73912","Ge12",10.*cm);
  horus->PlaceHPGe("73913","Ge13",10.*cm);

  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{

  for(int i=0; i<=13; i++){
    std::stringstream position;
    position << "Ge" << std::setw(2) << std::setfill('0') << i;
    G4MultiFunctionalDetector* cryst = new G4MultiFunctionalDetector(position.str());
    G4VPrimitiveScorer* primitiv = new G4PSEnergyDeposit("edep");
    cryst->RegisterPrimitive(primitiv);
    SetSensitiveDetector("HPGe_" + position.str() + "_Kristall_Logical",cryst);
  }


 /* G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  //
  // Scorers
  //


  // declare Absorber as a MultiFunctionalDetector scorer
  //
  //G4MultiFunctionalDetector* absDetector
  //  = new G4MultiFunctionalDetector("Absorber");

  G4VPrimitiveScorer* primitive;
  //primitive = new G4PSEnergyDeposit("Edep");
  //absDetector->RegisterPrimitive(primitive);

  //primitive = new G4PSTrackLength("TrackLength");
  //G4SDChargedFilter* charged = new G4SDChargedFilter("chargedFilter");
  //primitive ->SetFilter(charged);
  //absDetector->RegisterPrimitive(primitive);

  //SetSensitiveDetector("Filter_Logical",absDetector);

  // declare Gap as a MultiFunctionalDetector scorer
  //
  G4MultiFunctionalDetector* gapDetector
    = new G4MultiFunctionalDetector("Gap");

  //G4VPrimitiveScorer* primitive;
  primitive = new G4PSEnergyDeposit("Edep");
  gapDetector->RegisterPrimitive(primitive);

  //primitive = new G4PSTrackLength("TrackLength");
  //primitive ->SetFilter(charged);
  //gapDetector->RegisterPrimitive(primitive);

  SetSensitiveDetector("HPGe_Ge00_Kristall_Logical",gapDetector);

  //
  // Magnetic field
  //
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  //G4ThreeVector fieldValue = G4ThreeVector();
  //fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  //fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  //G4AutoDelete::Register(fMagFieldMessenger);*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
