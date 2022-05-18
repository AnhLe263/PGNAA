//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#include "source.hh"
#include "geometryconstruction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
source::source(geometryconstruction* det)
: G4VUserPrimaryGeneratorAction(),fParticelGun(nullptr),fGeometry(det)
{
    fParticelGun = new G4ParticleGun(1);
    G4ParticleDefinition* partDef = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
    fParticelGun->SetParticleDefinition(partDef);
    fParticelGun->SetParticleEnergy(2.0*MeV);
    fParticelGun->SetParticleMomentumDirection(G4ThreeVector(1,0,0));
}

source::~source()
{
    delete fParticelGun;
}

void source::GeneratePrimaries(G4Event* evt)
{
    G4double x = 0*cm;
    G4double y =0 *cm;
    G4double z = 0*cm;

    fParticelGun->SetParticlePosition(G4ThreeVector(x,y,z));
    fParticelGun->GeneratePrimaryVertex(evt);
}