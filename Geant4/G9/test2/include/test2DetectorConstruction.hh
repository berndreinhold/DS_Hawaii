/* Definition of the test2DetectorConstruction class. */

#ifndef test2DetectorConstruction_h
#define test2DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"


class G4VPhysicalVolume;
class G4Material;

//Detector Construction

class test2DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    	test2DetectorConstruction();
	virtual ~test2DetectorConstruction();

  public:
	virtual G4VPhysicalVolume* Construct();

 	void ConstructMaterials();

};

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

#endif
