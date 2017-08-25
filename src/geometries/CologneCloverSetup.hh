#ifndef G4HORUS_COLOGNECLOVERSETUP_HH
#define G4HORUS_COLOGNECLOVERSETUP_HH

#include "Setup.hh"

class CologneCloverSetup : public Setup {
  public:
    explicit CologneCloverSetup(G4LogicalVolume *theMother);
};

#endif //G4HORUS_COLOGNECLOVERSETUP_HH
