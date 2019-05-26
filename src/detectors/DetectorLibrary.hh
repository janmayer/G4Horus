#pragma once

#include "Detector.hh"
#include "HPGe.hh"
#include "HPGeClover.hh"
#include "HPGeCoaxial.hh"
#include "HPGeHexagonal.hh"
#include "PIPS.hh"

class DetectorLibrary {
  public:
    DetectorLibrary() = default;

    Detector *GetDetector(const std::string &id, const std::string &position) const;

    static const std::map<std::string, HPGe::_spec> specifications;
};
