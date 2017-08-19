#ifndef HPGEHEXAGONAL_HH
#define HPGEHEXAGONAL_HH

#include "HPGe.hh"

namespace HPGe {

class Hexagonal : public HPGe {
  public:
    Hexagonal(const _spec &spec, const std::string &name, const std::vector<Detector::_filter> &filters);

  private:
    G4VSolid *HexShape(const std::string &name, const G4double &base_radius, const G4double &half_length);
};

} //namespace HPGe

#endif //HPGEHEXAGONAL_HH
