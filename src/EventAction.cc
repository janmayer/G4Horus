#include "EventAction.hh"

#include "G4Event.hh"
#include "G4SDManager.hh"
#include <numeric>

#include "g4root.hh"


EventAction::EventAction() : G4UserEventAction()
{}


EventAction::~EventAction()
{}


G4THitsMap<G4double>* EventAction::GetHitsCollection(const G4int hcID, const G4Event* event) const
{
  G4THitsMap<G4double>* hitsCollection
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}


inline G4double EventAction::GetSum(const G4THitsMap<G4double>* hitsMap) const
{
  return std::accumulate(hitsMap->GetMap()->begin(), hitsMap->GetMap()->end(), (G4double)0.0,
  [](const G4double previous, const std::pair<G4int, G4double*> &p) {
    return previous + *(p.second);
  });
}


void EventAction::BeginOfEventAction(const G4Event*)
{}


void EventAction::EndOfEventAction(const G4Event* event)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4double edep;

  for ( auto &det : detectors ) {
    auto fHPGeedep = G4SDManager::GetSDMpointer()->GetCollectionID( det + "/edep" );
    edep = GetSum( GetHitsCollection(fHPGeedep, event) );
    int id = std::addressof(det) - std::addressof(detectors[0]);
    analysisManager->FillH1( id, edep );
#if(NTUPLE_ENABLED)
    analysisManager->FillNtupleDColumn( id, edep );
#endif
  }
#if(NTUPLE_ENABLED)
  analysisManager->AddNtupleRow();
#endif
}
