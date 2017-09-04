#pragma once

#include "HPGe.hh"

namespace HPGe {

class Coaxial : public HPGe {
  public:
    Coaxial(const _spec &spec, const std::string &name, const std::vector<Detector::_filter> &filters);
};

} //namespace HPGe
