#pragma once

#include "G4UIcmdWithAString.hh"
#include "G4UImessenger.hh"
#include <memory>

class SocoAnalysisManager;

class SocoFileMessenger : public G4UImessenger {
  public:
    explicit SocoFileMessenger(SocoAnalysisManager*);
    void SetNewValue(G4UIcommand* command, G4String value) override;

  private:
    SocoAnalysisManager* fManager; // non-owning
    std::unique_ptr<G4UIcmdWithAString> fSetFileNameCmd;
};
