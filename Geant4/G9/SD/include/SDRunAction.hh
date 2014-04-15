/* Definition of the SDRunAction class. */

#ifndef SDRunAction_h
#define SDRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

class G4Run;

//run action class

class SDRunAction : public G4UserRunAction
{
  public:
	SDRunAction();
	virtual ~SDRunAction();

	virtual void BeginOfRunAction(const G4Run* run);
	virtual void EndOfRunAction(const G4Run* run);
};

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

#endif
