
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
#include "G4UnionSolid.hh"
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
    G4double outterRadiusDetHole = 7.6*cm/2; 
    G4double heighSample = 25.0*cm;
    G4double outterRadiusSample = 33.*cm/2.;
    G4double innerRadiusSample = outterRadiusDetHole;
    G4double outterRadiusParafin = outterRadiusSample+ 15.*cm;
    G4double innerRadiusParafin1 = outterRadiusDetHole;
    G4double heighParafin1 = 10*cm + 25*cm;
    
    G4double sourceCfThickness = 3.*cm;
    G4double sourceRadius = 2*cm;// Can hoi lai Chu Tuy
    G4double graphiteThickness = 12.*cm;
    G4double heighParafin2 = 7*cm + graphiteThickness + sourceCfThickness +6*cm;
    //Hinh tru Pb:
    G4double outterRadiusPb = outterRadiusParafin+3*cm;;
    G4double outterHeightPb = 67*cm;
    // The World
    //G4double outterRadiusWorld = outterRadiusPb*1.2;
    G4double outterHeightWorld = outterHeightPb*1.2;
    G4Box *worldSolid = new G4Box("World",outterHeightWorld*0.5,outterHeightWorld*0.5,outterHeightWorld*0.5);
    G4LogicalVolume *worldLogic = new G4LogicalVolume(worldSolid,matAir,"World");
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0,G4ThreeVector(),"World",worldLogic,0,false,0,true);

    //outter Pb layer
    G4double tubPhi = 180*deg;
    G4Tubs *leadSolid = new G4Tubs("Lead",0,outterRadiusPb,outterHeightPb*0.5,0*deg,tubPhi);
    G4LogicalVolume* leadLogic = new G4LogicalVolume(leadSolid,matLead,"Lead");
    G4RotationMatrix* rotLead = new G4RotationMatrix();
    rotLead->rotateX(90*deg);
    G4double posX = 0.*cm, posY = 0.*cm, posZ = 0*cm;
    G4VPhysicalVolume* leadPhys =  new G4PVPlacement(rotLead,G4ThreeVector(posX,posY,posZ),"Lead",leadLogic,worldPhys,false,0,true);
    /*---------------------------parafin------------------------------------------------------------------------------*/
    // Chia phần parafin thành 2 phần nhỏ để implement cho dễ: Phần 1 chưa det và mẫu; Phần 2 chứa nguồn, graphite
    //Phần parafin thứ nhất:
    
    G4Tubs* parafin1Solid = new G4Tubs("Parafin1",innerRadiusParafin1,outterRadiusParafin,heighParafin1*0.5,0*deg,tubPhi);
    G4Tubs* parafin2Solid = new G4Tubs("Parafin2",0,outterRadiusParafin,heighParafin2*0.5,0*deg,tubPhi);
    G4double zTran = heighParafin1/2.0 + heighParafin2/2.;
    G4ThreeVector zTranV(0,0,-zTran);
    G4UnionSolid* parafinSolid = new G4UnionSolid("Parafin",parafin1Solid,parafin2Solid,0,zTranV);
    G4LogicalVolume* parafinLogic = new G4LogicalVolume(parafinSolid,matParafin,"Parafin");
    posX = 0*cm;
    posY = 0.*cm;
    posZ = outterHeightPb/2. - 2.*cm - heighParafin1/2.0;
    G4VPhysicalVolume* parafinPhys =  new G4PVPlacement(
        0,
        G4ThreeVector(posX,posY,posZ),
        "Parafin",
        parafinLogic,
        leadPhys,//mother
        false,
        0,
        true
    );
    // Sample
    G4Material *matSample = nist->FindOrBuildMaterial("CoalM4");
    
    G4Tubs *sampleSolid = new G4Tubs("Sample",innerRadiusSample,outterRadiusSample,heighSample*0.5,0*deg,tubPhi);
    G4LogicalVolume *sampleLogic = new G4LogicalVolume(sampleSolid,matSample,"Sample");
    posX = 0*cm;
    posY = 0.*cm;
    posZ = heighParafin1/2. - 10.*cm - heighSample/2.0;
    new G4PVPlacement(
        0,
        G4ThreeVector(posX,posY,posZ),
        "Sample",
        sampleLogic,
        parafinPhys,//Mother
        false,
        0,
        true
    );

    /*---------------------------0000------------------------------------------------------------------------------*/
    // The vung khong gian nguon
    G4Tubs *sourceRegionSolid = new G4Tubs("SourceRegion",0,outterRadiusSample,sourceCfThickness*0.5,0,tubPhi);
    G4LogicalVolume *sourceRegionLogic = new G4LogicalVolume(sourceRegionSolid,matAir,"SourceRegion");
    posX = 0*cm;
    posY = 0.*cm;
    posZ = heighParafin1/2. - 10.*cm - heighSample - 6.0*cm - sourceCfThickness/2.;
    G4VPhysicalVolume* sourceRegionPhys = new G4PVPlacement(
        0,
        G4ThreeVector(posX,posY,posZ),
        "SourceRegion",
        sourceRegionLogic,
        parafinPhys,//Mother
        false,
        0,
        true
    );
    // The tinh nguon
    G4Material* matCf = nist->FindOrBuildMaterial("G4_Cf");
    G4Tubs *sourceSolid = new G4Tubs("Source",0,sourceRadius,sourceCfThickness*0.5,0,tubPhi);
    G4LogicalVolume *sourceLogic = new G4LogicalVolume(sourceSolid,matCf,"Source");
    posX = 0*cm;
    posY = 0.*cm;
    posZ = 0;
    new G4PVPlacement(
        0,
        G4ThreeVector(posX,posY,posZ),
        "Source",
        sourceLogic,
        sourceRegionPhys,//Mother
        false,
        0,
        true
    );
    /*---------------------------0000------------------------------------------------------------------------------*/
    //Graphite
    G4Tubs *graphiteSolid = new G4Tubs("Graphite",0,outterRadiusSample,graphiteThickness*0.5,0,tubPhi);
    G4LogicalVolume *graphiteLogic = new G4LogicalVolume(graphiteSolid,matGraphite,"Graphite");
    posX = 0*cm;
    posY = 0.*cm;
    posZ = heighParafin1/2. - 10.*cm - heighSample - 6.0*cm - sourceCfThickness - graphiteThickness/2.;
    new G4PVPlacement(
        0,
        G4ThreeVector(posX,posY,posZ),
        "Graphite",
        graphiteLogic,
        parafinPhys,//Mother
        false,
        0,
        true
    );
    /*---------------------------0000------------------------------------------------------------------------------*/
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
    G4Element* Fe = new G4Element("Iron"  ,"Fe", z=26., a= 55.845*g/mole);
    G4Element* Ti = new G4Element("Titanium"  ,"Ti", z=22., a= 47.867*g/mole);
    G4Element* K = new G4Element("Potassium"  ,"K", z=19., a= 39.0983*g/mole);
    G4Element* Na = new G4Element("Sodium"  ,"Na", z=11., a= 22.989769*g/mole);
    G4Element* Ca = new G4Element("Calcium"  ,"Ca", z=20., a= 40.078*g/mole);
    G4Element* Mg = new G4Element("Magnesium"  ,"Mg", z=12., a= 24.304*g/mole);
    G4Element* P = new G4Element("Phosphorus"  ,"P", z=15., a= 30.973*g/mole);
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
    //---------Mau chuan M4 ---------------------------------------------------
    
    auto nist = G4NistManager::Instance();
    G4Material* matC = nist->FindOrBuildMaterial("G4_C");
    G4Material* matSiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    G4Material* matAl2O3 = nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
    G4Material* matFe2O3 = new G4Material("Fe2O3", density= 5.24*g/cm3, ncomponents=2);
    matFe2O3->AddElement(O , natoms=3);
    matFe2O3->AddElement(Fe, natoms= 2);
    G4Material* matTiO2 = new G4Material("TiO2", density= 4.23*g/cm3, ncomponents=2);
    matTiO2->AddElement(O , natoms=2);
    matTiO2->AddElement(Ti, natoms= 1);
    G4Material* matK2O = new G4Material("K2O", density= 2.32*g/cm3, ncomponents=2);
    matK2O->AddElement(O , natoms=1);
    matK2O->AddElement(K, natoms= 2);
    G4Material* matNa2O = new G4Material("Na2O", density= 2.27*g/cm3, ncomponents=2);
    matNa2O->AddElement(O , natoms=1);
    matNa2O->AddElement(Na, natoms= 2);   
    G4Material* matCaO = new G4Material("CaO", density= 3.34*g/cm3, ncomponents=2);
    matCaO->AddElement(O , natoms=1);
    matCaO->AddElement(Ca, natoms= 1);
    G4Material* matMgO = new G4Material("MgO", density= 3.6*g/cm3, ncomponents=2);
    matMgO->AddElement(O , natoms=1);
    matMgO->AddElement(Mg, natoms= 1); 
    G4Material* matP2O5 = new G4Material("P2O5", density= 2.39*g/cm3, ncomponents=2);
    matP2O5->AddElement(O , natoms=5);
    matP2O5->AddElement(P, natoms= 2);  
    
    G4Material* matCoalM4 = new G4Material("CoalM4",density = 1.2*g/cm3,ncomponents=10);
    matCoalM4->AddMaterial(matC,    fractionmass=76.89*perCent);
    matCoalM4->AddMaterial(matSiO2, fractionmass=12.9*perCent);
    matCoalM4->AddMaterial(matAl2O3,fractionmass=5.58*perCent);
    matCoalM4->AddMaterial(matFe2O3,fractionmass=2.62*perCent);
    matCoalM4->AddMaterial(matTiO2, fractionmass=0.13*perCent);
    matCoalM4->AddMaterial(matK2O,  fractionmass=1.03*perCent);
    matCoalM4->AddMaterial(matNa2O, fractionmass=0.16*perCent);
    matCoalM4->AddMaterial(matCaO,  fractionmass=0.22*perCent);
    matCoalM4->AddMaterial(matMgO,  fractionmass=0.4*perCent);
    matCoalM4->AddMaterial(matP2O5, fractionmass=0.07*perCent);
    

}