//////////////////////////////Including libraries////////////////////////////////    
//////Read TFiles and TTrees, also basic functions////
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "iostream"
#include "TString.h"
#include "TChain.h"

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

void bdt_scores(){

TFile *f_sig = new TFile("MC_data/bdt_bbar/bdt_signalmc_taum_mup_tightcuts.root");
TTree *t_sig = (TTree*)f_sig->Get("incl");

TChain *c_bkg_continuum = new TChain("incl");
TChain *c_bkg_bbar = new TChain("incl");

c_bkg_continuum->Add("MC_data/bdt_bbar/bdt_bkg_uds_*.root");
c_bkg_continuum->Add("MC_data/bdt_bbar/bdt_bkg_charm_*.root");
c_bkg_bbar->Add("MC_data/bdt_bbar/bdt_bkg_charged_*.root");
c_bkg_bbar->Add("MC_data/bdt_bbar/bdt_bkg_mixed_*.root");

TH1F *h_signal_bdtc = new TH1F("h_signal_bdtc", "bdt scores distributions; bdt", 21, -1, 1);
TH1F *h_continuum_bdtc = new TH1F("h_continuum_bdtc", "bdt scores distributions; bdt", 21, -1, 1);
TH1F *h_bbar_bdtc = new TH1F("h_bbar_bdtc", "bdt scores distributions; bdt", 21, -1, 1);

TH1F *h_signal_bdtb = new TH1F("h_signal_bdtb", "bdt scores distributions; bdt", 21, -1, 1);
TH1F *h_continuum_bdtb = new TH1F("h_continuum_bdtb", "bdt scores distributions; bdt", 21, -1, 1);
TH1F *h_bbar_bdtb = new TH1F("h_bbar_bdtb", "bdt scores distributions; bdt", 21, -1, 1);

TString cuts = "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15";

t_sig->Draw("bdt_continuum>>h_signal_bdtc", cuts, "goff");
c_bkg_continuum->Draw("bdt_continuum>>h_continuum_bdtc",  cuts, "goff");
c_bkg_bbar->Draw("bdt_continuum>>h_bbar_bdtc",  cuts, "goff");
t_sig->Draw("bdt_bbar>>h_signal_bdtb", cuts, "goff");
c_bkg_continuum->Draw("bdt_bbar>>h_continuum_bdtb",  cuts, "goff");
c_bkg_bbar->Draw("bdt_bbar>>h_bbar_bdtb",  cuts, "goff");

h_signal_bdtc->Scale(1.0/h_signal_bdtc->Integral());
h_continuum_bdtc->Scale(1.0/h_continuum_bdtc->Integral());
h_bbar_bdtc->Scale(1.0/h_bbar_bdtc->Integral());
h_signal_bdtb->Scale(1.0/h_signal_bdtb->Integral());
h_continuum_bdtb->Scale(1.0/h_continuum_bdtb->Integral());
h_bbar_bdtb->Scale(1.0/h_bbar_bdtb->Integral());

h_signal_bdtc->SetLineColor(kBlue);
h_continuum_bdtc->SetLineColor(kRed);
h_bbar_bdtc->SetLineColor(kGreen);
h_signal_bdtb->SetLineColor(kBlue);
h_continuum_bdtb->SetLineColor(kRed);
h_bbar_bdtb->SetLineColor(kGreen);

h_signal_bdtc->SetLineStyle(1);
h_continuum_bdtc->SetLineStyle(1);
h_bbar_bdtc->SetLineStyle(1);
h_signal_bdtb->SetLineStyle(2);
h_continuum_bdtb->SetLineStyle(2);
h_bbar_bdtb->SetLineStyle(2);

TCanvas *c0 = new TCanvas("c0", "bdt scores", 1024, 786);

h_signal_bdtc->Draw("HIST");
h_continuum_bdtc->Draw("SAMESHIST");
h_bbar_bdtc->Draw("SAMESHIST");
h_signal_bdtb->Draw("SAMESHIST");
h_continuum_bdtb->Draw("SAMESHIST");
h_bbar_bdtb->Draw("SAMESHIST");

gPad->Update();

  TPaveStats *s_sig_bdtc = (TPaveStats*)h_signal_bdtc->FindObject("stats");
    s_sig_bdtc->SetX1NDC(0.75 - 0 * 0.15);
    s_sig_bdtc->SetX2NDC(0.90 - 0 * 0.15);
    s_sig_bdtc->SetY1NDC(0.90 - 0 * 0.05);
    s_sig_bdtc->SetY2NDC(1.00 - 0 * 0.05);
    s_sig_bdtc->SetTextColor(kBlue);

  TPaveStats *s_bkg_continuum_bdtc = (TPaveStats*)h_continuum_bdtc->FindObject("stats");
    s_bkg_continuum_bdtc->SetX1NDC(0.75 - 1 * 0.15);
    s_bkg_continuum_bdtc->SetX2NDC(0.90 - 1 * 0.15);
    s_bkg_continuum_bdtc->SetY1NDC(0.90 - 1 * 0.05);
    s_bkg_continuum_bdtc->SetY2NDC(1.00 - 1 * 0.05);
    s_bkg_continuum_bdtc->SetTextColor(kRed);

  TPaveStats *s_bkg_bbar_bdtc = (TPaveStats*)h_bbar_bdtc->FindObject("stats");
    s_bkg_bbar_bdtc->SetX1NDC(0.75 - 1 * 0.15);
    s_bkg_bbar_bdtc->SetX2NDC(0.90 - 1 * 0.15);
    s_bkg_bbar_bdtc->SetY1NDC(0.90 - 1 * 0.05);
    s_bkg_bbar_bdtc->SetY2NDC(1.00 - 1 * 0.05);
    s_bkg_bbar_bdtc->SetTextColor(kGreen);

    TPaveStats *s_sig_bdtb = (TPaveStats*)h_signal_bdtb->FindObject("stats");
    s_sig_bdtb->SetX1NDC(0.75 - 0 * 0.15);
    s_sig_bdtb->SetX2NDC(0.90 - 0 * 0.15);
    s_sig_bdtb->SetY1NDC(0.90 - 0 * 0.05);
    s_sig_bdtb->SetY2NDC(1.00 - 0 * 0.05);
    s_sig_bdtb->SetTextColor(kBlue);

  TPaveStats *s_bkg_continuum_bdtb = (TPaveStats*)h_continuum_bdtb->FindObject("stats");
    s_bkg_continuum_bdtb->SetX1NDC(0.75 - 1 * 0.15);
    s_bkg_continuum_bdtb->SetX2NDC(0.90 - 1 * 0.15);
    s_bkg_continuum_bdtb->SetY1NDC(0.90 - 1 * 0.05);
    s_bkg_continuum_bdtb->SetY2NDC(1.00 - 1 * 0.05);
    s_bkg_continuum_bdtb->SetTextColor(kRed);

  TPaveStats *s_bkg_bbar_bdtb = (TPaveStats*)h_bbar_bdtb->FindObject("stats");
    s_bkg_bbar_bdtb->SetX1NDC(0.75 - 1 * 0.15);
    s_bkg_bbar_bdtb->SetX2NDC(0.90 - 1 * 0.15);
    s_bkg_bbar_bdtb->SetY1NDC(0.90 - 1 * 0.05);
    s_bkg_bbar_bdtb->SetY2NDC(1.00 - 1 * 0.05);
    s_bkg_bbar_bdtb->SetTextColor(kGreen);

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9);
  leg->AddEntry(h_signal_bdtc,"bdt_continuum signal", "f");
  leg->AddEntry(h_continuum_bdtc,"bdt_continuum continuum", "f");
  leg->AddEntry(h_bbar_bdtc,"bdt_continuum bbar", "f");

  leg->AddEntry(h_signal_bdtb,"bdt_bbar signal", "f");
  leg->AddEntry(h_continuum_bdtb,"bdt_bbar continuum", "f");
  leg->AddEntry(h_bbar_bdtb,"bdt_bbar bbar", "f");

  leg->Draw();

}