#include "EventActionNtuple.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "g4root.hh"
#include <numeric>

extern const std::vector<std::string> detectors;

inline G4THitsMap<G4double>* GetHitsCollection(const G4int id, const G4Event* event)
{
    auto hits_collection = dynamic_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(id));

    if (hits_collection == nullptr) {
        G4ExceptionDescription msg;
        msg << "Cannot access hits collection with ID: " << id;
        G4Exception("EventActionNtuple::GetHitsCollection()", "#EA001", FatalException, msg);
    }

    return hits_collection;
}

inline G4double GetSum(const G4THitsMap<G4double>* hits)
{
    return std::accumulate(hits->GetMap()->begin(), hits->GetMap()->end(), (G4double)0.0,
                           [](const G4double sum, const std::pair<G4int, G4double*>& p) {
                               return sum + *(p.second);
                           });
}

EventActionNtuple::EventActionNtuple()
    : fIDsCached(false)
{
}

void EventActionNtuple::EndOfEventAction(const G4Event* event)
{
    if (!fIDsCached) {
        for (const auto& det : detectors) {
            fHitCollectionIDs.push_back(G4SDManager::GetSDMpointer()->GetCollectionID(det + "/edep"));
        }
        fIDsCached = true;
    }

    auto analysisManager = G4AnalysisManager::Instance();
    const size_t ndets = detectors.size();
    for (size_t i = 0; i < ndets; i++) {
        const G4double edep = GetSum(GetHitsCollection(fHitCollectionIDs.at(i), event));
        analysisManager->FillH1(i, edep);
        analysisManager->FillNtupleDColumn(i, edep);
    }
    analysisManager->AddNtupleRow();
}
