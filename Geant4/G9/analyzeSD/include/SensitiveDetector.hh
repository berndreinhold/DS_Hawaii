/* Definition of the SensitiveDetector class. */

#ifndef SensitiveDetector_h
#define SensitiveDetector_h 1

#include "globals.hh"
#include "G4VSensitiveDetector.hh"
#include "MyHit.hh"

class G4Step;
class G4Track;
class G4HCofThisEvent;
class G4TouchableHistory;


//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

class Sensitive : public G4VSensitiveDetector
{
  public:
	Sensitive(G4String name);
	virtual ~Sensitive();

	virtual void Initialize(G4HCofThisEvent* collection);
	virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* history);
	virtual void EndOfEvent(G4HCofThisEvent* collection);

  private:
	MyHitsCollection* collection;
};

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

#endif
