/* Implementation of the testDetectorConstruction class. */

#include "testDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"

//.....oooOO0OO000.....oooOO0OO000.....oooOO0OO000.....oooOO0OO000.....

testDetectorConstruction::testDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{}

//.....oooOO0OO000.....oooOO0OO000.....oooOO0OO000.....oooOO0OO000.....

testDetectorConstruction::~testDetectorConstruction()
{}

//.....oooOO0OO000.....oooOO0OO000.....oooOO0OO000.....oooOO0OO000.....

G4VPhysicalVolume* testDetectorConstruction::Construct()
{
  //get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  //option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  // World = box of air
  G4double world_hx = 5.0*m;
  G4double world_hy = 5.0*m;
  G4double world_hz = 5.0*m;
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* worldSolid = new G4Box("World", world_hx, world_hy, world_hz);

  G4LogicalVolume* worldLogic = new G4LogicalVolume(worldSolid, air, "World");

  G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(0,0,0), worldLogic, "World", 0, false, 0, checkOverlaps);

  //Tank = cylinder of water
  G4double innerRadius = 0.*cm;
  G4double outerRadius = 50.*cm;
  G4double hz = 50.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;
  G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

  G4Tubs* tankSolid = new G4Tubs("Tank", innerRadius, outerRadius, hz, startAngle, spanningAngle);

  G4LogicalVolume* tankLogic = new G4LogicalVolume(tankSolid, water, "Tank");

  new G4PVPlacement(0, G4ThreeVector(0,0,0), tankLogic, "Tank", worldLogic, false, 0, checkOverlaps);

  //print the list of materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //set the Tank as a scoring volume
  fScoringVolume = tankLogic;

  //always return the physical world
  return worldPhys;

}

