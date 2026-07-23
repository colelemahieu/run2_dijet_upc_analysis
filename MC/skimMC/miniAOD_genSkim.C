// miniAOD_genSkim.C
// this skims the MC Forest files (gen level) and applies some inital cuts

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
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
using namespace std;

void miniAOD_genSkim(string inputfile, string outfile)
{    
  TChain* calochain = new TChain("ggHiNtuplizer/EventTree");
  //TChain* jetchain = new TChain("ak2PFJetAnalyzer/t");
  TChain* jetchain = new TChain("ak4PFJetAnalyzer/t");
  //TChain* jetchain = new TChain("ak6PFJetAnalyzer/t");
  TChain* hiEvtchain = new TChain("hiEvtAnalyzer/HiTree");
  TChain* pfchain = new TChain("particleFlowAnalyser/pftree");

  jetchain->Add(inputfile.c_str());
  hiEvtchain->Add(inputfile.c_str());
  pfchain->Add(inputfile.c_str());

  int jetentries = jetchain->GetEntries();
  int hiEvtEntries = hiEvtchain->GetEntries();
  cout << "Entries in jet chain = " << jetentries << endl;
  cout << "Entries in hiEvt chain = " << hiEvtEntries << endl;


  // Tree Variables
  int nGen=0, nRef=0, n=0, nPFpart=0, vtxFilter=0, clusterFilter=0;
  unsigned int run=0, lumis=0;
  ULong64_t event=0;
  float vtx_z=0;
  float genPt[200]={0}, genEta[200]={0}, genPhi[200]={0}, genM[200]={0};
  float jetPt[200]={0}, jetEta[200]={0}, jetPhi[200]={0}, jetM[200]={0};
  vector<float> *pfEnergy=0, *pfEta=0, *pfPhi=0, *pfPt=0, *pfEt=0, *pfE=0, *pfTrkEta=0, *pfTrkPt=0;
  vector<int> *pfId=0;

  // miniAOD read Variables
  float hiHE_pfle=0, hiHEMinus_pfle=0, hiHEPlus_pfle=0;
  float hiEE_pfle=0, hiEEMinus_pfle=0, hiEEPlus_pfle=0; 

  hiEvtchain->SetBranchAddress("vz",&vtx_z);
  jetchain->SetBranchStatus("*",0);
  jetchain->SetBranchStatus("nref",1);
  jetchain->SetBranchStatus("jtpt",1);
  jetchain->SetBranchStatus("jteta",1);
  jetchain->SetBranchStatus("jtphi",1);
  jetchain->SetBranchStatus("jtm",1);
  jetchain->SetBranchStatus("ngen",1);
  jetchain->SetBranchStatus("genpt",1);
  jetchain->SetBranchStatus("geneta",1);
  jetchain->SetBranchStatus("genphi",1);
  jetchain->SetBranchStatus("genm",1);
  
  jetchain->SetBranchAddress("nref", &nRef);
  jetchain->SetBranchAddress("jtpt", &jetPt);
  jetchain->SetBranchAddress("jteta", &jetEta);
  jetchain->SetBranchAddress("jtphi", &jetPhi);
  jetchain->SetBranchAddress("jtm", &jetM);
  jetchain->SetBranchAddress("ngen", &nGen);
  jetchain->SetBranchAddress("genpt", &genPt);
  jetchain->SetBranchAddress("geneta", &genEta);
  jetchain->SetBranchAddress("genphi", &genPhi);
  jetchain->SetBranchAddress("genm", &genM);

  
  pfchain->SetBranchStatus("*",0);
  pfchain->SetBranchStatus("nPF",1);
  pfchain->SetBranchStatus("pfPt",1);
  pfchain->SetBranchStatus("pfEt",1);
  pfchain->SetBranchStatus("pfE",1);
  pfchain->SetBranchStatus("pfEta",1);
  pfchain->SetBranchStatus("pfPhi",1);
  pfchain->SetBranchStatus("pfId",1);
  pfchain->SetBranchStatus("pfTrkEta",1);
  pfchain->SetBranchStatus("pfTrkPt",1);
  pfchain->SetBranchAddress("nPF", &nPFpart);
  pfchain->SetBranchAddress("pfPt", &pfPt);
  pfchain->SetBranchAddress("pfEt", &pfEt);
  pfchain->SetBranchAddress("pfE", &pfE);
  pfchain->SetBranchAddress("pfEta", &pfEta);
  pfchain->SetBranchAddress("pfPhi", &pfPhi);
  pfchain->SetBranchAddress("pfId", &pfId);
  pfchain->SetBranchAddress("pfTrkEta", &pfTrkEta);
  pfchain->SetBranchAddress("pfTrkPt", &pfTrkPt);


  // Clone Trees
  TFile newfile(outfile.c_str(),"recreate");
  TTree *pfClone = pfchain->CloneTree(0);
  TTree *jetClone = jetchain->CloneTree(0);

  // New ROOT File
  TTree *hiEvent = new TTree("hiEvent","hiEvent");
  hiEvent->Branch("Vertex_Z", &vtx_z);

  int goodEvt=0;
  int pfGoodTrk, pfHadronYes;



  // Event Loop
  //for (int i=0; i<jetentries; i++)
  int halfEntries = ceil(jetentries/2);
  int quarterEntries = ceil(jetentries/4);
  int thirdEntries = ceil(jetentries/3);
  int twoThirdEntries = 2*ceil(jetentries/3); 
  for (int i=0; i<jetentries; i++)
  //for (int i=0; i<halfEntries; i++)  // for consistency check
  //for (int i=halfEntries; i<jetentries; i++)  // for consistency check
    {
      jetchain->GetEntry(i);
      hiEvtchain->GetEntry(i);
      pfchain->GetEntry(i);
     
      pfGoodTrk=0, pfHadronYes=0;

      // Vertex Cut
      if (fabs(vtx_z) > 20) continue;


      // At least 1 PF Hadron
      for (int pf=0; pf<nPFpart; pf++)
      {
        if (pfId->at(pf)==1) pfHadronYes = pfHadronYes + 1;
      }     

      if (pfHadronYes<2) continue; 

      
      // gen sim cuts
      if (nGen==0) continue;
      if (nGen==1) continue;
      if ((fabs(genEta[0]) > 3.0) || (fabs(genEta[1]) > 3.0)) continue;
      if (genPt[0]<30 || genPt[1]<20) continue;

      // Fill Branches
      pfClone->Fill();     
      jetClone->Fill();
      hiEvent->Fill();
   
      goodEvt=  goodEvt+ 1;
    }
 
  cout << "goodEvt=" << goodEvt << endl;
  newfile.Write();
  newfile.Close();
}
