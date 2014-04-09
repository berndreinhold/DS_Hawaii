/* Implementation of the SDRunAction class. */

#include "SDRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

SDRunAction::SDRunAction()
: G4UserRunAction()
{}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

SDRunAction::~SDRunAction()
{}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void SDRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "#### Run " << aRun->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed

  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void SDRunAction::EndOfRunAction(const G4Run* )
{}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....
