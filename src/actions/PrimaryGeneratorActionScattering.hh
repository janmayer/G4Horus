#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "PrimaryGeneratorScattering.hh"

class G4Event;

class PrimaryGeneratorActionScattering : public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorActionScattering();
    void GeneratePrimaries(G4Event* event) override;

  private:
    PrimaryGeneratorScattering fAct;
};