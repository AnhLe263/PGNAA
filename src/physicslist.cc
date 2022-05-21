#include "physicslist.hh"
#include "G4RadioactiveDecayPhysics.hh"
physicslist::physicslist(/* args */)
: G4VModularPhysicsList()
{

    // Radioractive decay
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}