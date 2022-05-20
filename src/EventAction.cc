//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#include "EventAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"
EventAction::EventAction()
: G4UserEventAction(), fCollectonID(-1)
{

}

EventAction::~EventAction()
{

}

void EventAction::BeginOfEventAction(const G4Event*)
{

}

void EventAction::EndOfEventAction(const G4Event *event)
{
    G4HCofThisEvent* HCE = event->GetHCofThisEvent();
    if (!HCE) return;
    if (fCollectonID < 0) {
        G4SDManager *SDman = G4SDManager::GetSDMpointer();
        fCollectonID = SDman->GetCollectionID("BGOdet/edep");
    }

    auto anaMan = G4AnalysisManager::Instance();
    G4THitsMap<G4double> *evtMap = (G4THitsMap<G4double> *)(HCE->GetHC(fCollectonID));
    
    auto tmp_map = *(evtMap->GetMap());
    for (const auto [key, value] : tmp_map) {
        auto edep = *value;
        if (edep > 0) {
            anaMan->FillNtupleDColumn(0,edep/MeV);
            anaMan->AddNtupleRow();
        }
    }
}
