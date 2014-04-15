/* Implementation of the SensitiveDetector class. */

#include "SensitiveDetector.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4VPhysicalVolume.hh"

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

Sensitive::Sensitive(G4String name) 
: G4VSensitiveDetector(name)
{
  G4String HCname; //name of the hits collection
  collectionName.insert(HCname=name);
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

Sensitive::~Sensitive()
{}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

void Sensitive::Initialize(G4HCofThisEvent *HCE)
{
  //creates a collection of hits
  collection = new MyHitsCollection(SensitiveDetectorName,SensitiveDetectorName);
  G4int HCID = -1;
  if (HCID < 0)
  {
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(SensitiveDetectorName);
  }
  HCE->AddHitsCollection(HCID,collection);
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

//create the hits and store them in the collection
G4bool Sensitive::ProcessHits( G4Step* aStep, G4TouchableHistory* )
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(!edep) return false;

  G4Track* aTrack = aStep->GetTrack();
  G4String type = aTrack->GetDefinition()->GetParticleName();
  
  //save the information on the hits
  MyHit* newHit = new MyHit();
  //returns a null pointer if the track is created by the primary particle
  const G4VProcess* process = aTrack->GetCreatorProcess();
  if(process)
  {
    const G4String& nomeproc = process->GetProcessName();
    newHit->SetProcess (nomeproc);
  }
  else
  {
    newHit->SetProcess("primary");
  }

  newHit->SetEdep 		(edep);
  newHit->SetParticle		(aTrack->GetDefinition());
  newHit->SetID		  	(aTrack->GetTrackID());
  newHit->SetParentID		(aTrack->GetParentID());
  newHit->SetPosition	  	(aStep->GetPostStepPoint()->GetPosition());
  newHit->SetTime		(aStep->GetPostStepPoint()->GetGlobalTime());
  newHit->SetKineticEnergy	(aTrack->GetKineticEnergy());
  newHit->SetVolume		(aTrack->GetVolume());
  newHit->SetVolName		(aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName());
  collection->insert(newHit);

  return true;
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

void Sensitive::EndOfEvent(G4HCofThisEvent*)
{
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......
