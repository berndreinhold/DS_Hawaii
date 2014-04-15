/* Definition of the EventAction class. */

#ifndef EventAction_h
#define EventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

class EventAction : public G4UserEventAction
{
  public:
	EventAction();
	virtual ~EventAction();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void   EndOfEventAction(const G4Event*);

  private:
	G4int fVetoHCID;
	G4int fTPCHCID;
};

#endif


//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......
