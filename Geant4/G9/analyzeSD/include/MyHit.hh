// Definition of the MyHit class. */

#ifndef MyHit_h
#define MyHit_h 1

#include "globals.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4VPhysicalVolume.hh"

class MyHit : public G4VHit
{
  public:
	MyHit();
	virtual ~MyHit();
	MyHit(const MyHit &right);
	const MyHit& operator=(const MyHit &right);
	int operator==(const MyHit &right) const;

	inline void* operator new(size_t);
 	inline void  operator delete(void*);

	void Draw();
	void Print();

  public:
	void SetEdep		(G4double de)			{ edep = de; };
	void SetParticle	(G4ParticleDefinition* par)	{ particle=par; };
	void SetID		(G4int trackid)			{ id=trackid; };
	void SetParentID	(G4int parid)			{ parentid=parid; };
	void SetProcess		(G4String pro)			{ process=pro; };
	void SetPosition	(G4ThreeVector posi)		{ pos=posi; };
	void SetTime		(G4double tempo)		{ time=tempo; };
	void SetKineticEnergy	(G4double ee)			{ kinEnergy=ee; };
	void SetVolume		(G4VPhysicalVolume* vv)		{ volume=vv; };
  	void SetVolName		(G4String name)			{ volName=name; };
	void SetTallied		(G4bool tal = true)		{ tallied=tal; };

	G4double GetEdep()	{ return edep; };
	G4ParticleDefinition* GetParticle()	{ return particle; };
	G4int GetID()	{ return id; };
	G4int GetParentID()	{ return parentid; };
	G4String GetProcess()	{ return process; };
	G4ThreeVector GetPosition() { return pos; };
	G4double GetTime()	{ return time; };
	G4double GetKineticEnergy()	{ return kinEnergy; };
	G4VPhysicalVolume* GetVolume()	{ return volume; };
	G4String GetName()	{ return volName; };
	G4bool GetTallied()	{ return tallied; };

  private:
	G4double		edep;
	G4ParticleDefinition*	particle;
	G4int			id;
	G4int			parentid;
	G4String		process;
	G4ThreeVector		pos;
	G4double		time;
	G4double 		kinEnergy;
	G4VPhysicalVolume*	volume;
	G4String		volName;
	G4bool			tallied;

};

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

typedef G4THitsCollection<MyHit> MyHitsCollection;

extern G4Allocator<MyHit>* MyHitAllocator;

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

inline void* MyHit::operator new(size_t)
{
  if (!MyHitAllocator)
  {
    MyHitAllocator = new G4Allocator<MyHit>;
  }
  void *aHit;
  aHit = (void *) MyHitAllocator->MallocSingle();
  return aHit;
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

inline void MyHit::operator delete(void *aHit)
{
  MyHitAllocator->FreeSingle((MyHit*) aHit);
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

#endif
