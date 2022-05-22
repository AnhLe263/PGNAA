//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#include "sourceMessenger.hh"
#include "source.hh"
#include "G4UIcmdWithALongInt.hh"
#include "G4UIdirectory.hh"

sourceMessenger::sourceMessenger(source* s)
: fsource(s)
{
    fsourceDirectory = new G4UIdirectory("/PGNAA/source/");
    
    fSourceTypeCmd = new G4UIcmdWithALongInt("/PGNAA/source/sourceType",this);
    fSourceTypeCmd->SetParameterName("SourceType",true);
    fSourceTypeCmd->SetDefaultValue(0);
    fSourceTypeCmd->AvailableForStates(G4State_Idle,G4State_PreInit);
}

sourceMessenger::~sourceMessenger()
{
    delete fSourceTypeCmd;
    delete fsourceDirectory;
}

void sourceMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if (command == fSourceTypeCmd) {
        fsource->ChoosingTypeOfSource(fSourceTypeCmd->GetNewLongIntValue(newValue));
    }
}