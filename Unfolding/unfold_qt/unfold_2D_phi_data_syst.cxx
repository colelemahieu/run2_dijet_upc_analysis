#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)

// This code is an example of the unfolding code used with RooUnfold
// This code unfolds a 2D histogram, phi vs QT
// Corrections for fakes and misses (purity and acceptance) corrections must be done manually

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include "TRandom.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TBranch.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "RooUnfoldResponse.h"
#include "RooUnfoldInvert.h"
#include "RooUnfoldBayes.h"
//#include "RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h"
//#include "RooUnfoldIds.h"
#endif
#include "/afs/cern.ch/user/c/clemahie/Unfold2/RooUnfold/examples/JetCorrector.h"
#include "/afs/cern.ch/user/c/clemahie/Unfold2/RooUnfold/examples/JetUncertainty.h"


int jetsProperOrder(float genPhi_0, float genEta_0, float recoPhi_0, float recoEta_0, float recoPhi_1, float recoEta_1)
{
  // find distance between gen0 and reco0
  float phiDiff_00 = genPhi_0 - recoPhi_0;
  float etaDiff_00 = genEta_0 - recoEta_0;
  float jetDist_00 = sqrt(phiDiff_00*phiDiff_00 + etaDiff_00*etaDiff_00);

  // find distance between gen0 and reco1
  float phiDiff_01 = genPhi_0 - recoPhi_1;
  float etaDiff_01 = genEta_0 - recoEta_1;
  float jetDist_01 = sqrt(phiDiff_01*phiDiff_01 + etaDiff_01*etaDiff_01);

  int indexMin;
  if (jetDist_00 < jetDist_01) indexMin=1;
  if (jetDist_00 > jetDist_01) indexMin=0;

  return indexMin;
}


void unfold_2D_phi_data_syst()
{
 // bools for systematics
 bool noSystematics=true;
 bool jecSystematicsNom=false;
 bool jesSystematicsUp=false, jesSystematicsDown=false;
 bool jerSystematicsUp=false, jerSystematicsDown=false;
 bool jarSystematics=false;

 // JES
 vector<string> Files;
 JetCorrector* JEC_0 = nullptr;
 JetCorrector* JEC_1 = nullptr;
 JetUncertainty* JEU_0 = nullptr;
 JetUncertainty* JEU_1 = nullptr;
 Files.push_back("jecFiles/Autumn18_V9_MC_L2Relative_AK4PF.txt");
 JEC_0 = new JetCorrector(Files), JEC_1 = new JetCorrector(Files);
 JEU_0 = new JetUncertainty("jecFiles/Autumn18_V9_MC_Uncertainty_AK4PF.txt");
 JEU_1 = new JetUncertainty("jecFiles/Autumn18_V9_MC_Uncertainty_AK4PF.txt");
 float oldPt_0=0, oldPt_1=0, corrJet_0=0, corrJet_1=0;

 // JER
 SingleJetCorrector JERSF_0("jecFiles/Summer19UL18_JRV2_MC_SF_AK4PFchs.txt"), JERSF_1("jecFiles/Summer19UL18_JRV2_MC_SF_AK4PFchs.txt");
 vector<double> jer_param_0={0}, jer_param_1={0};
 double jer_min_0=0, jer_max_0=0, jer_min_1=0, jer_max_1=0, jer_nom_0=0, jer_nom_1=0;

 // Response Matrix, 2D phi vs QT
 RooUnfoldResponse response_phi12_QT5;
 TH2D *h2_true_phi12_QT5 = new TH2D("h2_true_phi12_QT5", "h2_true_phi12_QT5",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_smeared_phi12_QT5 = new TH2D("h2_smeared_phi12_QT5", "h2_smeared_phi12_QT5",5,0,40,12,-TMath::Pi(),TMath::Pi());
 response_phi12_QT5.Setup(h2_smeared_phi12_QT5, h2_true_phi12_QT5);

 // Read input file containing distribution to be unfolded
 //TFile *fileR4 = new TFile("allPlots_R2.root"); 
 TFile *fileR4 = new TFile("allPlots_R4.root");
 //TFile *fileR4 = new TFile("allPlots_R4_0n0n.root");
 //TFile *fileR4 = new TFile("allPlots_R6.root");
 TH2D *h2_phi12_QT5_meas = (TH2D*)fileR4->Get("h2_phiQTPT_QT_mpi"); 
 TH2D* h2_meas_orig = (TH2D*)h2_phi12_QT5_meas->Clone("h2_meas_orig");

 // Gen and Reco Level 2D QT vs cos2phi for Check
 TH2D *h2_phi12_QT5_gen = new TH2D("h2_phi12_QT5_gen","h2_phi12_QT5_gen",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_QT5_genMatch = new TH2D("h2_phi12_QT5_genMatch","h2_phi12_QT5_genMatch",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_QT5_reco = new TH2D("h2_phi12_QT5_reco","h2_phi12_QT5_reco",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_QT5_recoMatch = new TH2D("h2_phi12_QT5_recoMatch","h2_phi12_QT5_recoMatch",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_QT5_miss = new TH2D("h2_phi12_QT5_miss","h2_phi12_QT5_miss",5,0,40,12,-TMath::Pi(),TMath::Pi()); 
 TH2D *h2_phi12_QT5_fake = new TH2D("h2_phi12_QT5_fake","h2_phi12_QT5_fake",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_responseSlice = new TH2D("h2_responseSlice", "h2_responseSlice", 36,-TMath::Pi(),TMath::Pi(), 12,-TMath::Pi(),TMath::Pi());

 // Twiki Plots
 TH1D *h_recogen_ratio = new TH1D("h_recogen_ratio","h_recogen_ratio",100,0,2); 
 TH2D *h2_genPt_recoPt = new TH2D("h2_genPt_recoPt","h2_genPt_recoPt",16,20,60,16,20,60); 
 

 // Read in Pythia MC events to fill response matrix
 //TFile *file = new TFile("/eos/user/c/clemahie/pythia_pfCuts/pythiaPF_miniAOD_r2_full.root");
 TFile *file = new TFile("/eos/user/c/clemahie/pythia_pfCuts/pythiaPF_miniAOD_r4_full.root");
 //TFile *file = new TFile("/eos/cms/store/group/phys_heavyions/clemahie/pythia_pfCuts/pythiaPF_miniAOD_r6_full.root");
 //TTree *jetTree = (TTree*)file->Get("t");
 //TTree *evtTree = (TTree*)file->Get("hiEvent");
 //TTree *pfTree = (TTree*)file->Get("pftree");
 // Read in events TChain
 TChain* jetTree = new TChain("t");
 TChain* evtTree = new TChain("hiEvent");
 TChain* pfTree = new TChain("pftree");
 // r2
 //jetTree->Add("/eos/user/c/clemahie/r2/*.root");
 //evtTree->Add("/eos/user/c/clemahie/r2/*.root");
 //pfTree->Add("/eos/user/c/clemahie/r2/*.root"); 
 // r4
 jetTree->Add("/eos/user/c/clemahie/MC_samples/*.root");
 evtTree->Add("/eos/user/c/clemahie/MC_samples/*.root");
 pfTree->Add("/eos/user/c/clemahie/MC_samples/*.root");
 // r6
 //jetTree->Add("/eos/user/c/clemahie/r6/*.root");
 //evtTree->Add("/eos/user/c/clemahie/r6/*.root");
 //pfTree->Add("/eos/user/c/clemahie/r6/*.root"); 

 // Read Variables
 int nTrk=0, nRef=0, nGen=0;
 float vtx_z=0;
 unsigned int run=0, lumis=0;
 ULong64_t event=0;
 float jetEnt = jetTree->GetEntries();
 vector<float> *trkPt=0, *trkEta=0;
 float jetPt[200]={0}, jetEta[200]={0}, jetPhi[200]={0}, jetM[200]={0};
 float genPt[200]={0}, genEta[200]={0}, genPhi[200]={0}, genM[200]={0};
 vector<float> *caloEta=0, *caloPhi=0, *caloEn=0, *calo_hadE=0, *calo_emE=0;
 float e[18]={0};

 int nPF=0;
 vector<int> *pfId=0;
 vector<float> *pfEta=0, *pfE=0, *pfEt=0, *pfPhi=0, *pfTrkEta=0, *pfTrkPt=0;
  
 // gen, reco
 jetTree->SetBranchAddress("nref", &nRef);
 jetTree->SetBranchAddress("jteta", &jetEta);
 jetTree->SetBranchAddress("jtpt", &jetPt);
 jetTree->SetBranchAddress("jtphi", &jetPhi);
 jetTree->SetBranchAddress("jtm", &jetM);
 jetTree->SetBranchAddress("ngen", &nGen);
 jetTree->SetBranchAddress("geneta", &genEta);
 jetTree->SetBranchAddress("genpt", &genPt);
 jetTree->SetBranchAddress("genphi", &genPhi);
 jetTree->SetBranchAddress("genm", &genM);
 evtTree->SetBranchAddress("Vertex_Z", &vtx_z);
 pfTree->SetBranchAddress("nPF", &nPF);
 pfTree->SetBranchAddress("pfEt", &pfEt);
 pfTree->SetBranchAddress("pfE", &pfE);
 pfTree->SetBranchAddress("pfEta", &pfEta);
 pfTree->SetBranchAddress("pfPhi", &pfPhi);
 pfTree->SetBranchAddress("pfTrkEta", &pfTrkEta);
 pfTree->SetBranchAddress("pfTrkPt", &pfTrkPt);
 pfTree->SetBranchAddress("pfId", &pfId);

 // variables for v2 stuff
 float pi = TMath::Pi();
 int goodEvt=0;
 float px_1=0, px_2=0, py_1=0, py_2=0, avgRap=0;
 float px_1_gen=0, px_2_gen=0, py_1_gen=0, py_2_gen=0;
 TVector2 Q_T, P_T;
 TVector2 Q_T_gen, P_T_gen;
 float QT_norm, PT_norm, QT_phi, PT_phi, angleDiff;
 float QT_norm_gen, PT_norm_gen;
 TVector2 QT_unit, PT_unit;
 TVector2 QT_unit_gen, PT_unit_gen;
 float cos12, sin12, angle12, cos_2phi=0;
 float cos12_gen, sin12_gen, angle12_gen, cos_2phi_gen=0;

 // Evt labels
 int passGenCuts, passRecoCuts;
 int passGenCuts_noJetPt;
 int trueEvt, missEvt, fakeEvt;
 int trueCount=0, missCount=0, fakeCount=0, passGenCutsCount=0, passRecoCutsCount=0; 

 // pf leading energies
 float pfle_had, pfle_em;
 float pftotal_had, pftotal_hadE;

 cout << "There are " << jetEnt << " events" << endl;


 // evt loop
 for (int i=0; i<jetEnt; i++)
    {
      if (i%10000==0) cout << i << endl;
      jetTree->GetEntry(i);
      evtTree->GetEntry(i);
      pfTree->GetEntry(i);
      
      // initialize
      pfle_had=0, pfle_em=0, pftotal_had=0, pftotal_hadE=0;
      passGenCuts=0, passRecoCuts=0, passGenCuts_noJetPt=0;
      trueEvt=0, missEvt=0, fakeEvt=0;    


      // JES
      if (jesSystematicsDown)
      {
	// apply JES down correction
        JEC_0->SetJetPT(jetPt[0]), JEC_1->SetJetPT(jetPt[1]);
        JEC_0->SetJetEta(jetEta[0]), JEC_1->SetJetEta(jetEta[1]);
        JEC_0->SetJetPhi(jetPhi[0]), JEC_1->SetJetPhi(jetPhi[1]);
        JEU_0->SetJetEta(jetEta[0]), JEU_1->SetJetEta(jetEta[1]);
        JEU_0->SetJetPhi(jetPhi[0]), JEU_1->SetJetPhi(jetPhi[1]);
        JEU_0->SetJetPT(jetPt[0]), JEU_1->SetJetPT(jetPt[1]);
	double Correction_0=JEC_0->GetCorrection(), Correction_1=JEC_1->GetCorrection();
        double CorrectedPT_0=JEC_0->GetCorrectedPT(), CorrectedPT_1=JEC_1->GetCorrectedPT();
        double CorrectedPT_Down_0 = CorrectedPT_0 * (1 - JEU_0->GetUncertainty().first);
        double CorrectedPT_Down_1 = CorrectedPT_1 * (1 - JEU_1->GetUncertainty().first);
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0] = CorrectedPT_Down_0;
        jetPt[1] = CorrectedPT_Down_1;

	// apply JER norminal correction
        JERSF_0.SetJetPT(jetPt[0]), JERSF_1.SetJetPT(jetPt[1]);
        JERSF_0.SetJetEta(jetEta[0]), JERSF_1.SetJetEta(jetEta[1]);
        JERSF_0.SetJetPhi(jetPhi[0]), JERSF_1.SetJetPhi(jetPhi[1]);
        jer_param_0 = JERSF_0.GetParameters(), jer_param_1 = JERSF_1.GetParameters();
        jer_nom_0=jer_param_0[0], jer_nom_1=jer_param_1[0];
        corrJet_0=1+(jer_nom_0-1)*(jetPt[0]-genPt[0])/(jetPt[0]);
        corrJet_1=1+(jer_nom_1-1)*(jetPt[1]-genPt[1])/(jetPt[1]);
        if (corrJet_0<0) corrJet_0=0;
        if (corrJet_1<0) corrJet_1=0;
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0]=jetPt[0]*corrJet_0, jetPt[1]=jetPt[1]*corrJet_1;
      }
      if (jesSystematicsUp)
      {
	// apply JES up correction
        JEC_0->SetJetPT(jetPt[0]), JEC_1->SetJetPT(jetPt[1]);
        JEC_0->SetJetEta(jetEta[0]), JEC_1->SetJetEta(jetEta[1]);
        JEC_0->SetJetPhi(jetPhi[0]), JEC_1->SetJetPhi(jetPhi[1]);
        JEU_0->SetJetEta(jetEta[0]), JEU_1->SetJetEta(jetEta[1]);
        JEU_0->SetJetPhi(jetPhi[0]), JEU_1->SetJetPhi(jetPhi[1]);
        JEU_0->SetJetPT(jetPt[0]), JEU_1->SetJetPT(jetPt[1]);
	double Correction_0=JEC_0->GetCorrection(), Correction_1=JEC_1->GetCorrection();
        double CorrectedPT_0=JEC_0->GetCorrectedPT(), CorrectedPT_1=JEC_1->GetCorrectedPT();
        double CorrectedPT_Up_0 = CorrectedPT_0 * (1 + JEU_0->GetUncertainty().second);
        double CorrectedPT_Up_1 = CorrectedPT_1 * (1 + JEU_1->GetUncertainty().second);
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0] = CorrectedPT_Up_0;
        jetPt[1] = CorrectedPT_Up_1;

	// apply JER norminal correction
	JERSF_0.SetJetPT(jetPt[0]), JERSF_1.SetJetPT(jetPt[1]);
        JERSF_0.SetJetEta(jetEta[0]), JERSF_1.SetJetEta(jetEta[1]);
        JERSF_0.SetJetPhi(jetPhi[0]), JERSF_1.SetJetPhi(jetPhi[1]);
        jer_param_0 = JERSF_0.GetParameters(), jer_param_1 = JERSF_1.GetParameters();
        jer_nom_0=jer_param_0[0], jer_nom_1=jer_param_1[0];
        corrJet_0=1+(jer_nom_0-1)*(jetPt[0]-genPt[0])/(jetPt[0]);
        corrJet_1=1+(jer_nom_1-1)*(jetPt[1]-genPt[1])/(jetPt[1]);
        if (corrJet_0<0) corrJet_0=0;
        if (corrJet_1<0) corrJet_1=0;
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0]=jetPt[0]*corrJet_0, jetPt[1]=jetPt[1]*corrJet_1;
      }
      if (jecSystematicsNom)
      {
	// apply JES nominal correction
        JEC_0->SetJetPT(jetPt[0]), JEC_1->SetJetPT(jetPt[1]);
        JEC_0->SetJetEta(jetEta[0]), JEC_1->SetJetEta(jetEta[1]);
        JEC_0->SetJetPhi(jetPhi[0]), JEC_1->SetJetPhi(jetPhi[1]);
        double Correction_0=JEC_0->GetCorrection(), Correction_1=JEC_1->GetCorrection();
        double CorrectedPT_0=JEC_0->GetCorrectedPT(), CorrectedPT_1=JEC_1->GetCorrectedPT();
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0] = CorrectedPT_0;
        jetPt[1] = CorrectedPT_1;

        // apply JER nominal correction
        JERSF_0.SetJetPT(jetPt[0]), JERSF_1.SetJetPT(jetPt[1]);
        JERSF_0.SetJetEta(jetEta[0]), JERSF_1.SetJetEta(jetEta[1]);
        JERSF_0.SetJetPhi(jetPhi[0]), JERSF_1.SetJetPhi(jetPhi[1]);
        jer_param_0 = JERSF_0.GetParameters(), jer_param_1 = JERSF_1.GetParameters();
        jer_nom_0=jer_param_0[0], jer_nom_1=jer_param_1[0];
        corrJet_0=1+(jer_nom_0-1)*(jetPt[0]-genPt[0])/(jetPt[0]);
        corrJet_1=1+(jer_nom_1-1)*(jetPt[1]-genPt[1])/(jetPt[1]);
        if (corrJet_0<0) corrJet_0=0;
        if (corrJet_1<0) corrJet_1=0;
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0]=jetPt[0]*corrJet_0, jetPt[1]=jetPt[1]*corrJet_1;	
      }
      if (jerSystematicsDown)
      {
        // apply JES nominal correction
        JEC_0->SetJetPT(jetPt[0]), JEC_1->SetJetPT(jetPt[1]);
        JEC_0->SetJetEta(jetEta[0]), JEC_1->SetJetEta(jetEta[1]);
        JEC_0->SetJetPhi(jetPhi[0]), JEC_1->SetJetPhi(jetPhi[1]);
        double Correction_0=JEC_0->GetCorrection(), Correction_1=JEC_1->GetCorrection();
        double CorrectedPT_0=JEC_0->GetCorrectedPT(), CorrectedPT_1=JEC_1->GetCorrectedPT();
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0] = CorrectedPT_0;
        jetPt[1] = CorrectedPT_1; 	

	// apply JER down correction
        JERSF_0.SetJetPT(jetPt[0]), JERSF_1.SetJetPT(jetPt[1]);
        JERSF_0.SetJetEta(jetEta[0]), JERSF_1.SetJetEta(jetEta[1]);
        JERSF_0.SetJetPhi(jetPhi[0]), JERSF_1.SetJetPhi(jetPhi[1]);
        jer_param_0 = JERSF_0.GetParameters(), jer_param_1 = JERSF_1.GetParameters();
        
	jer_min_0=min(jer_param_0[1], jer_param_0[2]), jer_max_0=max(jer_param_0[1], jer_param_0[2]);
        jer_min_1=min(jer_param_1[1], jer_param_1[2]), jer_max_1=max(jer_param_1[1], jer_param_1[2]);
        corrJet_0=1+(jer_min_0-1)*(jetPt[0]-genPt[0])/(jetPt[0]);
        corrJet_1=1+(jer_min_0-1)*(jetPt[1]-genPt[1])/(jetPt[1]);
        if (corrJet_0<0) corrJet_0=0;
        if (corrJet_1<0) corrJet_1=0;
	oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0]=jetPt[0]*corrJet_0, jetPt[1]=jetPt[1]*corrJet_1;
      }
      if (jerSystematicsUp)
      {
        // apply JES nominal correction
	JEC_0->SetJetPT(jetPt[0]), JEC_1->SetJetPT(jetPt[1]);
        JEC_0->SetJetEta(jetEta[0]), JEC_1->SetJetEta(jetEta[1]);
        JEC_0->SetJetPhi(jetPhi[0]), JEC_1->SetJetPhi(jetPhi[1]);
        double Correction_0=JEC_0->GetCorrection(), Correction_1=JEC_1->GetCorrection();
        double CorrectedPT_0=JEC_0->GetCorrectedPT(), CorrectedPT_1=JEC_1->GetCorrectedPT();
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        jetPt[0] = CorrectedPT_0;
        jetPt[1] = CorrectedPT_1;

	// apply JER up correction
        JERSF_0.SetJetPT(jetPt[0]), JERSF_1.SetJetPT(jetPt[1]);
        JERSF_0.SetJetEta(jetEta[0]), JERSF_1.SetJetEta(jetEta[1]);
        JERSF_0.SetJetPhi(jetPhi[0]), JERSF_1.SetJetPhi(jetPhi[1]);
        jer_param_0 = JERSF_0.GetParameters(), jer_param_1 = JERSF_1.GetParameters();
        // scaling method
	jer_min_0=min(jer_param_0[1], jer_param_0[2]), jer_max_0=max(jer_param_0[1], jer_param_0[2]);
        jer_min_1=min(jer_param_1[1], jer_param_1[2]), jer_max_1=max(jer_param_1[1], jer_param_1[2]);
        corrJet_0=1+(jer_max_0-1)*(jetPt[0]-genPt[0])/(jetPt[0]);
        corrJet_1=1+(jer_max_0-1)*(jetPt[1]-genPt[1])/(jetPt[1]);
	if (corrJet_0<0) corrJet_0=0;
	if (corrJet_1<0) corrJet_1=0;
        oldPt_0=jetPt[0], oldPt_1=jetPt[1];
        // correct the reco value
	jetPt[0]=jetPt[0]*corrJet_0, jetPt[1]=jetPt[1]*corrJet_1;
      }
      // JAR systematic
      TRandom3 randomGauss(0);
      if (jarSystematics)
      {
        double mean=0.0, width_phi=0.022, width_eta=0.025;
        jetPhi[0] = jetPhi[0]+randomGauss.Gaus(mean, width_phi);
        jetPhi[1] = jetPhi[1]+randomGauss.Gaus(mean, width_phi);
        jetEta[0] = jetEta[0]+randomGauss.Gaus(mean, width_eta);
        jetEta[1] = jetEta[1]+randomGauss.Gaus(mean, width_eta);
       }


      // Calculate px1, py1, px2, py2 (GEN and RECO)
      if (jetsProperOrder(genPhi[0], genEta[0], jetPhi[0], jetEta[0], jetPhi[1], jetEta[1])==1)
      {
        px_1=(jetPt[0])*(cos(jetPhi[0]));
        py_1=(jetPt[0])*(sin(jetPhi[0]));
        px_2=(jetPt[1])*(cos(jetPhi[1]));
        py_2=(jetPt[1])*(sin(jetPhi[1]));

        px_1_gen=(genPt[0])*(cos(genPhi[0]));
        py_1_gen=(genPt[0])*(sin(genPhi[0]));
        px_2_gen=(genPt[1])*(cos(genPhi[1]));
        py_2_gen=(genPt[1])*(sin(genPhi[1]));
      }
      if (jetsProperOrder(genPhi[0], genEta[0], jetPhi[0], jetEta[0], jetPhi[1], jetEta[1])==0)
      {
        px_1=(jetPt[1])*(cos(jetPhi[1]));
        py_1=(jetPt[1])*(sin(jetPhi[1]));
        px_2=(jetPt[0])*(cos(jetPhi[0]));
        py_2=(jetPt[0])*(sin(jetPhi[0]));

        px_1_gen=(genPt[0])*(cos(genPhi[0]));
        py_1_gen=(genPt[0])*(sin(genPhi[0]));
        px_2_gen=(genPt[1])*(cos(genPhi[1]));
        py_2_gen=(genPt[1])*(sin(genPhi[1]));
      }


      // Define QT and PT 2-vectors
      float random=0;
      random=rand()%(2)+1;
      Q_T.Set(px_1+px_2, py_1+py_2);
      if (random==1) P_T.Set(0.5*(px_1-px_2), 0.5*(py_1-py_2));
      if (random==2) P_T.Set(0.5*(px_2-px_1), 0.5*(py_2-py_1));
      Q_T_gen.Set(px_1_gen+px_2_gen, py_1_gen+py_2_gen);
      if (random==1) P_T_gen.Set(0.5*(px_1_gen-px_2_gen), 0.5*(py_1_gen-py_2_gen));
      if (random==2) P_T_gen.Set(0.5*(px_2_gen-px_1_gen), 0.5*(py_2_gen-py_1_gen));

      // Compute the norm of QT, PT
      QT_norm = sqrt(Q_T.X()*Q_T.X() + Q_T.Y()*Q_T.Y());
      PT_norm = sqrt(P_T.X()*P_T.X() + P_T.Y()*P_T.Y());
      QT_norm_gen = sqrt(Q_T_gen.X()*Q_T_gen.X() + Q_T_gen.Y()*Q_T_gen.Y());
      PT_norm_gen = sqrt(P_T_gen.X()*P_T_gen.X() + P_T_gen.Y()*P_T_gen.Y());

      // Evt labels
      if (nGen!=0 && nGen!=1 && (fabs(genEta[0]) < 3.0) && (fabs(genEta[1]) < 3.0) && (genPt[0]>30) && (genPt[1]>20) && (PT_norm_gen>QT_norm_gen) && (genPt[2]<20) && (QT_norm_gen<40)) passGenCuts=1;
      if (nRef!=0 && nRef!=1 && (fabs(jetEta[0]) < 3.0) && (fabs(jetEta[1]) < 3.0) && (jetPt[0]>30) && (jetPt[1]>20) && (PT_norm>QT_norm) && (jetPt[2]<20) && (QT_norm<40)) passRecoCuts=1;
      // special selection for twiki page: gen cuts, no jet pt
      if (nGen!=0 && nGen!=1 && (fabs(genEta[0]) < 3.0) && (fabs(genEta[1]) < 3.0) && (PT_norm_gen>QT_norm_gen) && (genPt[2]<20) && (QT_norm_gen<40)) passGenCuts_noJetPt=1;

      if (passGenCuts==1) passGenCutsCount=passGenCutsCount+1;
      if (passRecoCuts==1) passRecoCutsCount=passRecoCutsCount+1;
      if (passGenCuts==1 && passRecoCuts==1) trueEvt=1;
      if (passGenCuts==1 && passRecoCuts==0) missEvt=1;
      if (passGenCuts==0 && passRecoCuts==1) fakeEvt=1;


      // calculate v2 stuff
      QT_unit.Set(Q_T.X()/QT_norm, Q_T.Y()/QT_norm);
      PT_unit.Set(P_T.X()/PT_norm, P_T.Y()/PT_norm);
      QT_unit_gen.Set(Q_T_gen.X()/QT_norm_gen, Q_T_gen.Y()/QT_norm_gen);
      PT_unit_gen.Set(P_T_gen.X()/PT_norm_gen, P_T_gen.Y()/PT_norm_gen);

      // cos(phi) = Dot Product of the unit vectors
      cos12 = QT_unit.X()*PT_unit.X() + QT_unit.Y()*PT_unit.Y();
      cos12_gen = QT_unit_gen.X()*PT_unit_gen.X() + QT_unit_gen.Y()*PT_unit_gen.Y();
      // sin(phi) = Cross Product of the unit vectors
      sin12 = QT_unit.X()*PT_unit.Y() - QT_unit.Y()*PT_unit.X();
      sin12_gen = QT_unit_gen.X()*PT_unit_gen.Y() - QT_unit_gen.Y()*PT_unit_gen.X();

      // Compute the angle by using arctan2 function
      angle12 = atan2(sin12, cos12);
      angle12_gen = atan2(sin12_gen, cos12_gen); 

      // cos(n*phi) values
      cos_2phi = cos(2*angle12);
      cos_2phi_gen = cos(2*angle12_gen);


      // gen comparison histograms
      if (passGenCuts==1) 
      {
        h2_phi12_QT5_gen->Fill(QT_norm_gen, angle12_gen);

	h_recogen_ratio->Fill(jetPt[0]/genPt[0]);
	h_recogen_ratio->Fill(jetPt[1]/genPt[1]);
      }
      if (passGenCuts_noJetPt==1)
      {
        h2_genPt_recoPt->Fill(genPt[0], jetPt[0]);
        h2_genPt_recoPt->Fill(genPt[1], jetPt[1]);
      }
      // reco comparison histograms
      if (passRecoCuts==1)
      {
        h2_phi12_QT5_reco->Fill(QT_norm, angle12);
      }

      // Fill Response Matrix
      if (trueEvt==1)
      {
        trueCount = trueCount + 1;
        response_phi12_QT5.Fill(QT_norm, angle12, QT_norm_gen, angle12_gen);

	h2_phi12_QT5_genMatch->Fill(QT_norm_gen, angle12_gen);
	h2_phi12_QT5_recoMatch->Fill(QT_norm, angle12);

	if (QT_norm>8 && QT_norm<16) h2_responseSlice->Fill(angle12_gen, angle12);
      }
      if (missEvt==1)
      {
        missCount = missCount + 1;
	h2_phi12_QT5_miss->Fill(QT_norm_gen, angle12_gen);
      }
      if (fakeEvt==1)
      {
        fakeCount = fakeCount + 1;
	h2_phi12_QT5_fake->Fill(QT_norm, angle12);
      }

    } // end evt loop

// Print Info
cout << "There are " << passGenCutsCount << " pass gen events" << endl;
cout << "There are " << passRecoCutsCount << " pass reco events" << endl;
cout << "There are " << trueCount << " true events" << endl;
cout << "There are " << missCount << " miss events" << endl;
cout << "There are " << fakeCount << " fake events" << endl;


// make purity histogram
TH2D* h2_purity_factor = (TH2D*)h2_phi12_QT5_recoMatch->Clone("h2_purity_factor");
TH2D* h2_purity_denom = (TH2D*)h2_phi12_QT5_recoMatch->Clone("h2_purity_denom");
h2_purity_denom->Sumw2();
h2_purity_denom->Add(h2_phi12_QT5_fake);
h2_purity_factor->Divide(h2_phi12_QT5_recoMatch,h2_purity_denom,1,1,"B");

// purity correction (for fakes)
h2_phi12_QT5_meas->Sumw2();
h2_phi12_QT5_meas->Multiply(h2_purity_factor);

// make acceptance histogram
TH2D* h2_acceptance_factor = (TH2D*)h2_phi12_QT5_recoMatch->Clone("h2_acceptance_factor");
TH2D* h2_denom = (TH2D*)h2_phi12_QT5_recoMatch->Clone("h2_denom");
h2_denom->Sumw2();
h2_denom->Add(h2_phi12_QT5_miss);
h2_acceptance_factor->Divide(h2_phi12_QT5_recoMatch,h2_denom,1,1,"B");


// Unfolding 
RooUnfoldBayes unfold_bayes_phi12_QT5(&response_phi12_QT5, h2_phi12_QT5_meas, 2);
auto* hReco_bayes_phi12_QT5 = unfold_bayes_phi12_QT5.Hunfold();

// Acceptance Correction
TH2D* h2_phi12_QT5_acceptance = (TH2D*)hReco_bayes_phi12_QT5->Clone("h2_phi12_QT5_acceptance");
h2_phi12_QT5_acceptance->Divide(h2_acceptance_factor);


// write the histogram to the file
if (noSystematics)
{
  TFile newfile("fit_v2.root","recreate");
  h2_phi12_QT5_gen->Write("h2_gen");
  h2_phi12_QT5_genMatch->Write("h2_genMatch");
  h2_phi12_QT5_miss->Write("h2_miss");
  h2_phi12_QT5_fake->Write("h2_fake");
  response_phi12_QT5.Write("responseObject");
  response_phi12_QT5.Htruth()->Write("h_gen_fromResponse");
  response_phi12_QT5.Hmeasured()->Write("h_meas_fromResponse");
  h2_phi12_QT5_reco->Write("h2_reco");
  h2_phi12_QT5_recoMatch->Write("h2_recoMatch");
  h2_meas_orig->Write("h2_meas_orig");
  h2_phi12_QT5_meas->Write("h2_meas");
  hReco_bayes_phi12_QT5->Write("h2_unf");
  h2_phi12_QT5_acceptance->Write("h2_phi12_QT5_acceptance");
  h2_purity_factor->Write("h2_purity_factor");
  h2_acceptance_factor->Write("h2_acceptance_factor");
  h_recogen_ratio->Write();
  h2_genPt_recoPt->Write();
  h2_responseSlice->Write();
  newfile.Write();
}
if (jesSystematicsUp)
{
  TFile newfile("fit_v2_jesUp.root","recreate");
  h2_phi12_QT5_gen->Write("h2_gen");
  h2_phi12_QT5_genMatch->Write("h2_genMatch");
  h2_phi12_QT5_miss->Write("h2_miss");
  h2_phi12_QT5_fake->Write();
  response_phi12_QT5.Write("responseObject");
  response_phi12_QT5.Htruth()->Write("h_gen_fromResponse");
  response_phi12_QT5.Hmeasured()->Write("h_meas_fromResponse");
  h2_phi12_QT5_reco->Write("h2_reco");
  h2_phi12_QT5_recoMatch->Write();
  h2_meas_orig->Write("h2_meas_orig");
  h2_phi12_QT5_meas->Write("h2_meas");
  hReco_bayes_phi12_QT5->Write("h2_unf");
  h2_phi12_QT5_acceptance->Write("h2_phi12_QT5_acceptance");
  h2_purity_factor->Write("h2_purity_factor");
  h2_acceptance_factor->Write("h2_acceptance_factor");
  h2_genPt_recoPt->Write();
  newfile.Write();
}
if (jesSystematicsDown)
{
  TFile newfile("fit_v2_jesDown.root","recreate");
  h2_phi12_QT5_gen->Write("h2_gen");
  h2_phi12_QT5_genMatch->Write("h2_genMatch");
  h2_phi12_QT5_miss->Write("h2_miss");
  h2_phi12_QT5_fake->Write();
  response_phi12_QT5.Write("responseObject");
  response_phi12_QT5.Htruth()->Write("h_gen_fromResponse");
  response_phi12_QT5.Hmeasured()->Write("h_meas_fromResponse");
  h2_phi12_QT5_reco->Write("h2_reco");
  h2_phi12_QT5_recoMatch->Write();
  h2_meas_orig->Write("h2_meas_orig");
  h2_phi12_QT5_meas->Write("h2_meas");
  hReco_bayes_phi12_QT5->Write("h2_unf");
  h2_phi12_QT5_acceptance->Write("h2_phi12_QT5_acceptance");
  h2_purity_factor->Write("h2_purity_factor");
  h2_acceptance_factor->Write("h2_acceptance_factor");
  h2_genPt_recoPt->Write();
  newfile.Write();
}
if (jecSystematicsNom)
{
  TFile newfile("fit_v2_jecNom.root","recreate");
  h2_phi12_QT5_gen->Write("h2_gen");
  h2_phi12_QT5_genMatch->Write("h2_genMatch");
  h2_phi12_QT5_miss->Write("h2_miss");
  h2_phi12_QT5_fake->Write();
  response_phi12_QT5.Write("responseObject");
  response_phi12_QT5.Htruth()->Write("h_gen_fromResponse");
  response_phi12_QT5.Hmeasured()->Write("h_meas_fromResponse");
  h2_phi12_QT5_reco->Write("h2_reco");
  h2_phi12_QT5_recoMatch->Write();
  h2_meas_orig->Write("h2_meas_orig");
  h2_phi12_QT5_meas->Write("h2_meas");
  hReco_bayes_phi12_QT5->Write("h2_unf");
  h2_phi12_QT5_acceptance->Write("h2_phi12_QT5_acceptance");
  h2_purity_factor->Write("h2_purity_factor");
  h2_acceptance_factor->Write("h2_acceptance_factor");
  h2_genPt_recoPt->Write();
  newfile.Write();
}
if (jerSystematicsUp)
{
  TFile newfile("fit_v2_jerUp.root","recreate");
  h2_phi12_QT5_gen->Write("h2_gen");
  h2_phi12_QT5_genMatch->Write("h2_genMatch");
  h2_phi12_QT5_miss->Write("h2_miss");
  h2_phi12_QT5_fake->Write();
  response_phi12_QT5.Write("responseObject");
  response_phi12_QT5.Htruth()->Write("h_gen_fromResponse");
  response_phi12_QT5.Hmeasured()->Write("h_meas_fromResponse");
  h2_phi12_QT5_reco->Write("h2_reco");
  h2_phi12_QT5_recoMatch->Write();
  h2_meas_orig->Write("h2_meas_orig");
  h2_phi12_QT5_meas->Write("h2_meas");
  hReco_bayes_phi12_QT5->Write("h2_unf");
  h2_phi12_QT5_acceptance->Write("h2_phi12_QT5_acceptance");
  h2_purity_factor->Write("h2_purity_factor");
  h2_acceptance_factor->Write("h2_acceptance_factor");
  h_recogen_ratio->Write();
  newfile.Write();
}
if (jerSystematicsDown)
{
  TFile newfile("fit_v2_jerDown.root","recreate");
  h2_phi12_QT5_gen->Write("h2_gen");
  h2_phi12_QT5_genMatch->Write("h2_genMatch");
  h2_phi12_QT5_miss->Write("h2_miss");
  h2_phi12_QT5_fake->Write();
  response_phi12_QT5.Write("responseObject");
  response_phi12_QT5.Htruth()->Write("h_gen_fromResponse");
  response_phi12_QT5.Hmeasured()->Write("h_meas_fromResponse");
  h2_phi12_QT5_reco->Write("h2_reco");
  h2_phi12_QT5_recoMatch->Write();
  h2_meas_orig->Write("h2_meas_orig");
  h2_phi12_QT5_meas->Write("h2_meas");
  hReco_bayes_phi12_QT5->Write("h2_unf");
  h2_phi12_QT5_acceptance->Write("h2_phi12_QT5_acceptance");
  h2_purity_factor->Write("h2_purity_factor");
  h2_acceptance_factor->Write("h2_acceptance_factor");
  h_recogen_ratio->Write();
  newfile.Write();
}
if (jarSystematics)
{
  TFile newfile("fit_v2_jar.root","recreate");
  h2_phi12_QT5_gen->Write("h2_gen");
  h2_phi12_QT5_genMatch->Write("h2_genMatch");
  h2_phi12_QT5_miss->Write("h2_miss");
  h2_phi12_QT5_fake->Write();
  response_phi12_QT5.Write("responseObject");
  response_phi12_QT5.Htruth()->Write("h_gen_fromResponse");
  response_phi12_QT5.Hmeasured()->Write("h_meas_fromResponse");
  h2_phi12_QT5_reco->Write("h2_reco");
  h2_phi12_QT5_recoMatch->Write();
  h2_meas_orig->Write("h2_meas_orig");
  h2_phi12_QT5_meas->Write("h2_meas");
  hReco_bayes_phi12_QT5->Write("h2_unf");
  h2_phi12_QT5_acceptance->Write("h2_phi12_QT5_acceptance");
  h2_purity_factor->Write("h2_purity_factor");
  h2_acceptance_factor->Write("h2_acceptance_factor");
  newfile.Write();
}




}
#ifndef __CINT__
int main () { unfold_2D_phi_data_syst(); return 0; }  // Main program when run stand-alone
#endif
