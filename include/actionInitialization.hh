//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#pragma once
#include "G4VUserActionInitialization.hh"
class geometryconstruction;

class actionInitialization: public G4VUserActionInitialization
{
    public:
    actionInitialization(geometryconstruction*);
    ~actionInitialization() override;
    void BuildForMaster() const override;
    void Build() const override;
    private:
    geometryconstruction* fGeometry;
};