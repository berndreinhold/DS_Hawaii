/* Definition of the testActionInitialization class. */

#ifndef testActionInitialization_h
#define testActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

// Action initialization class

class testActionInitialization : public G4VUserActionInitialization
{
  public:
	testActionInitialization();
	virtual ~testActionInitialization();

	//this is called by each worker thread. 
	//Create here the user-actions needed by each thread:
	//RunAction, EventAction, SteppingAction, StackingAction
	virtual void Build() const; 

};

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

#endif
