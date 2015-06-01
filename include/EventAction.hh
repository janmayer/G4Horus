#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4THitsMap.hh"

extern const std::vector<std::string> detectors;

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);

private:
  G4THitsMap<G4double>* GetHitsCollection(const G4int hcID, const G4Event* event) const;
  inline G4double GetSum(const G4THitsMap<G4double>* hitsMap) const;
};

#endif //EVENTACTION_HH
