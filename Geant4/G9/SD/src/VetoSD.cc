/* Implementation of VetoSD class. */

#include "VetoSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

VetoSD::VetoSD(G4String name)
: G4VSensitiveDetector(name), 
  fHitsCollection(0),
  fHCID(-1)
{
   //G4String HCname = "vetoColl";
   G4String HCname; //name of the hits collection
   collectionName.insert(HCname=name);
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

VetoSD::~VetoSD()
{}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void VetoSD::Initialize(G4HCofThisEvent* hce)
{
  //create hits collection
  fHitsCollection = new VetoHitsCollection(SensitiveDetectorName, SensitiveDetectorName);

  //add this collection in hce
  if (fHCID < 0) 
  {
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(SensitiveDetectorName);
  }
    hce->AddHitsCollection( fHCID, fHitsCollection );
  
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

G4bool VetoSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  //energy deposit
  G4double edep = step->GetTotalEnergyDeposit();

  if (edep==0.) return false;

  VetoHit* newHit = new VetoHit();

  newHit->SetTrackID (step->GetTrack()->GetTrackID());
  newHit->SetEdep(edep);
  newHit->SetPos (step->GetPreStepPoint()->GetPosition());
  newHit->SetTime (step->GetPreStepPoint()->GetGlobalTime());
  newHit->SetLogicV (step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume());
  //newHit->SetName (step->GetTrack()->GetVolume()->GetName());
  newHit->SetVolName (step->GetPreStepPoint()->GetPhysicalVolume()->GetName());
  //newHit->SetName (step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName());

  fHitsCollection->insert( newHit );

  return true;
  
}
//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void VetoSD::EndOfEvent(G4HCofThisEvent*)
{
}

