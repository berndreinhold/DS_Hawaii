/* Implementation of the VetoHit class. */

#include "VetoHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4UnitsTable.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include <iomanip>

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

G4Allocator<VetoHit> VetoHitAllocator;

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

VetoHit::VetoHit()
: G4VHit(),
  fTrackID(-1),
  fEdep(0.),
  fPos(G4ThreeVector(0)),
  fLogicV(0),
  fVolName(0),
  fTime(0.)
{}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

VetoHit::~VetoHit()
{}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

VetoHit::VetoHit(const VetoHit& right)
: G4VHit()
{
  fTrackID = right.fTrackID;
  fEdep    = right.fEdep;
  fPos     = right.fPos;
  fLogicV  = right.fLogicV;
  fVolName = right.fVolName;
  fTime    = right.fTime;
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

const VetoHit& VetoHit::operator=(const VetoHit& right)
{
  fTrackID = right.fTrackID;
  fEdep    = right.fEdep;
  fPos     = right.fPos;
  fLogicV  = right.fLogicV;
  fVolName = right.fVolName;
  fTime    = right.fTime;

  return *this;
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

G4int VetoHit::operator==(const VetoHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void VetoHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager&&(fEdep>0.))
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(4);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void VetoHit::Print()
{
  G4cout
	<< " trackID: " << fTrackID 
        << " LogicalVolume: " << fLogicV
  	<< " Volume Name: " << fVolName 
        << " Edep: " << std::setw(7) << G4BestUnit(fEdep,"Energy") 
        << " Position: " << std::setw(7) << G4BestUnit(fPos,"Length")
        << " Time: " << fTime << " sec" << G4endl; 
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

