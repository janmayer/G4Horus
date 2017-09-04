#pragma once

#include "Event.hh"
#include "G4THitsMap.hh"
#include "G4UserEventAction.hh"

class EventActionSoco : public G4UserEventAction {
  public:
    EventActionSoco() = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

  private:
    SOCO::Event fEvent;
    inline G4THitsMap<G4double>* GetHitsCollection(const G4int hcID, const G4Event* event) const;
    inline G4double GetSum(const G4THitsMap<G4double>* hitsMap) const;
};
