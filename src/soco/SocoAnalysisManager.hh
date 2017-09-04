#pragma once

#include "Event.hh"
#include "G4VAnalysisManager.hh"
#include "Hit.hh"
#include <fstream>
#include <iostream>
#include <mutex>

class SocoAnalysisManager : public G4VAnalysisManager {
  public:
    // Similar to G4RootAnalysisManager.
    // It looks a bit like a singleton, but the constructor is public for no(?) reason
    explicit SocoAnalysisManager(G4bool isMaster = true);
    ~SocoAnalysisManager() override;

    static SocoAnalysisManager* Instance();

    inline void AddEvent(const SOCO::Event& event)
    {
        std::lock_guard<std::mutex> lock(fLockEvents);
        fEvents.push_back(event);
    };

  protected:
    G4bool OpenFileImpl(const G4String& fileName) override;
    G4bool WriteImpl() override;
    G4bool CloseFileImpl() override;

  private:
    std::mutex fLockEvents;
    std::vector<SOCO::Event> fEvents;
    std::ofstream fFile;

    static SocoAnalysisManager* fgMasterInstance;
    static G4ThreadLocal SocoAnalysisManager* fgInstance;
};
