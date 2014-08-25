#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"
//#include "globals.hh"

class PhysicsList: public G4VUserPhysicsList{
public:
  PhysicsList();
  ~PhysicsList();
protected:
  void ConstructParticle();
  void ConstructProcess();
  void SetCuts();
  void AddElectronInteraction();
  void AddGammaInteraction();
  void AddPositronInteraction();
};

#endif
