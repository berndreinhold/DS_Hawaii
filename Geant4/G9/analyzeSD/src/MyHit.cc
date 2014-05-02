// Implementation of the MyHit class. */

#include "MyHit.hh"

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

G4Allocator<MyHit>* MyHitAllocator;

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

MyHit::MyHit()
 : G4VHit()
{
  tallied = false;
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

MyHit::~MyHit()
{}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

MyHit::MyHit(const MyHit &right)
: G4VHit()
{
  edep		= right.edep;
  particle	= right.particle;
  id		= right.id;
  parentid	= right.parentid;
  process	= right.process;
  pos		= right.pos;
  time		= right.time;
  kinEnergy	= right.kinEnergy;
  volume	= right.volume;
  volName	= right.volName;
  tallied	= right.tallied; 	
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

const MyHit& MyHit::operator=(const MyHit& right)
{
  edep		= right.edep;
  particle	= right.particle;
  id		= right.id;
  parentid	= right.parentid;
  process	= right.process;
  pos		= right.pos;
  time		= right.time;
  kinEnergy	= right.kinEnergy;
  volume	= right.volume;
  volName	= right.volName;
  tallied	= right.tallied;
  return *this; 
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

int MyHit::operator==(const MyHit& right) const
{
  return 0;
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

void MyHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(0.20);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour Red(1.,0.,0.);
    G4VisAttributes attribs(Red);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle); 
  }
} 

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

void MyHit::Print()
{
  G4cout 
  << " energy deposit: " << G4BestUnit(edep,"Energy")
  << " position: " << G4BestUnit(pos,"Length") << G4endl;

}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......
