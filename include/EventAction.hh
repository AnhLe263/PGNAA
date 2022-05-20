//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#pragma once
#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction: public G4UserEventAction
{
    public:
    EventAction();
    ~EventAction() override;
    void BeginOfEventAction(const G4Event *event) override;
    void EndOfEventAction(const G4Event *event) override;
    private:
    G4int fCollectonID;
};