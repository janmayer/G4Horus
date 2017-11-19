// clang-format off
#include "CADMesh.hh" // Include this first to avoid warnings about shadowed variables
// clang-format on
#include "HPGeClover.hh"
#include "CADHelper.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4VisAttributes.hh"

HPGe::Clover::Clover(const _spec& spec, const std::string& name, const std::vector<Detector::_filter>& filters)
    : HPGe(spec, name, filters)
{
    // hull
    //auto rot = new G4RotationMatrix();
    //rot->rotateX(-90. * deg);
    new G4PVPlacement(nullptr, G4ThreeVector(), this->BuildHull(), "HPGe_" + name + "_hull", fDetectorLV, false, 0, fSpec.check_overlaps);

    // TODO: Move that out. Maybe some Variant / Union stuff? Or derived data storage classes

    fCloverSpec.teflonThickness = 0.19 * mm;
    fCloverSpec.teflonLength = 80. * mm; // guess
    fCloverSpec.teflonEndcapThickness = 3. * mm;
    fCloverSpec.cavityLength = 20. * mm;

    _cloverLeaf baseLeaf;
    baseLeaf.alCupThickness = 0.51 * mm;
    baseLeaf.alCupLength = 30. * mm;
    baseLeaf.crystalOffset = 24. * mm;
    baseLeaf.holeLength = 51. * mm;
    baseLeaf.holeRadius = 4.5 * mm;
    baseLeaf.lilayerThickness = 0.7 * mm;

    if (fSpec.id != "CloziA" && fSpec.id != "CloziB") {
        throw(fSpec.id + " is not a known Clover Type detector");
    }

    if (fSpec.id == "CloziB") {
        _cloverLeaf B0(baseLeaf);
        B0.name = "B0";
        B0.allayerThickness = 1.5 * mm;
        B0.crystalRadius = 28.75 * mm;
        B0.crystalLength = 59.5 * mm;
        B0.deadlayerThickness = 0.0003 * mm;
        B0.distanceToEndcap = 16.0 * mm;
        fCloverSpec.crystals.push_back(B0);

        _cloverLeaf B1(baseLeaf);
        B1.name = "B1";
        B1.allayerThickness = 1.1 * mm; // 1.5
        B1.crystalRadius = 28.50 * mm;
        B1.crystalLength = 58.5 * mm;
        B1.deadlayerThickness = 0.0003 * mm;
        B1.distanceToEndcap = 18.0 * mm;
        fCloverSpec.crystals.push_back(B1);

        _cloverLeaf B2(baseLeaf);
        B2.name = "B2";
        B2.allayerThickness = 1.2 * mm; // 1.5
        B2.crystalRadius = 28.55 * mm;
        B2.crystalLength = 58.7 * mm;
        B2.deadlayerThickness = 0.0003 * mm;
        B2.distanceToEndcap = 16.0 * mm;
        fCloverSpec.crystals.push_back(B2);

        _cloverLeaf B3(baseLeaf);
        B3.name = "B3";
        B3.allayerThickness = 1.1 * mm; // 1.5
        B3.crystalRadius = 28.60 * mm;
        B3.crystalLength = 57.2 * mm;
        B3.deadlayerThickness = 0.0003 * mm;
        B3.distanceToEndcap = 15.0 * mm;
        fCloverSpec.crystals.push_back(B3);
    }

    if (fSpec.id == "CloziA") {
        _cloverLeaf A0(baseLeaf);
        A0.name = "A0";
        A0.allayerThickness = 0.8 * mm;
        A0.crystalRadius = 28.40 * mm;
        A0.crystalLength = 56.8 * mm;
        A0.deadlayerThickness = 0.0003 * mm;
        A0.distanceToEndcap = 17.0 * mm;
        fCloverSpec.crystals.push_back(A0);

        _cloverLeaf A1(baseLeaf);
        A1.name = "A1";
        A1.allayerThickness = 0.8 * mm;
        A1.crystalRadius = 28.50 * mm;
        A1.crystalLength = 59.0 * mm;
        A1.deadlayerThickness = 0.0003 * mm;
        A1.distanceToEndcap = 13.0 * mm;
        fCloverSpec.crystals.push_back(A1);

        _cloverLeaf A2(baseLeaf);
        A2.name = "A2";
        A2.allayerThickness = 0.8 * mm;
        A2.crystalRadius = 28.05 * mm;
        A2.crystalLength = 56.0 * mm;
        A2.deadlayerThickness = 0.0003 * mm;
        A2.distanceToEndcap = 18.0 * mm;
        fCloverSpec.crystals.push_back(A2);

        _cloverLeaf A3(baseLeaf);
        A3.name = "A3";
        A3.allayerThickness = 0.8 * mm;
        A3.crystalRadius = 28.40 * mm;
        A3.crystalLength = 56.6 * mm;
        A3.deadlayerThickness = 0.0003 * mm;
        A3.distanceToEndcap = 20.0 * mm;
        fCloverSpec.crystals.push_back(A3);
    }

    Leaf(-1., +1., 000. * deg, fCloverSpec.crystals.at(0), fSpec.check_overlaps);
    Leaf(-1., -1., 090. * deg, fCloverSpec.crystals.at(1), fSpec.check_overlaps);
    Leaf(+1., -1., 180. * deg, fCloverSpec.crystals.at(2), fSpec.check_overlaps);
    Leaf(+1., +1., 270. * deg, fCloverSpec.crystals.at(3), fSpec.check_overlaps);

    // Teflon Insulator
    {
        auto box = new G4Box("", 2 * fCloverSpec.crystals.at(0).crystalRadius, fCloverSpec.teflonThickness, fCloverSpec.teflonLength / 2.);

        auto rm90 = new G4RotationMatrix();
        rm90->rotateZ(90. * deg);
        auto insulatorSV = new G4UnionSolid(fSpec.id + "_insulatorSV", box, box, rm90, G4ThreeVector());

        auto insulatorLV = new G4LogicalVolume(insulatorSV, G4NistManager::Instance()->FindOrBuildMaterial("G4_TEFLON"), fSpec.id + "_insulatorLV");
        auto insulatorVA = new G4VisAttributes(G4Colour(.4, .4, .8, .3));
        insulatorVA->SetForceSolid(true);
        insulatorLV->SetVisAttributes(insulatorVA);

        G4ThreeVector insulatorPO(0., 0., -(fLength / 2. - 3 * fCloverSpec.crystals.at(0).distanceToEndcap));
        new G4PVPlacement(nullptr, insulatorPO, insulatorLV, fSpec.id + "_insulatorPV", fDetectorLV, false, 0, fSpec.check_overlaps);
    }

    // Teflon endcap
    /*{
        const G4double outerRadius_Te_Cap = fSpec.hull.diameter / 2. - fSpec.hull.thickness;
        const G4double height_Te_Cap = fCloverSpec.teflonEndcapThickness / 2.;
        auto teEndcapSV = new G4Tubs(fSpec.id + "_teEndcapSV", 0., outerRadius_Te_Cap, height_Te_Cap, 0. * deg, 360. * deg);

        auto teEndcapLV = new G4LogicalVolume(teEndcapSV, G4NistManager::Instance()->FindOrBuildMaterial("G4_TEFLON"), fSpec.id + "_teEndcapLV");
        auto teEndcapVA = new G4VisAttributes(G4Colour(.4, .4, .8, .3));
        teEndcapVA->SetForceSolid(true);
        teEndcapLV->SetVisAttributes(teEndcapVA);

        G4ThreeVector teEndcapPO(0., 0., fLength / 2. - fCloverSpec.teflonEndcapThickness / 2.);
        new G4PVPlacement(nullptr, teEndcapPO, teEndcapLV, fSpec.id + "_teEndcapPV", fDetectorLV, false, 0, fSpec.check_overlaps);
    }*/
}

void HPGe::Clover::Leaf(const G4double mx, const G4double my, const G4double rotz, const _cloverLeaf& leaf, const bool checkOverlap) const
{
    auto Ge = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ge");
    auto Al = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
    auto Li = G4NistManager::Instance()->FindOrBuildMaterial("G4_Li");
    auto Au = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");

    const G4double cutbox_size = 30.0 * cm; // Size dons't matter, just needs to be large enough
    auto cutbox = new G4Box("cutbox", cutbox_size, cutbox_size, cutbox_size);

    auto tube = new G4Tubs("tube", 0., leaf.crystalRadius, leaf.crystalLength / 2., 0. * deg, 360. * deg);
    auto hole = new G4Tubs("hole", 0., leaf.holeRadius, leaf.holeLength / 2., 0. * deg, 360. * deg);

    auto crystal_cut1 = new G4SubtractionSolid("crystal_cut1", tube, cutbox, nullptr,
                                               G4ThreeVector(0, -(leaf.crystalOffset + cutbox_size), 0));
    auto crystal_cut2 = new G4SubtractionSolid("crystal_cut2", crystal_cut1, cutbox, nullptr,
                                               G4ThreeVector((leaf.crystalOffset + cutbox_size), 0, 0));

    G4RotationMatrix rm;
    rm.rotateZ(rotz);

    // Kristall
    {
        auto crystalSV = new G4SubtractionSolid(leaf.name + "_crystalSV", crystal_cut2, hole, nullptr, G4ThreeVector(0., 0., +((leaf.crystalLength - leaf.holeLength + 0.01) / 2.)));
        auto crystalLV = new G4LogicalVolume(crystalSV, Ge, "HPGe_" + leaf.name + "_crystal_logical");
        auto crystalVA = new G4VisAttributes(G4Colour(1.0, 1.0, 0.));
        crystalVA->SetForceSolid(true);
        crystalLV->SetVisAttributes(crystalVA);

        G4ThreeVector crystalPO(
            mx * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            my * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            -(fLength / 2. - leaf.distanceToEndcap - leaf.allayerThickness - leaf.deadlayerThickness - leaf.crystalLength / 2.));
        new G4PVPlacement(G4Transform3D(rm, crystalPO), crystalLV, leaf.name + "_crystalPV", fDetectorLV, false, 0, checkOverlap);
    }

    // Todschicht Kristall
    {
        auto inactiveSV_Step1 = new G4Tubs("", 0., leaf.crystalRadius, leaf.deadlayerThickness / 2., 0. * deg, 360. * deg);
        auto inactiveSV_Step2 = new G4SubtractionSolid("", inactiveSV_Step1, cutbox, nullptr, G4ThreeVector(0, -(leaf.crystalOffset + cutbox_size), 0));
        auto inactiveSV = new G4SubtractionSolid(leaf.name + "_inactiveSV", inactiveSV_Step2, cutbox, nullptr, G4ThreeVector((leaf.crystalOffset + cutbox_size), 0, 0));

        auto inactiveLV = new G4LogicalVolume(inactiveSV, Ge, leaf.name + "_inactiveLV");
        auto inactiveVA = new G4VisAttributes(G4Colour(.0, 1.0, 0.0));
        inactiveVA->SetForceSolid(true);
        inactiveLV->SetVisAttributes(inactiveVA);

        G4ThreeVector inactivePO(
            mx * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            my * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            -(fLength / 2. - leaf.distanceToEndcap - leaf.allayerThickness - leaf.deadlayerThickness / 2.));

        new G4PVPlacement(G4Transform3D(rm, inactivePO), inactiveLV, leaf.name + "_inactivePV", fDetectorLV, false, 0, checkOverlap);
    }

    // Aluschicht Kristall
    {
        auto alabsSV_Step1 = new G4Tubs("", 0., leaf.crystalRadius, leaf.allayerThickness / 2., 0. * deg, 360. * deg);
        auto alabsSV_Step2 = new G4SubtractionSolid("", alabsSV_Step1, cutbox, nullptr, G4ThreeVector(0, -(leaf.crystalOffset + cutbox_size), 0));
        auto alabsSV = new G4SubtractionSolid(leaf.name + "_alAbsSV", alabsSV_Step2, cutbox, nullptr, G4ThreeVector((leaf.crystalOffset + cutbox_size), 0, 0));

        auto alabsLV = new G4LogicalVolume(alabsSV, Ge, leaf.name + "_alAbsLV");
        auto alabsVA = new G4VisAttributes(G4Colour(1.0, .0, .0));
        alabsVA->SetForceSolid(true);
        alabsLV->SetVisAttributes(alabsVA);

        G4ThreeVector alabsPO(
            mx * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            my * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            -(fLength / 2. - leaf.distanceToEndcap - leaf.allayerThickness / 2.));

        new G4PVPlacement(G4Transform3D(rm, alabsPO), alabsLV, leaf.name + "_alAbsPV", fDetectorLV, false, 0, checkOverlap);
    }

    // Lithium Kontatktierung Kristall
    {
        auto liTubeSV = new G4Tubs(leaf.name + "_liTubeSV", leaf.holeRadius - leaf.lilayerThickness, leaf.holeRadius, leaf.holeLength / 2., 0. * deg, 360. * deg);

        auto liTubeLV = new G4LogicalVolume(liTubeSV, Li, leaf.name + "_liTubeLV");
        auto liTubeVA = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0));
        liTubeVA->SetForceSolid(true);
        liTubeLV->SetVisAttributes(liTubeVA);

        G4ThreeVector liTubePO(
            mx * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            my * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            -(fLength / 2. - leaf.distanceToEndcap - leaf.allayerThickness - leaf.deadlayerThickness - (leaf.crystalLength - leaf.holeLength) - leaf.lilayerThickness - leaf.holeLength / 2.));
        new G4PVPlacement(G4Transform3D(rm, liTubePO), liTubeLV, leaf.name + "_liTubePV", fDetectorLV, false, 0, checkOverlap);

        auto liCapSV = new G4Tubs(leaf.name + "_liCapSV", 0., leaf.holeRadius - leaf.lilayerThickness, leaf.lilayerThickness / 2., 0. * deg, 360. * deg);

        auto liCapLV = new G4LogicalVolume(liCapSV, Li, leaf.name + "_liCapLV");
        liCapLV->SetVisAttributes(liTubeVA);

        G4ThreeVector liCapPO(
            mx * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            my * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            -(fLength / 2. - leaf.distanceToEndcap - leaf.allayerThickness - leaf.deadlayerThickness - (leaf.crystalLength - leaf.holeLength) - leaf.lilayerThickness - leaf.lilayerThickness / 2.));

        new G4PVPlacement(G4Transform3D(rm, liCapPO), liCapLV, leaf.name + "_liCapPV", fDetectorLV, false, 0, checkOverlap);
    }

    // Kühlfinger Kristall
    {
        G4double height_finger = (fCloverSpec.cavityLength + leaf.holeLength - leaf.lilayerThickness) / 2.;
        auto fingerSV = new G4Tubs(leaf.name + "_fingerSV", 0., leaf.holeRadius / 3., height_finger,
                                   0. * deg, 360. * deg);

        auto fingerLV = new G4LogicalVolume(fingerSV, Au, leaf.name + "_fingerLV");
        auto fingerVA = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
        fingerVA->SetForceSolid(true);
        fingerLV->SetVisAttributes(fingerVA);

        G4ThreeVector fingerPO(
            mx * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            my * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            -(fLength / 2. - leaf.distanceToEndcap - leaf.allayerThickness - leaf.deadlayerThickness - (leaf.crystalLength - leaf.holeLength) - 2. * leaf.lilayerThickness - height_finger));
        new G4PVPlacement(G4Transform3D(rm, fingerPO), fingerLV, leaf.name + "_fingerPV", fDetectorLV, false, 0, checkOverlap);
    }

    // Alu Einfassung Kristall
    {
        G4double cutbox1_cup_x = (leaf.alCupThickness + leaf.crystalOffset) / 2.;
        G4double cutbox1_cup_y = (2 * leaf.alCupThickness + leaf.crystalRadius + leaf.crystalOffset) / 2.;
        G4double cutbox1_cup_z = leaf.alCupLength / 2.;
        auto cutbox1_cup = new G4Box("cutbox", cutbox1_cup_x, cutbox1_cup_y, cutbox1_cup_z);
        G4double cutbox2_cup_x = (leaf.alCupThickness + leaf.crystalRadius) / 2.;
        G4double cutbox2_cup_y = (leaf.alCupThickness + leaf.crystalOffset) / 2.;
        G4double cutbox2_cup_z = leaf.alCupLength / 2.;
        auto cutbox2_cup = new G4Box("cutbox", cutbox2_cup_x, cutbox2_cup_y, cutbox2_cup_z);
        auto cutbox_cup = new G4UnionSolid("cutbox_union", cutbox1_cup, cutbox2_cup, nullptr, G4ThreeVector(-cutbox1_cup_y, -cutbox2_cup_x, 0.));
        auto alCupSV = new G4SubtractionSolid(leaf.name + "_alCupSV", cutbox_cup, crystal_cut2, nullptr, G4ThreeVector(-(leaf.alCupThickness + leaf.crystalOffset) / 2, -(leaf.crystalRadius - leaf.crystalOffset) / 2., 0));

        auto alCupLV = new G4LogicalVolume(alCupSV, Al, leaf.name + "_alCupLV");
        auto alCupVA = new G4VisAttributes(G4Colour(1.0, .0, .0));
        alCupVA->SetForceSolid(true);
        alCupLV->SetVisAttributes(alCupVA);

        G4double y;
        G4double x;

        if (mx * my < 0) {
            x = (((leaf.crystalOffset + leaf.alCupThickness) / 2) + fCloverSpec.teflonThickness);
            y = (((2 * leaf.alCupThickness + leaf.crystalRadius + leaf.crystalOffset) / 2) + fCloverSpec.teflonThickness);
        } else {
            y = (((leaf.crystalOffset + leaf.alCupThickness) / 2) + fCloverSpec.teflonThickness);
            x = (((2 * leaf.alCupThickness + leaf.crystalRadius + leaf.crystalOffset) / 2) + fCloverSpec.teflonThickness);
        }

        G4ThreeVector alCupPO(
            mx * x,
            my * y,
            -(fLength / 2. - leaf.distanceToEndcap - leaf.allayerThickness - leaf.deadlayerThickness - (leaf.crystalLength - leaf.alCupLength) - leaf.alCupLength / 2.));
        new G4PVPlacement(G4Transform3D(rm, alCupPO), alCupLV, leaf.name + "_alCupPV", fDetectorLV, false, 0, checkOverlap);

        G4double innerRadius_Cup = leaf.crystalRadius;
        G4double outerRadius_Cup = leaf.crystalRadius + leaf.alCupThickness;
        G4double height_Cup = leaf.alCupLength / 2.;
        G4double startAngle_Cup = 90. * deg;
        G4double spanningAngle_Cup = 90. * deg;
        auto cup_tube = new G4Tubs(leaf.name + "_alTubeSV", innerRadius_Cup, outerRadius_Cup, height_Cup, startAngle_Cup,
                                   spanningAngle_Cup);

        auto alTubeLV = new G4LogicalVolume(cup_tube, Al, leaf.name + "_alTubeLV");
        alTubeLV->SetVisAttributes(alCupVA);

        G4ThreeVector alTubePO(
            mx * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            my * (leaf.alCupThickness + fCloverSpec.teflonThickness + leaf.crystalOffset),
            -(fLength / 2. - leaf.distanceToEndcap - leaf.allayerThickness - leaf.deadlayerThickness - (leaf.crystalLength - leaf.alCupLength) - leaf.alCupLength / 2.));
        new G4PVPlacement(G4Transform3D(rm, alTubePO), alTubeLV, leaf.name + "_alTubePV", fDetectorLV, false, 0, checkOverlap);
    }
}

G4LogicalVolume* HPGe::Clover::BuildHull()
{
    auto mesh = CADMesh((char*)GetCadFile("Clover-hull.stl").c_str());
    mesh.SetScale(mm);

    auto lV = new G4LogicalVolume(mesh.TessellatedMesh(), G4Material::GetMaterial("G4_Al"), "Clover_hull_lV");

    auto va = G4VisAttributes(G4Color(0.5, 0.5, 0.5));
    va.SetForceSolid(true);
    lV->SetVisAttributes(va);

    return lV;
}

G4LogicalVolume* HPGe::Clover::BuildHullFront()
{
    return nullptr;
}