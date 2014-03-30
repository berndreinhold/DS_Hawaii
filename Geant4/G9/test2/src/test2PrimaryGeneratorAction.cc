/* Implementation of the test2PrimaryGeneratorAction class. */

#include "test2PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

test2PrimaryGeneratorAction::test2PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleSource(0)
{
  fParticleSource = new G4GeneralParticleSource();
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

test2PrimaryGeneratorAction::~test2PrimaryGeneratorAction()
{
  delete fParticleSource;
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void test2PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleSource->GeneratePrimaryVertex(anEvent);
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....
