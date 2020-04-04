#include "PrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    gun.SetNumberOfParticles(1);
    gun.SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("gamma"));
    gun.SetParticleMomentumDirection(G4ParticleMomentum(1., 0., 0.));
    gun.SetParticlePosition(G4ThreeVector(0., 0., 0.));
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    const G4double phi = twopi * G4UniformRand();
    const G4double cos_theta = 2. * G4UniformRand() - 1.;
    const G4double sin_theta = std::sqrt(1. - cos_theta * cos_theta);

    const G4double x = sin_theta * std::cos(phi);
    const G4double y = sin_theta * std::sin(phi);
    const G4double z = cos_theta;

    gun.SetParticleMomentumDirection(G4ThreeVector(x, y, z));
    gun.GeneratePrimaryVertex(event);
}
