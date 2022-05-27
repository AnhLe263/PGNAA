//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#include "source.hh"
#include "sourceMessenger.hh"
#include "geometryconstruction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"
#include "CLHEP/Random/RandGeneral.h"
#include "G4AnalysisManager.hh"

source::source(geometryconstruction* det)
: G4VUserPrimaryGeneratorAction(),fParticleGun(nullptr),fGeometry(det), fUsingDirectNeutronBeam(true)
{
    fsourceMessenger = new sourceMessenger(this);
    fParticleGun = new G4ParticleGun(1);
    G4ParticleDefinition* partDef = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
    fParticleGun->SetParticleDefinition(partDef);
    fParticleGun->SetParticleEnergy(2.0*MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,1,0));


}

source::~source()
{
    delete fParticleGun;
}

void source::GeneratePrimaries(G4Event* evt)
{
    if (!fUsingDirectNeutronBeam) {  
        G4int Z = 98, A = 252;
        G4double ionCharge   = 0.*eplus;
        G4double excitEnergy = 0.*keV;
        G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(ionCharge);
    }  else {
        fParticleGun->SetParticleEnergy(5*MeV);//Tam thoi dat vay, sau nay implment watt distribution
    }
    //auto phyVol = G4PhysicalVolumeStore::GetInstance()->GetVolume("Source");
    auto pos = fGeometry->GetSourceCenterPosition();
    //G4cout<<pos.x()<<"\t"<<pos.y()<<"\t"<<pos.z()<<G4endl;
    G4double x = 0*cm;
    G4double y =0 *cm;
    G4double z = 0*cm;

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->GeneratePrimaryVertex(evt);
}

