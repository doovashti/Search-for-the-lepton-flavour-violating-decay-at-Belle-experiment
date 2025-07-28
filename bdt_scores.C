//////////////////////////////Including libraries////////////////////////////////    
//////Read TFiles and TTrees, also basic functions////
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "iostream"
#include "TString.h"
#include "TChain.h"
#include  <vector>

/////To create plots of histograms////
#include"TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"  
#include "THStack.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TGraph.h"
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
/*
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
/////////////////////////////////////
*/
double xVar, yVar;

    // Vectors to store data for each chain
    std::vector<double> x1, y1, x2, y2, x3, y3;

    // Extract data from chain1
    t_sig->SetBranchAddress("bdt_continuum", &xVar); // Replace "xVar" with your branch name
    t_sig->SetBranchAddress("bdt_bbar", &yVar); // Replace "yVar" with your branch name
    Long64_t nEntries1 = t_sig->GetEntries();
    for (Long64_t i = 0; i < nEntries1; i++) {
        t_sig->GetEntry(i);
        x1.push_back(xVar);
        y1.push_back(yVar);
    }

    // Extract data from chain2
    c_bkg_continuum->SetBranchAddress("bdt_continuum", &xVar);
    c_bkg_continuum->SetBranchAddress("bdt_bbar", &yVar);
    Long64_t nEntries2 = c_bkg_continuum->GetEntries();
    for (Long64_t i = 0; i < nEntries2; i++) {
        c_bkg_continuum->GetEntry(i);
        x2.push_back(xVar);
        y2.push_back(yVar);
    }

    // Extract data from chain3
    c_bkg_bbar->SetBranchAddress("bdt_continuum", &xVar);
    c_bkg_bbar->SetBranchAddress("bdt_bbar", &yVar);
    Long64_t nEntries3 = c_bkg_bbar->GetEntries();
    for (Long64_t i = 0; i < nEntries3; i++) {
        c_bkg_bbar->GetEntry(i);
        x3.push_back(xVar);
        y3.push_back(yVar);
    }

    // Create TGraph objects for each chain
    TGraph *graph1 = new TGraph(x1.size(), x1.data(), y1.data());
    TGraph *graph2 = new TGraph(x2.size(), x2.data(), y2.data());
    TGraph *graph3 = new TGraph(x3.size(), x3.data(), y3.data());

    // Customize graphs
    graph1->SetTitle("Signal and background distributions ;bdt_continuum;bdt_bbar");
    graph1->SetMarkerStyle(20); // Filled circle
    graph1->SetMarkerColor(kBlue);
    graph1->SetMarkerSize(1.2);

    graph2->SetMarkerStyle(21); // Filled square
    graph2->SetMarkerColor(kRed);
    graph2->SetMarkerSize(1.2);

    graph3->SetMarkerStyle(22); // Filled triangle
    graph3->SetMarkerColor(kGreen);
    graph3->SetMarkerSize(1.2);

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Scatter Plot", 800, 600);

    // Draw the first graph with axes
 

    // Draw additional graphs with points only ("P SAME")
    graph2->Draw("AP");
    graph3->Draw("P SAME");
    graph1->Draw("P SAME");
    // Customize appearance
    gStyle->SetOptStat(0); // Disable statistics box
    graph1->GetXaxis()->SetTitleSize(0.04);
    graph1->GetYaxis()->SetTitleSize(0.04);

    // Add a legend
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(graph1, "Chain 1", "p");
    legend->AddEntry(graph2, "Chain 2", "p");
    legend->AddEntry(graph3, "Chain 3", "p");
    legend->Draw();

    // Save the plot
    canvas->SaveAs("scatter_plot_tchains.png");

    // Clean up
    delete t_sig; delete c_bkg_continuum; delete c_bkg_bbar;
    delete canvas;






}