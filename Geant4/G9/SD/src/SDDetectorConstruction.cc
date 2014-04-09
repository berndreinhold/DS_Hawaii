/* Implementation of the SDDetectorConstruction class. */

#include "SDDetectorConstruction.hh"
#include "VetoSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SDManager.hh"

#include "G4SystemOfUnits.hh"

#include "G4ios.hh"

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

SDDetectorConstruction::SDDetectorConstruction()
: G4VUserDetectorConstruction(), 
  fCheckOverlaps(true)
{
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

SDDetectorConstruction::~SDDetectorConstruction()
{
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

G4VPhysicalVolume* SDDetectorConstruction::Construct()
{
  //construct materials
  DefineMaterials();

  //construct volumes
  return DefineVolumes();
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void SDDetectorConstruction::DefineMaterials()
{
  //material definition
  G4NistManager* nistManager = G4NistManager::Instance();

  //water
  nistManager->FindOrBuildMaterial("G4_WATER");

  //Scintillator = psuedocumene = 1,2,4-Trimethylborate
  G4Element* H = new G4Element("Hydrogen", "H", 1, 1.00794*g/mole);
  G4Element* C = new G4Element("Carbon", "C", 6, 12.0107*g/mole);
  G4Material* Scintillator = new G4Material("Scintillator", 0.8761*g/cm3, 2);
  Scintillator->AddElement(C, 9);
  Scintillator->AddElement(H, 12);

  G4cout << "The materials defined are: " << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

G4VPhysicalVolume* SDDetectorConstruction::DefineVolumes()
{
  //add materials
  G4Material* water = G4Material::GetMaterial("G4_WATER");
  G4Material* scintillator = G4Material::GetMaterial("Scintillator");

  //geometries
  //------------------------
  //world
  G4double innerRadius = 0.*cm;
  G4double worldOuterRadius = 5.*m;
  G4double worldHalfZ = 5.5*m;
  G4VSolid* worldSolid = new G4Tubs("worldSolid", innerRadius, worldOuterRadius, worldHalfZ, 0.*deg, 360.*deg);
  //
  G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid, water, "worldLogical");
  //
  G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), worldLogical, "worldPhysical", 0, false, 0, fCheckOverlaps);
  //
  //-------------------------
  //
  //veto
  G4double vetoRadius = 2.*m;
  G4double vetoHalfZ = 2.*m;
  G4VSolid* vetoSolid = new G4Orb("vetoSolid", vetoRadius);
  //
  G4LogicalVolume* vetoLogical = new G4LogicalVolume(vetoSolid, scintillator, "vetoLogical");
  //
  new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), vetoLogical, "vetoPhysical", worldLogical, false, 0, fCheckOverlaps);

  //Visualization attributes
  G4VisAttributes* visAttributesVeto = new G4VisAttributes(G4Colour(0.888,0.888,0.0));
  vetoLogical->SetVisAttributes(visAttributesVeto);

  G4VisAttributes* visAttributesWorld = new G4VisAttributes(G4Colour(0.0, 0.888, 0.0));
  visAttributesWorld->SetVisibility(false);
  worldLogical->SetVisAttributes(visAttributesWorld);

  //Sensitive volumes
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4VSensitiveDetector* vetoDet = new VetoSD("vetoDet");
  SDman->AddNewDetector(vetoDet);
  vetoLogical->SetSensitiveDetector(vetoDet);

  //always return the world physical volume
  return worldPhysical;
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

void SDDetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
{
  fCheckOverlaps = checkOverlaps;
}

//.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....oooOO0OOooo.....

