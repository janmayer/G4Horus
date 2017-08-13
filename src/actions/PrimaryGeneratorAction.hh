#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4Types.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include <memory>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() = default;

    void GeneratePrimaries(G4Event* event) override;

  private:
    std::unique_ptr<G4ParticleGun> gun;
};

#endif //PRIMARYGENERATORACTION_HH
