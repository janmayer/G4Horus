#include "EventAction.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "g4root.hh"
#include <numeric>

extern const std::vector<std::string> detectors;

inline G4THitsMap<G4double>* EventAction::GetHitsCollection(const G4int id, const G4Event* event) const
{
    auto hits_collection = dynamic_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(id));

    if (hits_collection == nullptr) {
        G4ExceptionDescription msg;
        msg << "Cannot access hits collection with ID: " << id;
        G4Exception("EventAction::GetHitsCollection()", "#EA001", FatalException, msg);
    }

    return hits_collection;
}

inline G4double EventAction::GetSum(const G4THitsMap<G4double>* hits) const
{
    return std::accumulate(hits->GetMap()->begin(), hits->GetMap()->end(), (G4double)0.0,
                           [](const G4double sum, const std::pair<G4int, G4double*>& p) {
                               return sum + *(p.second);
                           });
}

void EventAction::BeginOfEventAction(const G4Event* /*anEvent*/)
{
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    auto analysisManager = G4AnalysisManager::Instance();

    const size_t ndets = detectors.size();
    for (size_t i = 0; i < ndets; i++) {
        const G4int collection_id = G4SDManager::GetSDMpointer()->GetCollectionID(detectors.at(i) + "/edep");
        const G4double edep = GetSum(GetHitsCollection(collection_id, event));
        analysisManager->FillH1(i, edep);
#if (NTUPLE_ENABLED)
        analysisManager->FillNtupleDColumn(i, edep);
#endif
    }

#if (NTUPLE_ENABLED)
    analysisManager->AddNtupleRow();
#endif
}
