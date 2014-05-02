/* Definition of the SDPrimaryGeneratorAction class. */

#ifndef SDPrimaryGeneratorAction_h
#define SDPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;
class SDDetectorConstruction;

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

class SDPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
	SDPrimaryGeneratorAction();
	virtual ~SDPrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);

	//method from the base class
	const G4GeneralParticleSource* GetGeneralParticleSource() const { return fParticleSource; }

  private:
	G4GeneralParticleSource* fParticleSource; //pointer to a G4 generator class
};

#endif
