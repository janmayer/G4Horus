#include "RunActionSoco.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "SocoAnalysisManager.hh"

using G4AnalysisManager = SocoAnalysisManager;

extern const std::vector<std::string> detectors;

RunActionSoco::RunActionSoco()
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->SetVerboseLevel(0);

    G4cout << "Output: Using " << analysis_manager->GetType() << G4endl;
}

RunActionSoco::~RunActionSoco()
{
    delete G4AnalysisManager::Instance();
}

void RunActionSoco::BeginOfRunAction(const G4Run* /*aRun*/)
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->OpenFile();
}

void RunActionSoco::EndOfRunAction(const G4Run* /*aRun*/)
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->Write();
    analysis_manager->CloseFile();
}
