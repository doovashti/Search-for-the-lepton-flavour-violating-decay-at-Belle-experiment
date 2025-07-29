#include "TMath.h"
#include "TMVA/CrossValidation.h"
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/DataLoader.h"

void bdt()
{
    TMVA::Tools::Instance(); // Ensure TMVA is initialized

    TFile* outputFile = TFile::Open("OUTPUT_FILE_NAME_0.root", "RECREATE");

    // === Signal and background trees
    /*TFile* inputFileSig = new TFile("signalmc_taum_mup_tightcuts.root");
    TTree* sig = (TTree*)inputFileSig->Get("incl");

    TFile* inputFileBg1 = new TFile("bkg_charged_0.root");
    TTree* bkg1 = (TTree*)inputFileBg1->Get("incl");
    TFile* inputFileBg2 = new TFile("bkg_mixed_0.root");
    TTree* bkg2 = (TTree*)inputFileBg2->Get("incl");*/

    // Create signal chain (will be split randomly later)
    // Load original signal tree
    TFile* f_sig = TFile::Open("signalmc_taum_mup_tightcuts.root");
    TTree* sig = (TTree*)f_sig->Get("incl");

// Create true and mis-reconstructed signal subsets
    TCut true_reco = "isSignalAcceptMissingNeutrino_Bsig==1";
    TCut miss_reco = "isSignalAcceptMissingNeutrino_Bsig!=1";
    TTree* sig_true = sig->CopyTree(true_reco);
    TTree* sig_miss = sig->CopyTree(miss_reco);

// Background chains
    TChain* bkg_train = new TChain("incl");
    TChain* bkg_test  = new TChain("incl");

// Add Charged background files
    for (int i = 0; i <= 6; ++i)
        bkg_train->Add(Form("bkg_charged_%d.root", i));
    for (int i = 7; i <= 9; ++i)
        bkg_test->Add(Form("bkg_charged_%d.root", i));

// Add Mixed background files
    for (int i = 0; i <= 6; ++i)
        bkg_train->Add(Form("bkg_mixed_%d.root", i));
    for (int i = 7; i <= 9; ++i)
        bkg_test->Add(Form("bkg_mixed_%d.root", i));


    double sigWeight = 1.0;
    double bkgWeight = 1.0;

    // === Shared: variable list and cut
    TCut cut = "tauDecay_decayModeID==1 && Bsig_decayModeID==3 && foxWolframR2 < 0.4 && abs(m_Kpi - 1.864) > 0.2 && m_Krho > 1.95 && m_ROE < 2.15 && abs(cos_pBtag_Dltag) < 1.25";
    TCut signal_cut = true_reco && cut;
    Long64_t ntrain_bkg = bkg_train->GetEntries(cut);
    //during training, use only the correct signals --> only for signals!!, training on truth-matched 
    //apply with BDTG with all signals, and compare with just the true ones 
    //foxWolfram removes most of charm and uds backgrounds (compute percentage bkg removed and signal efficiency)

    /*// === CrossValidation DataLoader
    TMVA::DataLoader* cvLoader = new TMVA::DataLoader("dataset_cv");
    cvLoader->AddSignalTree(sig, sigWeight);
    cvLoader->AddBackgroundTrainTree(bkg_train, bkgWeight);
    cvLoader->AddBackgroundTestTree(bkg_test, bkgWeight);

    cvLoader->AddVariable("m_ROE", 'F');
    cvLoader->AddVariable("p_ltag", 'F');
    cvLoader->AddVariable("nLepton", 'I');
    cvLoader->AddVariable("deltaE_Btag", 'F');
    cvLoader->AddVariable("m_Kltaud", 'F');
    cvLoader->AddVariable("nPhotonsSelected", 'I');
    cvLoader->AddVariable("Alternate_cos_pBtag_Dltag", 'F');
    cvLoader->AddVariable("m_Krho", 'F');
    cvLoader->AddVariable("m_Kpi", 'F'); */

    /*// === CrossValidation
    TMVA::CrossValidation* cv = new TMVA::CrossValidation("CrossVal", cvLoader, outputFile, "SplitType=Random:NumFolds=5");
    cv->SetVerbose(true);

    cv->BookMethod(TMVA::Types::kBDT, "BDT",
        "!H:!V:NTrees=400:MinNodeSize=4%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.15:nCuts=80");
    cv->BookMethod(TMVA::Types::kBDT, "BDTG",
        "!H:!V:NTrees=400:Shrinkage=0.10:MaxDepth=3:BoostType=Grad:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20");
    cv->BookMethod(TMVA::Types::kMLP, "MLP",
        "H:!V:NeuronType=tanh:VarTransform=None:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS");

    cv->Evaluate();  // run CV
    delete cvLoader;*/

    // === Factory DataLoader (must be new and separate)
    TChain* bkg_all = new TChain("incl");
    for (int i = 0; i <= 9; ++i)
        bkg_all->Add(Form("bkg_charged_%d.root", i));
    for (int i = 0; i <= 9; ++i)
        bkg_all->Add(Form("bkg_mixed_%d.root", i));

// DataLoader
    TMVA::DataLoader* factoryLoader = new TMVA::DataLoader("dataset");
    factoryLoader->AddSignalTree(sig_true, sigWeight);
    factoryLoader->AddBackgroundTree(bkg_all, bkgWeight);

    factoryLoader->AddVariable("m_ROE", 'F');
    factoryLoader->AddVariable("p_ltag", 'F');
    factoryLoader->AddVariable("nLepton", 'I');
    factoryLoader->AddVariable("deltaE_Btag", 'F');
    //factoryLoader->AddVariable("m_Kltaud", 'F');
    factoryLoader->AddVariable("best_sum", 'F');
    factoryLoader->AddVariable("nPhotonsSelected", 'I');
    //factoryLoader->AddVariable("Alternate_cos_pBtag_Dltag", 'F');
    //factoryLoader->AddVariable("m_Krho", 'F');
    //factoryLoader->AddVariable("m_Kpi", 'F');

    factoryLoader->PrepareTrainingAndTestTree(
        signal_cut, cut,  // signal cut, background cut
        "SplitMode=Random:SplitSeed=42:NormMode=NumEvents:nTrain_Signal=70%: nTrain_Background=70%");
    //"SplitMode=Random:SplitSeed=42:NormMode=NumEvents:nTrain_Signal=0:nTrain_Background=0" --> 70/30


    // === Factory
    TMVA::Factory* factory = new TMVA::Factory("TMVAClassification", outputFile, "V:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");

    factory->BookMethod(factoryLoader, TMVA::Types::kBDT, "BDT",
        "!H:!V:NTrees=400:MinNodeSize=4%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.15:nCuts=80");
    factory->BookMethod(factoryLoader, TMVA::Types::kBDT, "BDTG",
        "!H:!V:NTrees=400:Shrinkage=0.10:MaxDepth=3:BoostType=Grad:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20");
    //factory->BookMethod(factoryLoader, TMVA::Types::kMLP, "MLP",
        //"H:!V:NeuronType=tanh:VarTransform=None:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS");

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    outputFile->Close();

    delete factoryLoader;
    delete factory;
    //delete cv;
}
