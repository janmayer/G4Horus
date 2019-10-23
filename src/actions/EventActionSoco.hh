#pragma once

#include "Event.hh"
#include "G4THitsMap.hh"
#include "G4UserEventAction.hh"
#include <vector>

class EventActionSoco : public G4UserEventAction {
  public:
    EventActionSoco();
    void EndOfEventAction(const G4Event* event) override;

  private:
    SOCO::Event fEvent;
    bool fIDsCached;
    std::vector<G4int> fHitCollectionIDs;
};
