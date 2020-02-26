#include "CADElement.hh"
#include "CADMesh.hh"
#include "G4VisAttributes.hh"

CADElement::CADElement(std::string filename, const std::string& material, const G4Color& color)
    : fFilename(std::move(filename))
    , fLV(nullptr)
{
    const auto file = GetCadFile(fFilename);
    std::cout << "CADElement: Meshing " << fFilename << "(" << file << ") ..." << std::endl;
    // This Version of Cadmesh wants and non-const char ...
    auto mesh = CADMesh(const_cast<char*>(file.c_str()));
    mesh.SetScale(mm);
    fLV = new G4LogicalVolume(mesh.TessellatedMesh(), G4Material::GetMaterial(material), fFilename + "_lV");
    auto va = G4VisAttributes(color);
    va.SetForceSolid(true);
    fLV->SetVisAttributes(va);
}

void CADElement::Place(G4LogicalVolume* worldLV, G4RotationMatrix* rot, const G4ThreeVector& trans,
                       const bool checkOverlaps) const
{
    new G4PVPlacement(rot, trans, fLV, fFilename + "_pV", worldLV, false, 0, checkOverlaps);
}

std::string CADElement::GetCadFile(const std::string& filename) const
{
    std::string loc;
    const char* path = std::getenv("G4HORUS_CAD_DIR");
    if (path == nullptr) {
        loc = std::string("../cad/") + filename + ".stl";
    } else {
        loc = std::string(path) + "/" + filename + ".stl";
    }
    return loc;
}
