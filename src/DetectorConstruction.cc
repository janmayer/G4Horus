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
#include "AstroTargetkammerV2.hh"
#include "BGO.hh"
#include "CologneCloverSetup.hh"
#include "DetectorLibrary.hh"
#include "DummyChamber.hh"
#include "HPGeClover.hh"
#include "Horus.hh"
#include "PIPS.hh"
#include "SONIC.hh"
#include "SonicV3.hh"
#include "SonicV3dEE.hh"

extern const std::vector<std::string> detectors = {
    "Ge00", "Ge01", "Ge02", "Ge03", "Ge04", "Ge05", "Ge06", "Ge07", "Ge08", "Ge09", "Ge10", "Ge11", "Ge12", "Ge13",
    //    "Si00", "Si01", "Si02", "Si03", "Si04", "Si05", "Si06", "Si07", "Si08", "Si09", "Si10", "Si11",
    "BGO00", "BGO03", "BGO06", "BGO07", "BGO08", "BGO09"
    //    "A0", "A1", "A2", "A3", "B0", "B1", "B2", "B3"
};

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
    // World
    const G4double worldSizeXYZ = 5. * m / 2;
    auto worldS = new G4Box("World", worldSizeXYZ, worldSizeXYZ, worldSizeXYZ);
    auto worldLV = new G4LogicalVolume(worldS, G4Material::GetMaterial("Galactic"), "World");
    worldLV->SetVisAttributes(G4VisAttributes::Invisible);

    auto sonic = new SonicV3(worldLV);
    // auto sonic = new SonicV3dEE(worldLV);
    sonic->PlaceDetector("PIPS", "Si00", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si01", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si02", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si03", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si04", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si05", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si06", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si07", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si08", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si09", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si10", 45.25 * mm);
    sonic->PlaceDetector("PIPS", "Si11", 45.25 * mm);

    // new AstroTargetkammer(worldLV);
    // new AstroTargetkammerV2(worldLV);
    // new DummyChamber(worldLV);

    auto horus = new Horus(worldLV);
    // ID, Position, Distance (to endcap or filters on endcap), Filters
    // BGO Type, Position, Distance (to BGO or filters on bgo), BGO-Filters
    horus->PlaceDetector("elek", "Ge00", 20. * cm);
    horus->PlaceDetector(BGO::tSMALLNOSE, "BGO00", 10. * cm);
    horus->PlaceDetector("609502", "Ge01", 20. * cm, {{"G4_Cu", 2. * mm}, {"G4_Pb", 1. * mm}});
    horus->PlaceDetector("73954", "Ge02", 20. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("adjusted_capsule", "Ge03", 20. * cm);
    horus->PlaceDetector(BGO::tSMALLNOSE, "BGO03", 10. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("73209", "Ge04", 20. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("72827", "Ge05", 20. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("adjusted_capsule", "Ge06", 20. * cm);
    horus->PlaceDetector(BGO::tLARGENOSE, "BGO06", 10. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("72811", "Ge07", 20. * cm);
    horus->PlaceDetector(BGO::tLARGENOSE, "BGO07", 10. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("73002", "Ge08", 20. * cm);
    horus->PlaceDetector(BGO::tLARGENOSE, "BGO08", 10. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("miniball_capsule", "Ge09", 20. * cm);
    horus->PlaceDetector(BGO::tLARGENOSE, "BGO09", 10. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("miniball_capsule", "Ge10", 20. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("72397", "Ge11", 20. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("72442", "Ge12", 20. * cm, {{"G4_Cu", 2. * mm}});
    horus->PlaceDetector("72341", "Ge13", 20. * cm, {{"G4_Cu", 2. * mm}});

    /*
    auto ccs = new CologneCloverSetup(worldLV);
    ccs->PlaceDetector("CloziA", "A", 5. * mm);
    ccs->PlaceDetector("CloziB", "B", 5. * mm);
    */

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
    nistManager->FindOrBuildMaterial("G4_POLYCARBONATE");

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
    PET->AddElement(O, 4);
    PET->AddElement(H, 8);

    G4Material* Brass = new G4Material("Brass", 8.5 * g / cm3, 2);
    Brass->AddElement(Cu, 70 * perCent);
    Brass->AddElement(Zn, 30 * perCent);

    new G4Material("Galactic", 1, 1.01 * g / mole, universe_mean_density, kStateGas, 2.73 * kelvin, 3.e-18 * pascal);
    new G4Material("Nothing", 1, 0, universe_mean_density, kStateUndefined, 0, 0);
}

void DetectorConstruction::ConstructSDandField()
{
    for (const auto& det : detectors) {
        auto activeVolume = new G4MultiFunctionalDetector(det);
        G4SDManager::GetSDMpointer()->AddNewDetector(activeVolume);
        activeVolume->RegisterPrimitive(new G4PSEnergyDeposit("edep"));

        if (det.rfind("BGO", 0) == 0) {
            SetSensitiveDetector("BGO_" + det + "_bgo_lv", activeVolume);
            continue;
        }
        if (det.rfind("Si", 0) == 0) {
            SetSensitiveDetector("PIPS_" + det + "_active_logical", activeVolume);
            continue;
        }
        if (det.rfind("Ge", 0) == 0 || det.rfind('A', 0) == 0 || det.rfind('B', 0) == 0) {
            SetSensitiveDetector("HPGe_" + det + "_crystal_logical", activeVolume);
            continue;
        }

        G4Exception("DetectorConstruction::ConstructSDandField", "Unknown detector type", FatalException, det.c_str());
    }
}
