#include "EventAction.hh"
#include <g4root.hh>

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
 : G4UserEventAction(),
   //fAbsoEdepHCID(-1),
   fHPGedepHCID(-1)
   //fAbsoTrackLengthHCID(-1),
   //fGapTrackLengthHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>*
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  G4THitsMap<G4double>* hitsCollection
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0;
  std::map<G4int, G4double*>::iterator it;
  for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++) {
    sumValue += *(it->second);
  }
  return sumValue;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::PrintEventStatistics(
                            //G4double absoEdep, G4double absoTrackLength,
                            //G4double gapEdep, G4double gapTrackLength
                            G4double Edep
                            ) const
{
  // Print event statistics
  //
  /*G4cout
     < "   Absorber: total energy: "
     << std::setw(7) << G4BestUnit(Edep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
     << G4endl
     << "        Gap: total energy: "
     << std::setw(7) << G4BestUnit(gapEdep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(gapTrackLength, "Length")
     << G4endl;*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  for(int i=0; i<=13; i++){
    std::stringstream detns;
    detns << "Ge" << std::setw(2) << std::setfill('0') << i << "/edep";
    auto fHPGeedep = G4SDManager::GetSDMpointer()->GetCollectionID(detns.str());
    G4double edep = GetSum(GetHitsCollection(fHPGeedep, event));
    analysisManager->FillNtupleDColumn(i, edep);
  }

  analysisManager->AddNtupleRow();

/*
 // Get hist collections IDs
  //if ( fAbsoEdepHCID == -1 ) {
    //fAbsoEdepHCID
    //  = G4SDManager::GetSDMpointer()->GetCollectionID("Absorber/Edep");
    fHPGedepHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("Gap/Edep");
    //fAbsoTrackLengthHCID
    //  = G4SDManager::GetSDMpointer()->GetCollectionID("Absorber/TrackLength");
    //fGapTrackLengthHCID
    //  = G4SDManager::GetSDMpointer()->GetCollectionID("Gap/TrackLength");
  //}

  // Get sum values from hits collections
  //
  //G4double absoEdep = GetSum(GetHitsCollection(fAbsoEdepHCID, event));


  //G4double absoTrackLength
  //  = GetSum(GetHitsCollection(fAbsoTrackLengthHCID, event));
  //G4double gapTrackLength
  //  = GetSum(GetHitsCollection(fGapTrackLengthHCID, event));

  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  //
  //analysisManager->FillH1(1, absoEdep);
  //analysisManager->FillH1(2, gapEdep);
  //analysisManager->FillH1(3, absoTrackLength);
  //analysisManager->FillH1(4, gapTrackLength);

  // fill ntuple
  //
  //analysisManager->FillNtupleDColumn(0, absoEdep);
  analysisManager->FillNtupleDColumn(1, gapEdep);
  //analysisManager->FillNtupleDColumn(2, absoTrackLength);
  //analysisManager->FillNtupleDColumn(3, gapTrackLength);
  analysisManager->AddNtupleRow();

  //print per event (modulo n)
  //
  G4int eventID = event->GetEventID();
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;
    //PrintEventStatistics(absoEdep, absoTrackLength, gapEdep, gapTrackLength);
    PrintEventStatistics(gapEdep);
  }*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
