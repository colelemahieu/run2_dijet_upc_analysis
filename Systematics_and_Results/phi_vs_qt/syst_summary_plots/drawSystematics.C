// drawSystematics.C
#include <iostream>
#include <fstream>
#include "TString.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TLine.h>
#include <TTree.h>
#include <TChain.h>
#include <TLatex.h>
#include "TCanvas.h"
#include "TMath.h"
#include "TLegend.h"
#include "TH1.h"
#include "TF1.h"
#include "TPad.h"
#include "TLorentzVector.h"
#include "/home/colelemahieu/Research2023/Run2/RapidityAnalysis/nicePlotting.h"
using namespace std;

void drawLegendStr9(TH1 *h1, TH1 *h2, TH1 *h3, TH1 *h4, TH1 *h5, TH1 *h6, TH1 *h7, TH1 *h8, TH1 *h9, float x1, float x2, float y1, float y2, string text1, string text2, string text3, string text4, string text5, string text6, string text7, string text8, string text9, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "l");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "l");
  legend->AddEntry(h3, text3.c_str(), "l");
  legend->AddEntry(h4, text4.c_str(), "l");
  legend->AddEntry(h5, text5.c_str(), "l");
  legend->AddEntry(h6, text6.c_str(), "l");
  legend->AddEntry(h7, text7.c_str(), "l");
  legend->AddEntry(h8, text8.c_str(), "l");
  legend->AddEntry(h9, text9.c_str(), "l");
  //legend->SetTextSize(0.04);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }


void drawSystematics(string JES_string, string JER_string, string JAR_string, string LSR_string, string Prior_string, string trkGap_string, string HF_string, string ITER_string, string outputName)
{
  // histograms for each systematic
  TH1F *h_JES = new TH1F("h_JES","h_JES",5,0,40);
  TH1F *h_JER = new TH1F("h_JER","h_JER",5,0,40);
  TH1F *h_JAR = new TH1F("h_JAR","h_JAR",5,0,40);
  TH1F *h_LSR = new TH1F("h_LSR","h_LSR",5,0,40);
  TH1F *h_Prior = new TH1F("h_prior","h_prior",5,0,40);
  TH1F *h_trkGap = new TH1F("h_trkGap","h_trkGap",5,0,40);
  TH1F *h_HF = new TH1F("h_HF","h_HF",5,0,40);
  TH1F *h_ITER = new TH1F("h_ITER","h_ITER",5,0,40);
  TH1F *h_total = new TH1F("h_total","h_total",5,0,40);

  // fill by looping through the text files
  ifstream JES_file(JES_string.c_str());
  ifstream JER_file(JER_string.c_str());
  ifstream JAR_file(JAR_string.c_str());
  ifstream LSR_file(LSR_string.c_str());
  ifstream Prior_file(Prior_string.c_str());
  ifstream trkGap_file(trkGap_string.c_str());
  ifstream HF_file(HF_string.c_str());
  ifstream iter_file(ITER_string.c_str());
  

  float value;
  int iBin=1;
  while (JES_file >> value) {
    //h_JES->SetBinContent(iBin, fabs(value));
    h_JES->SetBinContent(iBin, value);
    iBin++;
    }
  iBin=1;
  while (JER_file >> value) {
    //h_JER->SetBinContent(iBin, fabs(value));
    h_JER->SetBinContent(iBin, value);
    iBin++;
    }
  iBin=1;
  while (JAR_file >> value) {
    //h_JAR->SetBinContent(iBin, fabs(value));
    h_JAR->SetBinContent(iBin, value);
    iBin++;
    }
  iBin=1;
  while (LSR_file >> value) {
    //h_LSR->SetBinContent(iBin, fabs(value));
    h_LSR->SetBinContent(iBin, value);
    //cout << "mc stats bin " << iBin << " = " << fabs(value) << endl;
    iBin++;
    }
  iBin=1;
  while (Prior_file >> value) {
    //h_Prior->SetBinContent(iBin, fabs(value));
    h_Prior->SetBinContent(iBin, value);
    iBin++;
    }
  iBin=1;
  while (trkGap_file >> value) {
    //h_trkGap->SetBinContent(iBin, fabs(value));
    h_trkGap->SetBinContent(iBin, value);
    iBin++;
    }
  iBin=1;
  while (HF_file >> value) {
    //h_HF->SetBinContent(iBin, fabs(value));
    h_HF->SetBinContent(iBin, value);
    iBin++;
    }
  iBin=1;
  while (iter_file >> value) {
    //h_ITER->SetBinContent(iBin, fabs(value));
    h_ITER->SetBinContent(iBin, value);
    iBin++;
    }


  // calculate total systematic histogram
  for (int iBin=1; iBin<6; iBin++)
    {
      h_total->SetBinContent(iBin, sqrt(h_JES->GetBinContent(iBin)*h_JES->GetBinContent(iBin)+h_JER->GetBinContent(iBin)*h_JER->GetBinContent(iBin)+h_JAR->GetBinContent(iBin)*h_JAR->GetBinContent(iBin)+h_LSR->GetBinContent(iBin)*h_LSR->GetBinContent(iBin)+h_Prior->GetBinContent(iBin)*h_Prior->GetBinContent(iBin)+h_trkGap->GetBinContent(iBin)*h_trkGap->GetBinContent(iBin)+h_HF->GetBinContent(iBin)*h_HF->GetBinContent(iBin)+h_ITER->GetBinContent(iBin)*h_ITER->GetBinContent(iBin)));
    }


  // write out syst historgrams to output file
  TFile newfile("systematic_hists.root","recreate");
  h_JES->Write();
  h_JER->Write();
  h_JAR->Write();
  h_LSR->Write();
  h_Prior->Write();
  h_trkGap->Write();
  h_HF->Write();
  h_ITER->Write();
  h_total->Write();
  newfile.Close();


  
}
