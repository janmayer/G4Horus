#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4NistManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalConstants.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"

#include "AstroTargetkammer.hh"
#include "BGO.hh"
#include "DummyChamber.hh"
#include "Horus.hh"
#include "PIPS.hh"
#include "SONIC.hh"

extern const std::vector<std::string> detectors = {
    "Ge00", "Ge01", //"Ge02", "Ge03", "Ge04", "Ge05", "Ge06", "Ge07", "Ge08", "Ge09", "Ge10", "Ge11", "Ge12", "Ge13",
    "BGO00", //"BGO02", "BGO03", "BGO07", "BGO08", "BGO09"
};

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
    // World
    const G4double worldSizeXYZ = 5. * m / 2;
    auto worldS = new G4Box("World", worldSizeXYZ, worldSizeXYZ, worldSizeXYZ);
    auto worldLV = new G4LogicalVolume(worldS, G4Material::GetMaterial("Galactic"), "World");
    worldLV->SetVisAttributes(G4VisAttributes::Invisible);

    //new AstroTargetkammer(worldLV);
    //new SONIC(worldLV);
    new DummyChamber(worldLV);

    auto horus = new Horus(worldLV);
    // ID, Position, Distance (to endcap or filters on endcap), Filters
    // ID, Position, Distance to endcap, BGO, BGO-Filters)
    horus->PlaceHPGe("elek", "Ge00", 17. * cm, {BGO::tLARGENOSE, "BGO00"}, {{"G4_Cu", 1. * mm}, {"G4_Pb", 1. * mm}});
    horus->PlaceHPGe("609502", "Ge01", 7. * cm, {{"G4_Cu", 2. * mm}, {"G4_Pb", 1. * mm}});
    horus->PlaceHPGe("73954", "Ge02", 7. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("adjusted_capsule", "Ge03", 17 * cm, {BGO::tLARGENOSE, "BGO03"}, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("73209", "Ge04", 7. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("72827", "Ge05", 7. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("adjusted_capsule", "Ge06", 17. * cm, {BGO::tLARGENOSE, "BGO02"});
    horus->PlaceHPGe("72811", "Ge07", 17. * cm, {BGO::tSMALLNOSE, "BGO07"}, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("73002", "Ge08", 17. * cm, {BGO::tLARGENOSE, "BGO08"}, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("miniball_capsule", "Ge09", 17. * cm, {BGO::tSMALLNOSE, "BGO09"}, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("miniball_capsule", "Ge10", 7. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("72397", "Ge11", 7. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("72442", "Ge12", 7. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceHPGe("72341", "Ge13", 7. * cm, {{"G4_Cu", 2. * mm}});

    auto worldPV = new G4PVPlacement(nullptr, G4ThreeVector(), worldLV, "World", nullptr, false, 0, fCheckOverlaps);
    return worldPV;
}

DetectorConstruction::DetectorConstruction()
    : fCheckOverlaps(true)
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    DefineMaterials();
    return DefineVolumes();
}

void DetectorConstruction::DefineMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    nistManager->FindOrBuildMaterial("G4_Pb");
    nistManager->FindOrBuildMaterial("G4_Cu");
    nistManager->FindOrBuildMaterial("G4_Al");
    nistManager->FindOrBuildMaterial("G4_Ge");
    nistManager->FindOrBuildMaterial("G4_Ta");
    nistManager->FindOrBuildMaterial("G4_Si");

    G4Element* O = nistManager->FindOrBuildElement("O");
    G4Element* Bi = nistManager->FindOrBuildElement("Bi");
    G4Element* Ge = nistManager->FindOrBuildElement("Ge");
    G4Element* C = nistManager->FindOrBuildElement("C");
    G4Element* H = nistManager->FindOrBuildElement("H");
    G4Element* Cu = nistManager->FindOrBuildElement("Cu");
    G4Element* Zn = nistManager->FindOrBuildElement("Zn");

    G4Material* BGO_Material = new G4Material("BGO", 7.13 * g / cm3, 3);
    BGO_Material->AddElement(O, 12);
    BGO_Material->AddElement(Bi, 4);
    BGO_Material->AddElement(Ge, 3);

    G4Material* PET = new G4Material("PET", 1.4 * g / cm3, 3);
    PET->AddElement(C, 10);
    PET->AddElement(O, 3);
    PET->AddElement(H, 8);

    G4Material* Brass = new G4Material("Brass", 8.5 * g / cm3, 2);
    Brass->AddElement(Cu, 70 * perCent);
    Brass->AddElement(Zn, 30 * perCent);

    new G4Material("Galactic", 1, 1.01 * g / mole, universe_mean_density, kStateGas, 2.73 * kelvin, 3.e-18 * pascal);
    new G4Material("Nothing", 1, 0, universe_mean_density, kStateUndefined, 0, 0);

    //G4cout << *(G4Material::GetMaterialTable()) << G4endl; // Print materials
}

void DetectorConstruction::ConstructSDandField()
{
    for (const auto& det : detectors) {
        auto activeVolume = new G4MultiFunctionalDetector(det);
        activeVolume->RegisterPrimitive(new G4PSEnergyDeposit("edep"));

        if (det.rfind("Ge", 0) == 0) {
            SetSensitiveDetector("HPGe_" + det + "_crystal_logical", activeVolume);
            continue;
        }
        if (det.rfind("BGO", 0) == 0) {
            SetSensitiveDetector("BGO_" + det + "_bgo_lv", activeVolume);
            continue;
        }
        if (det.rfind("Si", 0) == 0) {
            SetSensitiveDetector("PIPS_" + det + "_active_logical", activeVolume);
            continue;
        }

        G4Exception("DetectorConstruction::ConstructSDandField", "Unknown detector type", FatalException, det.c_str());
    }
}
