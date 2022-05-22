#include "physicslist.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
#include "NeutronHPphysics.hh" //take from hadr04 example

physicslist::physicslist(/* args */)
: G4VModularPhysicsList()
{
    // Hadron Inelastic physics; Check elastic process provied by G4NeutronHPBuilder in G4HadronPhysicsQGSP_BIC_HP???
    //RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP());
    //RegisterPhysics( new G4HadronPhysicsQGSP_BIC_AllHP());
    RegisterPhysics(new NeutronHPphysics());
    ////RegisterPhysics( new G4HadronInelasticQBBC());        
    ////RegisterPhysics( new G4HadronPhysicsINCLXX());
    ////RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP());
    // Ion elastic
    RegisterPhysics(new G4IonElasticPhysics());
    //Ion inelastic
    RegisterPhysics(new G4IonPhysicsXS());
    //Stopping particle
    RegisterPhysics(new G4StoppingPhysics());
    // EM physics
    RegisterPhysics(new G4EmStandardPhysics());
    // Radioractive decay
    //RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new RadioactiveDecayPhysics());
}

physicslist::~physicslist()
{
}