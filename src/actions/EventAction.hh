#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4THitsMap.hh"
#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction {
  public:
    EventAction() = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

  private:
    inline G4THitsMap<G4double>* GetHitsCollection(const G4int hcID, const G4Event* event) const;
    inline G4double GetSum(const G4THitsMap<G4double>* hitsMap) const;
};

#endif //EVENTACTION_HH
