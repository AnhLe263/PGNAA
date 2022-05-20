//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#pragma once
#include "G4UserRunAction.hh"
class G4Run;
class RunAction: public G4UserRunAction
{
    public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
};