//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#pragma once
#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithALongInt;

class source;
class sourceMessenger: public G4UImessenger
{
  public:
    sourceMessenger(source* );
    ~sourceMessenger() override;

    void SetNewValue(G4UIcommand*, G4String) override;

  private:
    source*  fsource = nullptr;

    G4UIdirectory*         fsourceDirectory = nullptr;

    G4UIcmdWithALongInt*    fSourceTypeCmd = nullptr;
};