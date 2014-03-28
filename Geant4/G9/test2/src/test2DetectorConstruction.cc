/* Implementation of the test2DetectorConstruction clas. */

#include "test2DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

test2DetectorConstruction::test2DetectorConstruction()
: G4VUserDetectorConstruction()
  //fScoringVolume(0)
{ }

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

test2DetectorConstruction::~test2DetectorConstruction()
{ }

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

G4VPhysicalVolume* test2DetectorConstruction::Construct()
{ 
  //construct materials
  ConstructMaterials();
  G4Material* air = G4Material::GetMaterial("G4_AIR");
  G4Material* water = G4Material::GetMaterial("G4_WATER");
  G4Material* scintillator = G4Material::GetMaterial("Scintillator");

  G4bool checkOverlaps = true;

  //geometries
  //------------------------------------------
  //World
  G4double innerRadius = 0.*cm;
  G4double worldOuterRadius = 500.*cm;
  G4double worldHalfZ = 550.*cm;
  G4VSolid* worldSolid = new G4Tubs("World", innerRadius, worldOuterRadius, worldHalfZ, 0.*deg, 360.*deg);
  //
  G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid, water, "World");
  //
  G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0, G4ThreeVector(0,0,0), worldLogical, "World", 0, false, 0, checkOverlaps); 
  //--------------------------------------------
  //Tank
  G4double tankOuterRadius = 200.*cm;
  G4double tankHalfZ = 200.*cm;
  G4VSolid* tankSolid = new G4Tubs("Tank", innerRadius, tankOuterRadius, tankHalfZ, 0.*deg, 360.*deg);
  //
  G4LogicalVolume* tankLogical = new G4LogicalVolume(tankSolid, scintillator, "Tank");
  //
  G4VPhysicalVolume* tankPhysical = new G4PVPlacement(0, G4ThreeVector(0,0,0), tankLogical, "Tank", worldLogical, false, 0, checkOverlaps); 
  //-------------------------------------------

  //set the tank as the scoring volume
  //fScoringVolume = tankLogical;

  return worldPhysical;

}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void test2DetectorConstruction::ConstructMaterials()
{
  //get nist material manager
  G4NistManager* nistManager = G4NistManager::Instance();

  //Air
  nistManager->FindOrBuildMaterial("G4_AIR");
  

  //Water
  nistManager->FindOrBuildMaterial("G4_WATER");

  //Scintillator = psuedocumene = 1,2,4-Trimethylborate
  G4Element* H = new G4Element("Hydrogen", "H", 1, 1.00794*g/mole);
  G4Element* C = new G4Element("Carbon", "C", 6, 12.0107*g/mole);
  G4Material* Scintillator = new G4Material("Scintillator", 0.8761*g/cm3, 2);
  Scintillator->AddElement(C, 9);
  Scintillator->AddElement(H, 12);

  G4cout << G4endl << "The materials defined are: " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}



//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....
