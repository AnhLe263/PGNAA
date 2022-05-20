//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                            //
//---------------------------------------------------------------------//
#pragma once
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class geometryconstruction: public G4VUserDetectorConstruction
{
    public:
    geometryconstruction();
    ~geometryconstruction() override;
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;
    void ChooseOldGeometry();
    private:
    G4bool fUsingNewGeometry;// Dung cau hinh moi
    G4VPhysicalVolume* ConstructOldGeo();
    G4VPhysicalVolume* ConstructNewGeo();
    void DefineMaterials();
};

