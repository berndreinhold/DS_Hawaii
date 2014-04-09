/* Definition of the VetoSD class. */

#ifndef VetoSD_h
#define VetoSD_h 1

#include "G4VSensitiveDetector.hh"
#include "VetoHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

// veto sensitive detector
// in Initialize(), it creates one hit for each tracker volume.
// the values are accounted in hits in ProcessHits() function which is 
// called by Geant4 kernel at each step

class VetoSD : public G4VSensitiveDetector
{
  public:
	VetoSD(G4String name);
	virtual ~VetoSD();

	virtual void Initialize(G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
	VetoHitsCollection* fHitsCollection;
	G4int fHCID;

};

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

#endif
