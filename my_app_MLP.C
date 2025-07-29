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
#include "TStyle.h"

////////TMVA libraries//////////
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Types.h"
#include "TMVA/Reader.h"

void app_MLP(){
/////////////////////////Defining the input files/////////////////////////// 

////////////////////////Creating TFiles with the BTD score for each entry in each TFile//////////////////////////
///////////////Loading, creating and copying the TTrees
TFile *f_in_s = new TFile("MC_data/rootfiles/signalmc_taum_mup_tightcuts.root");
TFile* f_out_s = new TFile("MC_data/MLP_continuum/MLP_signalmc_taum_mup_tightcuts.root", "RECREATE"); 

TTree* Data_s = (TTree*)f_in_s->Get("incl");
TTree* t_out_s = Data_s->CloneTree(0); //cloning the input tree

//////////////Setting the new branches for the final file

Double_t s_MLP=-1;
Double_t s_var01=-99.,s_var02=-99.,s_var03=-99.,s_var04=-99.,s_var05=-99.,s_var06=-99.,s_var07=-99.,s_var08=-99.,s_var09=-99.,s_var10=-99.,s_var11=-99.,s_var12=-99.;
Double_t s_var13=-99.,s_var14=-99.,s_var15=-99.,s_var16=-99.,s_var17=-99.,s_var18=-99.,s_var19=-99.,s_var20=-99.,s_var21=-99.,s_var22=-99.,s_var23=-99.,s_var24=-99.;
Double_t s_var25=-99.,s_var26=-99.,s_var27=-99.,s_var28=-99.,s_var29=-99.,s_var30=-99.;
    
Data_s->SetBranchAddress("CleoConeCS_1", &s_var01);
Data_s->SetBranchAddress("CleoConeCS_2", &s_var02);
Data_s->SetBranchAddress("CleoConeCS_3", &s_var03);
Data_s->SetBranchAddress("CleoConeCS_4", &s_var04);
Data_s->SetBranchAddress("CleoConeCS_5", &s_var05);
Data_s->SetBranchAddress("CleoConeCS_6", &s_var06);
Data_s->SetBranchAddress("CleoConeCS_7", &s_var07);
Data_s->SetBranchAddress("CleoConeCS_8", &s_var08);
Data_s->SetBranchAddress("CleoConeCS_9", &s_var09);
Data_s->SetBranchAddress("KSFWVariables_et", &s_var10);
Data_s->SetBranchAddress("KSFWVariables_hoo0", &s_var11);
Data_s->SetBranchAddress("KSFWVariables_hoo1", &s_var12);
Data_s->SetBranchAddress("KSFWVariables_hoo2", &s_var13);
Data_s->SetBranchAddress("KSFWVariables_hoo3", &s_var14);
Data_s->SetBranchAddress("KSFWVariables_hoo4", &s_var15);
//Data_s->SetBranchAddress("KSFWVariables_hso00", &s_var16);
Data_s->SetBranchAddress("KSFWVariables_hso01", &s_var17);
//Data_s->SetBranchAddress("KSFWVariables_hso02", &s_var18);
Data_s->SetBranchAddress("KSFWVariables_hso03", &s_var19);
Data_s->SetBranchAddress("KSFWVariables_hso04", &s_var20);
Data_s->SetBranchAddress("KSFWVariables_hso10", &s_var21);
Data_s->SetBranchAddress("KSFWVariables_hso12", &s_var22);
Data_s->SetBranchAddress("KSFWVariables_hso14", &s_var23);
Data_s->SetBranchAddress("KSFWVariables_hso20", &s_var24);
Data_s->SetBranchAddress("KSFWVariables_hso22", &s_var25);
Data_s->SetBranchAddress("KSFWVariables_hso24", &s_var26);
//Data_s->SetBranchAddress("KSFWVariables_mm2", &s_var27);
Data_s->SetBranchAddress("r2", &s_var28);
Data_s->SetBranchAddress("thrust_Bm", &s_var29);
//Data_s->SetBranchAddress("thrust_Om", &s_var30);


TBranch* MLPBranch_s = t_out_s->Branch("MLP_continuum", &s_MLP, "MLP_continuum/D"); //Creating the new branch for the MLP variable
        
/////////////////////////Setting the TMVA READER/////////////////////////
        
Float_t s_uservar01=-99.,s_uservar02=-99.,s_uservar03=-99.,s_uservar04=-99.,s_uservar05=-99.,s_uservar06=-99.,s_uservar07=-99.,s_uservar08=-99.,s_uservar09=-99.,s_uservar10=-99.;
Float_t s_uservar11=-99.,s_uservar12=-99.,s_uservar13=-99.,s_uservar14=-99.,s_uservar15=-99.,s_uservar16=-99.,s_uservar17=-99.,s_uservar18=-99.,s_uservar19=-99.,s_uservar20=-99.;
Float_t s_uservar21=-99.,s_uservar22=-99.,s_uservar23=-99.,s_uservar24=-99.,s_uservar25=-99.,s_uservar26=-99.,s_uservar27=-99.,s_uservar28=-99.,s_uservar29=-99.,s_uservar30=-99.;
    
TMVA::Reader *reader_s = new TMVA::Reader();

reader_s->AddVariable("CleoConeCS_1", &s_uservar01);
reader_s->AddVariable("CleoConeCS_2", &s_uservar02);
reader_s->AddVariable("CleoConeCS_3", &s_uservar03);
reader_s->AddVariable("CleoConeCS_4", &s_uservar04);
reader_s->AddVariable("CleoConeCS_5", &s_uservar05);
reader_s->AddVariable("CleoConeCS_6", &s_uservar06);
reader_s->AddVariable("CleoConeCS_7", &s_uservar07);
reader_s->AddVariable("CleoConeCS_8", &s_uservar08);
reader_s->AddVariable("CleoConeCS_9", &s_uservar09);
reader_s->AddVariable("KSFWVariables_et", &s_uservar10);
reader_s->AddVariable("KSFWVariables_hoo0", &s_uservar11);
reader_s->AddVariable("KSFWVariables_hoo1", &s_uservar12);
reader_s->AddVariable("KSFWVariables_hoo2", &s_uservar13);
reader_s->AddVariable("KSFWVariables_hoo3", &s_uservar14);
reader_s->AddVariable("KSFWVariables_hoo4", &s_uservar15);
//reader_s->AddVariable("KSFWVariables_hso00", &s_uservar16);
reader_s->AddVariable("KSFWVariables_hso01", &s_uservar17);
//reader_s->AddVariable("KSFWVariables_hso02", &s_uservar18);
reader_s->AddVariable("KSFWVariables_hso03", &s_uservar19);
reader_s->AddVariable("KSFWVariables_hso04", &s_uservar20);
reader_s->AddVariable("KSFWVariables_hso10", &s_uservar21);
reader_s->AddVariable("KSFWVariables_hso12", &s_uservar22);
reader_s->AddVariable("KSFWVariables_hso14", &s_uservar23);
reader_s->AddVariable("KSFWVariables_hso20", &s_uservar24);
reader_s->AddVariable("KSFWVariables_hso22", &s_uservar25);
reader_s->AddVariable("KSFWVariables_hso24", &s_uservar26);
//reader_s->AddVariable("KSFWVariables_mm2", &s_uservar27);
reader_s->AddVariable("r2", &s_uservar28);
reader_s->AddVariable("thrust_Bm", &s_uservar29);
//reader_s->AddVariable("thrust_Om", &s_uservar30);

/////////////////////Selecting the method for the prediction/////////////////////////
reader_s->BookMVA("MLP", "continuum_MLP/weights/continuum_MLP_MLP.weights.xml");
 
////////////////////////Computing MLP for each Entry/////////////////////////////
int nEnt_s = Data_s->GetEntries();
        
// ------- start your event loop
for (Long64_t ievt_s=0; ievt_s<nEnt_s; ++ievt_s) {
     Data_s->GetEntry(ievt_s);
     
     // Check for NaN values in the input variables
     if (TMath::IsNaN(s_var01)) {
        continue; // Skip this entry
     }

     s_uservar01 = s_var01;
     s_uservar02 = s_var02;
     s_uservar03 = s_var03;
     s_uservar04 = s_var04;
     s_uservar05 = s_var05;
     s_uservar06 = s_var06;
     s_uservar07 = s_var07;
     s_uservar08 = s_var08;
     s_uservar09 = s_var09;
     s_uservar10 = s_var10;
     s_uservar11 = s_var11;
     s_uservar12 = s_var12;
     s_uservar13 = s_var13;
     s_uservar14 = s_var14;
     s_uservar15 = s_var15;
     //s_uservar16 = s_var16;
     s_uservar17 = s_var17;
     //s_uservar18 = s_var18;
     s_uservar19 = s_var19;
     s_uservar20 = s_var20;
     s_uservar21 = s_var21;
     s_uservar22 = s_var22;
     s_uservar23 = s_var23;
     s_uservar24 = s_var24;
     s_uservar25 = s_var25;
     s_uservar26 = s_var26;
     //s_uservar27 = s_var27;
     s_uservar28 = s_var28;
     s_uservar29 = s_var29;
     //s_uservar30 = s_var30;
     
     s_MLP = reader_s->EvaluateMVA("MLP");
     t_out_s->Fill();
}
std::cout<<" Total number of entries for which MLP is evaluated= "<<nEnt_s<<std::endl;
f_out_s->cd();
t_out_s->Write();
delete reader_s;
f_in_s->Close();
f_out_s->Close();

 
////////////////////////Creating TFiles with the BTD score for each entry in each TFile//////////////////////////
///////////////Loading, creating and copying the TTrees

for (int i=0; i<6;i++){
     TFile *f_in_s = new TFile(Form("MC_data/rootfiles/bkg_charm_%d.root",i));
     TFile* f_out_s = new TFile(Form("MC_data/MLP_continuum/MLP_bkg_charm_%d.root",i), "RECREATE"); 
     
     TTree* Data_s = (TTree*)f_in_s->Get("incl");
     TTree* t_out_s = Data_s->CloneTree(0); //cloning the input tree
     
     //////////////Setting the new branches for the final file
     
     Double_t s_MLP=-1;
     Double_t s_var01=-99.,s_var02=-99.,s_var03=-99.,s_var04=-99.,s_var05=-99.,s_var06=-99.,s_var07=-99.,s_var08=-99.,s_var09=-99.,s_var10=-99.,s_var11=-99.,s_var12=-99.;
     Double_t s_var13=-99.,s_var14=-99.,s_var15=-99.,s_var16=-99.,s_var17=-99.,s_var18=-99.,s_var19=-99.,s_var20=-99.,s_var21=-99.,s_var22=-99.,s_var23=-99.,s_var24=-99.;
     Double_t s_var25=-99.,s_var26=-99.,s_var27=-99.,s_var28=-99.,s_var29=-99.,s_var30=-99.;
     
     Data_s->SetBranchAddress("CleoConeCS_1", &s_var01);
     Data_s->SetBranchAddress("CleoConeCS_2", &s_var02);
     Data_s->SetBranchAddress("CleoConeCS_3", &s_var03);
     Data_s->SetBranchAddress("CleoConeCS_4", &s_var04);
     Data_s->SetBranchAddress("CleoConeCS_5", &s_var05);
     Data_s->SetBranchAddress("CleoConeCS_6", &s_var06);
     Data_s->SetBranchAddress("CleoConeCS_7", &s_var07);
     Data_s->SetBranchAddress("CleoConeCS_8", &s_var08);
     Data_s->SetBranchAddress("CleoConeCS_9", &s_var09);
     Data_s->SetBranchAddress("KSFWVariables_et", &s_var10);
     Data_s->SetBranchAddress("KSFWVariables_hoo0", &s_var11);
     Data_s->SetBranchAddress("KSFWVariables_hoo1", &s_var12);
     Data_s->SetBranchAddress("KSFWVariables_hoo2", &s_var13);
     Data_s->SetBranchAddress("KSFWVariables_hoo3", &s_var14);
     Data_s->SetBranchAddress("KSFWVariables_hoo4", &s_var15);
     //Data_s->SetBranchAddress("KSFWVariables_hso00", &s_var16);
     Data_s->SetBranchAddress("KSFWVariables_hso01", &s_var17);
     //Data_s->SetBranchAddress("KSFWVariables_hso02", &s_var18);
     Data_s->SetBranchAddress("KSFWVariables_hso03", &s_var19);
     Data_s->SetBranchAddress("KSFWVariables_hso04", &s_var20);
     Data_s->SetBranchAddress("KSFWVariables_hso10", &s_var21);
     Data_s->SetBranchAddress("KSFWVariables_hso12", &s_var22);
     Data_s->SetBranchAddress("KSFWVariables_hso14", &s_var23);
     Data_s->SetBranchAddress("KSFWVariables_hso20", &s_var24);
     Data_s->SetBranchAddress("KSFWVariables_hso22", &s_var25);
     Data_s->SetBranchAddress("KSFWVariables_hso24", &s_var26);
     //Data_s->SetBranchAddress("KSFWVariables_mm2", &s_var27);
     Data_s->SetBranchAddress("r2", &s_var28);
     Data_s->SetBranchAddress("thrust_Bm", &s_var29);
     //Data_s->SetBranchAddress("thrust_Om", &s_var30);
     
     
     TBranch* MLPBranch_s = t_out_s->Branch("MLP_continuum", &s_MLP, "MLP_continuum/D"); //Creating the new branch for the MLP variable
             
     /////////////////////////Setting the TMVA READER/////////////////////////
             
     Float_t s_uservar01=-99.,s_uservar02=-99.,s_uservar03=-99.,s_uservar04=-99.,s_uservar05=-99.,s_uservar06=-99.,s_uservar07=-99.,s_uservar08=-99.,s_uservar09=-99.,s_uservar10=-99.;
     Float_t s_uservar11=-99.,s_uservar12=-99.,s_uservar13=-99.,s_uservar14=-99.,s_uservar15=-99.,s_uservar16=-99.,s_uservar17=-99.,s_uservar18=-99.,s_uservar19=-99.,s_uservar20=-99.;
     Float_t s_uservar21=-99.,s_uservar22=-99.,s_uservar23=-99.,s_uservar24=-99.,s_uservar25=-99.,s_uservar26=-99.,s_uservar27=-99.,s_uservar28=-99.,s_uservar29=-99.,s_uservar30=-99.;
     
     TMVA::Reader *reader_s = new TMVA::Reader();
     
     reader_s->AddVariable("CleoConeCS_1", &s_uservar01);
     reader_s->AddVariable("CleoConeCS_2", &s_uservar02);
     reader_s->AddVariable("CleoConeCS_3", &s_uservar03);
     reader_s->AddVariable("CleoConeCS_4", &s_uservar04);
     reader_s->AddVariable("CleoConeCS_5", &s_uservar05);
     reader_s->AddVariable("CleoConeCS_6", &s_uservar06);
     reader_s->AddVariable("CleoConeCS_7", &s_uservar07);
     reader_s->AddVariable("CleoConeCS_8", &s_uservar08);
     reader_s->AddVariable("CleoConeCS_9", &s_uservar09);
     reader_s->AddVariable("KSFWVariables_et", &s_uservar10);
     reader_s->AddVariable("KSFWVariables_hoo0", &s_uservar11);
     reader_s->AddVariable("KSFWVariables_hoo1", &s_uservar12);
     reader_s->AddVariable("KSFWVariables_hoo2", &s_uservar13);
     reader_s->AddVariable("KSFWVariables_hoo3", &s_uservar14);
     reader_s->AddVariable("KSFWVariables_hoo4", &s_uservar15);
     //reader_s->AddVariable("KSFWVariables_hso00", &s_uservar16);
     reader_s->AddVariable("KSFWVariables_hso01", &s_uservar17);
     //reader_s->AddVariable("KSFWVariables_hso02", &s_uservar18);
     reader_s->AddVariable("KSFWVariables_hso03", &s_uservar19);
     reader_s->AddVariable("KSFWVariables_hso04", &s_uservar20);
     reader_s->AddVariable("KSFWVariables_hso10", &s_uservar21);
     reader_s->AddVariable("KSFWVariables_hso12", &s_uservar22);
     reader_s->AddVariable("KSFWVariables_hso14", &s_uservar23);
     reader_s->AddVariable("KSFWVariables_hso20", &s_uservar24);
     reader_s->AddVariable("KSFWVariables_hso22", &s_uservar25);
     reader_s->AddVariable("KSFWVariables_hso24", &s_uservar26);
     //reader_s->AddVariable("KSFWVariables_mm2", &s_uservar27);
     reader_s->AddVariable("r2", &s_uservar28);
     reader_s->AddVariable("thrust_Bm", &s_uservar29);
     //reader_s->AddVariable("thrust_Om", &s_uservar30);
     
     /////////////////////Selecting the method for the prediction/////////////////////////
     reader_s->BookMVA("MLP", "continuum_MLP/weights/continuum_MLP_MLP.weights.xml");
     
     ////////////////////////Computing MLP for each Entry/////////////////////////////
     int nEnt_s = Data_s->GetEntries();
             
     // ------- start your event loop
     for (Long64_t ievt_s=0; ievt_s<nEnt_s; ++ievt_s) {
          Data_s->GetEntry(ievt_s);
     
          // Check for NaN values in the input variables
          if (TMath::IsNaN(s_var01)) {
             continue; // Skip this entry
          }
     
          s_uservar01 = s_var01;
          s_uservar02 = s_var02;
          s_uservar03 = s_var03;
          s_uservar04 = s_var04;
          s_uservar05 = s_var05;
          s_uservar06 = s_var06;
          s_uservar07 = s_var07;
          s_uservar08 = s_var08;
          s_uservar09 = s_var09;
          s_uservar10 = s_var10;
          s_uservar11 = s_var11;
          s_uservar12 = s_var12;
          s_uservar13 = s_var13;
          s_uservar14 = s_var14;
          s_uservar15 = s_var15;
          //s_uservar16 = s_var16;
          s_uservar17 = s_var17;
          //s_uservar18 = s_var18;
          s_uservar19 = s_var19;
          s_uservar20 = s_var20;
          s_uservar21 = s_var21;
          s_uservar22 = s_var22;
          s_uservar23 = s_var23;
          s_uservar24 = s_var24;
          s_uservar25 = s_var25;
          s_uservar26 = s_var26;
          //s_uservar27 = s_var27;
          s_uservar28 = s_var28;
          s_uservar29 = s_var29;
          //s_uservar30 = s_var30;
          
          s_MLP = reader_s->EvaluateMVA("MLP");
          t_out_s->Fill();
     }
     std::cout<<" Total number of entries for which MLP is evaluated= "<<nEnt_s<<std::endl;
     f_out_s->cd();
     t_out_s->Write();
     delete reader_s;
     f_in_s->Close();
     f_out_s->Close();
     }


////////////////////////Creating TFiles with the BTD score for each entry in each TFile//////////////////////////
///////////////Loading, creating and copying the TTrees

for (int i=0; i<6;i++){
     TFile *f_in_s = new TFile(Form("MC_data/rootfiles/bkg_uds_%d.root",i));
     TFile* f_out_s = new TFile(Form("MC_data/MLP_continuum/MLP_bkg_uds_%d.root",i), "RECREATE"); 
     
     TTree* Data_s = (TTree*)f_in_s->Get("incl");
     TTree* t_out_s = Data_s->CloneTree(0); //cloning the input tree
     
     //////////////Setting the new branches for the final file
     
     Double_t s_MLP=-1;
     Double_t s_var01=-99.,s_var02=-99.,s_var03=-99.,s_var04=-99.,s_var05=-99.,s_var06=-99.,s_var07=-99.,s_var08=-99.,s_var09=-99.,s_var10=-99.,s_var11=-99.,s_var12=-99.;
     Double_t s_var13=-99.,s_var14=-99.,s_var15=-99.,s_var16=-99.,s_var17=-99.,s_var18=-99.,s_var19=-99.,s_var20=-99.,s_var21=-99.,s_var22=-99.,s_var23=-99.,s_var24=-99.;
     Double_t s_var25=-99.,s_var26=-99.,s_var27=-99.,s_var28=-99.,s_var29=-99.,s_var30=-99.;
     
     Data_s->SetBranchAddress("CleoConeCS_1", &s_var01);
     Data_s->SetBranchAddress("CleoConeCS_2", &s_var02);
     Data_s->SetBranchAddress("CleoConeCS_3", &s_var03);
     Data_s->SetBranchAddress("CleoConeCS_4", &s_var04);
     Data_s->SetBranchAddress("CleoConeCS_5", &s_var05);
     Data_s->SetBranchAddress("CleoConeCS_6", &s_var06);
     Data_s->SetBranchAddress("CleoConeCS_7", &s_var07);
     Data_s->SetBranchAddress("CleoConeCS_8", &s_var08);
     Data_s->SetBranchAddress("CleoConeCS_9", &s_var09);
     Data_s->SetBranchAddress("KSFWVariables_et", &s_var10);
     Data_s->SetBranchAddress("KSFWVariables_hoo0", &s_var11);
     Data_s->SetBranchAddress("KSFWVariables_hoo1", &s_var12);
     Data_s->SetBranchAddress("KSFWVariables_hoo2", &s_var13);
     Data_s->SetBranchAddress("KSFWVariables_hoo3", &s_var14);
     Data_s->SetBranchAddress("KSFWVariables_hoo4", &s_var15);
     //Data_s->SetBranchAddress("KSFWVariables_hso00", &s_var16);
     Data_s->SetBranchAddress("KSFWVariables_hso01", &s_var17);
     //Data_s->SetBranchAddress("KSFWVariables_hso02", &s_var18);
     Data_s->SetBranchAddress("KSFWVariables_hso03", &s_var19);
     Data_s->SetBranchAddress("KSFWVariables_hso04", &s_var20);
     Data_s->SetBranchAddress("KSFWVariables_hso10", &s_var21);
     Data_s->SetBranchAddress("KSFWVariables_hso12", &s_var22);
     Data_s->SetBranchAddress("KSFWVariables_hso14", &s_var23);
     Data_s->SetBranchAddress("KSFWVariables_hso20", &s_var24);
     Data_s->SetBranchAddress("KSFWVariables_hso22", &s_var25);
     Data_s->SetBranchAddress("KSFWVariables_hso24", &s_var26);
     //Data_s->SetBranchAddress("KSFWVariables_mm2", &s_var27);
     Data_s->SetBranchAddress("r2", &s_var28);
     Data_s->SetBranchAddress("thrust_Bm", &s_var29);
     //Data_s->SetBranchAddress("thrust_Om", &s_var30);
     
     
     TBranch* MLPBranch_s = t_out_s->Branch("MLP_continuum", &s_MLP, "MLP_continuum/D"); //Creating the new branch for the MLP variable
             
     /////////////////////////Setting the TMVA READER/////////////////////////
             
     Float_t s_uservar01=-99.,s_uservar02=-99.,s_uservar03=-99.,s_uservar04=-99.,s_uservar05=-99.,s_uservar06=-99.,s_uservar07=-99.,s_uservar08=-99.,s_uservar09=-99.,s_uservar10=-99.;
     Float_t s_uservar11=-99.,s_uservar12=-99.,s_uservar13=-99.,s_uservar14=-99.,s_uservar15=-99.,s_uservar16=-99.,s_uservar17=-99.,s_uservar18=-99.,s_uservar19=-99.,s_uservar20=-99.;
     Float_t s_uservar21=-99.,s_uservar22=-99.,s_uservar23=-99.,s_uservar24=-99.,s_uservar25=-99.,s_uservar26=-99.,s_uservar27=-99.,s_uservar28=-99.,s_uservar29=-99.,s_uservar30=-99.;
     
     TMVA::Reader *reader_s = new TMVA::Reader();
     
     reader_s->AddVariable("CleoConeCS_1", &s_uservar01);
     reader_s->AddVariable("CleoConeCS_2", &s_uservar02);
     reader_s->AddVariable("CleoConeCS_3", &s_uservar03);
     reader_s->AddVariable("CleoConeCS_4", &s_uservar04);
     reader_s->AddVariable("CleoConeCS_5", &s_uservar05);
     reader_s->AddVariable("CleoConeCS_6", &s_uservar06);
     reader_s->AddVariable("CleoConeCS_7", &s_uservar07);
     reader_s->AddVariable("CleoConeCS_8", &s_uservar08);
     reader_s->AddVariable("CleoConeCS_9", &s_uservar09);
     reader_s->AddVariable("KSFWVariables_et", &s_uservar10);
     reader_s->AddVariable("KSFWVariables_hoo0", &s_uservar11);
     reader_s->AddVariable("KSFWVariables_hoo1", &s_uservar12);
     reader_s->AddVariable("KSFWVariables_hoo2", &s_uservar13);
     reader_s->AddVariable("KSFWVariables_hoo3", &s_uservar14);
     reader_s->AddVariable("KSFWVariables_hoo4", &s_uservar15);
     //reader_s->AddVariable("KSFWVariables_hso00", &s_uservar16);
     reader_s->AddVariable("KSFWVariables_hso01", &s_uservar17);
     //reader_s->AddVariable("KSFWVariables_hso02", &s_uservar18);
     reader_s->AddVariable("KSFWVariables_hso03", &s_uservar19);
     reader_s->AddVariable("KSFWVariables_hso04", &s_uservar20);
     reader_s->AddVariable("KSFWVariables_hso10", &s_uservar21);
     reader_s->AddVariable("KSFWVariables_hso12", &s_uservar22);
     reader_s->AddVariable("KSFWVariables_hso14", &s_uservar23);
     reader_s->AddVariable("KSFWVariables_hso20", &s_uservar24);
     reader_s->AddVariable("KSFWVariables_hso22", &s_uservar25);
     reader_s->AddVariable("KSFWVariables_hso24", &s_uservar26);
     //reader_s->AddVariable("KSFWVariables_mm2", &s_uservar27);
     reader_s->AddVariable("r2", &s_uservar28);
     reader_s->AddVariable("thrust_Bm", &s_uservar29);
     //reader_s->AddVariable("thrust_Om", &s_uservar30);
     
     /////////////////////Selecting the method for the prediction/////////////////////////
     reader_s->BookMVA("MLP", "continuum_MLP/weights/continuum_MLP_MLP.weights.xml");
     
     ////////////////////////Computing MLP for each Entry/////////////////////////////
     int nEnt_s = Data_s->GetEntries();
             
     // ------- start your event loop
     for (Long64_t ievt_s=0; ievt_s<nEnt_s; ++ievt_s) {
          Data_s->GetEntry(ievt_s);
     
          // Check for NaN values in the input variables
          if (TMath::IsNaN(s_var01)) {
             continue; // Skip this entry
          }
     
          s_uservar01 = s_var01;
          s_uservar02 = s_var02;
          s_uservar03 = s_var03;
          s_uservar04 = s_var04;
          s_uservar05 = s_var05;
          s_uservar06 = s_var06;
          s_uservar07 = s_var07;
          s_uservar08 = s_var08;
          s_uservar09 = s_var09;
          s_uservar10 = s_var10;
          s_uservar11 = s_var11;
          s_uservar12 = s_var12;
          s_uservar13 = s_var13;
          s_uservar14 = s_var14;
          s_uservar15 = s_var15;
          //s_uservar16 = s_var16;
          s_uservar17 = s_var17;
          //s_uservar18 = s_var18;
          s_uservar19 = s_var19;
          s_uservar20 = s_var20;
          s_uservar21 = s_var21;
          s_uservar22 = s_var22;
          s_uservar23 = s_var23;
          s_uservar24 = s_var24;
          s_uservar25 = s_var25;
          s_uservar26 = s_var26;
          //s_uservar27 = s_var27;
          s_uservar28 = s_var28;
          s_uservar29 = s_var29;
          //s_uservar30 = s_var30;
          
          s_MLP = reader_s->EvaluateMVA("MLP");
          t_out_s->Fill();
     }
     std::cout<<" Total number of entries for which MLP is evaluated= "<<nEnt_s<<std::endl;
     f_out_s->cd();
     t_out_s->Write();
     delete reader_s;
     f_in_s->Close();
     f_out_s->Close();
     }


////////////////////////Creating TFiles with the BTD score for each entry in each TFile//////////////////////////
///////////////Loading, creating and copying the TTrees

for (int i=0; i<10;i++){
     TFile *f_in_s = new TFile(Form("MC_data/rootfiles/bkg_charged_%d.root",i));
     TFile* f_out_s = new TFile(Form("MC_data/MLP_continuum/MLP_bkg_charged_%d.root",i), "RECREATE"); 
     
     TTree* Data_s = (TTree*)f_in_s->Get("incl");
     TTree* t_out_s = Data_s->CloneTree(0); //cloning the input tree
     
     //////////////Setting the new branches for the final file
     
     Double_t s_MLP=-1;
     Double_t s_var01=-99.,s_var02=-99.,s_var03=-99.,s_var04=-99.,s_var05=-99.,s_var06=-99.,s_var07=-99.,s_var08=-99.,s_var09=-99.,s_var10=-99.,s_var11=-99.,s_var12=-99.;
     Double_t s_var13=-99.,s_var14=-99.,s_var15=-99.,s_var16=-99.,s_var17=-99.,s_var18=-99.,s_var19=-99.,s_var20=-99.,s_var21=-99.,s_var22=-99.,s_var23=-99.,s_var24=-99.;
     Double_t s_var25=-99.,s_var26=-99.,s_var27=-99.,s_var28=-99.,s_var29=-99.,s_var30=-99.;
     
     Data_s->SetBranchAddress("CleoConeCS_1", &s_var01);
     Data_s->SetBranchAddress("CleoConeCS_2", &s_var02);
     Data_s->SetBranchAddress("CleoConeCS_3", &s_var03);
     Data_s->SetBranchAddress("CleoConeCS_4", &s_var04);
     Data_s->SetBranchAddress("CleoConeCS_5", &s_var05);
     Data_s->SetBranchAddress("CleoConeCS_6", &s_var06);
     Data_s->SetBranchAddress("CleoConeCS_7", &s_var07);
     Data_s->SetBranchAddress("CleoConeCS_8", &s_var08);
     Data_s->SetBranchAddress("CleoConeCS_9", &s_var09);
     Data_s->SetBranchAddress("KSFWVariables_et", &s_var10);
     Data_s->SetBranchAddress("KSFWVariables_hoo0", &s_var11);
     Data_s->SetBranchAddress("KSFWVariables_hoo1", &s_var12);
     Data_s->SetBranchAddress("KSFWVariables_hoo2", &s_var13);
     Data_s->SetBranchAddress("KSFWVariables_hoo3", &s_var14);
     Data_s->SetBranchAddress("KSFWVariables_hoo4", &s_var15);
     //Data_s->SetBranchAddress("KSFWVariables_hso00", &s_var16);
     Data_s->SetBranchAddress("KSFWVariables_hso01", &s_var17);
     //Data_s->SetBranchAddress("KSFWVariables_hso02", &s_var18);
     Data_s->SetBranchAddress("KSFWVariables_hso03", &s_var19);
     Data_s->SetBranchAddress("KSFWVariables_hso04", &s_var20);
     Data_s->SetBranchAddress("KSFWVariables_hso10", &s_var21);
     Data_s->SetBranchAddress("KSFWVariables_hso12", &s_var22);
     Data_s->SetBranchAddress("KSFWVariables_hso14", &s_var23);
     Data_s->SetBranchAddress("KSFWVariables_hso20", &s_var24);
     Data_s->SetBranchAddress("KSFWVariables_hso22", &s_var25);
     Data_s->SetBranchAddress("KSFWVariables_hso24", &s_var26);
     //Data_s->SetBranchAddress("KSFWVariables_mm2", &s_var27);
     Data_s->SetBranchAddress("r2", &s_var28);
     Data_s->SetBranchAddress("thrust_Bm", &s_var29);
     //Data_s->SetBranchAddress("thrust_Om", &s_var30);
     
     
     TBranch* MLPBranch_s = t_out_s->Branch("MLP_continuum", &s_MLP, "MLP_continuum/D"); //Creating the new branch for the MLP variable
             
     /////////////////////////Setting the TMVA READER/////////////////////////
             
     Float_t s_uservar01=-99.,s_uservar02=-99.,s_uservar03=-99.,s_uservar04=-99.,s_uservar05=-99.,s_uservar06=-99.,s_uservar07=-99.,s_uservar08=-99.,s_uservar09=-99.,s_uservar10=-99.;
     Float_t s_uservar11=-99.,s_uservar12=-99.,s_uservar13=-99.,s_uservar14=-99.,s_uservar15=-99.,s_uservar16=-99.,s_uservar17=-99.,s_uservar18=-99.,s_uservar19=-99.,s_uservar20=-99.;
     Float_t s_uservar21=-99.,s_uservar22=-99.,s_uservar23=-99.,s_uservar24=-99.,s_uservar25=-99.,s_uservar26=-99.,s_uservar27=-99.,s_uservar28=-99.,s_uservar29=-99.,s_uservar30=-99.;
     
     TMVA::Reader *reader_s = new TMVA::Reader();
     
     reader_s->AddVariable("CleoConeCS_1", &s_uservar01);
     reader_s->AddVariable("CleoConeCS_2", &s_uservar02);
     reader_s->AddVariable("CleoConeCS_3", &s_uservar03);
     reader_s->AddVariable("CleoConeCS_4", &s_uservar04);
     reader_s->AddVariable("CleoConeCS_5", &s_uservar05);
     reader_s->AddVariable("CleoConeCS_6", &s_uservar06);
     reader_s->AddVariable("CleoConeCS_7", &s_uservar07);
     reader_s->AddVariable("CleoConeCS_8", &s_uservar08);
     reader_s->AddVariable("CleoConeCS_9", &s_uservar09);
     reader_s->AddVariable("KSFWVariables_et", &s_uservar10);
     reader_s->AddVariable("KSFWVariables_hoo0", &s_uservar11);
     reader_s->AddVariable("KSFWVariables_hoo1", &s_uservar12);
     reader_s->AddVariable("KSFWVariables_hoo2", &s_uservar13);
     reader_s->AddVariable("KSFWVariables_hoo3", &s_uservar14);
     reader_s->AddVariable("KSFWVariables_hoo4", &s_uservar15);
     //reader_s->AddVariable("KSFWVariables_hso00", &s_uservar16);
     reader_s->AddVariable("KSFWVariables_hso01", &s_uservar17);
     //reader_s->AddVariable("KSFWVariables_hso02", &s_uservar18);
     reader_s->AddVariable("KSFWVariables_hso03", &s_uservar19);
     reader_s->AddVariable("KSFWVariables_hso04", &s_uservar20);
     reader_s->AddVariable("KSFWVariables_hso10", &s_uservar21);
     reader_s->AddVariable("KSFWVariables_hso12", &s_uservar22);
     reader_s->AddVariable("KSFWVariables_hso14", &s_uservar23);
     reader_s->AddVariable("KSFWVariables_hso20", &s_uservar24);
     reader_s->AddVariable("KSFWVariables_hso22", &s_uservar25);
     reader_s->AddVariable("KSFWVariables_hso24", &s_uservar26);
     //reader_s->AddVariable("KSFWVariables_mm2", &s_uservar27);
     reader_s->AddVariable("r2", &s_uservar28);
     reader_s->AddVariable("thrust_Bm", &s_uservar29);
     //reader_s->AddVariable("thrust_Om", &s_uservar30);
     
     /////////////////////Selecting the method for the prediction/////////////////////////
     reader_s->BookMVA("MLP", "continuum_MLP/weights/continuum_MLP_MLP.weights.xml");
     
     ////////////////////////Computing MLP for each Entry/////////////////////////////
     int nEnt_s = Data_s->GetEntries();
             
     // ------- start your event loop
     for (Long64_t ievt_s=0; ievt_s<nEnt_s; ++ievt_s) {
          Data_s->GetEntry(ievt_s);
     
          // Check for NaN values in the input variables
          if (TMath::IsNaN(s_var01)) {
             continue; // Skip this entry
          }
     
          s_uservar01 = s_var01;
          s_uservar02 = s_var02;
          s_uservar03 = s_var03;
          s_uservar04 = s_var04;
          s_uservar05 = s_var05;
          s_uservar06 = s_var06;
          s_uservar07 = s_var07;
          s_uservar08 = s_var08;
          s_uservar09 = s_var09;
          s_uservar10 = s_var10;
          s_uservar11 = s_var11;
          s_uservar12 = s_var12;
          s_uservar13 = s_var13;
          s_uservar14 = s_var14;
          s_uservar15 = s_var15;
          //s_uservar16 = s_var16;
          s_uservar17 = s_var17;
          //s_uservar18 = s_var18;
          s_uservar19 = s_var19;
          s_uservar20 = s_var20;
          s_uservar21 = s_var21;
          s_uservar22 = s_var22;
          s_uservar23 = s_var23;
          s_uservar24 = s_var24;
          s_uservar25 = s_var25;
          s_uservar26 = s_var26;
          //s_uservar27 = s_var27;
          s_uservar28 = s_var28;
          s_uservar29 = s_var29;
          //s_uservar30 = s_var30;
          
          s_MLP = reader_s->EvaluateMVA("MLP");
          t_out_s->Fill();
     }
     std::cout<<" Total number of entries for which MLP is evaluated= "<<nEnt_s<<std::endl;
     f_out_s->cd();
     t_out_s->Write();
     delete reader_s;
     f_in_s->Close();
     f_out_s->Close();
     }    
     
     
////////////////////////Creating TFiles with the BTD score for each entry in each TFile//////////////////////////
///////////////Loading, creating and copying the TTrees

for (int i=0; i<10;i++){
     TFile *f_in_s = new TFile(Form("MC_data/rootfiles/bkg_mixed_%d.root",i));
     TFile* f_out_s = new TFile(Form("MC_data/MLP_continuum/MLP_bkg_mixed_%d.root",i), "RECREATE"); 
     
     TTree* Data_s = (TTree*)f_in_s->Get("incl");
     TTree* t_out_s = Data_s->CloneTree(0); //cloning the input tree
     
     //////////////Setting the new branches for the final file
     
     Double_t s_MLP=-1;
     Double_t s_var01=-99.,s_var02=-99.,s_var03=-99.,s_var04=-99.,s_var05=-99.,s_var06=-99.,s_var07=-99.,s_var08=-99.,s_var09=-99.,s_var10=-99.,s_var11=-99.,s_var12=-99.;
     Double_t s_var13=-99.,s_var14=-99.,s_var15=-99.,s_var16=-99.,s_var17=-99.,s_var18=-99.,s_var19=-99.,s_var20=-99.,s_var21=-99.,s_var22=-99.,s_var23=-99.,s_var24=-99.;
     Double_t s_var25=-99.,s_var26=-99.,s_var27=-99.,s_var28=-99.,s_var29=-99.,s_var30=-99.;
     
     Data_s->SetBranchAddress("CleoConeCS_1", &s_var01);
     Data_s->SetBranchAddress("CleoConeCS_2", &s_var02);
     Data_s->SetBranchAddress("CleoConeCS_3", &s_var03);
     Data_s->SetBranchAddress("CleoConeCS_4", &s_var04);
     Data_s->SetBranchAddress("CleoConeCS_5", &s_var05);
     Data_s->SetBranchAddress("CleoConeCS_6", &s_var06);
     Data_s->SetBranchAddress("CleoConeCS_7", &s_var07);
     Data_s->SetBranchAddress("CleoConeCS_8", &s_var08);
     Data_s->SetBranchAddress("CleoConeCS_9", &s_var09);
     Data_s->SetBranchAddress("KSFWVariables_et", &s_var10);
     Data_s->SetBranchAddress("KSFWVariables_hoo0", &s_var11);
     Data_s->SetBranchAddress("KSFWVariables_hoo1", &s_var12);
     Data_s->SetBranchAddress("KSFWVariables_hoo2", &s_var13);
     Data_s->SetBranchAddress("KSFWVariables_hoo3", &s_var14);
     Data_s->SetBranchAddress("KSFWVariables_hoo4", &s_var15);
     //Data_s->SetBranchAddress("KSFWVariables_hso00", &s_var16);
     Data_s->SetBranchAddress("KSFWVariables_hso01", &s_var17);
     //Data_s->SetBranchAddress("KSFWVariables_hso02", &sMLP_continuum_var18);
     Data_s->SetBranchAddress("KSFWVariables_hso0punzi.C3", &s_var19);
     Data_s->SetBranchAddress("KSFWVariables_hso04", &s_var20);
     Data_s->SetBranchAddress("KSFWVariables_hso10", &s_var21);
     Data_s->SetBranchAddress("KSFWVariables_hso12", &s_var22);
     Data_s->SetBranchAddress("KSFWVariables_hso14", &s_var23);
     Data_s->SetBranchAddress("KSFWVariables_hso20", &s_var24);
     Data_s->SetBranchAddress("KSFWVariables_hso22", &s_var25);
     Data_s->SetBranchAddress("KSFWVariables_hso24", &s_var26);
     //Data_s->SetBranchAddress("KSFWVariables_mm2", &s_var27);
     Data_s->SetBranchAddress("r2", &s_var28);
     Data_s->SetBranchAddress("thrust_Bm", &s_var29);
     //Data_s->SetBranchAddress("thrust_Om", &s_var30);
     
     
     TBranch* MLPBranch_s = t_out_s->Branch("MLP_continuum", &s_MLP, "MLP_continuum/D"); //Creating the new branch for the MLP variable
             
     /////////////////////////Setting the TMVA READER/////////////////////////
             
     Float_t s_uservar01=-99.,s_uservar02=-99.,s_uservar03=-99.,s_uservar04=-99.,s_uservar05=-99.,s_uservar06=-99.,s_uservar07=-99.,s_uservar08=-99.,s_uservar09=-99.,s_uservar10=-99.;
     Float_t s_uservar11=-99.,s_uservar12=-99.,s_uservar13=-99.,s_uservar14=-99.,s_uservar15=-99.,s_uservar16=-99.,s_uservar17=-99.,s_uservar18=-99.,s_uservar19=-99.,s_uservar20=-99.;
     Float_t s_uservar21=-99.,s_uservar22=-99.,s_uservar23=-99.,s_uservar24=-99.,s_uservar25=-99.,s_uservar26=-99.,s_uservar27=-99.,s_uservar28=-99.,s_uservar29=-99.,s_uservar30=-99.;
     
     TMVA::Reader *reader_s = new TMVA::Reader();
     
     reader_s->AddVariable("CleoConeCS_1", &s_uservar01);
     reader_s->AddVariable("CleoConeCS_2", &s_uservar02);
     reader_s->AddVariable("CleoConeCS_3", &s_uservar03);
     reader_s->AddVariable("CleoConeCS_4", &s_uservar04);
     reader_s->AddVariable("CleoConeCS_5", &s_uservar05);
     reader_s->AddVariable("CleoConeCS_6", &s_uservar06);
     reader_s->AddVariable("CleoConeCS_7", &s_uservar07);
     reader_s->AddVariable("CleoConeCS_8", &s_uservar08);
     reader_s->AddVariable("CleoConeCS_9", &s_uservar09);
     reader_s->AddVariable("KSFWVariables_et", &s_uservar10);
     reader_s->AddVariable("KSFWVariables_hoo0", &s_uservar11);
     reader_s->AddVariable("KSFWVariables_hoo1", &s_uservar12);
     reader_s->AddVariable("KSFWVariables_hoo2", &s_uservar13);
     reader_s->AddVariable("KSFWVariables_hoo3", &s_uservar14);
     reader_s->AddVariable("KSFWVariables_hoo4", &s_uservar15);
     //reader_s->AddVariable("KSFWVariables_hso00", &s_uservar16);
     reader_s->AddVariable("KSFWVariables_hso01", &s_uservar17);
     //reader_s->AddVariable("KSFWVariables_hso02", &s_uservar18);
     reader_s->AddVariable("KSFWVariables_hso03", &s_uservar19);
     reader_s->AddVariable("KSFWVariables_hso04", &s_uservar20);
     reader_s->AddVariable("KSFWVariables_hso10", &s_uservar21);
     reader_s->AddVariable("KSFWVariables_hso12", &s_uservar22);
     reader_s->AddVariable("KSFWVariables_hso14", &s_uservar23);
     reader_s->AddVariable("KSFWVariables_hso20", &s_uservar24);
     reader_s->AddVariable("KSFWVariables_hso22", &s_uservar25);
     reader_s->AddVariable("KSFWVariables_hso24", &s_uservar26);
     //reader_s->AddVariable("KSFWVariables_mm2", &s_uservar27);
     reader_s->AddVariable("r2", &s_uservar28);
     reader_s->AddVariable("thrust_Bm", &s_uservar29);
     //reader_s->AddVariable("thrust_Om", &s_uservar30);
     
     /////////////////////Selecting the method for the prediction/////////////////////////
     reader_s->BookMVA("MLP", "continuum_MLP/weights/continuum_MLP_MLP.weights.xml");
     
     ////////////////////////Computing MLP for each Entry/////////////////////////////
     int nEnt_s = Data_s->GetEntries();
             
     // ------- start your event loop
     for (Long64_t ievt_s=0; ievt_s<nEnt_s; ++ievt_s) {
          Data_s->GetEntry(ievt_s);
     
          // Check for NaN values in the input variables
          if (TMath::IsNaN(s_var01)) {
             continue; // Skip this entry
          }
     
          s_uservar01 = s_var01;
          s_uservar02 = s_var02;
          s_uservar03 = s_var03;
          s_uservar04 = s_var04;
          s_uservar05 = s_var05;
          s_uservar06 = s_var06;
          s_uservar07 = s_var07;
          s_uservar08 = s_var08;
          s_uservar09 = s_var09;
          s_uservar10 = s_var10;
          s_uservar11 = s_var11;
          s_uservar12 = s_var12;
          s_uservar13 = s_var13;
          s_uservar14 = s_var14;
          s_uservar15 = s_var15;
          //s_uservar16 = s_var16;
          s_uservar17 = s_var17;
          //s_uservar18 = s_var18;
          s_uservar19 = s_var19;
          s_uservar20 = s_var20;
          s_uservar21 = s_var21;
          s_uservar22 = s_var22;
          s_uservar23 = s_var23;
          s_uservar24 = s_var24;
          s_uservar25 = s_var25;
          s_uservar26 = s_var26;
          //s_uservar27 = s_var27;
          s_uservar28 = s_var28;
          s_uservar29 = s_var29;
          //s_uservar30 = s_var30;
          
          s_MLP = reader_s->EvaluateMVA("MLP");
          t_out_s->Fill();
     }
     std::cout<<" Total number of entries for which MLP is evaluated= "<<nEnt_s<<std::endl;
     f_out_s->cd();
     t_out_s->Write();
     delete reader_s;
     f_in_s->Close();
     f_out_s->Close();
     }
}



void plot_MLP() {
  // Enable statistics display
  gStyle->SetOptStat(1111); // Show entries, mean, RMS, etc.
  gStyle->SetStatW(0.15);   // Stats box width
  gStyle->SetStatH(0.15);   // Stats box height

  // Define input files and histogram properties
  TFile *f_sig = new TFile("MC_data/MLP_continuum/MLP_signalmc_taum_mup_tightcuts.root");

  TFile *f_bkg_uds0 = new TFile("MC_data/MLP_continuum/MLP_bkg_uds_0.root");
  TFile *f_bkg_uds1 = new TFile("MC_data/MLP_continuum/MLP_bkg_uds_1.root");
  TFile *f_bkg_uds2 = new TFile("MC_data/MLP_continuum/MLP_bkg_uds_2.root");
  TFile *f_bkg_uds3 = new TFile("MC_data/MLP_continuum/MLP_bkg_uds_3.root");
  TFile *f_bkg_uds4 = new TFile("MC_data/MLP_continuum/MLP_bkg_uds_4.root");
  TFile *f_bkg_uds5 = new TFile("MC_data/MLP_continuum/MLP_bkg_uds_5.root");

  TFile *f_bkg_charm0 = new TFile("MC_data/MLP_continuum/MLP_bkg_charm_0.root");
  TFile *f_bkg_charm1 = new TFile("MC_data/MLP_continuum/MLP_bkg_charm_1.root");
  TFile *f_bkg_charm2 = new TFile("MC_data/MLP_continuum/MLP_bkg_charm_2.root");
  TFile *f_bkg_charm3 = new TFile("MC_data/MLP_continuum/MLP_bkg_charm_3.root");
  TFile *f_bkg_charm4 = new TFile("MC_data/MLP_continuum/MLP_bkg_charm_4.root");
  TFile *f_bkg_charm5 = new TFile("MC_data/MLP_continuum/MLP_bkg_charm_5.root");

  TFile *f_bkg_charged0 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_0.root");
  TFile *f_bkg_charged1 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_1.root");
  TFile *f_bkg_charged2 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_2.root");
  TFile *f_bkg_charged3 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_3.root");
  TFile *f_bkg_charged4 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_4.root");
  TFile *f_bkg_charged5 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_5.root");
  TFile *f_bkg_charged6 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_6.root");
  TFile *f_bkg_charged7 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_7.root");
  TFile *f_bkg_charged8 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_8.root");
  TFile *f_bkg_charged9 = new TFile("MC_data/MLP_continuum/MLP_bkg_charged_9.root");


  TFile *f_bkg_mixed0 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_0.root");
  TFile *f_bkg_mixed1 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_1.root");
  TFile *f_bkg_mixed2 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_2.root");
  TFile *f_bkg_mixed3 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_3.root");
  TFile *f_bkg_mixed4 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_4.root");
  TFile *f_bkg_mixed5 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_5.root");
  TFile *f_bkg_mixed6 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_6.root");
  TFile *f_bkg_mixed7 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_7.root");
  TFile *f_bkg_mixed8 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_8.root");
  TFile *f_bkg_mixed9 = new TFile("MC_data/MLP_continuum/MLP_bkg_mixed_9.root");

  TTree *t_sig = (TTree*)f_sig->Get("incl");

  TTree *t_bkg_uds0 = (TTree*)f_bkg_uds0->Get("incl");
  TTree *t_bkg_uds1 = (TTree*)f_bkg_uds1->Get("incl");
  TTree *t_bkg_uds2 = (TTree*)f_bkg_uds2->Get("incl");
  TTree *t_bkg_uds3 = (TTree*)f_bkg_uds3->Get("incl");
  TTree *t_bkg_uds4 = (TTree*)f_bkg_uds4->Get("incl");
  TTree *t_bkg_uds5 = (TTree*)f_bkg_uds5->Get("incl");

  TTree *t_bkg_charm0 = (TTree*)f_bkg_charm0->Get("incl");
  TTree *t_bkg_charm1 = (TTree*)f_bkg_charm1->Get("incl");
  TTree *t_bkg_charm2 = (TTree*)f_bkg_charm2->Get("incl");
  TTree *t_bkg_charm3 = (TTree*)f_bkg_charm3->Get("incl");
  TTree *t_bkg_charm4 = (TTree*)f_bkg_charm4->Get("incl");
  TTree *t_bkg_charm5 = (TTree*)f_bkg_charm5->Get("incl");

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

  TH1F *h_sig = new TH1F("h_sig", "MLP scores;MLP scores; % events", 21, -1, 1);
  TH1F *h_bkg_continuum = new TH1F("h_bkg_continuum", "MLP scores;MLP scores; % events", 21, -1, 1);
  TH1F *h_bkg_bbar = new TH1F("h_bkg_bbar", "MLP scores;MLP scores; % events", 21, -1, 1);
 

  t_sig->Draw("MLP_continuum>>h_sig", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");

  t_bkg_uds0->Draw("MLP_continuum>>h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_uds1->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_uds2->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_uds3->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_uds4->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_uds5->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
 
  t_bkg_charm0->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charm1->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charm2->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charm3->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charm4->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charm5->Draw("MLP_continuum>>+h_bkg_continuum", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");

  t_bkg_charged0->Draw("MLP_continuum>>h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged1->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged2->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged3->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged4->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged5->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged6->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged7->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged8->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_charged9->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");

  t_bkg_mixed0->Draw("MLP_continuum>>++h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed1->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed2->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed3->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed4->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed5->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed6->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed7->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed8->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");
  t_bkg_mixed9->Draw("MLP_continuum>>+h_bkg_bbar", "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && abs(m_Kpi - 1.864) > 0.2 &&  m_Krho > 1.95 && m_ROE < 2.15", "goff");

  h_sig->Scale(1.0 / h_sig->Integral());
  h_sig->SetLineWidth(5);
  h_sig->SetLineColor(kBlue);
  h_sig->SetMarkerColor(kBlue);

  h_bkg_continuum->Scale(1.0 / h_bkg_continuum->Integral());
  h_bkg_continuum->SetLineWidth(5);
  h_bkg_continuum->SetLineColor(kRed);
  h_bkg_continuum->SetMarkerColor(kRed);

  h_bkg_bbar->Scale(1.0 / h_bkg_bbar->Integral());
  h_bkg_bbar->SetLineWidth(5);
  h_bkg_bbar->SetLineColor(kGreen);
  h_bkg_bbar->SetMarkerColor(kGreen);

  Float_t y_max = std::max({h_sig->GetMaximum(),h_bkg_continuum->GetMaximum(), h_bkg_bbar->GetMaximum()}); 
  y_max *= 1.2;

  TCanvas *c0 = new TCanvas("c0","MLP Scores", 1024, 786);

  h_sig->SetMaximum(y_max); h_sig->SetMinimum(0); h_sig->Draw("HIST");
  h_bkg_continuum->Draw("SAMESHIST");
  h_bkg_bbar->Draw("SAMESHIST");

  gPad->Update();

  TPaveStats *s_sig = (TPaveStats*)h_sig->FindObject("stats");
    s_sig->SetX1NDC(0.75 - 0 * 0.15);
    s_sig->SetX2NDC(0.90 - 0 * 0.15);
    s_sig->SetY1NDC(0.90 - 0 * 0.05);
    s_sig->SetY2NDC(1.00 - 0 * 0.05);
    s_sig->SetTextColor(kBlue);

  TPaveStats *s_bkg_continuum = (TPaveStats*)h_bkg_continuum->FindObject("stats");
    s_bkg_continuum->SetX1NDC(0.75 - 1 * 0.15);
    s_bkg_continuum->SetX2NDC(0.90 - 1 * 0.15);
    s_bkg_continuum->SetY1NDC(0.90 - 1 * 0.05);
    s_bkg_continuum->SetY2NDC(1.00 - 1 * 0.05);
    s_bkg_continuum->SetTextColor(kRed);

  TPaveStats *s_bkg_bbar = (TPaveStats*)h_bkg_bbar->FindObject("stats");
    s_bkg_bbar->SetX1NDC(0.75 - 1 * 0.15);
    s_bkg_bbar->SetX2NDC(0.90 - 1 * 0.15);
    s_bkg_bbar->SetY1NDC(0.90 - 1 * 0.05);
    s_bkg_bbar->SetY2NDC(1.00 - 1 * 0.05);
    s_bkg_bbar->SetTextColor(kGreen);

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9);
  leg->AddEntry(h_sig,"Signal MC", "f");
  leg->AddEntry(h_bkg_continuum,"continuum bkg", "f");
  leg->AddEntry(h_bkg_bbar,"bbar bkg", "f");

  leg->Draw();

}
