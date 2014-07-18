#ifndef HPGE_73954_HH
#define HPGE_73954_HH

#include "G4LogicalVolume.hh"

class HPGe_73954
{

public:
  HPGe_73954(std::string DetectorName, G4bool BGO_is_Used, G4double Filter_Dicke);
  ~HPGe_73954();

  G4LogicalVolume* GetLogical() { return HPGe_73954_Logical; }
  G4double GetLength(){ return Gesammt_Laenge; }
private:
  G4LogicalVolume* HPGe_73954_Logical;
  G4double Gesammt_Laenge;
};

#endif
