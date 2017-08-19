#ifndef BGO_HH
#define BGO_HH

#include "Detector.hh"
#include "G4LogicalVolume.hh"

class BGO : public Detector {
  public:
    enum _type { tSMALLNOSE,
                 tLARGENOSE };

    BGO(const _type& type, const G4String& name, const std::vector<Detector::_filter>& filters = {});

    G4double GetOverlapLength() const
    {
        return fOverlap;
    }

  private:
    G4double fOverlap;
};

#endif //BGO_HH
