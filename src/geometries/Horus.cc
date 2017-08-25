#include "Horus.hh"

// clang-format off
Horus::Horus(G4LogicalVolume *theMother)
    : Setup(theMother, {
        {"Ge00", {90. * deg, 0}},
        {"Ge01", {90. * deg, 55. * deg}},
        {"Ge02", {90. * deg, 125. * deg}},
        {"Ge03", {90. * deg, 180. * deg}},
        {"Ge04", {90. * deg, 235. * deg}},
        {"Ge05", {90. * deg, 305. * deg}},
        {"Ge06", {135. * deg, 270. * deg}},
        {"Ge07", {45. * deg, 270. * deg}},
        {"Ge08", {45. * deg, 90. * deg}},
        {"Ge09", {135. * deg, 90. * deg}},
        {"Ge10", {145. * deg, 0}},
        {"Ge11", {145. * deg, 180. * deg}},
        {"Ge12", {35. * deg, 180. * deg}},
        {"Ge13", {35. * deg, 0}}})
// clang-format on
{
}
