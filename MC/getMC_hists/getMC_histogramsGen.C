// getMC_histogramsGen.C
// this code calculates the v2=<cos(2phi)> variable
// this code also applies final event selections to gen level Pythia photonuclear MC and writes histograms to a file
// the histograms in these files are used to make analysis plots

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "TString.h"
#include "TTree.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TBranch.h"
#include "TFile.h"
#include <TTree.h>
#include <TChain.h>
#include "TCanvas.h"
#include "THStack.h"
#include "TLine.h"
#include "TMath.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TF1.h"
#include "TProfile.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "../commonUtility.h"
using namespace std;


int return_z(TH2 *h2_dummy, float qt, float phi)
{
 int x_bin = h2_dummy->GetXaxis()->FindBin(qt);
 int y_bin = h2_dummy->GetYaxis()->FindBin(phi);
 int z = y_bin + 12*(x_bin-1);

 return z;
}


void getMC_histogramsGen()
{
  bool thirdJetCut=true;
  
  // read in gen MC
  TFile *file = new TFile("../pythiaGen_miniAODr4_newCuts.root");
  TTree *jetTree = (TTree*)file->Get("t");
  TTree *evtTree = (TTree*)file->Get("hiEvent");
  TTree *pfTree = (TTree*)file->Get("pftree");

  // read variables
  int nTrk=0, nGen=0, nRef=0, trigger=0;
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

  // gen, RECO
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
  evtTree->SetBranchAddress("HLT_HIUPC_SingleEG5_NotMBHF2AND_v1", &trigger);
  pfTree->SetBranchAddress("nPF", &nPF);
  pfTree->SetBranchAddress("pfEt", &pfEt);
  pfTree->SetBranchAddress("pfE", &pfE);
  pfTree->SetBranchAddress("pfEta", &pfEta);
  pfTree->SetBranchAddress("pfPhi", &pfPhi);
  pfTree->SetBranchAddress("pfTrkEta", &pfTrkEta);
  pfTree->SetBranchAddress("pfTrkPt", &pfTrkPt);
  pfTree->SetBranchAddress("pfId", &pfId);

  // Analysis
  // Vectors for Calculating v2
  float rapPrime=0, rapPrime_gen=0;
  float pi = TMath::Pi();
  float px_1=0, px_2=0, py_1=0, py_2=0, avgRap=0;
  float px_1_gen=0, px_2_gen=0, py_1_gen=0, py_2_gen=0;
  TVector2 Q_T, P_T;
  TVector2 Q_T_gen, P_T_gen;
  float QT_norm, PT_norm, QT_phi, PT_phi, angleDiff;
  float QT_norm_gen, PT_norm_gen;
  TVector2 QT_unit, PT_unit;
  TVector2 QT_unit_gen, PT_unit_gen;
  float cos12, sin12, angle12, cos_2phi=0, cos_4phi=0, cos_6phi=0, cos_8phi=0, cos_10phi=0;
  float cos12_gen, sin12_gen, angle12_gen, cos_2phi_gen=0;
  float avg_v1=0, avg_v2=0, avg_v4=0, avg_v6=0, avg_v8=0, avg_v10=0;
  float v1_total=0, v2_total=0, v4_total=0, v6_total=0, v8_total=0, v10_total=0;
  int goodEvt=0;
  float heBad, eeBad;
  float eeMax_0nXn, eeMax_Xn0n;

  // New Root File
  TFile newfile("allPlots_test.root","recreate");
  TH1F *h_zvtx = new TH1F("h_zvtx","h_zvtx",100,-30,30);
  TH1F *h_ee_0nXn = new TH1F("h_ee_0nXn","h_ee_0nXn",100,0,20);
  TH1F *h_ee_Xn0n = new TH1F("h_ee_Xn0n","h_ee_Xn0n",100,0,20);
  TH1F *h_nRef = new TH1F("h_nRef","nRef",10,0,10);
  TH1F *h_nGen = new TH1F("h_nGen","nGen",10,0,10);
  TH1F *h_jtPt_L = new TH1F("h_jtPt_L","h_jtPt_L",40,0,80);
  TH1F *h_jtPt_S = new TH1F("h_jtPt_S","h_jtPt_S",40,0,80);
  TH1F *h_jtPt_L_gen = new TH1F("h_jtPt_L_gen","h_jtPt_L_gen",40,0,80);
  TH1F *h_jtPt_S_gen = new TH1F("h_jtPt_S_gen","h_jtPt_S_gen",40,0,80);
  TH1F *h_PT = new TH1F("h_PT","h_PT",40,0,80);
  TH1F *h_QT = new TH1F("h_QT","h_QT",40,0,80);
  TH1F *h_QTGen = new TH1F("h_QTGen","h_QTGen",40,0,80);
  TH1F *h_PT_10 = new TH1F("h_PT_10","h_PT_10",10,0,80);
  TH1F *h_QT_10 = new TH1F("h_QT_10","h_QT_10",10,0,80);
  TH1D *h_QT5_meas = new TH1D("h_QT5_meas","h_QT5_meas",5,0,40);
  TH1D *h_QT10_meas = new TH1D("h_QT10_meas","h_QT10_meas",10,0,40);
  TH1F *h_QT_40 = new TH1F("h_QT_40","h_QT_40",40,0,40);
  TH2F *h2_QTPT = new TH2F("h2_QTPT", "h2_QTPT",100,0,40,100,20,100);
  TH1D *h_phiQTPT_12 = new TH1D("h_phiQTPT_12","h_phiQTPT_12",12,-TMath::Pi(),TMath::Pi());
  TH1D *h_phiQTPT_12_abs = new TH1D("h_phiQTPT_12_abs","h_phiQTPT_12_abs",12,0,TMath::Pi());
  TH1D *h_cos2phi_meas_12 = new TH1D("h_cos2phi_meas_12","h_cos2phi_meas_12",12,-1,1);
  TH1F *h_etaRes = new TH1F("h_etaRes","genEta - jetEta",10000,-4,4);
  TH1F *h_phiRes = new TH1F("h_phiRes","genPhi - jetPhi",10000,-4,4);
  TH1F *h_dijetEtaRes = new TH1F("h_dijetEtaRes","genDijetEta - DijetEta",10000,-4,4);
  TH1F *h_QTPT_phiRes = new TH1F("h_QTPT_phiRes","gen_QTPT_phi - reco_QTPT_phi",10000,-TMath::Pi(),TMath::Pi());
  TH2F *h2_jetPhi1 = new TH2F("h2_jetPhi1","reco jet phi vs gen jet phi",100,0,50,100,0,50);
  TH1F *h_ptRes = new TH1F("h_ptRes","genPt - jetPt",100,-20,20);
  TH2F *h2_ptRes = new TH2F("h2_ptRes", "h2_ptRes",100,20,80,100,20,80);
  TH1F *h_deltaPhi_pre = new TH1F("h_deltaPhi_pre","h_deltaPhi_pre",100,-6.3,6.3);
  TH1F *h_deltaPhi = new TH1F("h_deltaPhi","h_deltaPhi",100,0,6.3);
  TH1F *h_angle12_pre = new TH1F("h_angle12_pre","h_angle12_pre",100,0,6.3);
  TH1F *h_angle12 = new TH1F("h_angle12","h_angle12",80,-TMath::Pi(),TMath::Pi());
  TH2F *h2_rapgaps_0nXn = new TH2F("h2_rapgaps_0nXn", "h2_rapgaps_0nXn",25,0,5,25,0,5);
  TH2F *h2_rapgaps_Xn0n = new TH2F("h2_rapgaps_Xn0n", "h2_rapgaps_Xn0n",25,0,5,25,0,5);
  TH1F *h_rapgap_forward = new TH1F("h_rapgaps_forward", "h_rapgaps_forward",25,0,5);
  TH1F *h_rapgap_backward = new TH1F("h_rapgaps_backward", "h_rapgaps_backward",25,0,5); 
  TProfile *h_profV1  = new TProfile("h_profV1","Profile v1",12,0,40,-1,1);
  TProfile *h_profV2  = new TProfile("h_profV2","Profile v2",12,0,40,-1,1);
  TProfile *h_profV2_gen  = new TProfile("h_profV2_gen","Profile v2 gen (pass reco)",12,0,40,-1,1);
  TProfile *h_profV2_10  = new TProfile("h_profV2_10","Profile v2 10",10,0,40,-1.0,1.0);
  TProfile *h_profV2_5  = new TProfile("h_profV2_5","Profile v2 5",5,0,40,-1,1);
  TProfile *h_profV2_full  = new TProfile("h_profV2_full","Profile v2_full",12,0,60,-1,1);
  TProfile *h_profV4  = new TProfile("h_profV4","Profile v4",12,0,40,-1,1);
  TProfile *h_profV4_5  = new TProfile("h_profV4_5","Profile v4_5",5,0,40,-1,1);
  TProfile *h_profV6  = new TProfile("h_profV6","Profile v6",12,0,40,-1,1);
  TProfile *h_profV8  = new TProfile("h_profV8","Profile v8",12,0,40,-1,1);
  TProfile *h_profV10  = new TProfile("h_profV10","Profile v10",12,0,40,-1,1);
  // QT Bins of 3
  TProfile *h_profV2_rap1_3  = new TProfile("h_profV2_rap1_3","h_profV2_rap1_3",3,0,40,-1,1);
  TProfile *h_profV2_rap2_3  = new TProfile("h_profV2_rap2_3","h_profV2_rap2_3",3,0,40,-1,1);
  TProfile *h_profV2_rap3_3  = new TProfile("h_profV2_rap3_3","h_profV2_rap3_3",3,0,40,-1,1);
  TProfile *h_profV2_rap4_3  = new TProfile("h_profV2_rap4_3","h_profV2_rap4_3",3,0,40,-1,1);
  TProfile *h_profV2_rap5_3  = new TProfile("h_profV2_rap5_3","h_profV2_rap5_3",3,0,40,-1,1);
  // QT Bins of 2
  double prime_bins[] = {0, 12, 40};
  TProfile *h_profV2_rapPrime1_2  = new TProfile("h_profV2_rapPrime1_2","h_profV2_rapPrime1_2",2,prime_bins,-1,1);
  TProfile *h_profV2_rapPrime2_2  = new TProfile("h_profV2_rapPrime2_2","h_profV2_rapPrime2_2",2,prime_bins,-1,1);
  TProfile *h_profV2_rapPrime3_2  = new TProfile("h_profV2_rapPrime3_2","h_profV2_rapPrime3_2",2,prime_bins,-1,1);
  TProfile *h_profV2_rapPrime4_2  = new TProfile("h_profV2_rapPrime4_2","h_profV2_rapPrime4_2",2,prime_bins,-1,1);
  TProfile *h_profV2_rapPrime5_2  = new TProfile("h_profV2_rapPrime5_2","h_profV2_rapPrime5_2",2,prime_bins,-1,1);
  // 2D Phi vs Rapidity
  const int nBins=5;
  double rapidityBins[nBins+1]= {-2.5,0.0,0.5,1.0,1.5,2.5};
  TH2D *h2_phi12_rap_qt0 = new TH2D("h2_phi12_rap_qt0","h2_phi12_rap_qt0",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
  TH2D *h2_phi12_rap_qt1 = new TH2D("h2_phi12_rap_qt1","h2_phi12_rap_qt1",nBins,rapidityBins, 12,-TMath::Pi(),TMath::Pi());
  
  // nJet distribution
  TH1F *h_dijetRap = new TH1F("h_dijetRap","h_dijetRap",10,-2.5,2.5);
  TH2F *h2_dijetRap_Res = new TH2F("h2_dijetRap_Res","h2_dijetRap_Res",20,-2.5,2.5,20,-2.5,2.5);
  TH2F *h2_dijetRapPrime_Res = new TH2F("h2_dijetRapPrime_Res","h2_dijetRapPrime_Res",20,-2.5,2.5,20,-2.5,2.5);

  // Phi vs Rapidity Distributions for Unfolding
  TH1F *h_phi_rapidity[2][5];
  for (int qtBin=0; qtBin<2; qtBin++)
    {
      for (int rapBin=0; rapBin<5; rapBin++)
	{
	  h_phi_rapidity[qtBin][rapBin] = new TH1F(Form("h_phi_rapidity_%i_%i",qtBin,rapBin),Form("h_phi_rapidity_%i_%i",qtBin,rapBin),12,-TMath::Pi(),TMath::Pi());
	} // end rap loop
    } // end qtBin loop
  

  // HE and EE histograms
  TH1F *h_he = new TH1F("h_he","h_he",100,0,10);
  TH1F *h_ee = new TH1F("h_ee","h_ee",100,0,10);

  // PF histograms
  TH1F *h_radius = new TH1F("h_radius","h_radius",100,0,5);
  TH1F *h_pfEt = new TH1F("h_pfEt","h_pfEt",100,0,30);
  TH1F *h_pfEta = new TH1F("h_pfEta","h_pfEta",100,-3.2,3.2);
  TH1F *h_pfEtaW = new TH1F("h_pfEtaW","h_pfEtaW",100,-3.2,3.2);

  TH1F *h_pfEt_2p8_15 = new TH1F("h_pfEt_2p8_15","h_pfEt_2p8_15",100,0,5);
  TH1F *h_pfEtsum_2p8_15 = new TH1F("h_pfEtsum_2p8_15","h_pfEtsum_2p8_15",100,0,5);
  TH1F *h_pfEsum_2p8_15 = new TH1F("h_pfEsum_2p8_15","h_pfEsum_2p8_15",100,0,30);
  TH1F *h_pfEt_2p8_4 = new TH1F("h_pfEt_2p8_4","h_pfEt_2p8_4",100,0,5);
  TH1F *h_pfE_2p8_4 = new TH1F("h_pfE_2p8_4","h_pfE_2p8_4",100,0,5);
  TH1F *h_pfId_2p8 = new TH1F("h_pfId_2p8", "h_pfId_2p8",8,0,8);
  TH1F *h_nPF_ch = new TH1F("h_nPF_ch","h_nPF_ch",40,0,40);


  TH2F *h2_v2Res = new TH2F("h2_v2Res", "h2_v2Res",15,0,40,30,-0.5,0.5);
  // hist for unfolding
  TH2F *h2_phiReco_phiGen = new TH2F("h2_phiReco_phiGen", "h2_phiReco_phiGen",40,0,6.3,20,0,6.3);
  TH2F *h2_qtReco_qtGen = new TH2F("h2_qtReco_qtGen", "h2_qtReco_qtGen",15,0,30,15,0,30);
  TH2F *h2_cosReco_cosGen = new TH2F("h2_cosReco_cosGen", "h2_cosReco_cosGen",40,-1,1,40,-1,1);
  TH1F *h_cosRes = new TH1F("h_cosRes","h_cosRes",100,-2.2,2.2);
  //TH1F *h_PhiRes = new TH1F("h_phiRes","h_phiRes",100,-7,7);
  TH2F *h2_genPhi_recoPhi = new TH2F("h2_genPhi_recoPhi","h2_genPhi_recoPhi",100,-7,7,100,-7,7);
  TH1F *h_qtRes = new TH1F("h_qtRes","h_qtRes",100,-20,20);
  TH1F *h_qtRes_x = new TH1F("h_qtRes_x","h_qtRes_x",100,-20,20);
  TH1F *h_qtRes_y = new TH1F("h_qtRes_y","h_qtRes_y",100,-20,20);
  TH1F *h_PtRes = new TH1F("h_PtRes","h_PtRes",100,-20,20);
  // hist for 2D response matrix
  TH2D *h2_true = new TH2D("h2_true", "h2_true",40,0,40.0,40,-1.0,1.0);
  TH2D *h2_smeared = new TH2D("h2_smeared", "h2_smeared",40,0,40.0,40,-1.0,1.0);
  TH2F *h_masterQT_5 = new TH2F("h_masterQT_5","h_masterQT_5",5,0,40,20,-10,10);
  TH2F *h_masterPhi_12 = new TH2F("h_masterPhi_12","h_masterPhi_12",12,0,2*(TMath::Pi()),20,-10,10);
  // pretend 2nd half of pythia is "data"
  TH2D *h2_phiQTPT_QT = new TH2D("h2_phiQTPT_QT","h2_phiQTPT_QT ",5,0,40,12,0,2*(TMath::Pi()));
  TH2D *h2_phiQTPT_QT_mpi = new TH2D("h2_phiQTPT_QT_mpi","h2_phiQTPT_QT_mpi ",5,0,40,12,-TMath::Pi(),TMath::Pi());



  // systematics /////////////////////
  TH2F *h2_genPt_recoPt = new TH2F("h2_genPt_recoPt","h2_genPt_recoPt",100,0,80,100,0,80);
  const int ptBins=6;
  TH1F *h_jetPhi_ratio[ptBins], *h_jetEta_ptBins[ptBins], *h_jetPt_ptBins[ptBins];
  TH1F *h_dijetPt_ptBins[ptBins], *h_dijetQt_ptBins[ptBins];
  for (int ptBin=0; ptBin<(ptBins); ptBin++)
    {
      h_jetPhi_ratio[ptBin] = new TH1F(Form("h_jetPhi_ratio_%i",ptBin),Form("h_jetPhi_ratio_%i",ptBin),20,-0.2,0.2);
      h_jetEta_ptBins[ptBin] = new TH1F(Form("h_jetEta_ptBins_%i",ptBin),Form("h_jetEta_ptBins_%i",ptBin),20,-0.2,0.2);
      h_jetPt_ptBins[ptBin] = new TH1F(Form("h_jetPt_ptBins_%i",ptBin),Form("h_jetPt_ptBins_%i",ptBin),20,0.4,1.8);
      h_dijetPt_ptBins[ptBin] = new TH1F(Form("h_dijetPt_ptBins_%i",ptBin),Form("h_dijetPt_ptBins_%i",ptBin),20,0.4,1.8);
      h_dijetQt_ptBins[ptBin] = new TH1F(Form("h_dijetQt_ptBins_%i",ptBin),Form("h_dijetQt_ptBins_%i",ptBin),20,0.4,1.8);
    } // end etaBin loop
  
  const int etaBins=3;
  TH1F *h_jetPhi_etaBins[etaBins], *h_jetEta_etaBins[etaBins], *h_jetPt_etaBins[etaBins];
  TH1F *h_dijetPt_etaBins[ptBins], *h_dijetQt_etaBins[ptBins];
  for (int etaBin=0; etaBin<(etaBins); etaBin++)
    {
      h_jetPhi_etaBins[etaBin] = new TH1F(Form("h_jetPhi_etaBins_%i",etaBin),Form("h_jetPhi_etaBins_%i",etaBin),20,-0.2,0.2);
      h_jetEta_etaBins[etaBin] = new TH1F(Form("h_jetEta_etaBins_%i",etaBin),Form("h_jetEta_etaBins_%i",etaBin),20,-0.2,0.2);
      h_jetPt_etaBins[etaBin] = new TH1F(Form("h_jetPt_etaBins_%i",etaBin),Form("h_jetPt_etaBins_%i",etaBin),20,0.4,1.8);
      h_dijetQt_etaBins[etaBin] = new TH1F(Form("h_dijetQt_etaBins_%i",etaBin),Form("h_dijetQt_etaBins_%i",etaBin),20,0.4,1.8);
      h_dijetPt_etaBins[etaBin] = new TH1F(Form("h_dijetPt_etaBins_%i",etaBin),Form("h_dijetPt_etaBins_%i",etaBin),20,0.4,1.8);
    } // end etaBin loop

  TH1F *h_trigger = new TH1F("h_trigger","h_trigger",2,0,2);
  
  // forward folding
  TH2F *h2_dummy = new TH2F("h2_dummy","h2_dummy",5,0,40,12,-TMath::Pi(), TMath::Pi());
  TH1D *h_measZ = new TH1D("h_measZ","h_measZ",60,0,60);
  TH2F *h2_dummy_rap0 = new TH2F("h2_dummy_rap0","h2_dummy_rap0",nBins,rapidityBins,12,-TMath::Pi(), TMath::Pi());
  TH1D *h_measZ_rap0 = new TH1D("h_measZ_rap0","h_measZ_rap0",60,0,60);
  TH2F *h2_dummy_rap1 = new TH2F("h2_dummy_rap1","h2_dummy_rap1",nBins,rapidityBins,12,-TMath::Pi(), TMath::Pi());
  TH1D *h_measZ_rap1 = new TH1D("h_measZ_rap1","h_measZ_rap1",60,0,60); 

  // good tuples
  TFile file2("goodTuples_4r_test1.root","recreate");
  TTree *jetClone = jetTree->CloneTree(0);
  TTree *evtClone = evtTree->CloneTree(0);

  // pf leading energies
  float pfle_had, pfle_em;
  float pftotal_had, pftotal_hadE;
  float pf_hfM, pf_hfP, pf_hfM_max, pf_hfP_max;
  float pf_heM, pf_heP, pf_heM_max, pf_heP_max;
  float pf_eeM, pf_eeP, pf_eeM_max, pf_eeP_max;
  float pfId_chH_sum=0;
  int chH_0nXn, chH_Xn0n;
  // pf eta max
  float forward_rapgap=0, backward_rapgap=0, pf_etaMax, pf_etaMin;

  
  // event loop
  for (int i=0; i<jetEnt; i++)
    {
      jetTree->GetEntry(i);
      evtTree->GetEntry(i);
      pfTree->GetEntry(i);
      heBad=0;
      eeBad=0;
      eeMax_0nXn=0;
      eeMax_Xn0n=0;
      pfId_chH_sum=0;
      pfle_had=0, pfle_em=0, pftotal_had=0, pftotal_hadE=0;
      pf_hfM=0, pf_hfP=0, pf_hfM_max=0, pf_hfP_max=0;
      pf_heM=0, pf_heP=0, pf_heM_max=0, pf_heP_max=0;
      pf_eeM=0, pf_eeP=0, pf_eeM_max=0, pf_eeP_max=0;
      chH_0nXn=0, chH_Xn0n=0;
      pf_etaMax=-1000, pf_etaMin=1000;
      h_zvtx->Fill(vtx_z);

      
      // phiRes2
      if ((genPhi[0]-jetPhi[0])<-2)
	{
	  h2_jetPhi1->Fill(genPhi[0],jetPhi[0]);
	}
      
      if ((genPhi[1]-jetPhi[1])<-2)
	{
	  h2_jetPhi1->Fill(genPhi[1],jetPhi[1]);
	}
      h2_ptRes->Fill(genPt[0],jetPt[0]);
      h2_ptRes->Fill(genPt[1],jetPt[1]);
        

      // RAPGAP CUT
      for (int iPF=0; iPF<nPF; iPF++)
	{
	  if (pfTrkEta->at(iPF)==-99) continue;
	  if (pfTrkEta->at(iPF)>pf_etaMax) pf_etaMax=pfTrkEta->at(iPF);
	  if (pfTrkEta->at(iPF)<pf_etaMin) pf_etaMin=pfTrkEta->at(iPF);
	}
      forward_rapgap=3-pf_etaMax;
      backward_rapgap=-3-pf_etaMin;

      // fill rapgap hist 0nXn
      h2_rapgaps_0nXn->Fill(fabs(backward_rapgap),fabs(forward_rapgap));
      // fill rapgap hist Xn0n
      h2_rapgaps_Xn0n->Fill(fabs(backward_rapgap),fabs(forward_rapgap));
   
      if (forward_rapgap<1.2) continue;        
      if (forward_rapgap<backward_rapgap) continue;
      

      
      // get max pfE for hf, HE
      // PF Loop
      for (int iPF=0; iPF<nPF; iPF++)
        {
          // HF+
          if (pfEta->at(iPF)>3 && pfEta->at(iPF)<5.2)
            {
              pf_hfP = pfE->at(iPF);
            }
          if (pf_hfP >= pf_hfP_max) pf_hfP_max = pf_hfP;
          // HE+
          if (pfEta->at(iPF)>2.8 && pfEta->at(iPF)<3.0)
            {
              if (pfId->at(iPF)==1 || pfId->at(iPF)==5)
                {
                  if (pfE->at(iPF) >= pf_heP_max) pf_heP_max = pfE->at(iPF);
                }
            } 
          // EE+
          if (pfEta->at(iPF)>2.8 && pfEta->at(iPF)<3.0)
            {
              if (pfId->at(iPF)==4)
                {
                  if (pfE->at(iPF) >= pf_eeP_max) pf_eeP_max = pfE->at(iPF);
                }
            }
	  // charged hadron in 2.4-3 region
          if (pfId->at(iPF)==1)
                {
                  if (pfEta->at(iPF)>(2.4) && pfEta->at(iPF)<(3.0))
                    {
                      chH_Xn0n=chH_Xn0n+1;
                    }
                }
         
        } // end PF Loop
      // apply HF, HE, EE noise cuts
	if (pf_hfP_max>11.75) continue;
        if (pf_heP_max>1.06) continue;
        if (pf_eeP_max>16.2) continue;

	
      // count number ch hadrons
      for (int iPF=0; iPF<nPF; iPF++)
	{	  
	  if (pfId->at(iPF)==1) pfId_chH_sum = pfId_chH_sum+1;
	}
      
      h_pfEt_2p8_15->Fill(pfle_had);
      h_pfEtsum_2p8_15->Fill(pftotal_had);
      h_pfEsum_2p8_15->Fill(pftotal_hadE);
      h_pfEt_2p8_4->Fill(pfle_em);


      // Calculate px1, py1, px2, py2 (RECO)
      px_1=(jetPt[0])*(cos(jetPhi[0]));
      py_1=(jetPt[0])*(sin(jetPhi[0]));
      px_2=(jetPt[1])*(cos(jetPhi[1]));
      py_2=(jetPt[1])*(sin(jetPhi[1]));

      px_1_gen=(genPt[0])*(cos(genPhi[0]));
      py_1_gen=(genPt[0])*(sin(genPhi[0]));
      px_2_gen=(genPt[1])*(cos(genPhi[1]));
      py_2_gen=(genPt[1])*(sin(genPhi[1]));

      
      // Define QT and PT 2-vectors
      float random=0;
      random=rand()%(2)+1;
      Q_T.Set(px_1+px_2, py_1+py_2);
      if (random==1) P_T.Set(0.5*(px_1-px_2), 0.5*(py_1-py_2));
      if (random==2) P_T.Set(0.5*(px_2-px_1), 0.5*(py_2-py_1));
      float randomGen=0;
      randomGen=rand()%(2)+1;
      Q_T_gen.Set(px_1_gen+px_2_gen, py_1_gen+py_2_gen);
      if (randomGen==1) P_T_gen.Set(0.5*(px_1_gen-px_2_gen), 0.5*(py_1_gen-py_2_gen));
      if (randomGen==2) P_T_gen.Set(0.5*(px_2_gen-px_1_gen), 0.5*(py_2_gen-py_1_gen));

      // Compute the norm of QT, PT
      QT_norm = sqrt(Q_T.X()*Q_T.X() + Q_T.Y()*Q_T.Y());
      PT_norm = sqrt(P_T.X()*P_T.X() + P_T.Y()*P_T.Y());
      QT_norm_gen = sqrt(Q_T_gen.X()*Q_T_gen.X() + Q_T_gen.Y()*Q_T_gen.Y());
      PT_norm_gen = sqrt(P_T_gen.X()*P_T_gen.X() + P_T_gen.Y()*P_T_gen.Y());

      // Further selections
      h2_QTPT->Fill(QT_norm,PT_norm);
      if (PT_norm_gen<QT_norm_gen) continue;

      h_nRef->Fill(nRef);
      h_nGen->Fill(nGen);

      // get rid of 3rd jets
      if (thirdJetCut)
	{
	  if (genPt[2] > 20) continue;
	}

      
      // make TLorentz Dijet objects for the good evts
      TLorentzVector jet1, jet2;
      jet1.SetPtEtaPhiM(jetPt[0],jetEta[0],jetPhi[0],jetM[0]);
      jet2.SetPtEtaPhiM(jetPt[1],jetEta[1],jetPhi[1],jetM[1]);
      float dijetRap = (jet1+jet2).Rapidity();
      float dPhi=fabs(jet1.DeltaPhi(jet2));
      // 5pi/6 cut
      //if (dPhi<5*TMath::Pi()/6) continue;
      // Since Pythia is asymmetric
      rapPrime = dijetRap*(-1);

      // gen TLorentz Dijet object
      TLorentzVector gen_jet1, gen_jet2;
      gen_jet1.SetPtEtaPhiM(genPt[0],genEta[0],genPhi[0],genM[0]);
      gen_jet2.SetPtEtaPhiM(genPt[1],genEta[1],genPhi[1],genM[1]);
      float gen_dijetRap = (gen_jet1+gen_jet2).Rapidity();
      rapPrime_gen = gen_dijetRap*(-1);

      
      goodEvt = goodEvt + 1;



      // Calculate v2 stuff
      // Make unit vectors of QT, PT
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

      // Qt and Pt angles
      QT_phi = atan2(QT_unit.Y(), QT_unit.X());
      PT_phi = atan2(PT_unit.Y(), PT_unit.X());
      angleDiff = PT_phi - QT_phi;
      if (angleDiff < 0) angleDiff = angleDiff + 2*pi;

      
      // Compute the angle by using arctan2 function
      angle12 = atan2(sin12, cos12);
      float angle12_orig = angle12;
      angle12_gen = atan2(sin12_gen, cos12_gen);

      // cos(n*phi) values
      cos_2phi = cos(2*angle12);
      float cos_2phi_orig = cos(2*angle12_orig);
      cos_4phi = cos(4*angle12);
      cos_6phi = cos(6*angle12);
      cos_8phi = cos(8*angle12);
      cos_10phi = cos(10*angle12);
      cos_2phi_gen = cos(2*angle12_gen);
      h2_v2Res->Fill(QT_norm_gen, (cos_2phi-cos_2phi_gen)/cos_2phi_gen);

      v1_total = v1_total + cos12;
      v2_total = v2_total + cos_2phi_gen;
      v4_total = v4_total + cos_4phi;
      v6_total = v6_total + cos_6phi;
      v8_total = v8_total + cos_8phi;
      v10_total = v10_total + cos_10phi;


      // fill histograms
      h_dijetRap->Fill(rapPrime);
      h2_dijetRap_Res->Fill(gen_dijetRap, dijetRap);
      h2_dijetRapPrime_Res->Fill(rapPrime_gen, rapPrime);
      if (rapPrime>-2.5 && rapPrime<0)
	{
	  h_profV2_rapPrime1_2->Fill(QT_norm,cos_2phi);
	  if (QT_norm>0 && QT_norm<12) h_phi_rapidity[0][0]->Fill(angle12);
	  if (QT_norm>12 && QT_norm<40) h_phi_rapidity[1][0]->Fill(angle12);
	}
      if (rapPrime>0 && rapPrime<0.5)
	{
	  h_profV2_rapPrime2_2->Fill(QT_norm,cos_2phi);
	  if (QT_norm>0 && QT_norm<12) h_phi_rapidity[0][1]->Fill(angle12);
	  if (QT_norm>12 && QT_norm<40) h_phi_rapidity[1][1]->Fill(angle12);
	}
      if (rapPrime>0.5 && rapPrime<1.0)
	{
	  h_profV2_rapPrime3_2->Fill(QT_norm,cos_2phi);
	  if (QT_norm>0 && QT_norm<12) h_phi_rapidity[0][2]->Fill(angle12);
	  if (QT_norm>12 && QT_norm<40) h_phi_rapidity[1][2]->Fill(angle12);
	}
      if (rapPrime>1.0 && rapPrime<1.5)
	{
	  h_profV2_rapPrime4_2->Fill(QT_norm,cos_2phi);
	  if (QT_norm>0 && QT_norm<12) h_phi_rapidity[0][3]->Fill(angle12);
	  if (QT_norm>12 && QT_norm<40) h_phi_rapidity[1][3]->Fill(angle12);
	}
      if (rapPrime>1.5 && rapPrime<2.5)
	{
	  h_profV2_rapPrime5_2->Fill(QT_norm,cos_2phi);
	  if (QT_norm>0 && QT_norm<12) h_phi_rapidity[0][4]->Fill(angle12);
	  if (QT_norm>12 && QT_norm<40) h_phi_rapidity[1][4]->Fill(angle12);
	}
      if (QT_norm>0 && QT_norm<12) h2_phi12_rap_qt0->Fill(rapPrime, angle12);
      if (QT_norm>12 && QT_norm<40) h2_phi12_rap_qt1->Fill(rapPrime, angle12);


      if (jetsProperOrder(genPhi[0], genEta[0], jetPhi[0], jetEta[0], jetPhi[1], jetEta[1])==1)
	{
	  h2_genPt_recoPt->Fill(genPt[0],jetPt[0]);
	  h2_genPt_recoPt->Fill(genPt[1],jetPt[1]);
	  h_etaRes->Fill(genEta[0]-jetEta[0]);
          h_phiRes->Fill(genPhi[0]-jetPhi[0]);
          h_etaRes->Fill(genEta[1]-jetEta[1]);
          h_phiRes->Fill(genPhi[1]-jetPhi[1]);

	  // ptBins
	  if (genPt[1]>20 && genPt[1]<25)
	    {
	      h_jetPhi_ratio[0]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_ptBins[0]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_ptBins[0]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_ptBins[0]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[0]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>25 && genPt[1]<30)
	    {
	      h_jetPhi_ratio[1]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_ptBins[1]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_ptBins[1]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_ptBins[1]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[1]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>30 && genPt[1]<35)
	    {
	      h_jetPhi_ratio[2]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_ptBins[2]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_ptBins[2]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_ptBins[2]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[2]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[0]>30 && genPt[0]<35)
	    {
	      h_jetPhi_ratio[2]->Fill(jetPhi[0]-genPhi[0]);
	      h_jetEta_ptBins[2]->Fill(jetEta[0]-genEta[0]);
	      h_jetPt_ptBins[2]->Fill(jetPt[0]/genPt[0]);
	      h_dijetPt_ptBins[2]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[2]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>35 && genPt[1]<40)
	    {
	      h_jetPhi_ratio[3]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_ptBins[3]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_ptBins[3]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_ptBins[3]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[3]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[0]>35 && genPt[0]<40)
	    {
	      h_jetPhi_ratio[3]->Fill(jetPhi[0]-genPhi[0]);
	      h_jetEta_ptBins[3]->Fill(jetEta[0]-genEta[0]);
	      h_jetPt_ptBins[3]->Fill(jetPt[0]/genPt[0]);
	      h_dijetPt_ptBins[3]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[3]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>40 && genPt[1]<45)
	    {
	      h_jetPhi_ratio[4]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_ptBins[4]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_ptBins[4]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_ptBins[4]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[4]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[0]>40 && genPt[0]<45)
	    {
	      h_jetPhi_ratio[4]->Fill(jetPhi[0]-genPhi[0]);
	      h_jetEta_ptBins[4]->Fill(jetEta[0]-genEta[0]);
	      h_jetPt_ptBins[4]->Fill(jetPt[0]/genPt[0]);
	      h_dijetPt_ptBins[4]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[4]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>45 && genPt[1]<50)
	    {
	      h_jetPhi_ratio[5]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_ptBins[5]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_ptBins[5]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_ptBins[5]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[5]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[0]>45 && genPt[0]<50)
	    {
	      h_jetPhi_ratio[5]->Fill(jetPhi[0]-genPhi[0]);
	      h_jetEta_ptBins[5]->Fill(jetEta[0]-genEta[0]);
	      h_jetPt_ptBins[5]->Fill(jetPt[0]/genPt[0]);
	      h_dijetPt_ptBins[5]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[5]->Fill(QT_norm/QT_norm_gen);
	    }
	  // etaBins
	  if (genEta[0]>0 && genEta[0]<0.8)
	    {
	      h_jetPhi_etaBins[0]->Fill(jetPhi[0]-genPhi[0]);
	      h_jetEta_etaBins[0]->Fill(jetEta[0]-genEta[0]);
	      h_jetPt_etaBins[0]->Fill(jetPt[0]/genPt[0]);
	      h_dijetPt_etaBins[0]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[0]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>0 && genEta[0]<0.8)
	    {
	      h_jetPhi_etaBins[0]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_etaBins[0]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_etaBins[0]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_etaBins[0]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[0]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>0.8 && genEta[0]<1.6)
	    {
	      h_jetPhi_etaBins[1]->Fill(jetPhi[0]-genPhi[0]);
	      h_jetEta_etaBins[1]->Fill(jetEta[0]-genEta[0]);
	      h_jetPt_etaBins[1]->Fill(jetPt[0]/genPt[0]);
	      h_dijetPt_etaBins[1]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[1]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>0.8 && genEta[0]<1.6)
	    {
	      h_jetPhi_etaBins[1]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_etaBins[1]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_etaBins[1]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_etaBins[1]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[1]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>1.6 && genEta[0]<2.4)
	    {
	      h_jetPhi_etaBins[2]->Fill(jetPhi[0]-genPhi[0]);
	      h_jetEta_etaBins[2]->Fill(jetEta[0]-genEta[0]);
	      h_jetPt_etaBins[2]->Fill(jetPt[0]/genPt[0]);
	      h_dijetPt_etaBins[2]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[2]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>1.6 && genEta[0]<2.4)
	    {
	      h_jetPhi_etaBins[2]->Fill(jetPhi[1]-genPhi[1]);
	      h_jetEta_etaBins[2]->Fill(jetEta[1]-genEta[1]);
	      h_jetPt_etaBins[2]->Fill(jetPt[1]/genPt[1]);
	      h_dijetPt_etaBins[2]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[2]->Fill(QT_norm/QT_norm_gen);
	    }
	  
	}
	if (jetsProperOrder(genPhi[0], genEta[0], jetPhi[0], jetEta[0], jetPhi[1], jetEta[1])==0)
	{
	  h2_genPt_recoPt->Fill(genPt[0],jetPt[1]);
	  h2_genPt_recoPt->Fill(genPt[1],jetPt[0]);
	  h_etaRes->Fill(genEta[0]-jetEta[1]);
          h_phiRes->Fill(genPhi[0]-jetPhi[1]);
          h_etaRes->Fill(genEta[1]-jetEta[0]);
          h_phiRes->Fill(genPhi[1]-jetPhi[0]);

	  // ratios
	  if (genPt[1]>20 && genPt[1]<25)
	    {
	      h_jetPhi_ratio[0]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_ptBins[0]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_ptBins[0]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_ptBins[0]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[0]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>25 && genPt[1]<30)
	    {
	      h_jetPhi_ratio[1]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_ptBins[1]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_ptBins[1]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_ptBins[1]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[1]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>30 && genPt[1]<35)
	    {
	      h_jetPhi_ratio[2]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_ptBins[2]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_ptBins[2]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_ptBins[2]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[2]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[0]>30 && genPt[0]<35)
	    {
	      h_jetPhi_ratio[2]->Fill(jetPhi[0]-genPhi[1]);
	      h_jetEta_ptBins[2]->Fill(jetEta[0]-genEta[1]);
	      h_jetPt_ptBins[2]->Fill(jetPt[0]/genPt[1]);
	      h_dijetPt_ptBins[2]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[2]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>35 && genPt[1]<40)
	    {
	      h_jetPhi_ratio[3]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_ptBins[3]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_ptBins[3]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_ptBins[3]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[3]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[0]>35 && genPt[0]<40)
	    {
	      h_jetPhi_ratio[3]->Fill(jetPhi[0]-genPhi[1]);
	      h_jetEta_ptBins[3]->Fill(jetEta[0]-genEta[1]);
	      h_jetPt_ptBins[3]->Fill(jetPt[0]/genPt[1]);
	      h_dijetPt_ptBins[3]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[3]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>40 && genPt[1]<45)
	    {
	      h_jetPhi_ratio[4]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_ptBins[4]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_ptBins[4]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_ptBins[4]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[4]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[0]>40 && genPt[0]<45)
	    {
	      h_jetPhi_ratio[4]->Fill(jetPhi[0]-genPhi[1]);
	      h_jetEta_ptBins[4]->Fill(jetEta[0]-genEta[1]);
	      h_jetPt_ptBins[4]->Fill(jetPt[0]/genPt[1]);
	      h_dijetPt_ptBins[4]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[4]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[1]>45 && genPt[1]<50)
	    {
	      h_jetPhi_ratio[5]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_ptBins[5]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_ptBins[5]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_ptBins[5]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[5]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genPt[0]>45 && genPt[0]<50)
	    {
	      h_jetPhi_ratio[5]->Fill(jetPhi[0]-genPhi[1]);
	      h_jetEta_ptBins[5]->Fill(jetEta[0]-genEta[1]);
	      h_jetPt_ptBins[5]->Fill(jetPt[0]/genPt[1]);
	      h_dijetPt_ptBins[5]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_ptBins[5]->Fill(QT_norm/QT_norm_gen);
	    }
	  // etaBins
	  if (genEta[0]>0 && genEta[0]<0.8)
	    {
	      h_jetPhi_etaBins[0]->Fill(jetPhi[0]-genPhi[1]);
	      h_jetEta_etaBins[0]->Fill(jetEta[0]-genEta[1]);
	      h_jetPt_etaBins[0]->Fill(jetPt[0]/genPt[1]);
	      h_dijetPt_etaBins[0]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[0]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>0 && genEta[0]<0.8)
	    {
	      h_jetPhi_etaBins[0]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_etaBins[0]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_etaBins[0]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_etaBins[0]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[0]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>0.8 && genEta[0]<1.6)
	    {
	      h_jetPhi_etaBins[1]->Fill(jetPhi[0]-genPhi[1]);
	      h_jetEta_etaBins[1]->Fill(jetEta[0]-genEta[1]);
	      h_jetPt_etaBins[1]->Fill(jetPt[0]/genPt[1]);
	      h_dijetPt_etaBins[1]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[1]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>0.8 && genEta[0]<1.6)
	    {
	      h_jetPhi_etaBins[1]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_etaBins[1]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_etaBins[1]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_etaBins[1]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[1]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>1.6 && genEta[0]<2.4)
	    {
	      h_jetPhi_etaBins[2]->Fill(jetPhi[0]-genPhi[1]);
	      h_jetEta_etaBins[2]->Fill(jetEta[0]-genEta[1]);
	      h_jetPt_etaBins[2]->Fill(jetPt[0]/genPt[1]);
	      h_dijetPt_etaBins[2]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[2]->Fill(QT_norm/QT_norm_gen);
	    }
	  if (genEta[0]>1.6 && genEta[0]<2.4)
	    {
	      h_jetPhi_etaBins[2]->Fill(jetPhi[1]-genPhi[0]);
	      h_jetEta_etaBins[2]->Fill(jetEta[1]-genEta[0]);
	      h_jetPt_etaBins[2]->Fill(jetPt[1]/genPt[0]);
	      h_dijetPt_etaBins[2]->Fill(PT_norm/PT_norm_gen);
	      h_dijetQt_etaBins[2]->Fill(QT_norm/QT_norm_gen);
	    }
	}
	h_dijetEtaRes->Fill(gen_dijetRap-dijetRap);
	h_QTPT_phiRes->Fill(angle12_gen-angle12);


      
      h_rapgap_backward->Fill(backward_rapgap);
      h_rapgap_forward->Fill(forward_rapgap);	
      //h_zvtx->Fill(vtx_z);
      h_measZ->Fill(return_z(h2_dummy, QT_norm, angle12));
      h_jtPt_L->Fill(jetPt[0]);
      h_jtPt_S->Fill(jetPt[1]);
      h_jtPt_L_gen->Fill(genPt[0]);
      h_jtPt_S_gen->Fill(genPt[1]);
      h_ptRes->Fill(genPt[0]-jetPt[0]);
      h_ptRes->Fill(genPt[1]-jetPt[1]);
      h_PT->Fill(PT_norm);
      h_QT->Fill(QT_norm);
      h_QTGen->Fill(QT_norm_gen);
      h_PT_10->Fill(PT_norm);
      h_QT_10->Fill(QT_norm);
      h_QT5_meas->Fill(QT_norm);
      h_QT10_meas->Fill(QT_norm);
      h_phiQTPT_12->Fill(angle12_orig);
      h_phiQTPT_12_abs->Fill(fabs(angle12_orig));
      h_cos2phi_meas_12->Fill(cos_2phi_orig);
      h_QT_40->Fill(QT_norm);
      h_profV1->Fill(QT_norm, cos12);
      h_profV2->Fill(QT_norm,cos_2phi);
      h_profV2_gen->Fill(QT_norm_gen,cos_2phi_gen);
      h_profV2_10->Fill(QT_norm,cos_2phi);
      h_profV2_5->Fill(QT_norm,cos_2phi);
      h_profV2_full->Fill(QT_norm,cos_2phi);
      h_profV4->Fill(QT_norm,cos_4phi);
      h_profV4_5->Fill(QT_norm,cos_4phi);
      h_profV6->Fill(QT_norm,cos_6phi);
      h_profV8->Fill(QT_norm,cos_8phi);
      h_profV10->Fill(QT_norm,cos_10phi);
      h_deltaPhi->Fill(angleDiff);
      h_deltaPhi_pre->Fill(PT_phi - QT_phi);
      h_angle12->Fill(angle12);
      h_angle12_pre->Fill(atan2(sin12, cos12));
      h2_phiReco_phiGen->Fill(angle12,angle12_gen);
      h2_cosReco_cosGen->Fill(cos_2phi_gen, cos_2phi);
      h_cosRes->Fill(cos_2phi_gen - cos_2phi);
      h2_genPhi_recoPhi->Fill(angle12_gen, angle12);
      h_qtRes->Fill(QT_norm_gen-QT_norm);
      h_qtRes_x->Fill(Q_T_gen.X()-Q_T.X());
      h_qtRes_y->Fill(Q_T_gen.Y()-Q_T.Y());
      h_PtRes->Fill(PT_norm_gen-PT_norm);
      h2_qtReco_qtGen->Fill(QT_norm_gen, QT_norm);
      h2_smeared->Fill(QT_norm, cos_2phi);
      h2_true->Fill(QT_norm_gen, cos_2phi_gen);
      h2_phiQTPT_QT->Fill(QT_norm, angle12);
      h2_phiQTPT_QT_mpi->Fill(QT_norm, angle12);
      h_masterQT_5->Fill(QT_norm_gen, (QT_norm-QT_norm_gen)/QT_norm_gen);
      float fillAngleDiff = angle12-angle12_gen;
      h_masterPhi_12->Fill(angle12_gen, (fillAngleDiff)/angle12_gen);
      h_trigger->Fill(trigger);
      h_nPF_ch->Fill(pfId_chH_sum);
  
      
    } // end event loop 

  // print out v2 info
  avg_v2 = v2_total / goodEvt;
  avg_v4 = v4_total / goodEvt;
  avg_v6 = v6_total / goodEvt;
  avg_v8 = v8_total / goodEvt;
  avg_v10 = v10_total / goodEvt;
  cout << "overall v2=" << avg_v2 << endl;
  cout << "overall v4=" << avg_v4 << endl;
  cout << "overall v6=" << avg_v6 << endl;
  cout << "overall v8=" << avg_v8 << endl;
  cout << "overall v10=" << avg_v10 << endl;
  cout << goodEvt << endl;

  // write histograms
  h_measZ->Write();
  h_zvtx->Write();
  h_ee_0nXn->Write();
  h_ee_Xn0n->Write();
  h_nRef->Write();
  h_nGen->Write();
  h_jtPt_L->Write();
  h_jtPt_S->Write();
  h_jtPt_L_gen->Write();
  h_jtPt_S_gen->Write();
  h_PT->Write();
  h_QT->Write();
  h_QTGen->Write();
  h_PT_10->Write();
  h_QT_10->Write();
  h_QT5_meas->Write();
  h_QT10_meas->Write();
  h_QT_40->Write();
  h_phiQTPT_12->Write();
  h_phiQTPT_12_abs->Write();
  h_cos2phi_meas_12->Write();
  h2_QTPT->Write();
  h_etaRes->Write();
  h_phiRes->Write();
  h_dijetEtaRes->Write();
  h_QTPT_phiRes->Write();
  h_ptRes->Write();
  h2_jetPhi1->Write();
  h2_ptRes->Write();
  h_deltaPhi->Write();
  h_deltaPhi_pre->Write();
  h_angle12->Write();
  h_angle12_pre->Write();
  h2_rapgaps_0nXn->Write();
  h2_rapgaps_Xn0n->Write();
  h_rapgap_backward->Write();
  h_rapgap_forward->Write();
  h2_phiReco_phiGen->Write();
  h2_qtReco_qtGen->Write();
  h2_cosReco_cosGen->Write();
  h2_phiQTPT_QT->Write();
  h2_phiQTPT_QT_mpi->Write();
  h_cosRes->Write();
  h2_genPhi_recoPhi->Write();
  h2_true->Write();
  h2_smeared->Write();
  h_qtRes->Write();
  h_qtRes_x->Write();
  h_qtRes_y->Write();
  h_PtRes->Write();
  h_profV2->Write();
  h_profV2_gen->Write();
  h_profV2_10->Write();
  h_profV2_5->Write();
  h_profV4->Write();
  h_profV4_5->Write();
  h_profV6->Write();
  h_profV8->Write();
  h_profV10->Write();
  h_profV2_rapPrime1_2->Write();
  h_profV2_rapPrime2_2->Write();
  h_profV2_rapPrime3_2->Write();
  h_profV2_rapPrime4_2->Write();
  h_profV2_rapPrime5_2->Write();
  h2_phi12_rap_qt0->Write();
  h2_phi12_rap_qt1->Write();
  h_dijetRap->Write();
  h2_dijetRap_Res->Write();
  h2_dijetRapPrime_Res->Write();
  h_pfEtsum_2p8_15->Write();
  h_pfEsum_2p8_15->Write();

  h2_genPt_recoPt->Write();
  for (int qtBin=0; qtBin<2; qtBin++)
    {
      for (int rapBin=0; rapBin<5; rapBin++)
	{
	  h_phi_rapidity[qtBin][rapBin]->Write();
	} // end rap loop
    } // end qtBin loop

  // systematics
  for (int ptBin=0; ptBin<(ptBins); ptBin++)
    {
      h_jetPhi_ratio[ptBin]->Write();
      h_jetEta_ptBins[ptBin]->Write();
      h_jetPt_ptBins[ptBin]->Write();
    } // end ptBin loop
  for (int etaBin=0; etaBin<(etaBins); etaBin++)
    {
      h_jetPhi_etaBins[etaBin]->Write();
      h_jetEta_etaBins[etaBin]->Write();
      h_jetPt_etaBins[etaBin]->Write();
    } // end etaBin loop
  h_trigger->Write();
  h_nPF_ch->Write();  
  newfile.Write();
  

} // end code
