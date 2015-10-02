#include "EventAction.hh"

#include "G4Event.hh"
#include "G4SDManager.hh"
#include "g4root.hh"

#include <numeric>


extern const std::vector<std::string> detectors;


EventAction::EventAction() : G4UserEventAction()
{}


EventAction::~EventAction()
{}


G4THitsMap<G4double>* EventAction::GetHitsCollection(const G4int id, const G4Event* event) const
{
  G4THitsMap<G4double>* hits_collection
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(id));

  if (!hits_collection) {
    G4ExceptionDescription msg;
    msg << "Cannot access hits collection with ID: " << id;
    G4Exception("EventAction::GetHitsCollection()", "#EA001", FatalException, msg);
  }

  return hits_collection;
}


inline G4double EventAction::GetSum(const G4THitsMap<G4double>* hits) const
{
  return std::accumulate(hits->GetMap()->begin(), hits->GetMap()->end(), (G4double)0.0,
  [](const G4double sum, const std::pair<G4int, G4double*> &p) {
    return sum + *(p.second);
  });
}


void EventAction::BeginOfEventAction(const G4Event*)
{}


void EventAction::EndOfEventAction(const G4Event* event)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  for (auto &det : detectors) {
    const G4int collection_id = G4SDManager::GetSDMpointer()->GetCollectionID(det + "/edep");
    const G4double edep = GetSum( GetHitsCollection(collection_id, event) );
    const G4int hist_id = std::addressof(det) - std::addressof(detectors[0]);
    analysisManager->FillH1(hist_id, edep);
#if(NTUPLE_ENABLED)
    analysisManager->FillNtupleDColumn(id, edep);
#endif
  }

#if(NTUPLE_ENABLED)
  analysisManager->AddNtupleRow();
#endif
}
