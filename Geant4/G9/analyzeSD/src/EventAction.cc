/* Implementation of the EventAction class. */

#include "EventAction.hh"
#include "MyHit.hh"
#include "Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4VHitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

EventAction::EventAction()
: G4UserEventAction(),
  fVetoHCID(-1),
  fTPCHCID(-1)
{}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

EventAction::~EventAction()
{
  delete G4AnalysisManager::Instance();
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

void EventAction::BeginOfEventAction(const G4Event* event)
{
  //MyAnalysis::GetInstance()->StartEvent(event->GetEventID());
  if (fVetoHCID==-1)
  {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    fVetoHCID = sdManager->GetCollectionID("vetoDet");
    fTPCHCID = sdManager->GetCollectionID("activeDet");
  }
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

void EventAction::EndOfEventAction(const G4Event* event)
{
  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if (!hce)
  {
    G4ExceptionDescription msg;
    msg << "No hits collection of this event found.\n";
    G4Exception("EventAction::EndOfEventAction()","Code001", JustWarning, msg);
    return;
  }

  //get hits collections
  MyHitsCollection* vetoHC = static_cast<MyHitsCollection*>(hce->GetHC(fVetoHCID));

  MyHitsCollection* tpcHC = static_cast<MyHitsCollection*>(hce->GetHC(fTPCHCID));

  if ((!vetoHC) || (!tpcHC))
  {
    G4ExceptionDescription msg;
    msg << "Some of hits collections of this event not found.\n";
    G4Exception("EventAction::EndOfEventAction()","Code001",JustWarning,msg);
    return;
  }

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  //fill ntuple
  //
  //VETO
  G4int n_hit = vetoHC->entries();
  
  for (G4int i=0; i < n_hit; i++)
  {
    MyHit* hit = (*vetoHC)[i];
    G4ThreeVector Pos = hit->GetPosition();

    analysisManager->FillNtupleDColumn(0, Pos.x());
    analysisManager->FillNtupleDColumn(1, Pos.y());
    analysisManager->FillNtupleDColumn(2, Pos.z());
    analysisManager->FillNtupleDColumn(7, hit->GetEdep());
    analysisManager->FillNtupleIColumn(8, hit->GetID());
    analysisManager->FillNtupleIColumn(10, hit->GetParentID());
  }
  //
  //ACTIVE
  for (G4int i=0; i < tpcHC->entries(); i++)
  {
    MyHit* hit = (*tpcHC)[i];
    G4ThreeVector Pos = hit->GetPosition();

    analysisManager->FillNtupleDColumn(3, Pos.x());
    analysisManager->FillNtupleDColumn(4, Pos.y());
    analysisManager->FillNtupleDColumn(5, Pos.z());
    analysisManager->FillNtupleDColumn(6, hit->GetEdep());
    analysisManager->FillNtupleIColumn(9, hit->GetID());
    analysisManager->FillNtupleIColumn(11, hit->GetParentID());
  }

  analysisManager->AddNtupleRow(); //required!!!
  
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......


