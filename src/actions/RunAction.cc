#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

extern const std::vector<std::string> detectors;

RunAction::RunAction()
    : G4UserRunAction()
{
    G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->SetVerboseLevel(0);

    G4cout << "Using " << analysis_manager->GetType() << G4endl;
#if (NTUPLE_ENABLED)
    G4cout << "... with ntuple" << G4endl;
#endif

    analysis_manager->SetHistoDirectoryName("histograms");
#if (NTUPLE_ENABLED)
    analysis_manager->SetNtupleDirectoryName("ntuple");
    analysis_manager->CreateNtuple("Horus", "Edep");
#endif

    for (auto& det : detectors) {
        analysis_manager->CreateH1(det, "Edep in " + det, 10000, 0., 10. * MeV); // Always use 1keV/bin!
#if (NTUPLE_ENABLED)
        analysis_manager->CreateNtupleDColumn(det);
#endif
    }

#if (NTUPLE_ENABLED)
    analysis_manager->FinishNtuple();
#endif
}

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run*)
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->Write();
    analysis_manager->CloseFile();
}
