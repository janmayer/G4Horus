#pragma once

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4Types.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorAction();
    void GeneratePrimaries(G4Event* event) override;

  private:
    G4ParticleGun gun;
};
