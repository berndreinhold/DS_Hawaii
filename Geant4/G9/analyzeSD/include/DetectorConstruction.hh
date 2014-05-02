/* Definition of the DetectorConstruction class. */

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

	virtual G4VPhysicalVolume* Construct();

  private:
	//methods
	void ConstructMaterials();
	G4VPhysicalVolume* ConstructVolumes();
};

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

#endif
