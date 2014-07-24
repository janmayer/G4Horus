#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "globals.hh"
#include "G4UserEventAction.hh"
#include "G4THitsMap.hh"

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);

private:
  G4THitsMap<G4double>* GetHitsCollection(G4int hcID, const G4Event* event) const;
  inline G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
};

#endif //EVENTACTION_HH
