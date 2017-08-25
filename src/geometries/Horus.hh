#ifndef HORUS_HH
#define HORUS_HH

#include "Setup.hh"

class Horus : public Setup {
  public:
    explicit Horus(G4LogicalVolume *theMother);
};

#endif //HORUS_HH
