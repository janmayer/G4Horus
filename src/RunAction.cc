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
  std::vector<std::string> detectors = {"Ge00", "Ge01", "Ge02", "Ge03", "Ge04", "Ge05", "Ge06", "Ge07", "Ge08", "Ge09", "Ge10", "Ge11", "Ge12", "Ge13"};

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->SetHistoDirectoryName("histograms");
  analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);

  analysisManager->CreateNtuple("Horus", "Edep");
  for( auto &det : detectors ) {
    analysisManager->CreateH1( det, "Edep in " + det, 1000, 0., 10.*MeV);
    analysisManager->CreateNtupleDColumn(det);
  }
  analysisManager->FinishNtuple();
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
