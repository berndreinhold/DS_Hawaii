/* Implementation of the SDEventAction class. */

#include "SDEventAction.hh"
#include "VetoHit.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"


//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

SDEventAction::SDEventAction()
: G4UserEventAction(),
  fVetoHCID(-1)
{}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

SDEventAction::~SDEventAction()
{}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void SDEventAction::BeginOfEventAction(const G4Event* event)
{
  G4int eventID = event->GetEventID();
  G4cout << "\n---> Begin of event: " << eventID << G4endl;
  if (fVetoHCID==-1)
  {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    fVetoHCID = sdManager->GetCollectionID("vetoDet");
  }
  
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void SDEventAction::EndOfEventAction(const G4Event* event)
{
  

 // print per event
 G4int eventID = event->GetEventID();
 G4cout << "---> End of event: " << eventID << G4endl;

 G4HCofThisEvent* hce = event->GetHCofThisEvent();
 if (!hce)
 {
   G4ExceptionDescription msg;
   msg << "No hits collection of this event found.\n";
   G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
   return;
 }

 //get hits collection
 VetoHitsCollection* vHC = static_cast<VetoHitsCollection*>(hce->GetHC(fVetoHCID));

 if (!vHC)
 {
   G4ExceptionDescription msg;
   msg << "Some of hits collections of this event are not found.\n";
   G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
   return;
 }


 // get number of stored trajectories

  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

 //periodic printing
 if (eventID < 100 || eventID % 100 == 0)
 {
   G4cout << ">>> Event: " << eventID << G4endl;
 }
 if (trajectoryContainer)
 {
   G4cout << "   " << n_trajectories << " trajectories stored in this event." << G4endl;
 }

 //loop on hits collection and dump on hits on screen
 G4int n_hit = vHC->entries();
 G4cout << "Veto has " << n_hit << "hits." << G4endl;
 for (G4int i=0; i<n_hit; i++)
 {
   VetoHit* hit = (*vHC)[i];
   hit->Print();
 }


}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....
