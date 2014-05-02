/* Definition of the SDDetectorConstruction class. */

#ifndef SDDetectorConstruction_h
#define SDDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;


//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

class SDDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
	SDDetectorConstruction();
	virtual ~SDDetectorConstruction();

  public:
	virtual G4VPhysicalVolume* Construct();

  //set methods
  	void SetCheckOverlaps(G4bool);

  private:
	void DefineMaterials();
	G4VPhysicalVolume* DefineVolumes();

  	G4bool fCheckOverlaps;
};

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

#endif

