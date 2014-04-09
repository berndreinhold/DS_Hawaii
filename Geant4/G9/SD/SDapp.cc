/* Main program of the SD Geant4.9.6 application. Created March 31, 2014 by E. Edkins. */

#include "SDDetectorConstruction.hh"
#include "SDPrimaryGeneratorAction.hh"
#include "SDEventAction.hh"
#include "SDRunAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "FTFP_BERT.hh"
#include "G4StepLimiterBuilder.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

int main(int argc, char** argv)
{
  //construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  //mandator user initialization class
  //
  //detector construction
  runManager->SetUserInitialization(new SDDetectorConstruction());
  //
  //physics list
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  physicsList->RegisterPhysics(new G4StepLimiterBuilder());
  runManager->SetUserInitialization(physicsList);

  //mandatory user action class
  runManager->SetUserAction(new SDPrimaryGeneratorAction());

  //optional user action classes
  runManager->SetUserAction(new SDEventAction());
  runManager->SetUserAction(new SDRunAction());

 #ifdef G4VIS_USE
  //visualization manager contruction
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
 #endif

  //Get the pointer to the user interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc>1) {
    //execute an argument macro file if one exists
    G4String command = "/control/execute ";
    G4String filename = argv[1];
    UImanager->ApplyCommand(command+filename);
  }
  else {
    //initialize the G4 kernel
    runManager->Initialize();
    //start interactive session
  #ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  #ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac");
  #else
    UImanager->ApplyCommand("/control/execute init.mac");
  #endif
    if (ui->IsGUI())
        UImanager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();
    delete ui;
  #endif
  }

  //job termination. 
  //Free the store: user actions, physics list and detector description are
  //owned and deleted by the run manager, so they should not be deleted
  //in the main() program!

  #ifdef G4VIS_USE
    delete visManager;
  #endif
    delete runManager;

    return 0;
}//end main

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....
