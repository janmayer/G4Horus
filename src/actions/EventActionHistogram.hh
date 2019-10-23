#pragma once

#include "G4THitsMap.hh"
#include "G4UserEventAction.hh"
#include <vector>

class EventActionHistogram : public G4UserEventAction {
  public:
    EventActionHistogram();
    void EndOfEventAction(const G4Event* event) override;

  private:
    bool fIDsCached;
    std::vector<G4int> fHitCollectionIDs;
};
