#ifndef HPGECOAXIAL_HH
#define HPGECOAXIAL_HH

#include "HPGe.hh"

namespace HPGe {

class Coaxial : public HPGe {
  public:
    Coaxial(const _spec &spec, const std::string &name, const G4double &filter_thickness);
    ~Coaxial();
};

} //namespace HPGe

#endif //HPGECOAXIAL_HH
