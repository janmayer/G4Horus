#include "Horus.hh"

// clang-format off
Horus::Horus(G4LogicalVolume* theMother)
    : Setup(theMother, {{"Ge00",  { 90. * deg,   0. * deg}},
                        {"Ge01",  { 90. * deg,  55. * deg}},
                        {"Ge02",  { 90. * deg, 125. * deg}},
                        {"Ge03",  { 90. * deg, 180. * deg}},
                        {"Ge04",  { 90. * deg, 235. * deg}},
                        {"Ge05",  { 90. * deg, 305. * deg}},
                        {"Ge06",  {135. * deg, 270. * deg}},
                        {"Ge07",  { 45. * deg, 270. * deg}},
                        {"Ge08",  { 45. * deg,  90. * deg}},
                        {"Ge09",  {135. * deg,  90. * deg}},
                        {"Ge10",  {145. * deg,   0. * deg}},
                        {"Ge11",  {145. * deg, 180. * deg}},
                        {"Ge12",  { 35. * deg, 180. * deg}},
                        {"Ge13",  { 35. * deg,   0. * deg}},
                        {"BGO00", { 90. * deg,   0. * deg}},
                        {"BGO01", { 90. * deg,  55. * deg}},
                        {"BGO02", { 90. * deg, 125. * deg}},
                        {"BGO03", { 90. * deg, 180. * deg}},
                        {"BGO04", { 90. * deg, 235. * deg}},
                        {"BGO05", { 90. * deg, 305. * deg}},
                        {"BGO06", {135. * deg, 270. * deg}},
                        {"BGO07", { 45. * deg, 270. * deg}},
                        {"BGO08", { 45. * deg,  90. * deg}},
                        {"BGO09", {135. * deg,  90. * deg}},
                        {"BGO10", {145. * deg,   0. * deg}},
                        {"BGO11", {145. * deg, 180. * deg}},
                        {"BGO12", { 35. * deg, 180. * deg}},
                        {"BGO13", { 35. * deg,   0. * deg}},
                       })
// clang-format on
{
}
