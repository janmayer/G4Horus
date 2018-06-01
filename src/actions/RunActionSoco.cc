#include "RunActionSoco.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "SocoAnalysisManager.hh"

RunActionSoco::RunActionSoco()
{
    SocoAnalysisManager::Instance();
    G4cout << "Output: Using Soco" << G4endl;
}

RunActionSoco::~RunActionSoco()
{
    SocoAnalysisManager::Instance()->Destroy();
}

void RunActionSoco::BeginOfRunAction(const G4Run* /*aRun*/)
{
}

void RunActionSoco::EndOfRunAction(const G4Run* /*aRun*/)
{
    SocoAnalysisManager::Instance()->Write();
}
