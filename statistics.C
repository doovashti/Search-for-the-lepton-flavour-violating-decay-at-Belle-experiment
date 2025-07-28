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
#include "TChain.h"

void statistics(){
Float_t int_luminosity = 711; //fb^-1
Float_t f_charged = 1-0.486; // fraction of the upsilon decaying into b⁺b⁻
Float_t bbar_cs = 1.1e06; //fb
Float_t nBBbar = 2 * int_luminosity * bbar_cs * f_charged; // computing the number of B⁺B⁻
Float_t br_BtoKTauMu = 5e-5;  //Branching ratio of the LVF process??
Float_t br_TautoRho = 0.228; //Branching ratio retrived from Inspired
Float_t sigtheory = round(nBBbar * br_BtoKTauMu * br_TautoRho); // actual signal events expected at belle

TFile *f_sig_original = new TFile("MC_data/rootfiles/signalmc_taum_mup_tightcuts.root");
TTree *t_sig_original = (TTree*)f_sig_original->Get("incl");

TCut obv_bkg = "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15 && abs(cos_pBtag_Dltag) < 1.25";


Float_t original_signal = t_sig_original->GetEntries(); 

///////////////////////////continuum BDT////////////////////
TChain *c_bkg_continuum = new TChain("incl");

TFile *f_sig_continuum = new TFile("MC_data/bdt_continuum/bdt_signalmc_taum_mup_tightcuts.root");

c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_uds_0.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_uds_1.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_uds_2.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_uds_3.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_uds_4.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_uds_5.root");

c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charm_0.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charm_1.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charm_2.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charm_3.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charm_4.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charm_5.root");

c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_0.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_1.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_2.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_3.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_4.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_5.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_6.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_7.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_8.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_charged_9.root");

c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_0.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_1.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_2.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_3.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_4.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_5.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_6.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_7.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_8.root");
c_bkg_continuum->Add("MC_data/bdt_continuum/bdt_bkg_mixed_9.root");


TTree *t_sig_continuum = (TTree*)f_sig_continuum->Get("incl");

TCut continuum_cut = "bdt_continuum > 0.0338";


Float_t continuum_signal = t_sig_continuum->GetEntries(obv_bkg && continuum_cut); 
Float_t continuum_bkg = c_bkg_continuum->GetEntries(obv_bkg && continuum_cut); 
Float_t original_continuum_bkg = c_bkg_continuum->GetEntries(); 

Float_t continuum_eff_signal = continuum_signal/original_signal;
Float_t continuum_eff_bkg = continuum_bkg/original_continuum_bkg;

std::cout << continuum_eff_signal << std::endl;
std::cout << continuum_eff_bkg << std::endl;




///////////////////////////////////////ALL CUTS//////////////////////////
TChain *c_bkg_all_cuts = new TChain("incl");

TFile *f_sig_all_cuts = new TFile("MC_data/bdt_bbar/bdt_signalmc_taum_mup_tightcuts.root");

c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_uds_0.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_uds_1.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_uds_2.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_uds_3.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_uds_4.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_uds_5.root");

c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charm_0.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charm_1.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charm_2.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charm_3.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charm_4.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charm_5.root");

c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_0.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_1.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_2.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_3.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_4.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_5.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_6.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_7.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_8.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_charged_9.root");

c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_0.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_1.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_2.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_3.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_4.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_5.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_6.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_7.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_8.root");
c_bkg_all_cuts->Add("MC_data/bdt_both/bdt_bkg_mixed_9.root");


//////////////cuts for the bdt scores 

TCut bdt_continuum = "bdt_continuum > 0.038";
TCut bdt_bbar = "bdt_bbar > 0.013";

TTree *t_sig_all_cuts = (TTree*)f_sig_all_cuts->Get("incl");

Float_t signal_all_cuts = t_sig_all_cuts->GetEntries(obv_bkg && bdt_continuum && bdt_bbar); 
Float_t bkg_all_cuts = c_bkg_all_cuts->GetEntries(obv_bkg && bdt_continuum && bdt_bbar); 
Float_t original_all_cuts_bkg = c_bkg_all_cuts->GetEntries(); 

Float_t all_cuts_eff_signal = signal_all_cuts/original_signal;
Float_t all_cuts_eff_bkg = bkg_all_cuts/original_all_cuts_bkg;

std::cout <<"The relative signal efficiency after all the cuts and the original signal events is: " << all_cuts_eff_signal << std::endl;
std::cout << "The relative background efficiency after all the cuts and the original background events is: " << all_cuts_eff_bkg << std::endl;

std::cout << "The remaining number of signal events is: "<< signal_all_cuts << std::endl;
std::cout << "The remaining number of background events is " << bkg_all_cuts << std::endl;

std::cout << "The expected number of true signal events observed at belle is: " << all_cuts_eff_signal*sigtheory <<std::endl;


}