//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#pragma once
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
class geometryconstruction;
class G4Event;
class sourceMessenger;
class source : public G4VUserPrimaryGeneratorAction
{
    public:
    source(geometryconstruction*);
    ~source();
    void GeneratePrimaries(G4Event*) override;
    void ChoosingTypeOfSource(G4int i=0);
    private:
    G4ParticleGun* fParticleGun;
    geometryconstruction* fGeometry;
    G4bool fUsingDirectNeutronBeam;
    sourceMessenger* fsourceMessenger;
};

inline void source::ChoosingTypeOfSource(G4int i)
{
    if (i == 0) {
        fUsingDirectNeutronBeam = false;// Dung decay source Cf-252
        G4cout
          << G4endl
          << "----> The neutron source: spontaneous fission Cf-252 "<< G4endl;
    }
    else {
        fUsingDirectNeutronBeam = true;// Dung nguon histogram neutron, ko co decay
        G4cout
          << G4endl
          << "----> The newtron source: Using direct neutron spectra "<< G4endl;
    }
}