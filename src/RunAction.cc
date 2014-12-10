#include "RunAction.hh"

#include "g4root.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction() : G4UserRunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
#if(NTUPLE_ENABLED)
  G4cout << "... with ntuple" << G4endl;
#endif

  analysisManager->SetHistoDirectoryName("histograms");
#if(NTUPLE_ENABLED)
  analysisManager->SetNtupleDirectoryName("ntuple");
#endif
  analysisManager->SetVerboseLevel(0);

#if(NTUPLE_ENABLED)
  analysisManager->CreateNtuple("Horus", "Edep");
#endif
  for( auto &det : detectors ) {
    analysisManager->CreateH1( det, "Edep in " + det, 10000, 0., 10.*MeV); // 1keV/Bin
#if(NTUPLE_ENABLED)
    analysisManager->CreateNtupleDColumn(det);
#endif
  }
#if(NTUPLE_ENABLED)
  analysisManager->FinishNtuple();
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
