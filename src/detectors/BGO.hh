#pragma once

#include "Detector.hh"
#include "G4LogicalVolume.hh"

class BGO : public Detector {
  public:
    enum _type { tSMALLNOSE,
                 tLARGENOSE };

    BGO(const _type& type, std::string name);

    G4double GetOverlapLength() const
    {
        return fOverlap;
    }

    G4double GetOffset() const override
    {
        return fOffset;
    }

  private:
    G4double fOverlap;
    G4double fOffset;
};
