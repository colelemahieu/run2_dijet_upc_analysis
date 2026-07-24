// getSystematics.C

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


void makeSystematicsPlot(TH1 *h_sigma, const char *titleX, const char *titleY, const char *name)
{
  TString uniqueCanvasName = Form("canvas_%p", h_sigma);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);
  h_sigma->GetXaxis()->SetTitle(titleX);
  h_sigma->GetXaxis()->SetTitleSize(0.05);
  h_sigma->GetXaxis()->SetTitleOffset(1.0);
  h_sigma->GetYaxis()->SetTitle(titleY);
  h_sigma->GetYaxis()->SetTitleSize(0.05);
  h_sigma->GetYaxis()->SetTitleOffset(1.2);
  h_sigma->SetMarkerColor(kRed);
  h_sigma->SetLineColor(kRed);
  h_sigma->SetMarkerStyle(kFullDotLarge);
  h_sigma->GetYaxis()->SetRangeUser(0,0.1);
  h_sigma->SetTitle("");
  h_sigma->SetStats(0);
  h_sigma->Draw("hist pE");
  drawText(.13, .915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.55, 0.915, "PbPb: #sqrt{s}=5.02 TeV (2018)", kBlack, 28);
  canvas->SaveAs(name);
  delete canvas;
  
}


void makeSystematicsPlot_Pt(TH1 *h_sigma, const char *titleX, const char *titleY, const char *name)
{
  TString uniqueCanvasName = Form("canvas_%p", h_sigma);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",300,300);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);
  h_sigma->GetXaxis()->SetTitle(titleX);
  h_sigma->GetXaxis()->SetTitleSize(0.05);
  h_sigma->GetXaxis()->SetTitleOffset(1.0);
  h_sigma->GetYaxis()->SetTitle(titleY);
  h_sigma->GetYaxis()->SetTitleSize(0.05);
  h_sigma->GetYaxis()->SetTitleOffset(1.2);
  h_sigma->SetMarkerColor(kRed);
  h_sigma->SetLineColor(kRed);
  h_sigma->SetMarkerStyle(kFullDotLarge);
  h_sigma->GetYaxis()->SetRangeUser(0,0.5);
  h_sigma->SetTitle("");
  h_sigma->SetStats(0);
  h_sigma->Draw("hist pE");
  //drawText(.13, .915, "#bf{CMS} #it{work in progress}", kBlack, 28);
  //drawText(0.55, 0.915, "PbPb: #sqrt{s}=5.02 TeV (2018)", kBlack, 28);
  drawText(.13, .915, "#bf{CMS} #it{Internal}", kBlack, 8);
  drawText(0.55, 0.915, "PbPb: #sqrt{s}=5.02 TeV (2018)", kBlack, 8);
  canvas->SaveAs(name);
  delete canvas;
  
}





void getSystematics()
{
  TFile *file = new TFile("/home/colelemahieu/Research2023/Run2/Files/allPlots_reco_full_12p5.root");

  // fits
  TF1 *gaus_pt = new TF1("gaus_pt", "gaus", 0.4, 1.8);
  TF1 *gaus_eta = new TF1("gaus_eta", "gaus", -0.2, 0.2);
  TF1 *gaus_phi = new TF1("gaus_phi", "gaus", -0.2, 0.2);
  TF1 *gaus_dijetPt = new TF1("gaus_dijetPt", "gaus", 0.4, 1.8);
  TF1 *gaus_dijetQt = new TF1("gaus_dijetQt", "gaus", 0.4, 1.8);

  // sigma phi histogram
  TH1F *h_sigmaPhi = new TH1F("h_sigmaPhi","h_sigmaPhi",6,20,50);
  TH1F *h_sigmaPhi_etaBins = new TH1F("h_sigmaPhi_etaBins","h_sigmaPhi_etaBins",3,0,2.4);
  TH1F *h_sigmaEta_ptBins = new TH1F("h_sigmaEta_ptBins","h_sigmaEta_ptBins",6,20,50);
  TH1F *h_sigmaEta_etaBins = new TH1F("h_sigmaEta_etaBins","h_sigmaEta_etaBins",3,0,2.4);
  TH1F *h_sigmaPt_ptBins = new TH1F("h_sigmaPt_ptBins","h_sigmaPt_ptBins",6,20,50);
  TH1F *h_sigmaPt_etaBins = new TH1F("h_sigmaPt_etaBins","h_sigmaPt_etaBins",3,0,2.4);
  TH1F *h_sigmaDijetPt_ptBins = new TH1F("h_sigmaDijetPt_ptBins","h_sigmaDijetPt_ptBins",6,20,50);
  TH1F *h_sigmaDijetPt_etaBins = new TH1F("h_sigmaDijetPt_etaBins","h_sigmaDijetPt_etaBins",3,0,2.4);
  TH1F *h_sigmaDijetQt_ptBins = new TH1F("h_sigmaDijetQt_ptBins","h_sigmaDijetQt_ptBins",6,20,50);
  TH1F *h_sigmaDijetQt_etaBins = new TH1F("h_sigmaDijetQt_etaBins","h_sigmaDijetQt_etaBins",3,0,2.4);

  const int ptBins=6;
  TH1F *h_jetPhi_ratio[ptBins];
  TH1F *h_jetEta_ptBins[ptBins];
  TH1F *h_jetPt_ptBins[ptBins];
  TH1F *h_dijetPt_ptBins[ptBins];
  TH1F *h_dijetQt_ptBins[ptBins];
  for (int ptBin=0; ptBin<(ptBins); ptBin++)
  {
    h_jetPhi_ratio[ptBin] = (TH1F*)file->Get(Form("h_jetPhi_ratio_%i",ptBin));
    h_jetPhi_ratio[ptBin]->Fit(gaus_phi);
    double sigmaPhi = gaus_phi->GetParameter(2);
    double sigmaPhi_error = gaus_phi->GetParError(2);
    h_jetEta_ptBins[ptBin] = (TH1F*)file->Get(Form("h_jetEta_ptBins_%i",ptBin));
    h_jetEta_ptBins[ptBin]->Fit(gaus_eta);
    double sigmaEta = gaus_eta->GetParameter(2);
    //cout << "sigmaEta=" << sigmaEta << endl;
    double sigmaEta_error = gaus_eta->GetParError(2);
    h_jetPt_ptBins[ptBin] = (TH1F*)file->Get(Form("h_jetPt_ptBins_%i",ptBin));
    h_jetPt_ptBins[ptBin]->Fit(gaus_pt);
    double sigmaPt = gaus_pt->GetParameter(2);
    cout << "sigmaPt=" << sigmaPt << endl;
    double sigmaPt_error = gaus_pt->GetParError(2);
    h_dijetPt_ptBins[ptBin] = (TH1F*)file->Get(Form("h_dijetPt_ptBins_%i",ptBin));
    h_dijetPt_ptBins[ptBin]->Fit(gaus_dijetPt);
    double sigmadijetPt = gaus_dijetPt->GetParameter(2);
    double sigmadijetPt_error = gaus_dijetPt->GetParError(2);
    h_dijetQt_ptBins[ptBin] = (TH1F*)file->Get(Form("h_dijetQt_ptBins_%i",ptBin));
    h_dijetQt_ptBins[ptBin]->Fit(gaus_dijetQt);
    double sigmadijetQt = gaus_dijetQt->GetParameter(2);
    double sigmadijetQt_error = gaus_dijetQt->GetParError(2);
    h_sigmaPhi->SetBinContent(ptBin+1, sigmaPhi);
    h_sigmaPhi->SetBinError(ptBin+1, sigmaPhi_error);
    h_sigmaEta_ptBins->SetBinContent(ptBin+1, sigmaEta);
    h_sigmaEta_ptBins->SetBinError(ptBin+1, sigmaEta_error);
    h_sigmaPt_ptBins->SetBinContent(ptBin+1, sigmaPt);
    h_sigmaPt_ptBins->SetBinError(ptBin+1, sigmaPt_error);
    h_sigmaDijetPt_ptBins->SetBinContent(ptBin+1, sigmadijetPt);
    h_sigmaDijetPt_ptBins->SetBinError(ptBin+1, sigmadijetPt_error);
    h_sigmaDijetQt_ptBins->SetBinContent(ptBin+1, sigmadijetQt);
    h_sigmaDijetQt_ptBins->SetBinError(ptBin+1, sigmadijetQt_error);

    cout << ptBin << " " << sigmaPt << endl;
  }

  const int etaBins=3;
  TH1F *h_jetPhi_etaBins[etaBins];
  TH1F *h_jetEta_etaBins[etaBins];
  TH1F *h_jetPt_etaBins[etaBins];
  TH1F *h_dijetPt_etaBins[etaBins];
  TH1F *h_dijetQt_etaBins[etaBins];
  for (int etaBin=0; etaBin<(etaBins); etaBin++)
  {
    h_jetPhi_etaBins[etaBin] = (TH1F*)file->Get(Form("h_jetPhi_etaBins_%i",etaBin));
    h_jetPhi_etaBins[etaBin]->Fit(gaus_phi);
    double sigmaPhi = gaus_phi->GetParameter(2);
    double sigmaPhi_error = gaus_phi->GetParError(2);
    h_jetEta_etaBins[etaBin] = (TH1F*)file->Get(Form("h_jetEta_etaBins_%i",etaBin));
    h_jetEta_etaBins[etaBin]->Fit(gaus_eta);
    double sigmaEta = gaus_eta->GetParameter(2);
    //cout << "sigmaEta=" << sigmaEta << endl;
    double sigmaEta_error = gaus_eta->GetParError(2);
    h_jetPt_etaBins[etaBin] = (TH1F*)file->Get(Form("h_jetPt_etaBins_%i",etaBin));
    h_jetPt_etaBins[etaBin]->Fit(gaus_pt);
    double sigmaPt = gaus_pt->GetParameter(2);
    double sigmaPt_error = gaus_pt->GetParError(2);
    h_dijetPt_etaBins[etaBin] = (TH1F*)file->Get(Form("h_dijetPt_etaBins_%i",etaBin));
    h_dijetPt_etaBins[etaBin]->Fit(gaus_dijetPt);
    double sigmadijetPt = gaus_dijetPt->GetParameter(2);
    double sigmadijetPt_error = gaus_dijetPt->GetParError(2);
    h_dijetQt_etaBins[etaBin] = (TH1F*)file->Get(Form("h_dijetQt_etaBins_%i",etaBin));
    h_dijetQt_etaBins[etaBin]->Fit(gaus_dijetQt);
    double sigmadijetQt = gaus_dijetQt->GetParameter(2);
    double sigmadijetQt_error = gaus_dijetQt->GetParError(2);
    h_sigmaPhi_etaBins->SetBinContent(etaBin+1, sigmaPhi);
    h_sigmaPhi_etaBins->SetBinError(etaBin+1, sigmaPhi_error);
    h_sigmaEta_etaBins->SetBinContent(etaBin+1, sigmaEta);
    h_sigmaEta_etaBins->SetBinError(etaBin+1, sigmaEta_error);
    h_sigmaPt_etaBins->SetBinContent(etaBin+1, sigmaPt);
    h_sigmaPt_etaBins->SetBinError(etaBin+1, sigmaPt_error);
    h_sigmaDijetPt_etaBins->SetBinContent(etaBin+1, sigmadijetPt);
    h_sigmaDijetPt_etaBins->SetBinError(etaBin+1, sigmadijetPt_error);
    h_sigmaDijetQt_etaBins->SetBinContent(etaBin+1, sigmadijetQt);
    h_sigmaDijetQt_etaBins->SetBinError(etaBin+1, sigmadijetQt_error);
  }



  ///////////////////////// make Plots ///////////////////////////////

  // directory to write to
  string dirPath = "forAN/Systematics/";


  // jet phi plot /////////////////
  makeSystematicsPlot(h_sigmaPhi, "Gen p_{T} [GeV]", "#sigma of Gaus fit", (dirPath + "jetPhi_sigma_ptbins.png").c_str());

  // jet phi eta bins plot ////////////////////
  makeSystematicsPlot(h_sigmaPhi_etaBins, "Gen #eta", "#sigma of Gaus fit", (dirPath + "jetPhi_sigma_etabins.png").c_str());


  // jet eta pt bins plot //////////////////
  makeSystematicsPlot(h_sigmaEta_ptBins, "Gen p_{T} [GeV]", "#sigma of Gaus fit", (dirPath + "jetEta_sigma_ptbins.png").c_str());


  // jet eta eta bins plot //////////////////
  makeSystematicsPlot(h_sigmaEta_etaBins, "Gen #eta", "#sigma of Gaus fit", (dirPath + "jetEta_sigma_etabins.png").c_str());


  // jet pt pt bins plot //////////////////
  makeSystematicsPlot_Pt(h_sigmaPt_ptBins, "Gen p_{T} [GeV]", "#sigma of Gaus fit", (dirPath + "jetPt_sigma_ptbins.png").c_str());


  // jet pt eta bins plot //////////////////
  makeSystematicsPlot_Pt(h_sigmaPt_etaBins, "Gen #eta", "#sigma of Gaus fit", (dirPath + "jetPt_sigma_etabins.png").c_str());

  // dijet Pt pt bins plot //////////////////
  makeSystematicsPlot_Pt(h_sigmaDijetPt_ptBins, "Gen p_{T} [GeV]", "#sigma of Gaus fit", (dirPath + "dijetPt_sigma_ptbins.png").c_str());

   // dijet Pt eta bins plot //////////////////
  makeSystematicsPlot_Pt(h_sigmaDijetPt_etaBins, "Gen #eta", "#sigma of Gaus fit", (dirPath + "dijetPt_sigma_etabins.png").c_str());

  // dijet Qt pt bins plot //////////////////
  makeSystematicsPlot_Pt(h_sigmaDijetQt_ptBins, "Gen p_{T} [GeV]", "#sigma of Gaus fit", (dirPath + "dijetQt_sigma_ptbins.png").c_str());

  // dijet Qt eta bins plot //////////////////
  makeSystematicsPlot_Pt(h_sigmaDijetQt_etaBins, "Gen #eta", "#sigma of Gaus fit", (dirPath + "dijetQt_sigma_etabins.png").c_str());
  
  
}
