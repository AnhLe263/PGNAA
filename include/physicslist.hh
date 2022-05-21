//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#pragma once
#include "G4VModularPhysicsList.hh"

class physicslist: public G4VModularPhysicsList
{
private:
    /* data */
public:
    physicslist(/* args */);
    ~physicslist();
    
};



physicslist::~physicslist()
{
}
