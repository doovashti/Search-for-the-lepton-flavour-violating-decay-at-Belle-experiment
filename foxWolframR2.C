#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TString.h"

void foxWolframR2() {
    gStyle->SetOptStat("emr");

    // Open ROOT files
    TFile *f_sig     = new TFile("MC_data/rootfiles/signalmc_taum_mup_tightcuts.root");
    TFile *f_uds     = new TFile("MC_data/rootfiles/bkg_uds_0.root");
    TFile *f_charm   = new TFile("MC_data/rootfiles/bkg_charm_0.root");
    TFile *f_mixed   = new TFile("MC_data/rootfiles/bkg_mixed_0.root");
    TFile *f_charged = new TFile("MC_data/rootfiles/bkg_charged_0.root");

    // Get TTrees
    TTree *t_sig     = (TTree*)f_sig->Get("incl");
    TTree *t_uds     = (TTree*)f_uds->Get("incl");
    TTree *t_charm   = (TTree*)f_charm->Get("incl");
    TTree *t_mixed   = (TTree*)f_mixed->Get("incl");
    TTree *t_charged = (TTree*)f_charged->Get("incl");

    TString variable = "foxWolframR2";
    TString unit = "[GeV/c^{2}]";

    double lowrange = std::min({t_sig->GetMinimum(variable), t_uds->GetMinimum(variable),(t_charm->GetMinimum(variable), t_mixed->GetMinimum(variable)),t_charged->GetMinimum(variable)});

    double highrange = std::max({t_sig->GetMaximum(variable), t_uds->GetMaximum(variable),t_charm->GetMaximum(variable), t_mixed->GetMaximum(variable),t_charged->GetMaximum(variable)});

    double bin_width = 0.005;

    int nbins = (highrange - lowrange)/bin_width;

    // Create histograms
    TH1F *h_sig = new TH1F("h_sig", "foxWolframR2;Invariant Mass [GeV];Entries", nbins, lowrange, highrange);
    TH1F *h_uds     = new TH1F("h_uds",     "", nbins, lowrange, highrange);
    TH1F *h_charm   = new TH1F("h_charm",   "", nbins, lowrange, highrange);
    TH1F *h_mixed   = new TH1F("h_mixed",   "", nbins, lowrange, highrange);
    TH1F *h_charged = new TH1F("h_charged", "", nbins, lowrange, highrange);

    // Apply cuts
    TString cut = "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 && m_Krho > 1.95 && m_ROE < 2.15 && foxWolframR2 < 0.4";
    t_sig->Draw(variable + ">>h_sig", cut, "goff");
    t_uds->Draw(variable + ">>h_uds", cut, "goff");
    t_charm->Draw(variable + ">>h_charm", cut, "goff");
    t_mixed->Draw(variable + ">>h_mixed", cut, "goff");
    t_charged->Draw(variable + ">>h_charged", cut, "goff");

    h_sig->SetLineWidth(2);
    h_sig->SetLineStyle(1);
    h_sig->SetLineColor(kBlue);
    h_sig->SetMarkerColor(kBlue);

    h_uds->SetLineWidth(2);
    h_uds->SetLineStyle(1);
    h_uds->SetLineColor(kGreen);
    h_uds->SetMarkerColor(kGreen);

    h_charm->SetLineWidth(2);
    h_charm->SetLineStyle(1);
    h_charm->SetLineColor(kRed);
    h_charm->SetMarkerColor(kRed);

    h_charged->SetLineWidth(2);
    h_charged->SetLineStyle(1);
    h_charged->SetLineColor(kBlack);
    h_charged->SetMarkerColor(kBlack);

    h_mixed->SetLineWidth(2);
    h_mixed->SetLineStyle(1);
    h_mixed->SetLineColor(kViolet);
    h_mixed->SetMarkerColor(kViolet);

    TLegend *leg = new TLegend(0.65, 0.7, 0.88, 0.88);
    leg->AddEntry(h_sig,     "Signal MC",       "f");
    leg->AddEntry(h_uds,     "uds MC",          "f");
    leg->AddEntry(h_charm,   "charm MC",        "f");
    leg->AddEntry(h_mixed,   "Mixed B#bar{B} MC", "f");
    leg->AddEntry(h_charged, "Charged B#bar{B} MC", "f");

    h_sig->Draw("HIST");
    h_uds->Draw("SAMESHIST");
    h_charm->Draw("SAMESHIST");
    h_mixed->Draw("SAMESHIST");
    h_charged->Draw("SAMESHIST");
    leg->Draw();
    gPad->Update();       


    // Update stats boxes color
    TPaveStats *ps_uds = (TPaveStats*) h_uds->FindObject("stats");
    ps_uds->SetLineColor(kGreen);
    ps_uds->SetTextColor(kGreen);

    TPaveStats *ps_charm = (TPaveStats*) h_charm->FindObject("stats");
    ps_charm->SetLineColor(kRed);
    ps_charm->SetTextColor(kRed);

    TPaveStats *ps_mixed = (TPaveStats*) h_mixed->FindObject("stats");
    ps_mixed->SetLineColor(kViolet);
    ps_mixed->SetTextColor(kViolet);

    TPaveStats *ps_charged = (TPaveStats*) h_charged->FindObject("stats");
    ps_charged->SetLineColor(kBlack);
    ps_charged->SetTextColor(kBlack);

    TPaveStats *ps_sig = (TPaveStats*) h_sig->FindObject("stats");
    ps_sig->SetLineColor(kBlue);
    ps_sig->SetTextColor(kBlue);

    h_sig ->Scale(1.0/h_sig->Integral());
    h_uds->Scale(1.0/h_uds->Integral());
    h_charm->Scale(1.0/h_charm->Integral());
    h_mixed->Scale(1.0/h_mixed->Integral());
    h_charged->Scale(1.0/h_charged->Integral());
    
    THStack *hs = new THStack("hs", Form(";%s %s; Entries/(%.3f%s)", variable.Data(), unit.Data(), bin_width, unit.Data()));
    hs->Add(h_sig);
    hs->Add(h_uds);
    hs->Add(h_charm);
    hs->Add(h_mixed);
    hs->Add(h_charged);

    TCanvas *c = new TCanvas("c1", "Stacked Histogram", 800, 600);
    //hs->Draw();
    h_sig->Draw("HIST");
    h_uds->Draw("SAMESHIST");
    h_charm->Draw("SAMESHIST");
    h_mixed->Draw("SAMESHIST");
    h_charged->Draw("SAMESHIST");
    leg->Draw();

}




