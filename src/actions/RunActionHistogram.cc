#include "RunActionHistogram.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

extern const std::vector<std::string> detectors;

RunActionHistogram::RunActionHistogram()
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->SetVerboseLevel(0);

    G4cout << "Output: Using " << analysis_manager->GetType() << G4endl;

    analysis_manager->SetHistoDirectoryName("histograms");
    for (auto& det : detectors) {
        analysis_manager->CreateH1(det, "Edep in " + det, 20000, 0., 20. * MeV); // Always use 1keV/bin!
    }
}

RunActionHistogram::~RunActionHistogram()
{
    delete G4AnalysisManager::Instance();
}

void RunActionHistogram::BeginOfRunAction(const G4Run* /*aRun*/)
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->OpenFile();
}

void RunActionHistogram::EndOfRunAction(const G4Run* /*aRun*/)
{
    auto analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->Write();
    analysis_manager->CloseFile();
}
