#include "PrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
    , gun(new G4ParticleGun(1))
{
    gun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("gamma"));
    gun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));
    //gun->SetParticleEnergy();
    gun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    G4double phi = twopi * G4UniformRand();
    G4double cos_theta = 2. * G4UniformRand() - 1.;
    G4double sin_theta = std::sqrt(1. - cos_theta * cos_theta);

    G4double ux = sin_theta * std::cos(phi);
    G4double uy = sin_theta * std::sin(phi);
    G4double uz = cos_theta;

    gun->SetParticleMomentumDirection(G4ThreeVector(ux, uy, uz));
    gun->GeneratePrimaryVertex(event);
}
