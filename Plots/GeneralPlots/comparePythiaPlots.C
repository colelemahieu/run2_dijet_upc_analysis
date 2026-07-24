// comparePythiaPlots.C
// This code produces plots for the Analysis Note comparing data and MC distributions

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

void comparePythiaPlots(string genPythiaFile, string recoPythiaFile, string dataFile)
{
  // Read in files
  TFile *genPythia = new TFile(genPythiaFile.c_str());
  TFile *recoPythia = new TFile(recoPythiaFile.c_str());
  TFile *data = new TFile(dataFile.c_str());

  // Directory to Store
  string dirPath = "forAN/";
  
  // Updated gen and reco v2 plots
  TFile *dataUnf = new TFile("/home/colelemahieu/Research2023/Run2/Files/fit_v2_R4.root");
  TProfile *h_profV2_genSim = (TProfile*)dataUnf->Get("h_profV2_gen");
  TProfile *h_profV2_pythia = (TProfile*)dataUnf->Get("h_profV2_reco");

  // Pythia Gen Sim Histograms
  TH1F *hGen_QT_10 = (TH1F*)genPythia->Get("h_QT_10");
  TH1F *h_trigPhi_gen = (TH1F*)genPythia->Get("h_angle12");
  //TProfile *h_profV2_5_gen = (TProfile*)genPythia->Get("h_profV2_5");

  
  // Pythia Reco Histograms
  TH1F *hPythia_QT_10 = (TH1F*)recoPythia->Get("h_QT_10");
  TH1F *h_trigPhi_reco = (TH1F*)recoPythia->Get("h_angle12");
  //TProfile *h_profV2_5_pythia = (TProfile*)recoPythia->Get("h_profV2_5");
  
  TH1F *hPythia_jtPt_L = (TH1F*)recoPythia->Get("h_jtPt_L");
  TH1F *hPythia_jtPt_S = (TH1F*)recoPythia->Get("h_jtPt_S");
  TH1F *hPythia_PT = (TH1F*)recoPythia->Get("h_PT");
  TH1F *hPythia_QT = (TH1F*)recoPythia->Get("h_QT");
  TH1F *hPythia_forwardRapGap = (TH1F*)recoPythia->Get("h_rapgaps_forward");
  TH1F *hPythia_nPF_ch = (TH1F*)recoPythia->Get("h_nPF_ch");
  TH1F *hPythia_dijetRap = (TH1F*)recoPythia->Get("h_dijetRap");
  TH1F *hPythia_dijetRap_abs = (TH1F*)recoPythia->Get("h_dijetRap_abs");
  TH1F *hPythia_jetRap_L = (TH1F*)recoPythia->Get("h_jetRap_L");
  TH1F *hPythia_jetRap_S = (TH1F*)recoPythia->Get("h_jetRap_S");

  // other kinematics
  TH1F *hPythia_dijetMass = (TH1F*)recoPythia->Get("h_dijetMass");
  
  // Data Histograms
  TH1F *h_QT_10 = (TH1F*)data->Get("h_QT_10");
  TH1F *h_trigPhi = (TH1F*)data->Get("h_angle12");
  TProfile *h_profV2_R4 = (TProfile*)data->Get("h_profV2_5");
  TProfile *h_profV2_5_R4 = (TProfile*)data->Get("h_profV2_5");
  
  TH1F *h_jtPt_L = (TH1F*)data->Get("h_jtPt_L");
  TH1F *h_jtPt_S = (TH1F*)data->Get("h_jtPt_S");
  TH1F *h_PT = (TH1F*)data->Get("h_PT");
  TH1F *h_QT = (TH1F*)data->Get("h_QT");
  TH1F *h_forwardRapGap = (TH1F*)data->Get("h_rapgaps_forward");
  TH1F *h_nPF_ch = (TH1F*)data->Get("h_nPF_ch");
  TH1F *h_dijetRap = (TH1F*)data->Get("h_dijetRap");
  TH1F *h_dijetRap_abs = (TH1F*)data->Get("h_dijetRap_abs");
  TH1F *h_jetRap_L = (TH1F*)data->Get("h_jetRap_L");
  TH1F *h_jetRap_S = (TH1F*)data->Get("h_jetRap_S");

  // other kinematics
  TH1F *h_dijetMass = (TH1F*)data->Get("h_dijetMass");
  

  // vtx Plots, just condor cuts
  TFile *condorData = new TFile("Files/allPlots_R4.root");
  TFile *condorPythia = new TFile("Files/allPlots_reco_full_12p5.root");
  TH1F *h_condor_vtxData = (TH1F*)condorData->Get("h_zvtx");
  TH1F *h_condor_vtxPythia = (TH1F*)condorPythia->Get("h_zvtx");
  


  /////////////// Plotting //////////////////////////////////////////



  /////////    Jet Kinematics with Reco Pythia    //////////////////
  
  TCanvas *c14 = new TCanvas("c14","Title",800,800);
  h_jtPt_L->SetTitle(";p_{T} [GeV]; Counts");
  h_jtPt_L->SetStats(0);
  h_jtPt_L->SetMarkerColor(kBlack);
  h_jtPt_L->SetLineColor(kBlack);
  h_jtPt_L->SetMarkerStyle(20);
  h_jtPt_S->SetTitle(";p_{T} [GeV]; Counts");
  h_jtPt_S->SetStats(0);
  h_jtPt_S->SetMarkerColor(kBlack);
  h_jtPt_S->SetLineColor(kBlack);
  h_jtPt_S->SetMarkerStyle(21);
  hPythia_jtPt_L->SetTitle(";p_{T} [GeV]; Counts");
  hPythia_jtPt_L->SetStats(0);
  hPythia_jtPt_L->SetMarkerColor(kRed);
  hPythia_jtPt_S->SetMarkerColor(kBlue);
  hPythia_jtPt_L->SetLineColor(kRed);
  hPythia_jtPt_S->SetLineColor(kBlue);
  hPythia_jtPt_L->SetLineWidth(2);
  hPythia_jtPt_S->SetLineWidth(2);
  hPythia_jtPt_L->Scale(h_jtPt_L->Integral()/hPythia_jtPt_L->Integral());
  hPythia_jtPt_S->Scale(h_jtPt_S->Integral()/hPythia_jtPt_S->Integral());
  h_jtPt_L->GetXaxis()->SetTitleSize(0.05);
  h_jtPt_L->GetYaxis()->SetTitleSize(0.05);
  h_jtPt_L->GetYaxis()->SetTitleOffset(1.3);
  h_jtPt_L->GetYaxis()->SetRangeUser(0,1500);  // gg->qq, 0nXn
  //h_jtPt_L->GetYaxis()->SetRangeUser(0,750);  // gg->qq, 0n0n
  h_jtPt_L->Draw("p E");
  hPythia_jtPt_S->Draw("hist E same");
  hPythia_jtPt_L->Draw("hist E same");
  h_jtPt_S->Draw("p E same");
  drawText(0.63, 0.65, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.63, 0.59, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.63, 0.53, "|#eta_{1,2}| < 3.0", kBlack, 31);
  drawText(0.63, 0.47, "P_{T} > Q_{T}", kBlack, 31);
  //drawLegendStr(hPythia_jtPt_L, hPythia_jtPt_S, 0.65, 0.8, 0.8, 0.875, "Leading Jet", "Subleading Jet");
  drawLegendStr4(hPythia_jtPt_L, "le", h_jtPt_L, "pe", hPythia_jtPt_S, "le", h_jtPt_S, "pe", 0.43, 0.79, 0.725, 0.88, "Leading Jet Pythia", "Leading Jet Data", "Subleading Jet Pythia", "Subleading Jet Data");
  drawCMS_lumi(c14);
  c14->SaveAs((dirPath + "pythiaReco_data_jets_pt.png").c_str());
  //c14->SaveAs((dirPath + "pythiaReco_data_jets_pt.pdf").c_str());



   /////////    Jet Kinematics with Reco Pythia, ratio plot    //////////////////
  
  TCanvas *c145 = new TCanvas("c145","Title",800,800);
  TPad *main145 = new TPad("main145", "new pad", 0.01, 0.315, 0.99, 0.99);
  TPad *ratio145 = new TPad("ratio145", "new pad 2", 0.01, 0.1, 0.99, 0.38);
  // ratios
  TH1F* hRatio_jtPt_L = (TH1F*)h_jtPt_L->Clone("hRatio_jtPt_L");
  hRatio_jtPt_L->Divide(hPythia_jtPt_L);
  TH1F* hRatio_jtPt_S = (TH1F*)h_jtPt_S->Clone("hRatio_jtPt_S");
  hRatio_jtPt_S->Divide(hPythia_jtPt_S);

  c145->cd();
  main145->Draw();
  ratio145->Draw();

  main145->cd();
  main145->SetLeftMargin(0.125);
  main145->SetBottomMargin(0.13);
  main145->SetTickx(1);
  main145->SetTicky(1);
  h_jtPt_L->SetTitle(";p_{T} [GeV]; Counts");
  h_jtPt_L->SetStats(0);
  h_jtPt_L->SetMarkerColor(kBlack);
  h_jtPt_L->SetLineColor(kBlack);
  h_jtPt_L->SetMarkerStyle(20);
  h_jtPt_S->SetTitle(";p_{T} [GeV]; Counts");
  h_jtPt_S->SetStats(0);
  h_jtPt_S->SetMarkerColor(kBlack);
  h_jtPt_S->SetLineColor(kBlack);
  h_jtPt_S->SetMarkerStyle(21);
  hPythia_jtPt_L->SetTitle(";p_{T} [GeV]; Counts");
  hPythia_jtPt_L->SetStats(0);
  hPythia_jtPt_L->SetMarkerColor(kRed);
  hPythia_jtPt_S->SetMarkerColor(kBlue);
  hPythia_jtPt_L->SetLineColor(kRed);
  hPythia_jtPt_S->SetLineColor(kBlue);
  hPythia_jtPt_L->SetLineWidth(2);
  hPythia_jtPt_S->SetLineWidth(2);
  //hPythia_jtPt_L->Scale(h_jtPt_L->Integral()/hPythia_jtPt_L->Integral());
  //hPythia_jtPt_S->Scale(h_jtPt_S->Integral()/hPythia_jtPt_S->Integral());
  h_jtPt_L->GetXaxis()->SetTitleSize(0.05);
  h_jtPt_L->GetXaxis()->SetLabelSize(0.00000000001);
  h_jtPt_L->GetYaxis()->SetTitleSize(0.065);
  h_jtPt_L->GetYaxis()->SetTitleOffset(1.0);
  h_jtPt_L->GetYaxis()->SetLabelSize(0.045);
  h_jtPt_L->GetYaxis()->SetRangeUser(0,1600);  // gg->qq, 0nXn
  //h_jtPt_L->GetYaxis()->SetRangeUser(0,750);  // gg->qq, 0n0n
  h_jtPt_L->Draw("p E");
  hPythia_jtPt_S->Draw("hist E same");
  hPythia_jtPt_L->Draw("hist E same");
  h_jtPt_S->Draw("p E same");
  drawText(0.15, 0.82, "0nXn", kBlack, 29);
  drawText(0.66, 0.61, "p_{T,1} > 30 GeV", kBlack, 25);
  drawText(0.66, 0.55, "p_{T,2} > 20 GeV", kBlack, 25);
  drawText(0.66, 0.49, "|#eta_{1,2}| < 3.0", kBlack, 25);
  drawText(0.66, 0.43, "P_{T} > Q_{T}", kBlack, 25);
  //drawLegendStr(hPythia_jtPt_L, hPythia_jtPt_S, 0.65, 0.8, 0.8, 0.875, "Leading Jet", "Subleading Jet");
  //drawLegendStr4(hPythia_jtPt_L, "le", h_jtPt_L, "pe", hPythia_jtPt_S, "le", h_jtPt_S, "pe", 0.6, 0.79, 0.7, 0.88, "Leading Jet Pythia", "Leading Jet Data", "Subleading Jet Pythia", "Subleading Jet Data");
  drawGridLegend(h_jtPt_L, hPythia_jtPt_L, h_jtPt_S, hPythia_jtPt_S, "#bf{Leading}", "#bf{Subleading}", "#bf{Data}", "#bf{MC}",0.7,0.7);
  drawText(0.1325, 0.915, "#bf{CMS} #it{Internal}", kBlack, 30);
  drawText(0.4, 0.915, "PbPb #sqrt{s_{_{NN}}} = 5.02 TeV; 1.67 nb^{-1}", kBlack, 30);
  
  ratio145->cd();
  ratio145->SetTopMargin(0.045);
  ratio145->SetLeftMargin(0.125);
  ratio145->SetBottomMargin(0.275);
  ratio145->SetTickx(1);
  ratio145->SetTicky(1);
  hRatio_jtPt_L->SetStats(0);
  hRatio_jtPt_S->SetStats(0);
  hRatio_jtPt_L->SetLineColor(kRed);
  hRatio_jtPt_S->SetLineColor(kBlue);
  hRatio_jtPt_L->SetMarkerColor(kRed);
  hRatio_jtPt_S->SetMarkerColor(kBlue);
  hRatio_jtPt_L->SetTitle("");
  hRatio_jtPt_S->SetTitle("");
  hRatio_jtPt_L->GetXaxis()->SetLabelSize(0.18);
  hRatio_jtPt_L->GetXaxis()->SetTitleSize(0.15);  
  hRatio_jtPt_L->GetXaxis()->SetTitleOffset(0.8);
  hRatio_jtPt_L->GetYaxis()->SetLabelSize(0.11);
  hRatio_jtPt_L->GetYaxis()->SetTitleSize(0.17);
  hRatio_jtPt_L->GetXaxis()->SetTitle("p_{T} [GeV]");
  hRatio_jtPt_L->GetXaxis()->SetLabelSize(0.11);
  hRatio_jtPt_L->GetYaxis()->SetTitle("Data / MC");
  hRatio_jtPt_L->GetYaxis()->SetTitleSize(0.17);
  hRatio_jtPt_L->GetYaxis()->SetRangeUser(0.5,1.5);
  hRatio_jtPt_L->GetYaxis()->SetTitleOffset(0.35);
  hRatio_jtPt_L->GetYaxis()->SetNdivisions(303);
  hRatio_jtPt_L->SetMarkerSize(1);
  hRatio_jtPt_L->SetLineWidth(2);
  hRatio_jtPt_S->SetMarkerSize(1);
  hRatio_jtPt_S->SetLineWidth(2);
  hRatio_jtPt_L->Draw("hist pE");
  hRatio_jtPt_S->Draw("hist pE same");
  float xmaxRatio = hRatio_jtPt_L->GetXaxis()->GetXmax();
  float xminRatio = hRatio_jtPt_L->GetXaxis()->GetXmin();
  TLine *lineRatio = new TLine(xminRatio,1,xmaxRatio,1);
  lineRatio->SetLineColor(kBlack);
  lineRatio->SetLineWidth(3);
  lineRatio->SetLineStyle(2); // dash
  lineRatio->Draw("LSAME");
  hRatio_jtPt_L->Draw("hist pE same");
  hRatio_jtPt_S->Draw("hist pE same");
  //drawText(0.135, 0.8, Form("#chi^{2}/NDF=%0.2f",find_hist_chi2_ndf(h_jtPt_L, hPythia_jtPt_L)), kRed, 26);
  //drawText(0.135, 0.65, Form("#chi^{2}/NDF=%0.2f",find_hist_chi2_ndf(h_jtPt_S, hPythia_jtPt_S)), kBlue, 26);
  c145->SaveAs((dirPath + "pythiaReco_data_jets_pt_ratio.pdf").c_str());


  
  
  ///////////    QT and PT, data and reco Pythia  //////////////////////
  
  TCanvas *c5 = new TCanvas("c5","Title5",800,800);
  h_PT->SetStats(0);
  h_PT->SetMarkerColor(kBlack);
  h_PT->SetLineColor(kBlack);
  h_PT->SetMarkerStyle(20);
  h_QT->SetStats(0);
  h_QT->SetMarkerColor(kBlack);
  h_QT->SetLineColor(kBlack);
  h_QT->SetMarkerStyle(21);
  hPythia_PT->Scale(h_PT->Integral()/hPythia_PT->Integral());
  hPythia_QT->Scale(h_QT->Integral()/hPythia_QT->Integral());
  //hPythia_QTGen->Scale(h_QT->Integral()/hPythia_QTGen->Integral());
  h_PT->SetTitle(";P_{T} and Q_{T} [GeV]; Counts");
  hPythia_PT->SetStats(0);
  hPythia_PT->SetMarkerColor(kOrange+7);
  hPythia_QT->SetMarkerColor(kGreen+2);
  hPythia_PT->SetLineColor(kOrange+7);
  hPythia_PT->SetLineWidth(2);
  hPythia_QT->SetLineWidth(2);
  hPythia_QT->SetLineColor(kGreen+2);
  hPythia_QT->SetMarkerSize(7);
  //hPythia_PT->SetMarkerStyle(kFullCircle);
  //hPythia_QT->SetMarkerStyle(kFullTriangleUp);
  //hPythia_QTGen->SetMarkerColor(kBlack);
  //hPythia_QTGen->SetLineColor(kBlack);
  //hPythia_QTGen->SetLineWidth(3);
  h_PT->GetXaxis()->SetTitleSize(0.05);
  h_PT->GetYaxis()->SetTitleSize(0.05);
  h_PT->GetYaxis()->SetTitleOffset(1.3);
  h_PT->GetYaxis()->SetRangeUser(0,1500); // 0nXn
  //h_PT->GetYaxis()->SetRangeUser(0,700);  // gg->qq, 0n0n
  h_PT->Draw("p E");
  hPythia_PT->Draw("hist E same");
  h_QT->Draw("hist p E same");
  hPythia_QT->Draw("hist same E");
  //hPythia_QTGen->Draw("hist same");
  drawLegendStr4(hPythia_PT, "le", h_PT, "pe", hPythia_QT, "le", h_QT, "pe", 0.63, 0.8, 0.7, 0.875, "P_{T} Pythia", "P_{T} Data", "Q_{T} Pythia", "Q_{T} Data");
  drawText(0.63, 0.6, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.63, 0.54, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.63, 0.48, "|#eta_{1,2}| < 3.0", kBlack, 31);
  drawText(0.63, 0.42, "P_{T} > Q_{T}", kBlack, 31);
  drawCMS_lumi(c5);
  c5->SaveAs((dirPath + "qtpt_Pythia.png").c_str());
  //c5->SaveAs((dirPath + "qtpt_Pythia.pdf").c_str());

  

   ///////////    QT and PT, data and reco Pythia, ratio  //////////////////////
  
  TCanvas *c555 = new TCanvas("c555","Title555",800,800);
  TPad *main55 = new TPad("main55", "new pad", 0.01, 0.315, 0.99, 0.99);
  TPad *ratio55 = new TPad("ratio55", "new pad 2", 0.01, 0.1, 0.99, 0.38);
  // ratios
  TH1F* hRatio_PT = (TH1F*)h_PT->Clone("h_PT");
  hRatio_PT->Divide(hPythia_PT);
  TH1F* hRatio_QT = (TH1F*)h_QT->Clone("h_QT");
  hRatio_QT->Divide(hPythia_QT);

  c555->cd();
  main55->Draw();
  ratio55->Draw();

  main55->cd();
  main55->SetLeftMargin(0.125);
  main55->SetBottomMargin(0.13);
  main55->SetTickx(1);
  main55->SetTicky(1);
  h_PT->SetStats(0);
  h_PT->SetMarkerColor(kOrange+7);
  h_PT->SetLineColor(kOrange+7);
  h_PT->SetMarkerStyle(20);
  h_QT->SetStats(0);
  h_QT->SetMarkerColor(kGreen+2);
  h_QT->SetLineColor(kGreen+2);
  h_QT->SetMarkerStyle(21);
  h_PT->SetTitle(";P_{T} and Q_{T} [GeV]; Counts");
  hPythia_PT->SetStats(0);
  hPythia_PT->SetMarkerColor(kOrange+7);
  hPythia_QT->SetMarkerColor(kGreen+2);
  hPythia_PT->SetLineColor(kOrange+7);
  hPythia_PT->SetLineWidth(2);
  hPythia_QT->SetLineWidth(2);
  hPythia_QT->SetLineColor(kGreen+2);
  hPythia_QT->SetMarkerSize(7);
  h_PT->GetXaxis()->SetLabelSize(0.00000000000001);
  h_PT->GetXaxis()->SetTitleSize(0.05);
  h_PT->GetYaxis()->SetTitleSize(0.065);
  h_PT->GetYaxis()->SetTitleOffset(1.0);
  h_PT->GetYaxis()->SetLabelSize(0.045);
  h_PT->GetYaxis()->SetRangeUser(0,1500); // 0nXn
  h_PT->Draw("p E");
  hPythia_PT->Draw("hist E same");
  h_QT->Draw("hist p E same");
  hPythia_QT->Draw("hist same E");
  //drawLegendStr4(hPythia_PT, "le", h_PT, "pe", hPythia_QT, "le", h_QT, "pe", 0.63, 0.8, 0.7, 0.875, "P_{T} Pythia", "P_{T} Data", "Q_{T} Pythia", "Q_{T} Data");
  drawGridLegend_qtpt(h_QT, hPythia_QT, h_PT, hPythia_PT, "#bf{Q_{T}}", "#bf{P_{T}}", "#bf{Data}", "#bf{Pythia}",0.7,0.7);
  drawText(0.172, 0.82, "0nXn", kBlack, 29);
  drawText(0.66, 0.6, "p_{T,1} > 30 GeV", kBlack, 25);
  drawText(0.66, 0.54, "p_{T,2} > 20 GeV", kBlack, 25);
  drawText(0.66, 0.48, "|#eta_{1,2}| < 3.0", kBlack, 25);
  drawText(0.66, 0.42, "P_{T} > Q_{T}", kBlack, 25);
  //drawText(0.175, 0.82, Form("#chi^{2}/NDF=%0.2f",find_hist_chi2_ndf(h_PT, hPythia_PT)), kOrange+7, 26);
  //drawText(0.175, 0.75, Form("#chi^{2}/NDF=%0.2f",find_hist_chi2_ndf(h_QT, hPythia_QT)), kGreen+2, 26);
  drawText(0.1325, 0.915, "#bf{CMS} #it{Internal}", kBlack, 30);
  drawText(0.4, 0.915, "PbPb #sqrt{s_{_{NN}}} = 5.02 TeV; 1.67 nb^{-1}", kBlack, 30);

  ratio55->cd();
  ratio55->SetTopMargin(0.045);
  ratio55->SetLeftMargin(0.125);
  ratio55->SetBottomMargin(0.275);
  ratio55->SetTickx(1);
  ratio55->SetTicky(1);
  hRatio_PT->SetStats(0);
  hRatio_QT->SetStats(0);
  hRatio_PT->SetLineColor(kOrange+7);
  hRatio_QT->SetLineColor(kGreen+2);
  hRatio_PT->SetMarkerColor(kOrange+7);
  hRatio_QT->SetMarkerColor(kGreen+2);
  hRatio_PT->SetTitle("");
  hRatio_QT->SetTitle("");
  hRatio_PT->GetXaxis()->SetLabelSize(0.18);
  hRatio_PT->GetXaxis()->SetTitleSize(0.15);  
  hRatio_PT->GetXaxis()->SetTitleOffset(0.8);
  hRatio_PT->GetYaxis()->SetLabelSize(0.11);
  hRatio_PT->GetYaxis()->SetTitleSize(0.17);
  hRatio_PT->GetXaxis()->SetTitle("p_{T} [GeV]");
  hRatio_PT->GetXaxis()->SetLabelSize(0.11);
  hRatio_PT->GetYaxis()->SetTitle("Data / MC");
  hRatio_PT->GetYaxis()->SetTitleSize(0.17);
  hRatio_PT->GetYaxis()->SetRangeUser(0.25,1.75);
  hRatio_PT->GetYaxis()->SetTitleOffset(0.35);
  hRatio_PT->GetYaxis()->SetNdivisions(303);
  hRatio_PT->SetMarkerSize(1);
  hRatio_PT->SetLineWidth(2);
  hRatio_QT->SetMarkerSize(1);
  hRatio_QT->SetLineWidth(2);
  hRatio_PT->Draw("hist pE");
  hRatio_QT->Draw("hist pE same");
  float xmaxRatio55 = hRatio_PT->GetXaxis()->GetXmax();
  float xminRatio55 = hRatio_PT->GetXaxis()->GetXmin();
  TLine *lineRatio55 = new TLine(xminRatio55,1,xmaxRatio55,1);
  lineRatio55->SetLineColor(kBlack);
  lineRatio55->SetLineWidth(3);
  lineRatio55->SetLineStyle(2); // dash
  lineRatio55->Draw("LSAME");
  hRatio_PT->Draw("hist pE same");
  hRatio_QT->Draw("hist pE same");
  c555->SaveAs((dirPath + "qtpt_Pythia_ratio.pdf").c_str());
  



    ///////////   dijet rapidity prime, data and reco Pythia  //////////////////////
  
  TCanvas *c55 = new TCanvas("c55","Title55",800,800);
  c55->SetTickx(1);
  c55->SetTicky(1);
  h_dijetRap->SetStats(0);
  h_dijetRap->SetMarkerColor(kBlack);
  h_dijetRap->SetLineColor(kBlack);
  h_dijetRap->SetMarkerStyle(20);
  hPythia_dijetRap->Scale(h_dijetRap->Integral()/hPythia_dijetRap->Integral());
  h_dijetRap->SetTitle(";dijet y'; Counts");
  hPythia_dijetRap->SetStats(0);
  hPythia_dijetRap->SetMarkerColor(kRed);
  hPythia_dijetRap->SetLineColor(kRed);
  h_dijetRap->GetXaxis()->SetTitleSize(0.05);
  h_dijetRap->GetYaxis()->SetTitleSize(0.05);
  h_dijetRap->GetYaxis()->SetTitleOffset(1.3);
  h_dijetRap->Draw("p E");
  hPythia_dijetRap->Draw("hist E same");
  drawLegendStr(h_dijetRap, hPythia_dijetRap, 0.15, 0.475, 0.7, 0.85, "0nXn data", "reco Pythia");
  drawCMS_lumi(c55);
  c55->SaveAs((dirPath + "dijetRap_Pythia.png").c_str());


  /////////////  dijet absolute rapidity, data and reco Pythia  //////////////////////

  TCanvas *c56 = new TCanvas("c56","Title56",800,800);
  h_dijetRap_abs->SetStats(0);
  h_dijetRap_abs->SetMarkerColor(kBlack);
  h_dijetRap_abs->SetLineColor(kBlack);
  h_dijetRap_abs->SetMarkerStyle(20);
  hPythia_dijetRap_abs->Scale(h_dijetRap_abs->Integral()/hPythia_dijetRap_abs->Integral());
  h_dijetRap_abs->SetTitle(";dijet |y|; Counts");
  hPythia_dijetRap_abs->SetStats(0);
  hPythia_dijetRap_abs->SetMarkerColor(kRed);
  hPythia_dijetRap_abs->SetLineColor(kRed);
  h_dijetRap_abs->GetXaxis()->SetTitleSize(0.05);
  h_dijetRap_abs->GetYaxis()->SetTitleSize(0.05);
  h_dijetRap_abs->GetYaxis()->SetTitleOffset(1.3);
  h_dijetRap_abs->GetYaxis()->SetRangeUser(0,1000);
  h_dijetRap_abs->Draw("p E");
  hPythia_dijetRap_abs->Draw("hist E same");
  drawLegendStr(h_dijetRap_abs, hPythia_dijetRap_abs, 0.15, 0.475, 0.7, 0.85, "0nXn data", "reco Pythia");
  drawCMS_lumi(c56);
  c56->SaveAs((dirPath + "dijetRap_abs_Pythia.png").c_str());

  //////////// jet absolute rapidity, data and reco Pythia /////////////////////////

  TCanvas *c146 = new TCanvas("c146","Title",800,800);
  h_jetRap_L->SetTitle(";Jet |y|; Counts");
  h_jetRap_L->SetStats(0);
  h_jetRap_L->SetMarkerColor(kBlack);
  h_jetRap_L->SetLineColor(kBlack);
  h_jetRap_L->SetMarkerStyle(20);
  h_jetRap_S->SetTitle(";|y|; Counts");
  h_jetRap_S->SetStats(0);
  h_jetRap_S->SetMarkerColor(kBlack);
  h_jetRap_S->SetLineColor(kBlack);
  h_jetRap_S->SetMarkerStyle(21);
  hPythia_jetRap_L->SetTitle(";|y|; Counts");
  hPythia_jetRap_L->SetStats(0);
  hPythia_jetRap_L->SetMarkerColor(kRed);
  hPythia_jetRap_S->SetMarkerColor(kBlue);
  hPythia_jetRap_L->SetLineColor(kRed);
  hPythia_jetRap_S->SetLineColor(kBlue);
  hPythia_jetRap_L->SetLineWidth(2);
  hPythia_jetRap_S->SetLineWidth(2);
  hPythia_jetRap_L->Scale(h_jetRap_L->Integral()/hPythia_jetRap_L->Integral());
  hPythia_jetRap_S->Scale(h_jetRap_S->Integral()/hPythia_jetRap_S->Integral());
  h_jetRap_L->GetXaxis()->SetTitleSize(0.05);
  h_jetRap_L->GetYaxis()->SetTitleSize(0.05);
  h_jetRap_L->GetYaxis()->SetTitleOffset(1.3);
  h_jetRap_L->GetYaxis()->SetRangeUser(0,1100);  // gg->qq, 0nXn
  h_jetRap_L->Draw("p E");
  hPythia_jetRap_S->Draw("hist E same");
  hPythia_jetRap_L->Draw("hist E same");
  h_jetRap_S->Draw("p E same");
  //drawText(0.63, 0.65, "p_{T,1} > 30 GeV", kBlack, 31);
  //drawText(0.63, 0.59, "p_{T,2} > 20 GeV", kBlack, 31);
  //drawText(0.63, 0.53, "|#eta_{1,2}| < 3.0", kBlack, 31);
  //drawText(0.63, 0.47, "P_{T} > Q_{T}", kBlack, 31);
  //drawLegendStr(hPythia_jtPt_L, hPythia_jtPt_S, 0.65, 0.8, 0.8, 0.875, "Leading Jet", "Subleading Jet");
  drawLegendStr4(hPythia_jetRap_L, "le", h_jetRap_L, "pe", hPythia_jetRap_S, "le", h_jetRap_S, "pe", 0.43, 0.79, 0.725, 0.88, "Leading Jet Pythia", "Leading Jet Data", "Subleading Jet Pythia", "Subleading Jet Data");
  drawCMS_lumi(c146);
  c146->SaveAs((dirPath + "pythiaReco_data_jets_rap_abs.png").c_str());
  
  


  /////////  v2 R4: DATA AND GEN SIM /////////////////////////

  TH1D *h_ratio_genSim = h_profV2_R4->ProjectionX("h_ratio_genSim");
  TH1D *h2 = h_profV2_genSim->ProjectionX("h2");
  h_ratio_genSim->Divide(h2);
  h_ratio_genSim->SetMarkerColor(kBlack);
  h_ratio_genSim->SetMarkerStyle(kFullDotLarge);
  
  TCanvas *c10 = new TCanvas("c10","Title",800,800);
  TPad *main = new TPad("main", "new pad", 0.01, 0.315, 0.99, 0.99);
  TPad *ratio = new TPad("ratio", "new pad 2", 0.01, 0.1, 0.99, 0.38);

  c10->cd();
  main->Draw();
  ratio->Draw();

  main->cd();
  main->SetLeftMargin(0.125);
  main->SetTickx(1);
  main->SetTicky(1);
  h_profV2_R4->SetStats(0);
  h_profV2_R4->SetMarkerStyle(kFullDotLarge);
  h_profV2_R4->SetMarkerColor(kBlack);
  h_profV2_R4->SetLineColor(kBlack);
  h_profV2_R4->SetMarkerSize(1);
  h_profV2_R4->GetYaxis()->SetRangeUser(0,1.1);
  h_profV2_R4->SetTitle("");
  h_profV2_R4->GetYaxis()->SetTitle("<cos(2#phi)>");
  h_profV2_R4->GetYaxis()->SetLabelSize(0.04);
  h_profV2_R4->GetYaxis()->SetTitleSize(0.08);
  h_profV2_R4->GetYaxis()->SetTitleOffset(0.75);
  h_profV2_R4->Draw();
  //h_profV2_pythia->SetFillStyle(3001);
  //h_profV2_pythia->SetFillColor(kBlue-7);
  h_profV2_genSim->SetFillStyle(3001);
  h_profV2_genSim->SetFillColor(kCyan-6);
  h_profV2_genSim->SetLineColor(kBlack);
  h_profV2_genSim->Draw("same hist E");
  drawLegendProfile(h_profV2_genSim, h_profV2_R4, 0.15, 0.5, 0.725, 0.85, "Pythia Gen", "anti-k_{T} R=0.4 data");

  ratio->cd();
  ratio->SetLeftMargin(0.125);
  ratio->SetBottomMargin(0.29);
  ratio->SetTickx(1);
  ratio->SetTicky(1);
  h_ratio_genSim->SetStats(0);
  h_ratio_genSim->SetTitle("");
  h_ratio_genSim->GetXaxis()->SetTitle("Q_{T} [GeV]");
  h_ratio_genSim->GetXaxis()->SetTitleSize(0.18);
  h_ratio_genSim->GetXaxis()->SetTitleOffset(0.7);
  h_ratio_genSim->GetXaxis()->SetLabelSize(0.10);
  h_ratio_genSim->GetYaxis()->SetRangeUser(0,4);
  h_ratio_genSim->GetYaxis()->SetTitle("Data / MC");
  h_ratio_genSim->GetYaxis()->SetTitleOffset(0.35);
  h_ratio_genSim->GetYaxis()->SetTitleSize(0.17);
  h_ratio_genSim->GetYaxis()->SetLabelSize(0.09);
  h_ratio_genSim->SetLineColor(kBlack);
  h_ratio_genSim->Draw("samep");
  //line
  float xmax = h_ratio_genSim->GetXaxis()->GetXmax();
  float xmin = h_ratio_genSim->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,1,xmax,1);
  line->SetLineColor(kBlack);
  line->SetLineWidth(2);
  line->SetLineStyle(2);
  line->Draw("SAME");

  c10->cd();
  c10->SetRightMargin(0.125);
  c10->SetLeftMargin(0.125);
  c10->SetBottomMargin(0.125);
  drawText(0.14, 0.935, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.5, 0.935, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 26);
  //drawText(0.125, 0.935, "#bf{CMS} #it{work in progress}: #gamma+Pb#rightarrowDijets PbPb #sqrt{s}=5.02 TeV; 2018", kBlack, 23);
  c10->SaveAs((dirPath + "v2_data_pythiaGenSim.png").c_str());



  
  /////////  v2 R4: DATA AND RECO     ///////////////////////

  TH1D *h_ratio_reco = h_profV2_R4->ProjectionX("h_ratio_reco");
  TH1D *h2_reco = h_profV2_pythia->ProjectionX("h2_reco");
  h_ratio_reco->Divide(h2_reco);
  h_ratio_reco->SetMarkerColor(kBlack);
  h_ratio_reco->SetMarkerStyle(kFullDotLarge);
  
  TCanvas *c11 = new TCanvas("c11","Title",800,800);
  TPad *main_reco = new TPad("main_reco", "new pad", 0.01, 0.315, 0.99, 0.99);
  TPad *ratio_reco = new TPad("ratio_reco", "new pad 2", 0.01, 0.1, 0.99, 0.38);

  c11->cd();
  main_reco->Draw();
  ratio_reco->Draw();

  main_reco->cd();
  main_reco->SetLeftMargin(0.125);
  main_reco->SetTickx(1);
  main_reco->SetTicky(1);
  h_profV2_R4->SetStats(0);
  h_profV2_R4->SetMarkerStyle(kFullDotLarge);
  h_profV2_R4->SetMarkerColor(kBlack);
  h_profV2_R4->SetLineColor(kBlack);
  h_profV2_R4->SetMarkerSize(1);
  h_profV2_R4->GetYaxis()->SetRangeUser(0,1.1);
  h_profV2_R4->GetYaxis()->SetTitle("<cos(2#phi)>");
  h_profV2_R4->GetYaxis()->SetTitleSize(0.08);
  h_profV2_R4->GetYaxis()->SetTitleOffset(0.75);
  h_profV2_R4->GetYaxis()->SetLabelSize(0.04);
  h_profV2_R4->Draw();
  h_profV2_pythia->SetFillStyle(3001);
  h_profV2_pythia->SetLineColor(kBlack);
  h_profV2_pythia->SetFillColor(kBlue-7);
  h_profV2_pythia->Draw("same hist E");
  drawLegendProfile(h_profV2_pythia, h_profV2_R4, 0.15, 0.5, 0.725, 0.85, "Pythia RECO", "anti-k_{T} R=0.4 data");

  ratio_reco->cd();
  ratio_reco->SetLeftMargin(0.125);
  ratio_reco->SetBottomMargin(0.29);
  ratio_reco->SetTickx(1);
  ratio_reco->SetTicky(1);
  h_ratio_reco->SetStats(0);
  h_ratio_reco->SetTitle("");
  h_ratio_reco->SetLineColor(kBlack);
  h_ratio_reco->GetXaxis()->SetTitle("Q_{T} [GeV]");
  h_ratio_reco->GetXaxis()->SetTitleSize(0.18);
  h_ratio_reco->GetXaxis()->SetTitleOffset(0.7);
  h_ratio_reco->GetXaxis()->SetLabelSize(0.10);
  h_ratio_reco->GetYaxis()->SetLabelSize(0.09);
  h_ratio_reco->GetYaxis()->SetRangeUser(0.6,1.4);
  h_ratio_reco->GetYaxis()->SetTitle("Data / MC");
  h_ratio_reco->GetYaxis()->SetTitleOffset(0.35);
  h_ratio_reco->GetYaxis()->SetTitleSize(0.17);
  h_ratio_reco->GetYaxis()->SetLabelSize(0.09);
  h_ratio_reco->Draw("samep");
  //line
  float xmax_reco = h_ratio_reco->GetXaxis()->GetXmax();
  float xmin_reco = h_ratio_reco->GetXaxis()->GetXmin();
  TLine *line_reco = new TLine(xmin_reco,1,xmax_reco,1);
  line_reco->SetLineColor(kBlack);
  line_reco->SetLineWidth(2);
  line_reco->SetLineStyle(2);
  line_reco->Draw("SAME");
  
  c11->cd();
  c11->SetRightMargin(0.125);
  c11->SetLeftMargin(0.125);
  c11->SetBottomMargin(0.125);
  drawText(0.14, 0.935, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.5, 0.935, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 26);
  //drawText(0.125, 0.935, "#bf{CMS} #it{work in progress}: #gamma+Pb#rightarrowDijets PbPb #sqrt{s}=5.02 TeV; 2018", kBlack, 23);
  c11->SaveAs((dirPath + "v2_data_pythiaRECO.png").c_str()); 






  ////////////////    compare data and reco Delta Phi Distributions //////////////////////////////


  TCanvas *c1 = new TCanvas("c1","Title",800,800);
  setMargins(c1);
  h_trigPhi->SetStats(0);
  h_trigPhi->SetTitle(";#phi_{#vec{Q_{T}}, #vec{P_{T}}} [radians]; Counts");
  h_trigPhi_reco->Scale(h_trigPhi->Integral()/h_trigPhi_reco->Integral());
  h_trigPhi_reco->SetMarkerColor(kRed);
  h_trigPhi_reco->SetLineColor(kRed);
  h_trigPhi_reco->SetMarkerStyle(kFullDotLarge);
  h_trigPhi_reco->SetMarkerSize(1);
  h_trigPhi->SetMarkerColor(kBlack);
  h_trigPhi->SetLineColor(kBlack);
  h_trigPhi->SetMarkerStyle(kFullDotLarge);
  h_trigPhi->SetMarkerSize(1);
  h_trigPhi->Draw("hist pE");
  h_trigPhi_reco->Draw("hist pE same");
  drawLegendStr(h_trigPhi, h_trigPhi_reco, 0.25, 0.475, 0.75, 0.85, "Data", "reco Pythia");	     
  c1->SaveAs((dirPath + "data_reco_deltaPhi.png").c_str());


  //////////////// condor vtx comparisons /////////////////////////////
  TCanvas *c25 = new TCanvas("c25","Title",800,800);
  c25->SetLogy();
  c25->SetTickx(1);
  c25->SetTicky(1);
  c25->SetLeftMargin(0.125);
  h_condor_vtxPythia->Scale(h_condor_vtxData->Integral()/h_condor_vtxPythia->Integral());
  h_condor_vtxData->SetMarkerColor(kBlue);
  h_condor_vtxData->SetLineColor(kBlue);
  h_condor_vtxPythia->SetMarkerColor(kRed);
  h_condor_vtxPythia->SetLineColor(kRed);
  h_condor_vtxData->SetStats(0);
  h_condor_vtxData->SetTitle(";Z vertex [cm]; Counts");
  h_condor_vtxData->GetYaxis()->SetRangeUser(1,700000);
  h_condor_vtxData->Draw("hist E");
  h_condor_vtxPythia->Draw("hist E same");
  drawText(0.2, 0.78, "|vtx_{z}|< 20 cm", kBlack, 31);
  drawText(0.2, 0.72, "0nXn or Xn0n", kBlack, 31);
  drawText(0.2, 0.66, "skip nJet=0,1", kBlack, 31);
  drawText(0.2, 0.60, "|#eta_{jets}| < 2.4", kBlack, 31);
  drawText(0.2, 0.54, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.2, 0.48, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.14, 0.915, "#bf{CMS} #it{work in progress}", kBlack, 26);
  drawText(0.55, 0.915, "PbPb #sqrt{s}=5.02 TeV; 2018", kBlack, 26);
  drawLegendStr(h_condor_vtxData, h_condor_vtxPythia, 0.55, 0.75, 0.75, 0.85, "data", "reco Pythia");
  c25->SaveAs((dirPath + "vtxCut.png").c_str());

  

  ///////////////   compare reco and gen Delta Phi Distributions   ///////////////////////////////////



  TCanvas *c2 = new TCanvas("c2","Title",800,800);
  setMargins(c2);
  h_trigPhi_reco->SetStats(0);
  h_trigPhi_reco->SetTitle(";#phi_{#vec{Q_{T}}, #vec{P_{T}}} [radians]; Counts");
  h_trigPhi_reco->Scale(h_trigPhi_gen->Integral()/h_trigPhi_reco->Integral());
  h_trigPhi_reco->SetMarkerColor(kRed);
  h_trigPhi_reco->SetLineColor(kRed);
  h_trigPhi_reco->SetMarkerStyle(kFullDotLarge);
  h_trigPhi_reco->SetMarkerSize(1);
  h_trigPhi_gen->SetMarkerColor(kBlack);
  h_trigPhi_gen->SetLineColor(kBlack);
  h_trigPhi_gen->SetMarkerStyle(kFullDotLarge);
  h_trigPhi_gen->SetMarkerSize(1);
  h_trigPhi_reco->Draw("hist pE");
  h_trigPhi_gen->Draw("hist pE same");
  drawLegendStr(h_trigPhi_gen, h_trigPhi_reco, 0.175, 0.45, 0.75, 0.85, "gen Pythia", "reco Pythia");	     
  c2->SaveAs((dirPath + "gen_reco_deltaPhi.png").c_str());



  ////////////////////////// compare forward rap gap /////////////////////////////////////////////////
  TCanvas *c3 = new TCanvas("c3","Title",800,800);
  c3->SetLeftMargin(0.12);
  int bin_low = hPythia_forwardRapGap->FindBin(1.2), bin_lowD = h_forwardRapGap->FindBin(1.2);
  int bin_high = hPythia_forwardRapGap->GetNbinsX();
  hPythia_forwardRapGap->Scale(h_forwardRapGap->Integral(bin_lowD, bin_high)/hPythia_forwardRapGap->Integral(bin_low, bin_high));
  hPythia_forwardRapGap->SetLineColor(kRed);
  hPythia_forwardRapGap->SetMarkerColor(kRed);
  hPythia_forwardRapGap->SetMarkerStyle(kFullDotLarge);
  h_forwardRapGap->SetLineColor(kBlack);
  h_forwardRapGap->SetMarkerColor(kBlack);
  h_forwardRapGap->SetMarkerStyle(kFullDotLarge);
  h_forwardRapGap->SetTitle(";Forward Rapidity Gap; Counts Norm. to Data");
  h_forwardRapGap->Draw("hist pE");
  hPythia_forwardRapGap->Draw("hist same pE");
  
  /*line->SetLineColor(kBlack);    
  line->SetLineStyle(3);         
  line->SetLineWidth(2);         
  drawLegendStr(h_forwardRapGap, hPythia_forwardRapGap, 0.45, 0.6, 0.75, 0.85, "data", "reco Pythia");
  line->Draw("same");*/
  c3->SaveAs((dirPath + "forward_rapgap_comp.png").c_str());


  ////////////////////////// compare dijetMass ////////////////////////////////////////////////////////
  TCanvas *c8 = new TCanvas("c8","Title",800,800);
  hPythia_dijetMass->Scale(h_dijetMass->Integral()/hPythia_dijetMass->Integral());
  hPythia_dijetMass->SetLineColor(kRed);
  h_dijetMass->SetMarkerStyle(kFullDotLarge);
  h_dijetMass->SetMarkerColor(kBlack);
  h_dijetMass->SetLineColor(kBlack);
  h_dijetMass->SetStats(0);
  h_dijetMass->GetYaxis()->SetRangeUser(0,275);
  h_dijetMass->SetTitle(";dijet mass [GeV]; Counts");
  h_dijetMass->Draw("hist pE");
  hPythia_dijetMass->Draw("hist E same");
  drawText(0.63, 0.65, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.63, 0.59, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.63, 0.53, "|#eta_{1,2}| < 2.4", kBlack, 31);
  drawText(0.63, 0.47, "P_{T} > Q_{T}", kBlack, 31);
  drawLegendStr(h_dijetMass, hPythia_dijetMass, 0.63, 0.75, 0.75, 0.85, "Data", "Pythia");
  c8->SaveAs((dirPath + "dijetMass.png").c_str());

  ////////////////////////// compare dijetRap ////////////////////////////////////////////////////////
  TCanvas *c9 = new TCanvas("c9","Title",800,800);
  hPythia_dijetRap->Scale(h_dijetRap->Integral()/hPythia_dijetRap->Integral());
  hPythia_dijetRap->SetLineColor(kRed);
  h_dijetRap->SetMarkerStyle(kFullDotLarge);
  h_dijetRap->SetMarkerColor(kBlack);
  h_dijetRap->SetLineColor(kBlack);
  h_dijetRap->SetStats(0);
  h_dijetRap->GetYaxis()->SetRangeUser(0,300);
  h_dijetRap->SetTitle(";dijet rapidity; Counts");
  h_dijetRap->Draw("hist pE");
  hPythia_dijetRap->Draw("hist E same");
  drawText(0.67, 0.65, "p_{T,1} > 30 GeV", kBlack, 30);
  drawText(0.67, 0.59, "p_{T,2} > 20 GeV", kBlack, 30);
  drawText(0.67, 0.53, "|#eta_{1,2}| < 2.4", kBlack, 30);
  drawText(0.67, 0.47, "P_{T} > Q_{T}", kBlack, 30);
  drawLegendStr(h_dijetRap, hPythia_dijetRap, 0.67, 0.75, 0.75, 0.85, "Data", "Pythia");
  c9->SaveAs((dirPath + "dijetRap.png").c_str());


  ////////////////////////// compare nPF distribution /////////////////////////////////////////////////
  TCanvas *c4 = new TCanvas("c4","Title",800,800);
  hPythia_nPF_ch->Scale(h_nPF_ch->Integral()/hPythia_nPF_ch->Integral());
  hPythia_nPF_ch->SetLineColor(kRed);
  h_nPF_ch->Draw();
  hPythia_nPF_ch->Draw("hist same");
  drawLegendStr(h_nPF_ch, hPythia_nPF_ch, 0.55, 0.75, 0.75, 0.85, "Data", "Pythia");
  c4->SaveAs((dirPath + "nPF_ch.png").c_str());
}
