#ifndef G4HORUS_HPGECLOVER_HH
#define G4HORUS_HPGECLOVER_HH

#include "HPGe.hh"

namespace HPGe {

class Clover : public HPGe {
  public:
    Clover(const _spec& spec, const std::string& name, const std::vector<Detector::_filter>& filters);

  private:
    struct _cloverLeaf {
        G4String name;
        G4double alCupThickness;
        G4double alCupLength;
        G4double allayerThickness;
        G4double crystalRadius;
        G4double crystalOffset;
        G4double crystalLength;
        G4double deadlayerThickness;
        G4double distanceToEndcap;
        G4double holeRadius;
        G4double holeLength;
        G4double lilayerThickness;
    };

    struct _cloverSpec {
        G4double teflonThickness;
        G4double teflonLength;
        G4double teflonEndcapThickness;
        G4double cavityLength;
        std::vector<_cloverLeaf> crystals;
    };

    _cloverSpec fCloverSpec;

    void Leaf(const G4double mx, const G4double my, const G4double rotz, const _cloverLeaf& leaf, const bool checkOverlap) const;
};

} //namespace HPGe

#endif //G4HORUS_HPGECLOVER_HH
