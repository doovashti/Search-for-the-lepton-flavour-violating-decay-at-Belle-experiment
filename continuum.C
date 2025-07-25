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

void continuum(){

/////////////////Creating the factory///////////////////////
TFile *f_out = new TFile("continuum_BDT.root","RECREATE");
TMVA::Factory *factory = new TMVA::Factory("continuum_BDT", f_out,"!V:Color=True:DrawProgressBar=True");

///////////Upload the data to train and test the BDT///////////////////////////
TFile *f_sig = new TFile("MC_data/rootfiles/signalmc_taum_mup_tightcuts.root");

TFile *f_bkg_charm0 = new TFile("MC_data/rootfiles/bkg_charm_0.root");
TFile *f_bkg_charm1 = new TFile("MC_data/rootfiles/bkg_charm_1.root");
TFile *f_bkg_charm2 = new TFile("MC_data/rootfiles/bkg_charm_2.root");
TFile *f_bkg_charm3 = new TFile("MC_data/rootfiles/bkg_charm_3.root");
TFile *f_bkg_charm4 = new TFile("MC_data/rootfiles/bkg_charm_4.root");
TFile *f_bkg_charm5 = new TFile("MC_data/rootfiles/bkg_charm_5.root");


TFile *f_bkg_uds0 = new TFile("MC_data/rootfiles/bkg_uds_0.root");
TFile *f_bkg_uds1 = new TFile("MC_data/rootfiles/bkg_uds_1.root");
TFile *f_bkg_uds2 = new TFile("MC_data/rootfiles/bkg_uds_2.root");
TFile *f_bkg_uds3 = new TFile("MC_data/rootfiles/bkg_uds_3.root");
TFile *f_bkg_uds4 = new TFile("MC_data/rootfiles/bkg_uds_4.root");
TFile *f_bkg_uds5 = new TFile("MC_data/rootfiles/bkg_uds_5.root");


TTree *t_sig = (TTree*)f_sig->Get("incl");

TTree *t_bkg_charm0 = (TTree*)f_bkg_charm0->Get("incl");
TTree *t_bkg_charm1 = (TTree*)f_bkg_charm1->Get("incl");
TTree *t_bkg_charm2 = (TTree*)f_bkg_charm2->Get("incl");
TTree *t_bkg_charm3 = (TTree*)f_bkg_charm3->Get("incl");
TTree *t_bkg_charm4 = (TTree*)f_bkg_charm4->Get("incl");
TTree *t_bkg_charm5 = (TTree*)f_bkg_charm5->Get("incl");


TTree *t_bkg_uds0 = (TTree*)f_bkg_uds0->Get("incl");
TTree *t_bkg_uds1 = (TTree*)f_bkg_uds1->Get("incl");
TTree *t_bkg_uds2 = (TTree*)f_bkg_uds2->Get("incl");
TTree *t_bkg_uds3 = (TTree*)f_bkg_uds3->Get("incl");
TTree *t_bkg_uds4 = (TTree*)f_bkg_uds4->Get("incl");
TTree *t_bkg_uds5 = (TTree*)f_bkg_uds5->Get("incl");


//////////////////////////////////Adding the TTrees to the Dataloader//////////////////////
Double_t sig_weight = 1.0; Double_t bkg_weight = 1.0; 

TMVA::DataLoader *dataloader_continuum = new TMVA::DataLoader("continuum");

dataloader_continuum->AddSignalTree(t_sig,sig_weight); 

dataloader_continuum->AddBackgroundTree(t_bkg_charm0,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_charm1,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_charm2,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_charm3,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_charm4,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_charm5,bkg_weight, TMVA::Types::kTesting);

dataloader_continuum->AddBackgroundTree(t_bkg_uds0,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_uds1,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_uds2,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_uds3,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_uds4,bkg_weight, TMVA::Types::kTraining);
dataloader_continuum->AddBackgroundTree(t_bkg_uds5,bkg_weight, TMVA::Types::kTesting);


////////////////////////////////Adding the variables/////////////////////////////////////
dataloader_continuum->AddVariable("CleoConeCS_1", 'F');
dataloader_continuum->AddVariable("CleoConeCS_2", 'F');
dataloader_continuum->AddVariable("CleoConeCS_3", 'F');
dataloader_continuum->AddVariable("CleoConeCS_4", 'F');
dataloader_continuum->AddVariable("CleoConeCS_5", 'F');
dataloader_continuum->AddVariable("CleoConeCS_6", 'F');
dataloader_continuum->AddVariable("CleoConeCS_7", 'F');
dataloader_continuum->AddVariable("CleoConeCS_8", 'F');
dataloader_continuum->AddVariable("CleoConeCS_9", 'F');
dataloader_continuum->AddVariable("KSFWVariables_et", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hoo0", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hoo1", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hoo2", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hoo3", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hoo4", 'F');
//dataloader_continuum->AddVariable("KSFWVariables_hso00", 'F'); //partialy correlated with hoo1, hoo0
dataloader_continuum->AddVariable("KSFWVariables_hso01", 'F');
//dataloader_continuum->AddVariable("KSFWVariables_hso02", 'F'); //correlated with r2
dataloader_continuum->AddVariable("KSFWVariables_hso03", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hso04", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hso10", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hso12", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hso14", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hso20", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hso22", 'F');
dataloader_continuum->AddVariable("KSFWVariables_hso24", 'F');
//dataloader_continuum->AddVariable("KSFWVariables_mm2", 'F'); //correlated with hoo0, et, hso00
dataloader_continuum->AddVariable("r2", 'F');
dataloader_continuum->AddVariable("thrust_Bm", 'F');
//dataloader_continuum->AddVariable("thrust_Om", 'F'); //correlated with r2

/////////////////////////////Cutting and spliting the data//////////////////////////////
TCut out_layers = "deltaE_Btag<1 &&  deltaE_Btag >-4 && p_ltag < 2.5 && m_ROE<4 && best_sum > -50";
TCut cut ="tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15 && abs(cos_pBtag_Dltag) < 1.25";
TCut sig_cut = "isSignalAcceptMissingNeutrino_Bsig==1";
Int_t ntrain_sig = round((t_sig->GetEntries(cut +out_layers + sig_cut))*0.833333); Int_t ntest_sig = round((t_sig->GetEntries(cut +out_layers + sig_cut))*0.166667);


TString options_split =Form("nTrain_Signal=%d:nTest_Signal=%d::SplitMode=Random",ntrain_sig,ntest_sig);
dataloader_continuum->PrepareTrainingAndTestTree(cut +out_layers + sig_cut, cut +out_layers ,options_split);

/////////////////////////////BOOKING METHODS/////////////////////////////////
// Boosted Decision Trees with adaptive boosting

factory->BookMethod(dataloader_continuum, TMVA::Types::kBDT, "BDT_continuum", "!H:!V:NTrees=400:MinNodeSize=4%:\
MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.1:nCuts=120:UseNvars=6"); 

////////////////////////////////TRAINING, TESTING AND EVALUATING METHODS///////////////////////
factory->TrainAllMethods();
factory->TestAllMethods();
factory->EvaluateAllMethods();

///////////////////////////////SAVING MEMORY and ENABLING GUI INTERFACE/////////////////////
factory->SetVerbose(true); 
f_out->Close();
delete factory; delete dataloader_continuum;

}