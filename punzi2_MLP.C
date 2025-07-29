//////////////////////////////Including libraries////////////////////////////////    
//////Read TFiles and TTrees, also basic functions////
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "iostream"
#include "TString.h"
#include <vector>
#include "TChain.h"

/////To create plots of histograms////
#include"TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"  
#include "THStack.h"
#include "TPaveStats.h"
#include "TGraph.h"

////////TMVA libraries//////////
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Types.h"
#include "TMVA/Reader.h"
#include "TRandom.h"
#include "TMVA/ROCCurve.h"

////////////////////////////Defining the PUNZI FOM///////////////////////////////7
double punji_fom(float eff, float nb, float wb){
  double fig = eff/(1.5+sqrt(nb*wb));
  return fig;
}
// --- Compute Punzi FOM from ROC Curve ---
  // Estimate total expected background events (replace with your experiment’s value)
void punzi2_MLP(){

/////////////////// Upload the MC samples///////////////////////////////
TFile *f_sig = new TFile("MC_data/MLP_bbar/MLP_signalmc_taum_mup_tightcuts.root");

TChain *c_bkg_charged = new TChain("incl");
TChain *c_bkg_mixed = new TChain("incl");

c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_0.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_1.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_2.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_3.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_4.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_5.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_6.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_7.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_8.root");
c_bkg_charged->Add("MC_data/MLP_bbar/MLP_bkg_charged_9.root");

c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_0.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_1.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_2.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_3.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_4.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_5.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_6.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_7.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_8.root");
c_bkg_mixed->Add("MC_data/MLP_bbar/MLP_bkg_mixed_9.root");


TTree *t_sig = (TTree*)f_sig->Get("incl");


//////////////////Retriving important data from the mc samples TTrees//////////////////////
Double_t  sig_mKpi;
Double_t  sig_mKrho;
Double_t  sig_mROE;
Double_t  sig_taumode;
Double_t  sig_bmode;
Double_t  sig_MLPs;

Double_t bkg_mKpi_charged;
Double_t bkg_mKrho_charged;
Double_t bkg_taumode_charged;
Double_t bkg_bmode_charged;
Double_t bkg_MLPs_charged;
Double_t bkg_mROE_charged;

Double_t bkg_mROE_mixed;
Double_t bkg_mKrho_mixed;
Double_t bkg_taumode_mixed;
Double_t bkg_bmode_mixed;
Double_t bkg_MLPs_mixed;
Double_t bkg_mKpi_mixed;

t_sig->SetBranchAddress("tauDecay_decayModeID", &sig_taumode);
t_sig->SetBranchAddress("Bsig_decayModeID", &sig_bmode);
t_sig->SetBranchAddress("m_Kpi", &sig_mKpi);
t_sig->SetBranchAddress("m_Krho", &sig_mKrho);
t_sig->SetBranchAddress("m_ROE", &sig_mROE);
t_sig->SetBranchAddress("MLP_bbar", &sig_MLPs);

c_bkg_charged->SetBranchAddress("tauDecay_decayModeID", &bkg_taumode_charged);
c_bkg_charged->SetBranchAddress("Bsig_decayModeID", &bkg_bmode_charged);
c_bkg_charged->SetBranchAddress("m_Kpi", &bkg_mKpi_charged);
c_bkg_charged->SetBranchAddress("m_Krho", &bkg_mKrho_charged);
c_bkg_charged->SetBranchAddress("m_ROE", &bkg_mROE_charged);
c_bkg_charged->SetBranchAddress("MLP_bbar", &bkg_MLPs_charged);

c_bkg_mixed->SetBranchAddress("tauDecay_decayModeID", &bkg_taumode_mixed);
c_bkg_mixed->SetBranchAddress("Bsig_decayModeID", &bkg_bmode_mixed);
c_bkg_mixed->SetBranchAddress("m_Kpi", &bkg_mKpi_mixed);
c_bkg_mixed->SetBranchAddress("m_Krho", &bkg_mKrho_mixed);
c_bkg_mixed->SetBranchAddress("m_ROE", &bkg_mROE_mixed);
c_bkg_mixed->SetBranchAddress("MLP_bbar", &bkg_MLPs_mixed);


///////////////////////////Creating the new file to store the PUNZI FOM//////////////////////////
TFile *f_out = new TFile("punzi_bbar_MLP.root","RECREATE");

///////////////////////////Setting the parameter////////////////////////////
/////////amounth of data processed

Int_t entries_sig = t_sig->GetEntries();
Int_t entries_bkg_charged = c_bkg_charged->GetEntries();
Int_t entries_bkg_mixed = c_bkg_mixed->GetEntries();


Float_t processedevent = entries_sig; //1000000; //Total number of generated events

//////////amount of signal events expected
Float_t int_luminosity = 711; //fb^-1
Float_t f_charged = 1-0.486; // fraction of the upsilon decaying into b⁺b⁻
Float_t bbar_cs = 1.1e06; //fb
Float_t nBBbar = 2 * int_luminosity * bbar_cs * f_charged; // computing the number of B⁺B⁻
Float_t br_BtoKTauMu = 5e-05;  //Branching ratio of the LVF process?? 2.45e-5
Float_t br_TautoRho = 0.228; //Branching ratio retrived from Inspired
Float_t sigtheory = round(nBBbar * br_BtoKTauMu * br_TautoRho); // actual signal events expected at belle

///////////correction for the background
Float_t streams = 10;
Float_t ratio = 1.0/streams;

//////////Creating a new TTree to store relevant information
Float_t cut; // cut value ond the MLP score
Float_t sigmc; // # events categorized as signal
Float_t bkgmc; // # events categorized as background
Float_t eff_cut; // # efficiency of the signal
Float_t sig_weight; // weight of the signal
Float_t bkg_weight; // weight of the background
Float_t pun_fom; // value of the punzi fom

//names
//outline
//introduction
//10-12 slides 
// R2 >0.4


/////////////Rejection of the obvious background + outlayers
//TCut out_layers = "deltaE_Btag<1 &&  deltaE_Btag >-4 && p_ltag < 2.5 && m_ROE<4 && best_sum > -50";


TTree* tree = new TTree("tree","FOM");
tree->Branch("cut", &cut, "cut/F"); 
tree->Branch("sig_entries",&sigmc,"sig_entries/F");
tree->Branch("bkg_entries",&bkgmc,"bkg_entries/F");
tree->Branch("sig_theory",&sigtheory,"sig_theory/F");
tree->Branch("eff_cut",&eff_cut,"eff_cut/F");
tree->Branch("bkg_weight",&bkg_weight,"bkg_weight/F");
tree->Branch("sig_weight",&sig_weight,"bkg_weight/F");
tree->Branch("pun_fom",&pun_fom, "pun_fom/F");
 

float lowerrange = -0.8;
float upperrange = 0.8;
float stepsize = 0.01;
Float_t expectedsig;
Float_t sig_entries, bkg_entries; 


Float_t punzi_max = 0.0;
Float_t cut_max= 0.0;

TGraph *graph = new TGraph();
int ipoint = 0;

for (float cuts =lowerrange; cuts < upperrange; cuts+=stepsize){
  sigmc = 0;
  bkgmc = 0;
  for(int i =0; i<entries_sig; ++i){
    t_sig->GetEntry(i);
    if (sig_taumode!=1 || sig_bmode!=3 || abs(sig_mKpi - 1.864)< 0.2 || sig_mKrho <1.95 || sig_mROE > 2.15) continue;
    if (sig_MLPs<cuts) continue;
    sigmc++;
  }
   
  for(int i =0; i<entries_bkg_charged; ++i){
    c_bkg_charged->GetEntry(i);
    if (bkg_taumode_charged!=1 || bkg_bmode_charged!=3 || abs(bkg_mKpi_charged - 1.864)< 0.2 || bkg_mKrho_charged <1.95 || bkg_mROE_charged > 2.15) continue;
    if (bkg_MLPs_charged<cuts) continue;
    bkgmc++;
  } 

  for(int i =0; i<entries_bkg_mixed; ++i){
    c_bkg_mixed->GetEntry(i);
    if (bkg_taumode_mixed!=1 || bkg_bmode_mixed!=3 || abs(bkg_mKpi_mixed - 1.864)< 0.2 || bkg_mKrho_mixed <1.95 || bkg_mROE_mixed > 2.15) continue;
    if (bkg_MLPs_mixed<cuts) continue;
    bkgmc++;
  }
    
  if((sigmc + bkgmc)==0) continue;
    
  eff_cut = sigmc/processedevent; //The efficiency for the MLP at each cut on the MLP scores
  expectedsig = eff_cut*sigtheory; //The expected # of signal events in BELLE for each efficiency of the MLP
  sig_weight = expectedsig/sigmc; // Which fracction of the events simulated are we detecting 
  bkg_weight = ratio; 
  pun_fom = punji_fom(eff_cut,bkgmc,bkg_weight);
  cut = cuts;
  tree->Fill();
  std::cout << cut << " " << sigmc << " " << bkgmc << " " <<  pun_fom << std::endl;
  if (punzi_max < pun_fom){
    punzi_max = pun_fom;
    cut_max = cuts;
  }
  graph->SetPoint(ipoint,cut,pun_fom);
  ipoint++;
};

f_out->cd();
f_out->Write();

TCanvas *c1 = new TCanvas("c1", "Punzi FOM vs MLP Cut", 1024, 786);

graph->SetTitle("Punzi from; cut");
graph->SetMarkerStyle(20);
graph->SetMarkerSize(1.0);
graph->SetMarkerColor(kBlue);
graph->Draw("AP");

//Best cut for the macro (stepsize=0.03): 0.31
//Best cut for the command: 0.27



std::cout << "The optimal cut for the MLP score is: " << cut_max << std::endl;
std::cout << "Which recovers a punzi fom of: " << punzi_max << std::endl;
}