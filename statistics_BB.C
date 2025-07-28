#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCut.h"
#include "TMath.h"
#include "iostream"

void statistics_BB() {
    // Input signal file with bdt_bbar scores
    TFile *f_sig = new TFile("MC_data/bdt_bbar/bdt_signalmc_taum_mup_tightcuts.root");
    TTree *t_sig = (TTree*)f_sig->Get("incl");

    // Background files: charm, uds, charged, mixed
    TChain *c_bkg = new TChain("incl");
    for (int i = 0; i < 6; i++) {
        c_bkg->Add(Form("MC_data/bdt_bbar/bdt_bkg_charm_%d.root", i));
        c_bkg->Add(Form("MC_data/bdt_bbar/bdt_bkg_uds_%d.root", i));
    }
    for (int i = 0; i < 10; i++) {
        c_bkg->Add(Form("MC_data/bdt_bbar/bdt_bkg_charged_%d.root", i));
        c_bkg->Add(Form("MC_data/bdt_bbar/bdt_bkg_mixed_%d.root", i));
    }

    // Selection cuts
    TCut obv_bkg = "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15 && abs(cos_pBtag_Dltag) < 1.25";
    TCut bdt_cut = "bdt_bbar > -0.03";  // <- Update this cut as needed

    // Get total and selected counts
    float n_sig_total = t_sig->GetEntries();
    float n_sig_selected = t_sig->GetEntries(obv_bkg && bdt_cut);

    float n_bkg_total = c_bkg->GetEntries();
    float n_bkg_selected = c_bkg->GetEntries(obv_bkg && bdt_cut);

    // Efficiencies
    float eff_sig = n_sig_selected / n_sig_total;
    float eff_bkg = n_bkg_selected / n_bkg_total;

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Signal Events (total): " << n_sig_total << std::endl;
    std::cout << "Signal Events (selected): " << n_sig_selected << std::endl;
    std::cout << "Signal Efficiency: " << eff_sig << std::endl;

    std::cout << "Background Events (total): " << n_bkg_total << std::endl;
    std::cout << "Background Events (selected): " << n_bkg_selected << std::endl;
    std::cout << "Background Efficiency: " << eff_bkg << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}
