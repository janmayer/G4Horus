#ifndef BGO_HH
#define BGO_HH

#include "G4LogicalVolume.hh"

class BGO {
  public:
    enum _type { tNULL,
                 tSMALLNOSE,
                 tLARGENOSE };

    BGO(const _type type, const G4String name);
    ~BGO();

    G4LogicalVolume* GetLogical()
    {
        return mother_lv;
    }

    G4double GetLength()
    {
        return full_length;
    }

    G4double GetOverlapLength()
    {
        return overlap_length;
    }

  private:
    G4LogicalVolume* mother_lv;
    G4double full_length;
    G4double overlap_length;
};

#endif //BGO_HH
