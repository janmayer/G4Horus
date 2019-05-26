#include "SonicV3.hh"
#include "CADElement.hh"
#include "G4Color.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

// clang-format off
SonicV3::SonicV3(G4LogicalVolume* worldLV)
    : Setup(worldLV, {{"Si00", {145. * deg,  45. * deg}},
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
                      {"Si11", {107. * deg, 315. * deg}},
                     })
// clang-format on
{
    auto rot = new G4RotationMatrix();
    rot->rotateY(180. * deg);

    const std::vector<CADElement> elements = {
        {"SonicV3-Al-Chamber", "G4_Al", G4Color(0.517, 0.529, 0.537)},
        {"SonicV3-Al-ChamberCap", "G4_Al", G4Color(0.517, 0.529, 0.537)},
        // {"SonicV3-Plastic-Detectormount", "G4_POLYCARBONATE", G4Color(1, 1, 1)}
    };

    for (const auto& element : elements) {
        element.Place(worldLV, rot);
    }
}
