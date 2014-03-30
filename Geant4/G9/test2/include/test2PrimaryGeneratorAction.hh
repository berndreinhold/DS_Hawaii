/* Definition of the test2PrimaryGeneratorAction class. */

#ifndef test2PrimaryGeneratorAction_h
#define test2PrimaryGeneratorAction_h 1
 
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;
class test2DetectorConstruction;

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

class test2PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
	test2PrimaryGeneratorAction();
	virtual ~test2PrimaryGeneratorAction();

	//method from the base class
	virtual void GeneratePrimaries(G4Event*);

	//method to access particle generator
	const G4GeneralParticleSource* GetGeneralParticleSource() const { return fParticleSource; }

  private:
	G4GeneralParticleSource* fParticleSource; //pointer to a G4 generator class

};

#endif
