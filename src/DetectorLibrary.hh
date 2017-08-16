#ifndef DETECTORLIBRARY_HH
#define DETECTORLIBRARY_HH

#include "HPGe.hh"
#include "HPGeCoaxial.hh"
#include "HPGeHexagonal.hh"

class DetectorLibrary {
  public:
    DetectorLibrary() = default;

    HPGe::HPGe *GetDetector(const std::string &id, const std::string &position, const G4double filter) const;

    static const std::map<std::string, HPGe::_spec> specifications;
};

#endif //DETECTORLIBRARY_HH
