/* Definition of the testDetectorConstruction class. */

#ifndef testDetectorConstruction_h
#define testDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

// detector construction class to define the materials and the geometry

class testDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
	testDetectorConstruction();
	virtual ~testDetectorConstruction();

	virtual G4VPhysicalVolume* Construct();

	G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
	G4LogicalVolume* fScoringVolume;
};

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

#endif
