#ifndef PIPS_HH
#define PIPS_HH

#include "G4LogicalVolume.hh"

class PIPS
{
public:
  PIPS(const std::string &name);
  ~PIPS();

  G4LogicalVolume* GetLogical()
  {
    return detector_logical;
  }

  G4double GetLength()
  {
    return full_length;
  }

protected:
  G4LogicalVolume* detector_logical;
  G4double full_length;
};

#endif //PIPS_HH
