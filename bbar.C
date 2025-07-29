//////////////////////////////Including libraries////////////////////////////////    
//////Read TFiles and TTrees, also basic functions////
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "iostream"
#include "TString.h"

/////To create plots of histograms////
#include"TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"  
#include "THStack.h"
#include "TPaveStats.h"

////////TMVA libraries//////////
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Types.h"
#include "TMVA/Reader.h"

void bbar(){

/////////////////Creating the factory///////////////////////
TFile *f_out = new TFile("bbar_BDT.root","RECREATE");
TMVA::Factory *factory = new TMVA::Factory("bbar_BDT", f_out,"!V:Color=True:DrawProgressBar=True");

///////////Upload the data to train and test the BDT///////////////////////////
TFile *f_sig = new TFile("MC_data/bdt_continuum/bdt_signalmc_taum_mup_tightcuts.root");

TFile *f_bkg_charged0 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_0.root");
TFile *f_bkg_charged1 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_1.root");
TFile *f_bkg_charged2 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_2.root");
TFile *f_bkg_charged3 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_3.root");
TFile *f_bkg_charged4 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_4.root");
TFile *f_bkg_charged5 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_5.root");
TFile *f_bkg_charged6 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_6.root");
TFile *f_bkg_charged7 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_7.root");
TFile *f_bkg_charged8 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_8.root");
TFile *f_bkg_charged9 = new TFile("MC_data/bdt_continuum/bdt_bkg_charged_9.root");

TFile *f_bkg_mixed0 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_0.root");
TFile *f_bkg_mixed1 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_1.root");
TFile *f_bkg_mixed2 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_2.root");
TFile *f_bkg_mixed3 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_3.root");
TFile *f_bkg_mixed4 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_4.root");
TFile *f_bkg_mixed5 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_5.root");
TFile *f_bkg_mixed6 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_6.root");
TFile *f_bkg_mixed7 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_7.root");
TFile *f_bkg_mixed8 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_8.root");
TFile *f_bkg_mixed9 = new TFile("MC_data/bdt_continuum/bdt_bkg_mixed_9.root");


TTree *t_sig = (TTree*)f_sig->Get("incl");

TTree *t_bkg_charged0 = (TTree*)f_bkg_charged0->Get("incl");
TTree *t_bkg_charged1 = (TTree*)f_bkg_charged1->Get("incl");
TTree *t_bkg_charged2 = (TTree*)f_bkg_charged2->Get("incl");
TTree *t_bkg_charged3 = (TTree*)f_bkg_charged3->Get("incl");
TTree *t_bkg_charged4 = (TTree*)f_bkg_charged4->Get("incl");
TTree *t_bkg_charged5 = (TTree*)f_bkg_charged5->Get("incl");
TTree *t_bkg_charged6 = (TTree*)f_bkg_charged6->Get("incl");
TTree *t_bkg_charged7 = (TTree*)f_bkg_charged7->Get("incl");
TTree *t_bkg_charged8 = (TTree*)f_bkg_charged8->Get("incl");
TTree *t_bkg_charged9 = (TTree*)f_bkg_charged9->Get("incl");


TTree *t_bkg_mixed0 = (TTree*)f_bkg_mixed0->Get("incl");
TTree *t_bkg_mixed1 = (TTree*)f_bkg_mixed1->Get("incl");
TTree *t_bkg_mixed2 = (TTree*)f_bkg_mixed2->Get("incl");
TTree *t_bkg_mixed3 = (TTree*)f_bkg_mixed3->Get("incl");
TTree *t_bkg_mixed4 = (TTree*)f_bkg_mixed4->Get("incl");
TTree *t_bkg_mixed5 = (TTree*)f_bkg_mixed5->Get("incl");
TTree *t_bkg_mixed6 = (TTree*)f_bkg_mixed6->Get("incl");
TTree *t_bkg_mixed7 = (TTree*)f_bkg_mixed7->Get("incl");
TTree *t_bkg_mixed8 = (TTree*)f_bkg_mixed8->Get("incl");
TTree *t_bkg_mixed9 = (TTree*)f_bkg_mixed9->Get("incl");


//////////////////////////////////Adding the TTrees to the Dataloader//////////////////////
Double_t sig_weight = 1.0; Double_t bkg_weight = 1.0; 

TMVA::DataLoader *dataloader_bbar = new TMVA::DataLoader("bbar");

dataloader_bbar->AddSignalTree(t_sig,sig_weight); 

dataloader_bbar->AddBackgroundTree(t_bkg_charged0,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged1,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged2,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged3,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged4,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged5,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged6,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged7,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged8,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_charged9,bkg_weight, TMVA::Types::kTesting);

dataloader_bbar->AddBackgroundTree(t_bkg_mixed0,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed1,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed2,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed3,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed4,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed5,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed6,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed7,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed8,bkg_weight, TMVA::Types::kTraining);
dataloader_bbar->AddBackgroundTree(t_bkg_mixed9,bkg_weight, TMVA::Types::kTesting);


////////////////////////////////Adding the variables/////////////////////////////////////
dataloader_bbar->AddVariable("deltaE_Btag", 'F');
dataloader_bbar->AddVariable("p_ltag", 'F');
dataloader_bbar->AddVariable("m_ROE", 'F');
dataloader_bbar->AddVariable("nLepton", 'I');
dataloader_bbar->AddVariable("nPhotonsSelected", 'I');
dataloader_bbar->AddVariable("best_sum", 'F');

//motivation, what we are doing, types bkg , approach, conclusions 
/////////////////////////////Cutting and spliting the data//////////////////////////////
TCut out_layers = "deltaE_Btag<1 &&  deltaE_Btag >-4 && p_ltag < 2.5 && m_ROE<4 && best_sum > -50";
TCut cut ="tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15 && bdt_continuum > 0.28";
TCut sig_cut = "isSignalAcceptMissingNeutrino_Bsig==1";
Int_t ntrain_sig = round((t_sig->GetEntries(cut +out_layers +sig_cut))*0.9); Int_t ntest_sig = round((t_sig->GetEntries(cut +out_layers +sig_cut))*0.1); //0.15  


TString options_split =Form("nTrain_Signal=%d:nTest_Signal=%d::SplitMode=Random",ntrain_sig,ntest_sig);
dataloader_bbar->PrepareTrainingAndTestTree(cut +out_layers +sig_cut,cut + out_layers ,options_split);

/////////////////////////////BOOKING METHODS/////////////////////////////////
// Boosted Decision Trees with adaptive boosting

factory->BookMethod(dataloader_bbar, TMVA::Types::kBDT, "BDT_bbar", "!H:!V:NTrees=400:MinNodeSize=4%:\
MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.1:nCuts=120:UseNvars=6"); 
factory->BookMethod(dataloader_bbar, TMVA::Types::kBDT, "BDTG", "!H:!V:NTrees=400:MinNodeSize=4%:\
MaxDepth=3:BoostType=Grad:Shrinkage=0.1:nCuts=120:UseNvars=6");


////////////////////////////////TRAINING, TESTING AND EVALUATING METHODS///////////////////////
factory->TrainAllMethods();
factory->TestAllMethods();
factory->EvaluateAllMethods();

///////////////////////////////SAVING MEMORY and ENABLING GUI INTERFACE/////////////////////
factory->SetVerbose(true); 
f_out->Close();
delete factory; delete dataloader_bbar;

}