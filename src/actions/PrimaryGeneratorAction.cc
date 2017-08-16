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
    mom.setRThetaPhi(1., pi * G4UniformRand(), twopi * G4UniformRand());
    gun.SetParticleMomentumDirection(mom);
    gun.GeneratePrimaryVertex(event);
}
