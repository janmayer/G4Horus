#include "PrimaryGeneratorScattering.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4RandomDirection.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <cmath>

PrimaryGeneratorScattering::PrimaryGeneratorScattering(const LevelScheme& levelScheme,
                                                       const G4ParticleDefinition* projectile,
                                                       const G4double projectileKineticEnergy)
    : fLevelScheme(levelScheme)
    , fGamma(G4ParticleTable::GetParticleTable()->FindParticle("gamma"))
    , fProjectile(projectile)
    , fProjectileKineticEnergy(projectileKineticEnergy)
{
}

void PrimaryGeneratorScattering::GeneratePrimaryVertex(G4Event* event)
{
    // random from vector should be faster
    auto levelIt = fLevelScheme.begin();
    std::advance(levelIt, std::floor(G4UniformRand() * (fLevelScheme.size() - 1)));
    const auto level = levelIt->second;

    const auto scatteredProjectileKineticEnergy = fProjectileKineticEnergy - level.energy; //TODO: Use kinematics
    const auto scatteredProjectileDirection = G4RandomDirection();

    auto scatteredProjectile = new G4PrimaryParticle(fProjectile);
    scatteredProjectile->SetMomentumDirection(scatteredProjectileDirection);
    scatteredProjectile->SetKineticEnergy(scatteredProjectileKineticEnergy / 1.6021766e-13); // FIXME: Units don't work as expected
    auto scatteredProjectileVertex = new G4PrimaryVertex();
    scatteredProjectileVertex->SetPrimary(scatteredProjectile);
    event->AddPrimaryVertex(scatteredProjectileVertex);

    ProcessDecays(level.decays, event);
}

void PrimaryGeneratorScattering::ProcessDecays(const std::vector<PrimaryGeneratorScattering::Decay>& decays, G4Event* event)
{
    Decay decay {};
    if (decays.empty()) {
        return;
    } else if (decays.size() == 1) {
        decay = decays.at(0);
    } else {
        decay = decays.at(std::floor(G4UniformRand() * (decays.size() - 1))); // TODO: Use intensity
    }

    auto gamma = new G4PrimaryParticle(fGamma);
    gamma->SetMomentumDirection(G4RandomDirection());
    gamma->SetKineticEnergy(decay.energy / 1.6021766e-13); // FIXME: Units don't work as expected
    auto gammaVertex = new G4PrimaryVertex();
    gammaVertex->SetPrimary(gamma);
    event->AddPrimaryVertex(gammaVertex);

    ProcessDecays(fLevelScheme.at(decay.final).decays, event);
}
