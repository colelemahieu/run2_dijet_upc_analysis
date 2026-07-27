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



void unfold_2D_phi_data_rapgap_syst()
{
 // Rapidity Gap Cuts
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
  
	
 // Response Matrix, 2D phi vs QT
 RooUnfoldResponse response_phi12_QT5;
 TH2D *h2_true_phi12_QT5 = new TH2D("h2_true_phi12_QT5", "h2_true_phi12_QT5",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_smeared_phi12_QT5 = new TH2D("h2_smeared_phi12_QT5", "h2_smeared_phi12_QT5",5,0,40,12,-TMath::Pi(),TMath::Pi());
 response_phi12_QT5.Setup(h2_smeared_phi12_QT5, h2_true_phi12_QT5);
 // 2D QT slice from response matrixRooUnfoldResponse response_phi12_QT5;
 TH2D *h2_response_slice = new TH2D("h2_response_slice", "h2_response_slice",12,-TMath::Pi(),TMath::Pi(),12,-TMath::Pi(),TMath::Pi());

 //TFile *fileR4 = new TFile("allPlots_R2.root");
 //TFile *fileR4 = new TFile("allPlots_R2_rapDown.root");
 //TFile *fileR4 = new TFile("allPlots_R2_hf.root");
 //TFile *fileR4 = new TFile("allPlots_R2_rapUp.root");
 //TFile *fileR4 = new TFile("allPlots_R4_0n0n.root");
 //TFile *fileR4 = new TFile("allPlots_R4_0n0n_cut.root");
 TFile *fileR4 = new TFile("allPlots_R4.root");
 //TFile *fileR4 = new TFile("allPlots_R6_0n0n.root");
 //TFile *fileR4 = new TFile("allPlots_R4_ee.root");
 //TFile *fileR4 = new TFile("allPlots_R4_he.root");
 //TFile *fileR4 = new TFile("allPlots_R4_hf.root");
 //TFile *fileR4 = new TFile("allPlots_R4_rapUp.root");
 //TFile *fileR4 = new TFile("allPlots_R4_rapDown.root");
 //TFile *fileR4 = new TFile("allPlots_R6.root");
 //TFile *fileR4 = new TFile("allPlots_R6_hf.root");
 //TFile *fileR4 = new TFile("allPlots_R6_rapUp.root");
 //TFile *fileR4 = new TFile("allPlots_R6_rapDown.root");
 //TFile *fileR4 = new TFile("allPlots_R4_0n0n_hf.root");
 //TFile *fileR4 = new TFile("allPlots_R4_0n0n_rapUp.root");
 //TFile *fileR4 = new TFile("allPlots_R4_0n0n_rapDown.root");
 TH2D *h2_phi12_QT5_meas = (TH2D*)fileR4->Get("h2_phiQTPT_QT_mpi");
 TH2D* h2_meas_orig = (TH2D*)h2_phi12_QT5_meas->Clone("h2_meas_orig");
 

 // Gen and Reco Level 2D QT vs cos2phi for Check
 TH2D *h2_phi12_QT5_gen = new TH2D("h2_phi12_QT5_gen","h2_phi12_QT5_gen",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_QT5_genMatch = new TH2D("h2_phi12_QT5_genMatch","h2_phi12_QT5_genMatch",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_QT5_reco = new TH2D("h2_phi12_QT5_reco","h2_phi12_QT5_reco",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_QT5_recoMatch = new TH2D("h2_phi12_QT5_recoMatch","h2_phi12_QT5_recoMatch",5,0,40,12,-TMath::Pi(),TMath::Pi());
 TH2D *h2_phi12_QT5_miss = new TH2D("h2_phi12_QT5_miss","h2_phi12_QT5_miss",5,0,40,12,-TMath::Pi(),TMath::Pi()); 
 TH2D *h2_phi12_QT5_fake = new TH2D("h2_phi12_QT5_fake","h2_phi12_QT5_fake",5,0,40,12,-TMath::Pi(),TMath::Pi());
 
 // Twiki page 
 TH1D *h_recogen_ratio = new TH1D("h_recogen_ratio","h_recogen_ratio",100,0,2); 
 // TProfile check
 TProfile *h_profV2_gen  = new TProfile("h_profV2_gen","",5,0,40,-1,1);
 TProfile *h_profV2_reco  = new TProfile("h_profV2_reco","",5,0,40,-1,1);
 

 // Read in Events
 //TFile *file = new TFile("/eos/user/c/clemahie/pythiaPF_miniAOD_loose_r2.root");
 //TFile *file = new TFile("/eos/user/c/clemahie/pythiaPF_miniAOD_loose_r4.root");
 //TFile *file = new TFile("/eos/user/c/clemahie/pythiaPF_miniAOD_loose_r6.root");
 //TTree *jetTree = (TTree*)file->Get("t");
 //TTree *evtTree = (TTree*)file->Get("hiEvent");
 //TTree *pfTree = (TTree*)file->Get("pftree");
 // TChain
 TChain* jetTree = new TChain("t");
 TChain* evtTree = new TChain("hiEvent");
 TChain* pfTree = new TChain("pftree");
 // r2
 //jetTree->Add("/eos/user/c/clemahie/r2/pythiaPF_miniAOD_r2_loose_sample*.root");
 //evtTree->Add("/eos/user/c/clemahie/r2/pythiaPF_miniAOD_r2_loose_sample*.root");
 //pfTree->Add("/eos/user/c/clemahie/r2/pythiaPF_miniAOD_r2_loose_sample*.root");
 // r4
 jetTree->Add("/eos/user/c/clemahie/MC_samples/loose/pythiaPF_miniAOD_r4_loose_sample*.root");
 evtTree->Add("/eos/user/c/clemahie/MC_samples/loose/pythiaPF_miniAOD_r4_loose_sample*.root");
 pfTree->Add("/eos/user/c/clemahie/MC_samples/loose/pythiaPF_miniAOD_r4_loose_sample*.root");
 // r6
 //jetTree->Add("/eos/user/c/clemahie/r6/pythiaPF_miniAOD_r6_loose_sample*.root");
 //evtTree->Add("/eos/user/c/clemahie/r6/pythiaPF_miniAOD_r6_loose_sample*.root");
 //pfTree->Add("/eos/user/c/clemahie/r6/pythiaPF_miniAOD_r6_loose_sample*.root"); 

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
 float dPhi=0, dPhi_gen=0;
 int passGenCuts, passRecoCuts;
 int trueEvt, missEvt, fakeEvt;
 int trueCount=0, missCount=0, fakeCount=0, passGenCutsCount=0, passRecoCutsCount=0; 

 // pf leading energies
 float pfle_had, pfle_em;
 float pftotal_had, pftotal_hadE;
 float forward_rapgap=0, backward_rapgap=0, pf_etaMax, pf_etaMin;


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
      pf_etaMax=-1000, pf_etaMin=1000;
      passGenCuts=0, passRecoCuts=0;
      trueEvt=0, missEvt=0, fakeEvt=0;    

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

      // dPhi
      TLorentzVector jet1, jet2;
      jet1.SetPtEtaPhiM(jetPt[0],jetEta[0],jetPhi[0],jetM[0]);
      jet2.SetPtEtaPhiM(jetPt[1],jetEta[1],jetPhi[1],jetM[1]);
      dPhi=fabs(jet1.DeltaPhi(jet2));
      TLorentzVector jet1_gen, jet2_gen;
      jet1_gen.SetPtEtaPhiM(genPt[0], genEta[0],genPhi[0],genM[0]);
      jet2_gen.SetPtEtaPhiM(genPt[1],genEta[1],genPhi[1],genM[1]);
      dPhi_gen=fabs(jet1_gen.DeltaPhi(jet2_gen));

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

      // Evt labels
      if (nGen!=0 && nGen!=1 && (fabs(genEta[0]) < 3.0) && (fabs(genEta[1]) < 3.0) && (genPt[0]>30) && (genPt[1]>20) && (PT_norm_gen>QT_norm_gen) && (genPt[2]<20) && (QT_norm_gen<40) && (pf_hfP_max<hfP_noiseTH) && (pf_heP_max<heP_noiseTH) && (pf_eeP_max<eeP_noiseTH)) passGenCuts=1;
      if (nRef!=0 && nRef!=1 && (fabs(jetEta[0]) < 3.0) && (fabs(jetEta[1]) < 3.0) && (jetPt[0]>30) && (jetPt[1]>20) && (PT_norm>QT_norm) && (jetPt[2]<20) && (QT_norm<40) && (pf_hfP_max<hfP_noiseTH) && (pf_heP_max<heP_noiseTH) && (pf_eeP_max<eeP_noiseTH)) passRecoCuts=1;

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
	h_profV2_gen->Fill(QT_norm_gen, cos_2phi_gen);
      }
      // reco comparison histograms
      if (passRecoCuts==1)
      {
        h2_phi12_QT5_reco->Fill(QT_norm, angle12);
	h_profV2_reco->Fill(QT_norm, cos_2phi);
      }

      // Fill Response Matrix
      if (trueEvt==1)
      {
        trueCount = trueCount + 1;
        response_phi12_QT5.Fill(QT_norm, angle12, QT_norm_gen, angle12_gen);

	h2_phi12_QT5_genMatch->Fill(QT_norm_gen, angle12_gen);
	h2_phi12_QT5_recoMatch->Fill(QT_norm, angle12);
	h2_response_slice->Fill(angle12, angle12_gen);
      }
      if (missEvt==1)
      {
        missCount = missCount + 1;
	h2_phi12_QT5_miss->Fill(QT_norm_gen, angle12_gen);
        //response_phi12_QT5.Miss(QT_norm_gen, angle12_gen);
      }
      if (fakeEvt==1)
      {
        fakeCount = fakeCount + 1;
	h2_phi12_QT5_fake->Fill(QT_norm, angle12);
        //response_phi12_QT5.Fake(QT_norm, angle12);
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

// unfolding
RooUnfoldBayes unfold_bayes_phi12_QT5(&response_phi12_QT5, h2_phi12_QT5_meas, 2);
auto* hReco_bayes_phi12_QT5 = unfold_bayes_phi12_QT5.Hunfold();

// Acceptance Correction
TH2D* h2_phi12_QT5_acceptance = (TH2D*)hReco_bayes_phi12_QT5->Clone("h2_phi12_QT5_acceptance");
h2_phi12_QT5_acceptance->Divide(h2_acceptance_factor);

// write the histogram to the file
TFile newfile("fit_v2.root","recreate");
h2_phi12_QT5_gen->Write("h2_gen");
h2_phi12_QT5_genMatch->Write("h2_genMatch");
h2_phi12_QT5_miss->Write("h2_miss");
h2_phi12_QT5_fake->Write("h2_fake");
response_phi12_QT5.Write("responseObject");
response_phi12_QT5.Htruth()->Write("h_gen_fromResponse");
response_phi12_QT5.Hmeasured()->Write("h_meas_fromResponse");
h2_response_slice->Write();
h2_phi12_QT5_reco->Write("h2_reco");
h2_phi12_QT5_recoMatch->Write("h2_recoMatch");
h2_meas_orig->Write("h2_meas_orig");
h2_phi12_QT5_meas->Write("h2_meas");
hReco_bayes_phi12_QT5->Write("h2_unf");
h2_phi12_QT5_acceptance->Write("h2_phi12_QT5_acceptance");
h2_purity_factor->Write("h2_purity_factor");
h2_acceptance_factor->Write("h2_acceptance_factor");
newfile.Write();


}
#ifndef __CINT__
int main () { unfold_2D_phi_data_rapgap_syst(); return 0; }  // Main program when run stand-alone
#endif
