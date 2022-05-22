//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                            //
//---------------------------------------------------------------------//
#pragma once
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class geometryMessenger;
class geometryconstruction: public G4VUserDetectorConstruction
{
    public:
    geometryconstruction();
    ~geometryconstruction() override;
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;
    void ChooseOldGeometry();
    G4ThreeVector GetSourceCenterPosition() {return fSourceCenterPosition;}
    void SetSampleMaterial(G4String);
    private:
    G4bool fUsingNewGeometry;// Dung cau hinh moi
    G4VPhysicalVolume* ConstructOldGeo();
    G4VPhysicalVolume* ConstructNewGeo();
    void DefineMaterials();
    G4ThreeVector fSourceCenterPosition;
    G4Material* fSampleMaterial;
    G4LogicalVolume* fLogicSample;
    geometryMessenger* fgeometryMessenger;
};

