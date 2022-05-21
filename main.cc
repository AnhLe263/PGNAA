//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                            //
//---------------------------------------------------------------------//
#include <iostream>
#include "geometryconstruction.hh"
#include "actionInitialization.hh"
#include "physicslist.hh"

#include "QGSP_BIC.hh"
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
int main(int argc, char** argv)
{   
    G4UIExecutive* ui = nullptr;
    if (argc == 1) ui = new G4UIExecutive(argc,argv);
    
    auto runManager = G4RunManagerFactory::CreateRunManager();
    runManager->SetNumberOfThreads(4);

    //set mandatory initialization classes
    geometryconstruction* geo = new geometryconstruction();
    runManager->SetUserInitialization(geo);
    //runManager->SetUserInitialization(new QGSP_BIC());
    runManager->SetUserInitialization(new physicslist());
    runManager->SetUserInitialization(new actionInitialization(geo));

    //initialize visualization
    G4VisManager* visManager = nullptr;

    //get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (ui)  {
    //interactive mode
    visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
    }
    else  {
    //batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
    }


}