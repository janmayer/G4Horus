#ifndef DETECTORLIBRARY_HH
#define DETECTORLIBRARY_HH

#include "HPGe.hh"
#include "HPGeClover.hh"
#include "HPGeCoaxial.hh"
#include "HPGeHexagonal.hh"

class DetectorLibrary {
  public:
    DetectorLibrary() = default;

    HPGe::HPGe *GetDetector(const std::string &id, const std::string &position, const std::vector<Detector::_filter> &filters) const;

    static const std::map<std::string, HPGe::_spec> specifications;
};

#endif //DETECTORLIBRARY_HH
