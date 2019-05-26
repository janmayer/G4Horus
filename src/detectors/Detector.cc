#include "Detector.hh"
#include <utility>

Detector::Detector(std::string name, const G4double& length)
    : fDetectorLV(nullptr)
    , fLength(length)
    , fWidth(0)
    , fName(std::move(name))
{
}
