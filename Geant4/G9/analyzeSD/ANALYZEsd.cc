/* Main program of analyzeSD. Created April 3, 2014 by E. Edkins. */

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "FTFP_BERT.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

int main(int argc, char** argv)
{
  //construct the run manager
  G4RunManager* runManager = new G4RunManager;

  //construct the visualization manager
  #ifdef G4VIS_USE
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();
  #endif

  //get pointer to user interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

 //mandatory user initialization classes
 //
 //detector construction
 runManager->SetUserInitialization(new DetectorConstruction());
 //
 //physics list
 G4VModularPhysicsList* physicsList = new FTFP_BERT;
 runManager->SetUserInitialization(physicsList);

 //mandatory user action class
 //
 runManager->SetUserAction(new PrimaryGeneratorAction());
 //
 //optional user action classes
 //
 runManager->SetUserAction(new EventAction());
 runManager->SetUserAction(new RunAction());

 //initialize the G4 kernel
 runManager->Initialize();

 if(argc>1)
 {
   //execute an argument if a macro file exists
   G4String command = "/control/execute ";
   G4String filename = argv[1];
   UImanager->ApplyCommand(command+filename);
 }
 else
 {
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

  //Job termination
  //Free the store: user actions, physics ist and detector description are
  //owned and deleted by the run manager, so they should NOT be deleted 
  //in the main() program!

 #ifdef G4VIS_USE
   delete visManager;
 #endif
   delete runManager;

   return 0;

}//end main

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

