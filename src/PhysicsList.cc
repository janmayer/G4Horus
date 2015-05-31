#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"


PhysicsList::PhysicsList() : G4VModularPhysicsList() {
  SetVerboseLevel(0);
  RegisterPhysics(new G4EmStandardPhysics());
}

PhysicsList::~PhysicsList() {
}

void PhysicsList::SetCuts() {
  G4VUserPhysicsList::SetCuts();
}
