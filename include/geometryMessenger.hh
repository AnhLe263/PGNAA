//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#pragma once
#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class geometryconstruction;
class geometryMessenger: public G4UImessenger
{
  public:
    geometryMessenger(geometryconstruction* );
    ~geometryMessenger() override;

    void SetNewValue(G4UIcommand*, G4String) override;

  private:
    geometryconstruction*  fgeometryconstruction = nullptr;

    G4UIdirectory*         fDirectory = nullptr;
    G4UIdirectory*         fDetDirectory = nullptr;

    G4UIcmdWithAString*    fSampleMaterialCmd = nullptr;
};