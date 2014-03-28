/* Implementation of the testActionInitialization class. */

#include "testActionInitialization.hh"
#include "testPrimaryGeneratorAction.hh"
//#include "testRunAction.hh"
//#include "testEventAction.hh"
//#include "testSteppingAction.hh"

//.....oooOO0OOooo......oooOO0Oooo......oooOO0Oooo......oooOO0Oooo......

testActionInitialization::testActionInitialization()
 : G4VUserActionInitialization()
{}

//.....oooOO0OOooo......oooOO0Oooo......oooOO0Oooo......oooOO0Oooo......

testActionInitialization::~testActionInitialization()
{}

//.....oooOO0OOooo......oooOO0Oooo......oooOO0Oooo......oooOO0Oooo......

void testActionInitialization::Build() const
{
  SetUserAction(new testPrimaryGeneratorAction);
  /*SetUserAction(new testRunAction);

  testEventAction* eventAction = new testEventAction;
  SetUserAction(eventAction);

  SetUserAction(new testSteppingAction(eventAction));*/
}

//.....oooOO0OOooo......oooOO0Oooo......oooOO0Oooo......oooOO0Oooo......
