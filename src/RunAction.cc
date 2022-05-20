//---------------------------------------------------------------------//
// Created by L.T. Anh                                                 //
// Contribution: L.T. Anh, D.M. Linh                                   //
//---------------------------------------------------------------------//
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
RunAction::RunAction()
: G4UserRunAction()
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetDefaultFileType("root");

    //Creating ntuple:
    analysisManager->CreateNtuple("PGNAA","Edep in BGO");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    G4String fileName = "PGNAA.root";
    analysisManager->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}