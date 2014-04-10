/* Definition of the PrimaryGeneratorAction class. */

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
	PrimaryGeneratorAction();
	virtual ~PrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event* );

	const G4GeneralParticleSource* GetGeneralParticleSource() const { return fParticleSource; }

  private:
	G4GeneralParticleSource* fParticleSource; //pointer to a G4 generator class

};

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

#endif 


