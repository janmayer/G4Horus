#include "AstroTargetkammerV2.hh"
#include "CADElement.hh"
#include "G4Color.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

AstroTargetkammerV2::AstroTargetkammerV2(G4LogicalVolume* worldLV)
    : Setup(worldLV, {}) // TODO: Position of RBS detector
{
    auto rot = new G4RotationMatrix();
    rot->rotateX(180. * deg);

    const std::vector<CADElement> elements = {
        {"AstroTargetkammerV2-Al-ChamberCap-lowpoly", "G4_Al", G4Color(0.517, 0.529, 0.537)},
        {"AstroTargetkammerV2-Al-Chamber", "G4_Al", G4Color(0.517, 0.529, 0.537)},
        {"AstroTargetkammerV2-Cu-CoolingFinger", "G4_Cu", G4Color(0.722, 0.451, 0.200)},
        {"AstroTargetkammerV2-Ta-ChamberShieldCap", "G4_Ta", G4Color(0.180, 0.310, 0.310)},
        {"AstroTargetkammerV2-Ta-ChamberShield", "G4_Ta", G4Color(0.180, 0.310, 0.310)},
    };

    for (const auto& element : elements) {
        element.Place(worldLV, rot);
    }
}
