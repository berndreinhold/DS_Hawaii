/* First attempt at writing a Geant4 application. Created March 25, 2014. */

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "testDetectorConstruction.hh"
//#include "testPhysicsList.hh"
#include "FTFP_BERT.hh"
#include "testActionInitialization.hh"

#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc,char** argv)
{
  //choose the random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  //construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  //Set mandatory initialization classes
  //
  //Detector construction
  runManager->SetUserInitialization(new testDetectorConstruction());

  //Physics list
  //runManager->SetUserInitialization(new testPhysicsList());
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  runManager->SetUserInitialization(physicsList);

  //User action initialization
  runManager->SetUserInitialization(new testActionInitialization());

  //Initialize the G4 kernel
  runManager->Initialize();

  #ifdef G4VIS_USE
  //initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  #endif

  //get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");

  if (argc!=1) {
  //batch mode
  G4String command = "/control/execute ";
  G4String filename = argv[1];
  UI->ApplyCommand(command+filename);
  }
  else {
  //interactive mode : define UI session
  #ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  #ifdef G4VIS_USE
    UI->ApplyCommand("/control/execute init_vis.mac");
  #else
    UI->ApplyCommand("/control/execute init.mac");
  #endif
    ui->SessionStart();
    delete ui;
  #endif
  }

  //Job termination
  // Free the store: user actions, physics_list and detector_description are 
  // owned and deleted by the run manager, so they should NOT be deleted 
  // in the main() program!

  #ifdef G4VIS_USE
     delete visManager;
  #endif
     delete runManager;

     return 0;
}
