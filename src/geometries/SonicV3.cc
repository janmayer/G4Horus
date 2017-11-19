// clang-format off
#include "CADMesh.hh" // Include this first to avoid warnings about shadowed variables
#include "CADHelper.hh"
#include "SonicV3.hh"
#include "G4VisAttributes.hh"

SonicV3::SonicV3(G4LogicalVolume *worldLV)
    : Setup(worldLV, {
        {"Si00", {145. * deg,  45. * deg}},
        {"Si01", {145. * deg, 135. * deg}},
        {"Si02", {145. * deg, 225. * deg}},
        {"Si03", {145. * deg, 315. * deg}},
        {"Si04", {123. * deg,   0. * deg}},
        {"Si05", {123. * deg,  90. * deg}},
        {"Si06", {123. * deg, 180. * deg}},
        {"Si07", {123. * deg, 270. * deg}},
        {"Si08", {107. * deg,  45. * deg}},
        {"Si09", {107. * deg, 135. * deg}},
        {"Si10", {107. * deg, 225. * deg}},
        {"Si11", {107. * deg, 315. * deg}}})
// clang-format on
{
    G4ThreeVector trans = {0, 0, 0}; // Note MakeImpint missing const on trans&
    auto rot = new G4RotationMatrix();
    auto checkOverlaps = false;
    rot->rotateY(180. * deg);

    /*{
        auto mesh = CADMesh((char *)GetCadFile("SonicV3-beamin.ply").c_str());
        mesh.SetScale(mm);
        auto lV = new G4LogicalVolume(mesh.TessellatedMesh(), G4Material::GetMaterial("G4_Al"), "SONIC_V3_base_lV");
        auto va = G4VisAttributes(G4Color(0.5, 0.5, 0.5));
        va.SetForceSolid(true);
        lV->SetVisAttributes(va);
        new G4PVPlacement(rot, G4ThreeVector(), lV, "SONIC_V3_base_pV", worldLV, false, 0, checkOverlaps);
    }
    {
        auto mesh = CADMesh((char *)GetCadFile("SonicV3-beamout.ply").c_str());
        mesh.SetScale(mm);
        auto lV = new G4LogicalVolume(mesh.TessellatedMesh(), G4Material::GetMaterial("G4_Al"), "SONIC_V3_beamout_lV");
        auto va = G4VisAttributes(G4Color(0.5, 0.5, 0.5));
        va.SetForceSolid(true);
        lV->SetVisAttributes(va);
        new G4PVPlacement(rot, G4ThreeVector(), lV, "SONIC_V3_beamout_pV", worldLV, false, 0, checkOverlaps);
    }
    {
        auto mesh = CADMesh((char *)GetCadFile("SonicV3-detectormount.ply").c_str());
        mesh.SetScale(mm);
        auto lV = new G4LogicalVolume(mesh.TessellatedMesh(), G4Material::GetMaterial("G4_Al"), "SONIC_V3_detectormount_lV");
        auto va = G4VisAttributes(G4Color(1.0, 1.0, 1.0));
        va.SetForceSolid(true);
        lV->SetVisAttributes(va);
        new G4PVPlacement(rot, G4ThreeVector(), lV, "SONIC_V3_detectormount_pV", worldLV, false, 0, checkOverlaps);
    }*/
    {
        auto mesh = CADMesh((char *)GetCadFile("SonicV3-beamin.ply").c_str(), (char *)"PLY", G4Material::GetMaterial("G4_Al"));
        auto aV = mesh.TetrahedralMesh();
        aV->MakeImprint(worldLV, trans, rot, 0, checkOverlaps);
    }
    {
        auto mesh = CADMesh((char *)GetCadFile("SonicV3-beamout.ply").c_str(), (char *)"PLY", G4Material::GetMaterial("G4_Al"));
        auto aV = mesh.TetrahedralMesh();
        aV->MakeImprint(worldLV, trans, rot);
    }
    {
        auto mesh = CADMesh((char *)GetCadFile("SonicV3-detectormount.ply").c_str(), (char *)"PLY", G4Material::GetMaterial("G4_Al"));
        auto aV = mesh.TetrahedralMesh();
        aV->MakeImprint(worldLV, trans, rot);
    }
}
