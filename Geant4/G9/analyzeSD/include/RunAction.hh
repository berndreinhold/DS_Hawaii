/* Definition of the RunAction class. */

#ifndef RunAction_h
#define RunAction_h 1

#include "globals.hh"
#include "G4RunManager.hh"
#include "G4UserRunAction.hh"

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

class RunAction : public G4UserRunAction
{
  public:
	RunAction();
	virtual ~RunAction();

	virtual void BeginOfRunAction(const G4Run*);
	virtual void   EndOfRunAction(const G4Run*);
};

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

#endif
