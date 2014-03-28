/* Second attempt at writing a Geant4 application, this time specifically for version 9.6.3. Created March 26, 2014.*/

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "test2DetectorConstruction.hh"
#include "test2PrimaryGeneratorAction.hh"

#include "FTFP_BERT.hh"
//#include "G4StepLimiterPhysics.hh"

#include "G4ScoringManager.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

int main(int argc, char** argv)
{
  //construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  //activate the UI-command base scorer
  G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
  scoringManager->SetVerboseLevel(1);

  //set the mandatory initialization classes
  //
  //physics list
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  runManager->SetUserInitialization(physicsList);
  //
  //detector construction
  runManager->SetUserInitialization(new test2DetectorConstruction());

  //primary generator action - mandatory user action class
  runManager->SetUserAction(new test2PrimaryGeneratorAction());

   //initialize the Geant4 kernel
   runManager->Initialize();

 #ifdef G4VIS_USE
   //visualization manager construction
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();
 #endif

   //get the pointer to the user interface manager
   G4UImanager* UImanager = G4UImanager::GetUIpointer();

   if (argc > 1) {
      //execute an argument macro file if it exists
      G4String command = "/control/execute ";
      G4String filename = argv[1];
      UImanager->ApplyCommand(command+filename);
   }
   else {
      //start interactive session
 #ifdef G4UI_UDE
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);
 #ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute init_vis.mac");
 #else
      UImanager->ApplyCommand("/control/execute init.mac");
 #endif
      /*if (ui->IsGUI())
 	UImanager->ApplyCommand("/control/execute gui.mac");
      ui->SessionStart();
      delete ui;*/
 #endif
    }

    //Job termination. 
    //free the store: user actions, physics_list and detector_description are 
    //owned and deleted by the run manager, so they should not be deleted
    //in the main() program!

#ifdef G4VIS_USE
    delete visManager;
#endif
    delete runManager;

    return 0;

}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....
