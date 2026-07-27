#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)

// This code is an example of the unfolding code used with RooUnfold
// This code unfolds a 2D histogram, phi vs rapidity, for the lower QT bin
// Corrections for fakes and misses (purity and acceptance) corrections must be done manually

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include "TRandom.h"
#include "TRandom3.h"
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


// calculate rapidity gap in the positive eta region
float forwardRapGap(int nTrk, vector<float> *trkPt, vector<float> *trkEta, float ptThreshold)
{
  // FOR USE INSIDE A LOOP OVER EVENTS

  float etaEdg = 2.5;
  float etaBinNumber = 25;
  float etaBin = 2*etaEdg/etaBinNumber;
  float rapGap = 0;
  bool hit = false;

  // loop over eta bins
  for(int j=1; j<etaBinNumber; j++)
    {
      // loop over tracks
      for (int k=0; k<nTrk; k++)
        {
         // For hit=true, track must be above threshold, and within the current bin, starting from the right
         //cout << trkPt[k] << endl;
           if (trkPt->at(k) > ptThreshold && (trkEta->at(k) < etaEdg && trkEta->at(k) > (etaEdg-etaBin*j))) hit=true;
        }

      if( hit == false)
        {
          rapGap = rapGap+etaBin;
        }
    }

  return rapGap;
}




int return_z(TH2 *h2_dummy, float rap, float phi)
{
 int x_bin = h2_dummy->GetXaxis()->FindBin(rap);
 int y_bin = h2_dummy->GetYaxis()->FindBin(phi);
 int z = y_bin + 12*(x_bin-1);

 return z;
}


void unfold_2D_rap0_data_syst()
{
 // Rapidity Gap systematics
 float heP_noiseTH=1.06, eeP_noiseTH=16.2, hfP_noiseTH=11.75, trackGap=1.8;
 // vary HE by 5%
 //float heP_noiseTH=0.78, eeP_noiseTH=16.2, hfP_noiseTH=11.75, trackGap=1.8;
 // vary EE by 5%
 //float heP_noiseTH=1.06, eeP_noiseTH=0.2, hfP_noiseTH=11.75, trackGap=1.8;
 // vary HF by 5%
 //float heP_noiseTH=1.06, eeP_noiseTH=16.2, hfP_noiseTH=6.75, trackGap=1.8;
 // vary rapGap up
 //float heP_noiseTH=1.06, eeP_noiseTH=16.2, hfP_noiseTH=11.75, trackGap=2.0;
 // vary rapGap down
 //float heP_noiseTH=1.06, eeP_noiseTH=16.2, hfP_noiseTH=11.75, trackGap=1.6;
 
 
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
 Files.push_back("jecFiles/Autumn18_V9_MC_L2L3Residual_AK4PF.txt");
 JEC_0 = new JetCorrector(Files), JEC_1 = new JetCorrector(Files);
 JEU_0 = new JetUncertainty("jecFiles/Autumn18_V9_MC_Uncertainty_AK4PF.txt");
 JEU_1 = new JetUncertainty("jecFiles/Autumn18_V9_MC_Uncertainty_AK4PF.txt");
 float oldPt_0=0, oldPt_1=0, corrJet_0=0, corrJet_1=0;
 
 // JER
 SingleJetCorrector JERSF_0("jecFiles/Summer19UL18_JRV2_MC_SF_AK4PFchs.txt"), JERSF_1("jecFiles/Summer19UL18_JRV2_MC_SF_AK4PFchs.txt");
 vector<double> jer_param_0={0}, jer_param_1={0};
 double jer_min_0=0, jer_max_0=0, jer_min_1=0, jer_max_1=0, jer_nom_0=0, jer_nom_1=0;

 // Phi Response Object, 12 bins
 RooUnfoldResponse response_phi12_rap;
 const int nBins=5;
 double rapidityBins[nBins+1]= {-2.5,0.0,0.5,1.0,1.5,2.5};
 TH2D *h2_true_phi12_rap = new TH2D("h2_true_phi12_rap","h2_true_phi12_rap",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_smeared_phi12_rap = new TH2D("h2_smeared_phi12_rap","h2_smeared_phi12_rap",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
 response_phi12_rap.Setup(h2_smeared_phi12_rap, h2_true_phi12_rap);
 
 // Grab Phi hist
 //TFile *fileR4 = new TFile("allPlots_R4_hf.root");
 //TFile *fileR4 = new TFile("allPlots_R4_rapUp.root");
 //TFile *fileR4 = new TFile("allPlots_R4_rapDown.root");
 TFile *fileR4 = new TFile("allPlots_R4.root");
 //TFile *fileR4 = new TFile("allPlots_R4_0n0n.root");
 //TFile *fileR4 = new TFile("allPlots_R4_corr.root");
 TH2D *h2_phi12_rap_qt0_meas = (TH2D*)fileR4->Get("h2_phi12_rap_qt0");
 TH2D* h2_meas_orig = (TH2D*)h2_phi12_rap_qt0_meas->Clone("h2_meas_orig");
 TH1D *h_z_rap_qt0_meas = (TH1D*)fileR4->Get("h_measZ_rap0"); 
 TH2D *h2_phi12_rap_qt0_gen = new TH2D("h2_phi12_rap_qt0_gen","h2_phi12_rap_qt0_gen",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_rap_qt0_genMatch = new TH2D("h2_phi12_rap_qt0_genMatch","h2_phi12_rap_qt0_genMatch",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_rap_qt0_reco = new TH2D("h2_phi12_rap_qt0_reco","h2_phi12_rap_qt0_reco",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_rap_qt0_recoMatch = new TH2D("h2_phi12_rap_qt0_recoMatch","h2_phi12_rap_qt0_recoMatch",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_rap_qt0_miss = new TH2D("h2_phi12_rap_qt0_miss","h2_phi12_rap_qt0_miss",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_rap_qt0_fake = new TH2D("h2_phi12_rap_qt0_fake","h2_phi12_rap_qt0_fake",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
 // forward folding
 TH2F *h2_dummy = new TH2F("h2_dummy","h2_dummy",nBins,rapidityBins, 12,-TMath::Pi(), TMath::Pi());
 TH1F *h_genZ = new TH1F("h_genZ","h_genZ",60,0,60);
 TH1F *h_recoMatchZ = new TH1F("h_recoMatchZ","h_recoMatchZ",60,0,60);
 TH1F *h_fakeZ = new TH1F("h_fakeZ","h_fakeZ",60,0,60);
 TH1D *h_measZ = (TH1D*)fileR4->Get("h_measZ");
 RooUnfoldResponse response_z (60, 0, 60, 60, 0, 60); 

 // Read in Events
 //TFile *file = new TFile("/eos/user/c/clemahie/pythiaPF_miniAOD_loose_r4.root");
 //TFile *file = new TFile("/eos/user/c/clemahie/pythiaPF_miniAOD_r4.root");
 //TFile *file = new TFile("/eos/user/c/clemahie/pythiaPF_miniAOD_r4_half1.root");
 //TFile *file = new TFile("/eos/user/c/clemahie/pythiaPF_miniAOD_r4_half2.root");
 TChain* jetTree = new TChain("t");
 TChain* evtTree = new TChain("hiEvent");
 TChain* pfTree = new TChain("pftree");
 jetTree->Add("/eos/user/c/clemahie/MC_samples/loose/pythiaPF_miniAOD_r4_loose_sample*.root");
 evtTree->Add("/eos/user/c/clemahie/MC_samples/loose/pythiaPF_miniAOD_r4_loose_sample*.root");
 pfTree->Add("/eos/user/c/clemahie/MC_samples/loose/pythiaPF_miniAOD_r4_loose_sample*.root");
 //TTree *jetTree = (TTree*)file->Get("t");
 //TTree *evtTree = (TTree*)file->Get("hiEvent");
 //TTree *pfTree = (TTree*)file->Get("pftree");
 
 // Read Variables
 int nTrk=0, nRef=0, nGen=0;
 float vtx_z=0, pf_hfP_max=0, pf_heP_max=0, pf_eeP_max=0;
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
 evtTree->SetBranchAddress("pf_hfP_max", &pf_hfP_max);
 evtTree->SetBranchAddress("pf_heP_max", &pf_heP_max);
 evtTree->SetBranchAddress("pf_eeP_max", &pf_eeP_max);
 pfTree->SetBranchAddress("nPF", &nPF);
 pfTree->SetBranchAddress("pfEt", &pfEt);
 pfTree->SetBranchAddress("pfE", &pfE);
 pfTree->SetBranchAddress("pfEta", &pfEta);
 pfTree->SetBranchAddress("pfPhi", &pfPhi);
 pfTree->SetBranchAddress("pfTrkEta", &pfTrkEta);
 pfTree->SetBranchAddress("pfTrkPt", &pfTrkPt);
 pfTree->SetBranchAddress("pfId", &pfId);

 // variables for v2 stuff
 float pi = TMath::Pi(), rapPrime=0, rapPrime_gen=0;
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
 int trueEvt, missEvt, fakeEvt;
 int trueCount=0, missCount=0, fakeCount=0, passGenCutsCount=0, passRecoCutsCount; 

 // pf leading energies
 float pfle_had, pfle_em;
 float pftotal_had, pftotal_hadE;
 float forward_rapgap=0, backward_rapgap=0, pf_etaMax, pf_etaMin;



 // evt loop
 for (int i=0; i<jetEnt; i++)
 //for (int i=0; i<(jetEnt/2); i++)
 //for (int i=floor(jetEnt/2); i<jetEnt; i++)
    {
      if (i%10000==0) cout << i << endl;
      jetTree->GetEntry(i);
      evtTree->GetEntry(i);
      pfTree->GetEntry(i);
      
      // initialize
      pfle_had=0, pfle_em=0, pftotal_had=0, pftotal_hadE=0;
      pf_etaMax=-1000, pf_etaMin=1000;
      passGenCuts=0, passRecoCuts=0;
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

      // NEW RAPGAP CUT
      for (int iPF=0; iPF<nPF; iPF++)
        {
          if (pfTrkEta->at(iPF)==-99) continue;
          if (pfTrkEta->at(iPF)>pf_etaMax) pf_etaMax=pfTrkEta->at(iPF);
          if (pfTrkEta->at(iPF)<pf_etaMin) pf_etaMin=pfTrkEta->at(iPF);
        }
      forward_rapgap=3-pf_etaMax;
      backward_rapgap=-3-pf_etaMin;
      if (fabs(forward_rapgap)<trackGap) continue;
      if (forward_rapgap<fabs(backward_rapgap)) continue;

      // Evt labels (for rap bin0)
      if (nGen!=0 && nGen!=1 && (fabs(genEta[0]) < 2.4) && (fabs(genEta[1]) < 2.4) && (genPt[0]>30) && (genPt[1]>20) && (PT_norm_gen>QT_norm_gen) && (genPt[2]<20) && (QT_norm_gen<40) && (pf_hfP_max<hfP_noiseTH) && (pf_heP_max<heP_noiseTH) && (pf_eeP_max<eeP_noiseTH)) passGenCuts=1;
      if (nRef!=0 && nRef!=1 && (fabs(jetEta[0]) < 2.4) && (fabs(jetEta[1]) < 2.4) && (jetPt[0]>30) && (jetPt[1]>20) && (PT_norm>QT_norm) && (jetPt[2]<20) && (QT_norm<40) && (pf_hfP_max<hfP_noiseTH) && (pf_heP_max<heP_noiseTH) && (pf_eeP_max<eeP_noiseTH)) passRecoCuts=1;

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


      // make TLorentz Dijet objects
      TLorentzVector jet1, jet2;
      jet1.SetPtEtaPhiM(jetPt[0],jetEta[0],jetPhi[0],jetM[0]);
      jet2.SetPtEtaPhiM(jetPt[1],jetEta[1],jetPhi[1],jetM[1]);
      float dijetRap = (jet1+jet2).Rapidity();
      // Since Pythia is asymmetric
      rapPrime = dijetRap*(-1);

      // gen TLorentz Dijet object
      TLorentzVector gen_jet1, gen_jet2;
      gen_jet1.SetPtEtaPhiM(genPt[0],genEta[0],genPhi[0],genM[0]);
      gen_jet2.SetPtEtaPhiM(genPt[1],genEta[1],genPhi[1],genM[1]);
      float gen_dijetRap = (gen_jet1+gen_jet2).Rapidity();
      rapPrime_gen = gen_dijetRap*(-1);


      if (passGenCuts==1)
      {
       h2_phi12_rap_qt0_gen->Fill(rapPrime_gen, angle12_gen);
      }
      if (passRecoCuts==1)
      {
       h2_phi12_rap_qt0_reco->Fill(rapPrime,angle12);
      }

      // Fill Response Matrix
      // individual qt phi bin
      if (trueEvt==1)
      {
        trueCount = trueCount + 1;
	response_phi12_rap.Fill(rapPrime, angle12, rapPrime_gen, angle12_gen);

        h2_phi12_rap_qt0_genMatch->Fill(rapPrime_gen, angle12_gen);
	h2_phi12_rap_qt0_recoMatch->Fill(rapPrime, angle12);

	// forward folding
        int genZ = return_z(h2_dummy, rapPrime_gen, angle12_gen), recoZ = return_z(h2_dummy, rapPrime, angle12);
        response_z.Fill(recoZ, genZ);
        h_recoMatchZ->Fill(recoZ);
      }
      if (missEvt==1)
      {
	missCount = missCount + 1;
	//response_phi12_rap.Miss(rapPrime_gen, angle12_gen);
	
	h2_phi12_rap_qt0_miss->Fill(rapPrime_gen, angle12_gen);
      }
      if (fakeEvt==1)
      {
        fakeCount = fakeCount + 1;
	//response_phi12_rap.Fake(rapPrime, angle12);	
	
	h2_phi12_rap_qt0_fake->Fill(rapPrime, angle12);
	h_fakeZ->Fill(return_z(h2_dummy, rapPrime, angle12));
      }

   


    } // end evt loop

// make purity histogram
TH2D* h2_purity_factor = (TH2D*)h2_phi12_rap_qt0_recoMatch->Clone("h2_purity_factor");
TH2D* h2_purity_denom = (TH2D*)h2_phi12_rap_qt0_recoMatch->Clone("h2_purity_denom");
h2_purity_denom->Sumw2();
h2_purity_denom->Add(h2_phi12_rap_qt0_fake);
h2_purity_factor->Divide(h2_phi12_rap_qt0_recoMatch,h2_purity_denom,1,1,"B");

// purity correction (for fakes)
h2_phi12_rap_qt0_meas->Sumw2();
h2_phi12_rap_qt0_meas->Multiply(h2_purity_factor);

// make acceptance histogram
TH2D* h2_acceptance_factor = (TH2D*)h2_phi12_rap_qt0_recoMatch->Clone("h2_acceptance_factor");
TH2D* h2_denom = (TH2D*)h2_phi12_rap_qt0_recoMatch->Clone("h2_denom");
h2_denom->Sumw2();
h2_denom->Add(h2_phi12_rap_qt0_miss);
h2_acceptance_factor->Divide(h2_phi12_rap_qt0_recoMatch,h2_denom,1,1,"B");

// unfolding
RooUnfoldBayes unfold_bayes_phi12_rap_qt0(&response_phi12_rap, h2_phi12_rap_qt0_meas, 2);
auto* hReco_bayes_phi12_rap_qt0 = unfold_bayes_phi12_rap_qt0.Hunfold();

// Acceptance Correction
TH2D* h2_phi12_rap_qt0_acceptance = (TH2D*)unfold_bayes_phi12_rap_qt0.Clone("h2_phi12_QT5_acceptance");
h2_phi12_rap_qt0_acceptance->Divide(h2_acceptance_factor);

// z business
TH1D* h_measZ_orig = (TH1D*)h_z_rap_qt0_meas->Clone("h_measZ_orig");
TH1D* h_recoMatchPlusFake_Z = (TH1D*)h_recoMatchZ->Clone("h_recoMatchPlusFake_Z");
h_recoMatchPlusFake_Z->Add(h_fakeZ);
TH1D* h_purity_Z = (TH1D*)h_recoMatchZ->Clone("h_purity_Z");
h_purity_Z->Divide(h_recoMatchPlusFake_Z);
h_z_rap_qt0_meas->Multiply(h_purity_Z);
RooUnfoldBayes unfold_bayes_z(&response_z, h_z_rap_qt0_meas, 2);
auto* hUnf_bayes_z = unfold_bayes_z.Hunfold();


// write new root file
if (noSystematics)
{
  TFile newfile("unfolded2D_phiRapidity_data.root","recreate"); 
  response_phi12_rap.Write("responseObject");
  response_z.Write("responseObject_z");
  response_phi12_rap.Hresponse()->Write("response_hist");
  h_z_rap_qt0_meas->Write("h_measZ");
  h_recoMatchZ->Write();
  hReco_bayes_phi12_rap_qt0->Write("h2_unf");
  hUnf_bayes_z->Write("h_unf_z");
  h2_phi12_rap_qt0_meas->Write("h2_meas");
  h2_meas_orig->Write("h2_meas_orig");
  h2_phi12_rap_qt0_gen->Write("h2_gen");
  h2_phi12_rap_qt0_genMatch->Write("h2_genMatch");
  h2_phi12_rap_qt0_reco->Write("h2_reco");
  h2_phi12_rap_qt0_recoMatch->Write("h2_recoMatch");
  h2_phi12_rap_qt0_fake->Write("h2_fake");
  h2_phi12_rap_qt0_miss->Write("h2_miss");
  h2_phi12_rap_qt0_acceptance->Write("h2_phi12_rap_qt0_acceptance");
  h2_purity_factor->Write("h2_purity_factor");
  h2_acceptance_factor->Write("h2_acceptance_factor");
  newfile.Write();
  newfile.Close();
}
if (jesSystematicsUp)
{
  TFile newfile("unfolded2D_phiRapidity_JESup_rap0.root","recreate");
  response_phi12_rap.Write("responseObject");
  response_z.Write("responseObject_z");
  response_phi12_rap.Hresponse()->Write("response_hist");
  h_z_rap_qt0_meas->Write("h_measZ");
  h_recoMatchZ->Write();
  hReco_bayes_phi12_rap_qt0->Write("h2_unf");
  hUnf_bayes_z->Write("h_unf_z");
  h2_phi12_rap_qt0_gen->Write("h2_gen");
  h2_phi12_rap_qt0_genMatch->Write("h2_genMatch");
  h2_phi12_rap_qt0_reco->Write("h2_reco");
  h2_phi12_rap_qt0_recoMatch->Write();
  h2_phi12_rap_qt0_fake->Write();
  h2_phi12_rap_qt0_miss->Write("h2_miss");
  newfile.Write();
  newfile.Close();
}
if (jecSystematicsNom)
{
  TFile newfile("unfolded2D_phiRapidity_JECnom_rap0.root","recreate");
  response_phi12_rap.Write("responseObject");
  response_z.Write("responseObject_z");
  response_phi12_rap.Hresponse()->Write("response_hist");
  h_z_rap_qt0_meas->Write("h_measZ");
  h_recoMatchZ->Write();
  hReco_bayes_phi12_rap_qt0->Write("h2_unf");
  hUnf_bayes_z->Write("h_unf_z");
  h2_phi12_rap_qt0_gen->Write("h2_gen");
  h2_phi12_rap_qt0_genMatch->Write("h2_genMatch");
  h2_phi12_rap_qt0_reco->Write("h2_reco");
  h2_phi12_rap_qt0_recoMatch->Write();
  h2_phi12_rap_qt0_fake->Write();
  h2_phi12_rap_qt0_miss->Write("h2_miss");
  h2_phi12_rap_qt0_meas->Write("h2_meas");
  newfile.Write();
  newfile.Close();
}
if (jesSystematicsDown)
{
  TFile newfile("unfolded2D_phiRapidity_JESdown_rap0.root","recreate");
  response_phi12_rap.Write("responseObject");
  response_z.Write("responseObject_z");
  response_phi12_rap.Hresponse()->Write("response_hist");
  h_z_rap_qt0_meas->Write("h_measZ");
  h_recoMatchZ->Write();
  hReco_bayes_phi12_rap_qt0->Write("h2_unf");
  hUnf_bayes_z->Write("h_unf_z");
  h2_phi12_rap_qt0_gen->Write("h2_gen");
  h2_phi12_rap_qt0_genMatch->Write("h2_genMatch");
  h2_phi12_rap_qt0_reco->Write("h2_reco");
  h2_phi12_rap_qt0_recoMatch->Write();
  h2_phi12_rap_qt0_fake->Write();
  h2_phi12_rap_qt0_miss->Write("h2_miss");
  newfile.Write();
  newfile.Close();
}
if (jerSystematicsUp)
{
  TFile newfile("unfolded2D_phiRapidity_JERup_rap0.root","recreate");
  response_phi12_rap.Write("responseObject");
  response_z.Write("responseObject_z");
  response_phi12_rap.Hresponse()->Write("response_hist");
  h_z_rap_qt0_meas->Write("h_measZ");
  h_recoMatchZ->Write();
  hReco_bayes_phi12_rap_qt0->Write("h2_unf");
  hUnf_bayes_z->Write("h_unf_z");
  h2_phi12_rap_qt0_gen->Write("h2_gen");
  h2_phi12_rap_qt0_genMatch->Write("h2_genMatch");
  h2_phi12_rap_qt0_reco->Write("h2_reco");
  h2_phi12_rap_qt0_recoMatch->Write();
  h2_phi12_rap_qt0_fake->Write();
  h2_phi12_rap_qt0_miss->Write("h2_miss");
  newfile.Write();
  newfile.Close();
}
if (jerSystematicsDown)
{
  TFile newfile("unfolded2D_phiRapidity_JERdown_rap0.root","recreate");
  response_phi12_rap.Write("responseObject");
  response_z.Write("responseObject_z");
  response_phi12_rap.Hresponse()->Write("response_hist");
  h_z_rap_qt0_meas->Write("h_measZ");
  h_recoMatchZ->Write();
  hReco_bayes_phi12_rap_qt0->Write("h2_unf");
  hUnf_bayes_z->Write("h_unf_z");
  h2_phi12_rap_qt0_gen->Write("h2_gen");
  h2_phi12_rap_qt0_genMatch->Write("h2_genMatch");
  h2_phi12_rap_qt0_reco->Write("h2_reco");
  h2_phi12_rap_qt0_recoMatch->Write();
  h2_phi12_rap_qt0_fake->Write();
  h2_phi12_rap_qt0_miss->Write("h2_miss");
  newfile.Write();
  newfile.Close();
}
if (jarSystematics)
{
  TFile newfile("unfolded2D_phiRapidity_JAR_rap0.root","recreate");
  response_phi12_rap.Write("responseObject");
  response_z.Write("responseObject_z");
  response_phi12_rap.Hresponse()->Write("response_hist");
  h_z_rap_qt0_meas->Write("h_measZ");
  h_recoMatchZ->Write();
  hReco_bayes_phi12_rap_qt0->Write("h2_unf");
  hUnf_bayes_z->Write("h_unf_z");
  h2_phi12_rap_qt0_gen->Write("h2_gen");
  h2_phi12_rap_qt0_genMatch->Write("h2_genMatch");
  h2_phi12_rap_qt0_reco->Write("h2_reco");
  h2_phi12_rap_qt0_recoMatch->Write();
  h2_phi12_rap_qt0_fake->Write();
  h2_phi12_rap_qt0_miss->Write("h2_miss");
  newfile.Write();
  newfile.Close();
}





}
#ifndef __CINT__
int main () { unfold_2D_rap0_data_syst(); return 0; }  // Main program when run stand-alone
#endif
