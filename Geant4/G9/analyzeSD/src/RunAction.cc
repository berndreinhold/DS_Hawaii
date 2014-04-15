/* Implementation of the RunAction class. */

#include "RunAction.hh"
#include "Analysis.hh"

#include "G4UserRunAction.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

RunAction::RunAction()
: G4UserRunAction()
{
  //Since run action will not change between runs, can define content 
  //of output file here
  //Histograms:
  //
  //Ntuples:
  //Double column: deposited energy in tpc
  //Double column: deposited energy in veto
  //Double column: x coordinate
  //Double column: y coordinate
  //Double column: z coordinate
  //Integer column: track id
  //Integer column: parent id
  //
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  //default settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("analysisSD_output");

  //create ntuple
  //
  analysisManager->CreateNtuple("analysisSD_output", "Hits");
  analysisManager->CreateNtupleDColumn("veto_posX"); // column ID = 0
  analysisManager->CreateNtupleDColumn("veto_posY"); // column ID = 1
  analysisManager->CreateNtupleDColumn("veto_posZ"); // column ID = 2
  analysisManager->CreateNtupleDColumn("active_posX"); // column ID = 3
  analysisManager->CreateNtupleDColumn("active_posY"); // column ID = 4
  analysisManager->CreateNtupleDColumn("active_posZ"); // column ID = 5
  analysisManager->CreateNtupleDColumn("edep_active"); // column ID = 6
  analysisManager->CreateNtupleDColumn("edep_veto"); // column ID = 7
  analysisManager->CreateNtupleIColumn("veto_track_id"); // column ID = 8
  analysisManager->CreateNtupleIColumn("active_track_id"); // column ID = 9
  analysisManager->CreateNtupleIColumn("veto_parent_id"); // column ID = 10
  analysisManager->CreateNtupleIColumn("active_parent_id"); // column ID = 11
  analysisManager->FinishNtuple();
}


//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  //get analysis manager
  G4AnalysisManager* analysisManger = G4AnalysisManager::Instance();

  //open an output file
  //default name is set in RunAction::RunAction(),
  //can be overwritten in a macro
  analysisManger->OpenFile();
}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  //save ntuple
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

//.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......oooOO0OOooo.......
