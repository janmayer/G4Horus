#include "SocoFileMessenger.hh"
#include "G4AnalysisUtilities.hh"

#include "G4UIdirectory.hh"
#include "SocoAnalysisManager.hh"

SocoFileMessenger::SocoFileMessenger(SocoAnalysisManager* manager)
    : G4UImessenger()
    , fManager(manager)
    , fSetFileNameCmd(nullptr)
{
    fSetFileNameCmd = G4Analysis::make_unique<G4UIcmdWithAString>("/analysis/setFileName", this);
    fSetFileNameCmd->SetGuidance("Set name for the histograms & ntuple file");
    fSetFileNameCmd->SetParameterName("Filename", false);
    fSetFileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

void SocoFileMessenger::SetNewValue(G4UIcommand* command, G4String value)
{
    if (command == fSetFileNameCmd.get()) {
        G4cout << "Set file name: " << value << G4endl;
        SocoAnalysisManager::Instance()->SetFileName(value);
    }
}
