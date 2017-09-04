#include "EventActionSoco.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "SocoAnalysisManager.hh"
#include <iostream>
#include <numeric>

using G4AnalysisManager = SocoAnalysisManager;

extern const std::vector<std::string> detectors;

inline G4THitsMap<G4double>* EventActionSoco::GetHitsCollection(const G4int id, const G4Event* event) const
{
    auto hits_collection = dynamic_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(id));

    if (hits_collection == nullptr) {
        G4ExceptionDescription msg;
        msg << "Cannot access hits collection with ID: " << id;
        G4Exception("EventActionSoco::GetHitsCollection()", "#EA001", FatalException, msg);
    }

    return hits_collection;
}

inline G4double EventActionSoco::GetSum(const G4THitsMap<G4double>* hits) const
{
    return std::accumulate(hits->GetMap()->begin(), hits->GetMap()->end(), (G4double)0.0,
                           [](const G4double sum, const std::pair<G4int, G4double*>& p) {
                               return sum + *(p.second);
                           });
}

void EventActionSoco::BeginOfEventAction(const G4Event* /*anEvent*/)
{
}

void EventActionSoco::EndOfEventAction(const G4Event* event)
{
    fEvent.clear();

    const size_t ndets = detectors.size();
    for (size_t i = 0; i < ndets; i++) {
        const G4int collection_id = G4SDManager::GetSDMpointer()->GetCollectionID(detectors.at(i) + "/edep");
        const G4double edep = GetSum(GetHitsCollection(collection_id, event));
        if (edep > 1e-3) { // Energy Threshold
            fEvent.hits.emplace_back(SOCO::Hit(i, uint16_t(floor(edep * 1000.)), 0));
        }
    }

    if (!fEvent.hits.empty()) {
        fEvent.trigger_id = fEvent.hits.at(0).id;
        fEvent.timestamp = 0;
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->AddEvent(fEvent);
    }
}
