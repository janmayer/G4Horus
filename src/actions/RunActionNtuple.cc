#include "RunActionNtuple.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

extern const std::vector<std::string> detectors;

RunActionNtuple::RunActionNtuple()
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->SetVerboseLevel(0);

    G4cout << "Output: Using " << analysis_manager->GetType() << " with ntuple" << G4endl;

    analysis_manager->SetHistoDirectoryName("histograms");
    analysis_manager->SetNtupleDirectoryName("ntuple");
    analysis_manager->CreateNtuple("Horus", "Edep");
    for (auto& det : detectors) {
        analysis_manager->CreateH1(det, "Edep in " + det, 10000, 0., 10. * MeV); // Always use 1keV/bin!
        analysis_manager->CreateNtupleDColumn(det);
    }
    analysis_manager->FinishNtuple();
}

RunActionNtuple::~RunActionNtuple()
{
    delete G4AnalysisManager::Instance();
}

void RunActionNtuple::BeginOfRunAction(const G4Run* /*aRun*/)
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->OpenFile();
}

void RunActionNtuple::EndOfRunAction(const G4Run* /*aRun*/)
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->Write();
    analysis_manager->CloseFile();
}
