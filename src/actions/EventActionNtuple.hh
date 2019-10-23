#pragma once

#include "G4THitsMap.hh"
#include "G4UserEventAction.hh"
#include <vector>

class EventActionNtuple : public G4UserEventAction {
  public:
    EventActionNtuple();
    void EndOfEventAction(const G4Event* event) override;

  private:
    bool fIDsCached;
    std::vector<G4int> fHitCollectionIDs;
};
