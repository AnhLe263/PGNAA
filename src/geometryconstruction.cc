
//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#include "geometryconstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
geometryconstruction::geometryconstruction()
: G4VUserDetectorConstruction(), fUsingNewGeometry(false)
{
    DefineMaterials();
}

geometryconstruction::~geometryconstruction()
{
    
}

G4VPhysicalVolume* geometryconstruction::Construct()
{
    // Cleanup old geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
    return (fUsingNewGeometry) ? ConstructNewGeo() : ConstructOldGeo();
}

G4VPhysicalVolume* geometryconstruction::ConstructOldGeo()
{
    auto nist = G4NistManager::Instance();
    G4Material *matParafin = nist->FindOrBuildMaterial("G4_PARAFFIN");
    G4Material *matLead = nist->FindOrBuildMaterial("G4_Pb");
    G4Material *matGraphite = nist->FindOrBuildMaterial("G4_GRAPHITE");
    G4Material *matPOLYETHYLENE = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Material *matAir = nist->FindOrBuildMaterial("Air");
    G4Material *matBGO = nist->FindOrBuildMaterial("BGO");

    //Some size
    //Hinh tru Pb:
    G4double outterRadiusPb = 72.0*cm / 2.;
    G4double outterHeightPb = 67*cm + 2*cm + 2.*cm;
    // The World
    //G4double outterRadiusWorld = outterRadiusPb*1.2;
    G4double outterHeightWorld = outterHeightPb*1.2;
    G4Box *worldSolid = new G4Box("World",outterHeightWorld*0.5,outterHeightWorld*0.5,outterHeightWorld*0.5);
    G4LogicalVolume *worldLogic = new G4LogicalVolume(worldSolid,matAir,"World");
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0,G4ThreeVector(),"World",worldLogic,0,false,0,true);

    return worldPhys;
}

G4VPhysicalVolume* geometryconstruction::ConstructNewGeo()
{

}

void geometryconstruction::ChooseOldGeometry()
{
    fUsingNewGeometry = false;
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void geometryconstruction::DefineMaterials()
{
    // define Elements
    //
    G4double z,a;
    
    //G4Element* H  = new G4Element("Hydrogen" ,"H" , z= 1., a=   1.01*g/mole);
    G4Element* N  = new G4Element("Nitrogen" ,"N" , z= 7., a=  14.01*g/mole);
    G4Element* O  = new G4Element("Oxygen"   ,"O" , z= 8., a=  16.00*g/mole);
    G4Element* Ge = new G4Element("Germanium","Ge", z=32., a=  72.59*g/mole);
    G4Element* Bi = new G4Element("Bismuth"  ,"Bi", z=83., a= 208.98*g/mole);
    // define materials
    //
    G4double density;
    G4int ncomponents, natoms;
    G4double fractionmass; 
    G4Material* Air = 
    new G4Material("Air", density= 1.290*mg/cm3, ncomponents=2);
    Air->AddElement(N, fractionmass=70.*perCent);
    Air->AddElement(O, fractionmass=30.*perCent);
    G4Material* BGO = 
    new G4Material("BGO", density= 7.10*g/cm3, ncomponents=3);
    BGO->AddElement(O , natoms=12);
    BGO->AddElement(Ge, natoms= 3);
    BGO->AddElement(Bi, natoms= 4);

    //new G4Material("Lead", z=82., a=207.19*g/mole, density= 11.35*g/cm3);
}