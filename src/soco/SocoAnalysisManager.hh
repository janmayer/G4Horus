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
        {
            std::lock_guard<std::mutex> lock {fLockEvents};
            fEvents.push_back(event);
        }
        if (fEvents.size() > MAXEVENTSINBUFFER) {
            Write();
        }
    };

    void SetFileName(const G4String& fileName);
    G4bool Write();
    void Destroy();

    static constexpr size_t MAXEVENTSINBUFFER = 1000000;

  private:
    SocoAnalysisManager();
    ~SocoAnalysisManager() = default;

    std::mutex fLockEvents;
    std::vector<SOCO::Event> fEvents;
    std::mutex fLockFile; // not sure if needed
    std::ofstream fFile;
    SocoFileMessenger fFileMessenger;
    static SocoAnalysisManager* gInstance;
};
