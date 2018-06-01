#pragma once

#include "Event.hh"
#include "G4String.hh"
#include "G4Types.hh"
#include "SocoFileMessenger.hh"
#include <fstream>
#include <mutex>

class SocoAnalysisManager {
  public:
    SocoAnalysisManager(const SocoAnalysisManager&) = delete;
    SocoAnalysisManager(SocoAnalysisManager&&) = delete;
    SocoAnalysisManager& operator=(const SocoAnalysisManager&) = delete;
    SocoAnalysisManager& operator=(SocoAnalysisManager&&) = delete;
    static SocoAnalysisManager* Instance();

    inline void AddEvent(const SOCO::Event& event)
    {
        std::lock_guard<std::mutex> lock{fLockEvents};
        fEvents.push_back(event);
    };

    inline void SetFileName(const G4String& fileName)
    {
        fFileName = fileName;
    }

    G4bool Write();
    void Destroy();

  private:
    SocoAnalysisManager();
    ~SocoAnalysisManager() = default;

    std::mutex fLockEvents;
    std::vector<SOCO::Event> fEvents;
    G4String fFileName;
    SocoFileMessenger fFileMessenger;
    static SocoAnalysisManager* gInstance;
};
