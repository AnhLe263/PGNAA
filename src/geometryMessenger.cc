//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#include "geometryMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "geometryconstruction.hh"


geometryMessenger::geometryMessenger(geometryconstruction* geo)
: fgeometryconstruction(geo)
{
    fDirectory = new G4UIdirectory("/PGNAA/");
    fDirectory->SetGuidance("UI commands specific to this project.");

    fDetDirectory = new G4UIdirectory("/PGNAA/geo/");
    fDetDirectory->SetGuidance("geometry construction control");

    fSampleMaterialCmd = new G4UIcmdWithAString("/PGNAA/geo/setSampleMaterial",this);
    fSampleMaterialCmd->SetGuidance("Select Material of the Target.");
    fSampleMaterialCmd->SetParameterName("choice",false);
    fSampleMaterialCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

geometryMessenger::~geometryMessenger()
{
    delete fSampleMaterialCmd;
    delete fDirectory;
    delete fDetDirectory;
}

void geometryMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if (command == fSampleMaterialCmd) {
        fgeometryconstruction->SetSampleMaterial(newValue);
    }
}