#include "PhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

//Hinzufügen von GammaWechselwirkungn
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"


PhysicsList::PhysicsList(){
}
PhysicsList::~PhysicsList(){
}

void PhysicsList::ConstructParticle(){
//  G4Geantino::GeantinoDefinition();
  G4Electron::ElectronDefinition();
  G4Gamma::GammaDefinition();
  G4Positron::PositronDefinition();
}

void PhysicsList::ConstructProcess(){
  AddTransportation();
  AddElectronInteraction();
  AddGammaInteraction();
  AddPositronInteraction();
}

void PhysicsList::SetCuts(){
  G4int temp=GetVerboseLevel();
  SetVerboseLevel(0);
  SetCutsWithDefault();
  SetVerboseLevel(temp);

}

//Elektronenwechselwirkungen

void PhysicsList::AddElectronInteraction(){
  G4ParticleDefinition* particle = G4Electron::ElectronDefinition();
  G4ProcessManager* pmanager = particle->GetProcessManager();

  // AddProcess bekommt neben dem Prozess noch die Ordnungszahlen
  // ordAtRestDoIt, ordAlongStepDoIt, ordPostStepDoIt mit

  pmanager->AddProcess(new G4eMultipleScattering,-1,1,1);
  pmanager->AddProcess(new G4eIonisation,-1,2,2);
  pmanager->AddProcess(new G4eBremsstrahlung,-1,3,3);
}

  //Gamma-Wechselwirkungen

void PhysicsList::AddGammaInteraction(){
  G4ParticleDefinition* particle = G4Gamma::GammaDefinition();
  G4ProcessManager* pmanager = particle->GetProcessManager();

  //Wichtig: Hier AddDiscreteProcess verwenden, sonst passiert nichts

  pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());
  pmanager->AddDiscreteProcess(new G4ComptonScattering());
  pmanager->AddDiscreteProcess(new G4GammaConversion());
}

void PhysicsList::AddPositronInteraction(){
  G4ParticleDefinition* particle = G4Positron::PositronDefinition();
  G4ProcessManager* pmanager=particle->GetProcessManager();

  pmanager->AddProcess(new G4eMultipleScattering,-1,1,1);
  pmanager->AddProcess(new G4eIonisation,-1,2,2);
  pmanager->AddProcess(new G4eBremsstrahlung,-1,3,3);
  pmanager->AddProcess(new G4eplusAnnihilation,0,-1,4);
}
