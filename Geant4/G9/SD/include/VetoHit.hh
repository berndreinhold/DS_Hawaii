/* Definition of the VetoHit class. */

#ifndef VetoHit_h
#define VetoHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"

//Tracker hit class
//
// Defines data members to store the trackID, energy deposit, position of charged particles,
// logical volumes and times of hits.
// - fTrackID, fEdep, fPos, fLogicV, fTime

class VetoHit : public G4VHit
{
  public: 
	VetoHit();
	VetoHit(const VetoHit&);
	virtual ~VetoHit();

	//operators
	const VetoHit& operator=(const VetoHit&);
	G4int operator==(const VetoHit&) const;

	inline void* operator new(size_t);
	inline void operator delete(void*);

        //methods from base class
	virtual void Draw();
	virtual void Print();

 	//set methods
	void SetTrackID   (G4int track)       		{ fTrackID = track; };
	void SetEdep      (G4double edep)     		{ fEdep = edep; };
	void SetPos       (G4ThreeVector xyz)		{ fPos = xyz; };
	void SetTime      (G4double time)     	     	{ fTime = time; };
	void SetLogicV    (G4LogicalVolume* lvolume) 	{ fLogicV = lvolume; };
	void SetVolName	  (G4String* volName)	{ fVolName = volName; };
	//void SetVolume	  (G4VPhysicalVolume* volume)	{ fLogicV = volume; };
    	

    	//get methods
	G4int GetTrackID() const     		  { return fTrackID; };
	G4double GetEdep() const     		  { return fEdep; };
	G4ThreeVector GetPos() const 		  { return fPos; };
	G4double GetTime() const                  { return fTime; };
 	const G4LogicalVolume* GetLogV() const    { return fLogicV; };
	const G4String* GetVolName() const { return fVolName; };
	//const G4VPhysicalVolume* GetPhysV() const { return fLogicV; };

  private:
	G4int 			 fTrackID;
	G4double		 fEdep;
	G4ThreeVector		 fPos;
	G4double		 fTime;
	const G4LogicalVolume*	 fLogicV;
	const G4String* 	 fVolName;
	//const G4VPhysicalVolume* fLogicV;

};

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

typedef G4THitsCollection<VetoHit> VetoHitsCollection;

extern G4Allocator<VetoHit> VetoHitAllocator;

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

inline void* VetoHit::operator new(size_t)
{
  void *hit;
  hit = (void *) VetoHitAllocator.MallocSingle();
  return hit;
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

inline void VetoHit::operator delete(void *hit)
{
  VetoHitAllocator.FreeSingle((VetoHit*) hit);
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

#endif

