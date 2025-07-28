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
/////////////////////////// # Of events expected at belle //////////////////////

Float_t int_luminosity = 711; //fb^-1
Float_t f_charged = 1-0.486; // fraction of the upsilon decaying into b⁺b⁻
Float_t bbar_cs = 1.1e06; //fb
Float_t nBBbar = 2 * int_luminosity * bbar_cs * f_charged; // computing the number of B⁺B⁻
Float_t br_BtoKTauMu = 5e-5;  //Branching ratio of the LVF process??
Float_t br_TautoRho = 0.228; //Branching ratio retrived from Inspired
Float_t Pi0toPhotons = 0.988; //Branching ratio of the pi0 decaying into two photons
Float_t sigtheory = round(nBBbar * br_BtoKTauMu * br_TautoRho); // actual signal events expected at belle


//////////////////////////Uploading files//////////////////////////////////////////

TFile *f_sig_original = new TFile("MC_data/bdt_bbar/bdt_signalmc_taum_mup_tightcuts.root");
TTree *t_sig = (TTree*)f_sig_original->Get("incl");

TChain *c_bkg = new TChain("incl");

c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_uds_0.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_uds_1.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_uds_2.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_uds_3.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_uds_4.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_uds_5.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charm_0.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charm_1.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charm_2.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charm_3.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charm_4.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charm_5.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_0.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_1.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_2.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_3.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_4.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_5.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_6.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_7.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_8.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_charged_9.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_0.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_1.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_2.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_3.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_4.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_5.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_6.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_7.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_8.root");
c_bkg->Add("MC_data/bdt_bbar/bdt_bkg_mixed_9.root");


////////////////////////////////////Original number of events//////////////////////////////////////////
float n_sig_original =1e6;
float n_bkg_original = c_bkg->GetEntries();

////////////////////Rejection of obvious background/////////////////////////////////////////////////////
TCut obv_bkg = "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15 && abs(cos_pBtag_Dltag) < 1.25";

float n_sig_selected0 = t_sig->GetEntries(obv_bkg);
float n_bkg_selected0 = c_bkg->GetEntries(obv_bkg);

float sig_eff0 = n_sig_selected0/n_sig_original;
float bkg_eff0 = n_bkg_selected0/n_bkg_original;

std::cout << "--------------------------------------" << std::endl;
    std::cout << "Signal Events (total): " << n_sig_original << std::endl;
    std::cout << "Signal Events (selected): " << n_sig_selected0 << std::endl;
    std::cout << "Signal Efficiency: " << sig_eff0 << std::endl;

    std::cout << "Background Events (total): " << n_bkg_original << std::endl;
    std::cout << "Background Events (selected): " << n_bkg_selected0 << std::endl;
    std::cout << "Background Efficiency: " << bkg_eff0 << std::endl;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff0) << std::endl;
    std::cout << "--------------------------------------" << std::endl;


//////////////////////////////////////BDT CONTINUUM//////////////////////////////////////////////////
TCut continuum_cut = "bdt_continuum > 0.28";


float n_sig_selected1 = t_sig->GetEntries(obv_bkg + continuum_cut);
float n_bkg_selected1 = c_bkg->GetEntries(obv_bkg + continuum_cut);

float sig_eff1 = n_sig_selected1/n_sig_original;
float bkg_eff1 = n_bkg_selected1/n_bkg_original;

std::cout << "--------------------------------------" << std::endl;
    std::cout << "Signal Events (total): " << n_sig_original << std::endl;
    std::cout << "Signal Events (selected): " << n_sig_selected1 << std::endl;
    std::cout << "Signal Efficiency: " << sig_eff1 << std::endl;

    std::cout << "Background Events (total): " << n_bkg_original << std::endl;
    std::cout << "Background Events (selected): " << n_bkg_selected1 << std::endl;
    std::cout << "Background Efficiency: " << bkg_eff1 << std::endl;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff1) << std::endl;
    std::cout << "--------------------------------------" << std::endl;

////////////////////////////BDT BBAR/////////////////////////////////////
TCut bbar_cut = "bdt_bbar > 0.09";


float n_sig_selected2 = t_sig->GetEntries(obv_bkg + bbar_cut);
float n_bkg_selected2 = c_bkg->GetEntries(obv_bkg + bbar_cut);

float sig_eff2 = n_sig_selected2/n_sig_original;
float bkg_eff2 = n_bkg_selected2/n_bkg_original;

std::cout << "--------------------------------------" << std::endl;
    std::cout << "Signal Events (total): " << n_sig_original << std::endl;
    std::cout << "Signal Events (selected): " << n_sig_selected2 << std::endl;
    std::cout << "Signal Efficiency: " << sig_eff2 << std::endl;

    std::cout << "Background Events (total): " << n_bkg_original << std::endl;
    std::cout << "Background Events (selected): " << n_bkg_selected2 << std::endl;
    std::cout << "Background Efficiency: " << bkg_eff2 << std::endl;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff2) << std::endl;
    std::cout << "--------------------------------------" << std::endl;

///////////////////////////////////////ALL CUTS//////////////////////////
float n_sig_selected3 = t_sig->GetEntries(obv_bkg + bbar_cut + continuum_cut);
float n_bkg_selected3 = c_bkg->GetEntries(obv_bkg + bbar_cut + continuum_cut);

float sig_eff3 = n_sig_selected3/n_sig_original;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff3) << std::endl;
Float_t bkg_eff3 = n_bkg_selected3/n_bkg_original;

std::cout << "--------------------------------------" << std::endl;
    std::cout << "Signal Events (total): " << n_sig_original << std::endl;
    std::cout << "Signal Events (selected): " << n_sig_selected3 << std::endl;
    std::cout << "Signal Efficiency: " << sig_eff3 << std::endl;

    std::cout << "Background Events (total): " << n_bkg_original << std::endl;
    std::cout << "Background Events (selected): " << n_bkg_selected3 << std::endl;
    std::cout << "Background Efficiency: " << bkg_eff3 << std::endl;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff3) << std::endl;
    std::cout << "--------------------------------------" << std::endl;


///////////////////////////////BDTG Statistics/////////////////////////////////////

//////////////////////////////////////BDTG CONTINUUM//////////////////////////////////////////////////
TCut continuum_cut_bdtg = "bdtg_continuum > 0.79";

float n_sig_selected1_bdtg = t_sig->GetEntries(obv_bkg + continuum_cut_bdtg);
float n_bkg_selected1_bdtg = c_bkg->GetEntries(obv_bkg + continuum_cut_bdtg);

float sig_eff1_bdtg = n_sig_selected1_bdtg/n_sig_original;
float bkg_eff1_bdtg = n_sig_selected1_bdtg/n_bkg_original;

std::cout << "--------------------------------------" << std::endl;
    std::cout << "Signal Events (total): " << n_sig_original << std::endl;
    std::cout << "Signal Events (selected): " << n_sig_selected1_bdtg << std::endl;
    std::cout << "Signal Efficiency: " << sig_eff1_bdtg << std::endl;

    std::cout << "Background Events (total): " << n_bkg_original << std::endl;
    std::cout << "Background Events (selected): " << n_bkg_selected1_bdtg << std::endl;
    std::cout << "Background Efficiency: " << bkg_eff1_bdtg << std::endl;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff1_bdtg) << std::endl;
    std::cout << "--------------------------------------" << std::endl;

////////////////////////////BDT BBAR/////////////////////////////////////
TCut bbar_cut_bdtg = "bdt_bbar > -0.2";


float n_sig_selected2_bdtg = t_sig->GetEntries(obv_bkg + bbar_cut_bdtg);
float n_bkg_selected2_bdtg = c_bkg->GetEntries(obv_bkg + bbar_cut_bdtg);

float sig_eff2_bdtg = n_sig_selected2_bdtg/n_sig_original;
float bkg_eff2_bdtg = n_bkg_selected2_bdtg/n_bkg_original;

std::cout << "--------------------------------------" << std::endl;
    std::cout << "Signal Events (total): " << n_sig_original << std::endl;
    std::cout << "Signal Events (selected): " << n_sig_selected2_bdtg << std::endl;
    std::cout << "Signal Efficiency: " << sig_eff2_bdtg << std::endl;

    std::cout << "Background Events (total): " << n_bkg_original << std::endl;
    std::cout << "Background Events (selected): " << n_bkg_selected2_bdtg << std::endl;
    std::cout << "Background Efficiency: " << bkg_eff2_bdtg << std::endl;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff2_bdtg) << std::endl;
    std::cout << "--------------------------------------" << std::endl;

///////////////////////////////////////ALL CUTS//////////////////////////
float n_sig_selected3_bdtg = t_sig->GetEntries(obv_bkg + bbar_cut_bdtg + continuum_cut_bdtg);
float n_bkg_selected3_bdtg= c_bkg->GetEntries(obv_bkg + bbar_cut_bdtg + continuum_cut_bdtg);

float sig_eff3_bdtg = n_sig_selected3_bdtg/n_sig_original;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff3_bdtg) << std::endl;
Float_t bkg_eff3_bdtg = n_bkg_selected3/n_bkg_original;

std::cout << "--------------------------------------" << std::endl;
    std::cout << "Signal Events (total): " << n_sig_original << std::endl;
    std::cout << "Signal Events (selected): " << n_sig_selected3_bdtg << std::endl;
    std::cout << "Signal Efficiency: " << sig_eff3_bdtg << std::endl;

    std::cout << "Background Events (total): " << n_bkg_original << std::endl;
    std::cout << "Background Events (selected): " << n_bkg_selected3_bdtg << std::endl;
    std::cout << "Background Efficiency: " << bkg_eff3_bdtg << std::endl;
    std::cout << "Expected number of signal events: " << round(sigtheory*sig_eff3_bdtg) << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}