//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#pragma once
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
class geometryconstruction;
class G4Event;

class source : public G4VUserPrimaryGeneratorAction
{
    public:
    source(geometryconstruction*);
    ~source();
    void GeneratePrimaries(G4Event*) override;
    private:
    G4ParticleGun* fParticleGun;
    geometryconstruction* fGeometry;
};