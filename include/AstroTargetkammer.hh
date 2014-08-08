#ifndef ASTROTARGETKAMMER_HH
#define ASTROTARGETKAMMER_HH

#include "G4LogicalVolume.hh"

class AstroTargetkammer
{
public:
	AstroTargetkammer(G4LogicalVolume* expHall_log);
  	~AstroTargetkammer();
};

#endif //ASTROTARGETKAMMER_HH
