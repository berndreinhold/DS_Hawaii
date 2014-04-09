/* Implementation of the SDPrimaryGeneratorAction class. */

#include "SDPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

SDPrimaryGeneratorAction::SDPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleSource(0)
{
  fParticleSource = new G4GeneralParticleSource();
}

//......oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

SDPrimaryGeneratorAction::~SDPrimaryGeneratorAction()
{
  delete fParticleSource;
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void SDPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleSource->GeneratePrimaryVertex(anEvent);
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....
