/* Definition of the SDEventAction class. */

#ifndef SDEventAction_h
#define SDEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

class SDEventAction : public G4UserEventAction
{
  public:
	SDEventAction();
	virtual ~SDEventAction();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);

  private:
        G4int fVetoHCID;
};


#endif

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....
