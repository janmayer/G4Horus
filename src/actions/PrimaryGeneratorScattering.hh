#pragma once

#include "G4VPrimaryGenerator.hh"
#include <map>
#include <vector>

class G4ParticleDefinition;
class G4Event;

class PrimaryGeneratorScattering : public G4VPrimaryGenerator {
  public:
    struct Decay {
        G4double energy;
        G4double intensity;
        int final;
    };

    struct Level {
        G4double energy;
        std::vector<Decay> decays;
    };

    using LevelScheme = std::map<int, Level>;

    PrimaryGeneratorScattering(const LevelScheme& levelScheme, const G4ParticleDefinition* projectile, const G4double projectileKineticEnergy);
    void GeneratePrimaryVertex(G4Event*) override;

  private:
    void ProcessDecays(const std::vector<Decay>&, G4Event*);

    const LevelScheme fLevelScheme;
    const G4ParticleDefinition* fGamma;
    const G4ParticleDefinition* fProjectile;
    const G4double fProjectileKineticEnergy;
};
