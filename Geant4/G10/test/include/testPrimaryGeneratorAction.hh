/* Definition of the testPrimaryGeneratorAction class. */

#ifndef testPrimaryGeneratorAction_h
#define testPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

//the primary generator action clas with particle gun.

//the default kinematic is a 6 MeV electron

class testPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
	testPrimaryGeneratorAction();
	virtual ~testPrimaryGeneratorAction();

	//method from the base class
	virtual void GeneratePrimaries(G4Event*);

	//method to access particle gun
	const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
	G4ParticleGun* fParticleGun; //pointer to a G4 gun class

};

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

#endif
