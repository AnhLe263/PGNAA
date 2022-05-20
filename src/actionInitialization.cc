//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#include "actionInitialization.hh"
#include "geometryconstruction.hh"
#include "source.hh"
#include "RunAction.hh"
actionInitialization::actionInitialization(geometryconstruction* geo)
: G4VUserActionInitialization(), fGeometry(geo)
{

}

actionInitialization::~actionInitialization()
{

}

void actionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}

void actionInitialization::Build() const
{
    source* fSource = new source(fGeometry);
    SetUserAction(fSource);
    SetUserAction(new RunAction());
}