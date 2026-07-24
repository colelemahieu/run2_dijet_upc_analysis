// compare_0nXn_0n0n.C
// This code makes plots comparing 0n0n and 0nXn data kinematics

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

void pad2_3(TH1F *h1, TH1F *h2, TH1F *h1b, TH1F *h2b, TH1F *h1c, TH1F *h2c, const char *titleX, const char *titleY, string label1, string label2, string label3, string label4, const char *name, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80)
{
  // Plotting
  gStyle->SetOptStat(0);
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",1200,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.01,0.50,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p2","p2",0.50,0.01,0.99,0.99,0); p2->Draw();
  p1->SetRightMargin(0.01725);
  p2->SetLeftMargin(0.01725), p2->SetRightMargin(0.175);

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  p1->cd();
  p1->SetLeftMargin(0.175);
  //main->SetBottomMargin(0.11);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h1->SetStats(0);
  h2->SetStats(0);
  h1->GetYaxis()->SetRangeUser(yMinimum,yMaximum);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(1.75);
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitleOffset(0.9);
  h1->SetLineWidth(2);
  h1->SetLineColor(kRed);
  h2->SetLineWidth(2);
  h2->SetLineColor(kBlue);
  h1b->SetLineColor(kBlack);
  h1b->SetMarkerColor(kBlack);
  h1b->SetMarkerStyle(kFullDotLarge);
  h2b->SetLineColor(kBlack);
  h2b->SetMarkerColor(kBlack);
  h2b->SetMarkerStyle(kFullTriangleDown);
  h1->SetTitle("");
  h2->SetTitle("");
  h1b->SetTitle("");
  h1->Draw("hist E");
  h2->Draw("hist same E");
  h1b->Draw("hist same pE");
  h2b->Draw("hist same pE");
  drawText(0.225, 0.825, "0nXn", kBlack, 28);
  drawText(0.63, 0.65, "p_{T,1} > 30 GeV", kBlack, 28);
  drawText(0.63, 0.59, "p_{T,2} > 20 GeV", kBlack, 28);
  drawText(0.63, 0.53, "|#eta_{1,2}| < 2.4", kBlack, 28);
  drawText(0.63, 0.47, "P_{T} > Q_{T}", kBlack, 28);
  drawLegendStr4(h1, "le", h1b, "pe", h2, "le", h2b, "pe", 0.525, 0.85, 0.725, 0.88, "Leading Jet Pythia", "Leading Jet Data", "Subleading Jet Pythia", "Subleading Jet Data");
  
  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h2->SetStats(0);
  h2->GetXaxis()->SetLabelSize(0.04);
  h2->GetYaxis()->SetRangeUser(yMinimum,yMaximum);
  h2->GetYaxis()->SetLabelSize(0.0000000000001);
  h1c->SetLineColor(kBlack);
  h1c->SetMarkerColor(kBlack);
  h1c->SetMarkerStyle(kFullDotLarge);
  h2c->SetLineColor(kBlack);
  h2c->SetMarkerColor(kBlack);
  h2c->SetMarkerStyle(kFullTriangleDown);
  h1c->SetTitle("");
  h2c->SetTitle("");
  h2->Draw("hist E");
  h1->Draw("hist E same");
  h1c->Draw("hist same pE");
  h2c->Draw("hist same pE");
  drawText(0.05, 0.825, "0n0n", kBlack, 30);

  titlePad->cd();
  drawText(.1, .91, "#bf{CMS} #it{Preliminary}", kBlack, 28);
  drawText(0.65, 0.91, "PbPb: #sqrt{s}=5.02 TeV (2018)", kBlack, 28);
  drawText(0.42, 0.02, titleX, kBlack, 28);
  
  canvas->SaveAs(name);
  delete canvas;
}



void compare_0nXn_0n0n(string recoPythiaFile, string file_0nXn, string file_0n0n)
{
  // Read in files and histograms
  TFile *recoPythia = new TFile(recoPythiaFile.c_str());
  TFile *file0nXn = new TFile(file_0nXn.c_str());
  TFile *file0n0n = new TFile(file_0n0n.c_str());

  TH1F *h_jtPt_L_reco = (TH1F*)recoPythia->Get("h_jtPt_L");
  TH1F *h_jtPt_S_reco = (TH1F*)recoPythia->Get("h_jtPt_S");
  TH1F *h_PT_reco = (TH1F*)recoPythia->Get("h_PT");
  TH1F *h_QT_reco = (TH1F*)recoPythia->Get("h_QT");

  TH1F *h_jtPt_L_0nXn = (TH1F*)file0nXn->Get("h_jtPt_L");
  TH1F *h_jtPt_S_0nXn = (TH1F*)file0nXn->Get("h_jtPt_S");
  TH1F *h_PT_0nXn = (TH1F*)file0nXn->Get("h_PT");
  TH1F *h_QT_0nXn = (TH1F*)file0nXn->Get("h_QT");

  TH1F *h_jtPt_L_0n0n = (TH1F*)file0n0n->Get("h_jtPt_L");
  TH1F *h_jtPt_S_0n0n = (TH1F*)file0n0n->Get("h_jtPt_S");
  TH1F *h_PT_0n0n = (TH1F*)file0n0n->Get("h_PT");
  TH1F *h_QT_0n0n = (TH1F*)file0n0n->Get("h_QT");

  // Directory to Store
  string dirPath = "forAN/";

  // normalize to unity
  h_jtPt_L_reco->Scale(1/h_jtPt_L_reco->Integral());
  h_jtPt_S_reco->Scale(1/h_jtPt_S_reco->Integral());
  h_jtPt_L_0nXn->Scale(1/h_jtPt_L_0nXn->Integral());
  h_jtPt_S_0nXn->Scale(1/h_jtPt_S_0nXn->Integral());
  h_jtPt_L_0n0n->Scale(1/h_jtPt_L_0n0n->Integral());
  h_jtPt_S_0n0n->Scale(1/h_jtPt_S_0n0n->Integral());
  h_PT_reco->Scale(1/h_PT_reco->Integral());
  h_QT_reco->Scale(1/h_QT_reco->Integral());
  h_PT_0n0n->Scale(1/h_PT_0n0n->Integral());
  h_QT_0n0n->Scale(1/h_QT_0n0n->Integral());
  h_PT_0nXn->Scale(1/h_PT_0nXn->Integral());
  h_QT_0nXn->Scale(1/h_QT_0nXn->Integral());


  // use functions
  pad2_3(h_jtPt_L_reco, h_jtPt_S_reco, h_jtPt_L_0nXn, h_jtPt_S_0nXn, h_jtPt_L_0n0n, h_jtPt_S_0n0n, "Single jet p_{T} [GeV]", "#frac{dN}{N}", "Leading Jet Pythia", "Subleading Jet Pythia", "Leading Jet Data", "Subleading Jet Data", "singleJets_0nXn_0n0n.png", 0, 0.248);

  pad2_3(h_PT_reco, h_QT_reco, h_PT_0nXn, h_QT_0nXn, h_PT_0n0n, h_QT_0n0n, "Dijet P_{T} and Q_{T} [GeV]", "#frac{dN}{N}", "P_{T} Pythia", "Q_{T} Pythia", "P_{T} Data", "Q_{T} Jet Data", "dijet_0nXn_0n0n.png", 0, 0.248);



  /////////    Jet Kinematics, 0n0n compared to 0nXn    //////////////////
  
  TCanvas *c14 = new TCanvas("c14","Title",800,800);
  TPad *main14 = new TPad("main14", "new pad", 0.01, 0.315, 0.99, 0.99);
  TPad *ratio14 = new TPad("ratio14", "new pad 2", 0.01, 0.1, 0.99, 0.38);
  // ratios
  TH1F* hRatio_L = (TH1F*)h_jtPt_L_0nXn->Clone("hRatio_L");
  hRatio_L->Divide(h_jtPt_L_0n0n);
  TH1F* hRatio_S = (TH1F*)h_jtPt_S_0nXn->Clone("hRatio_S");
  hRatio_S->Divide(h_jtPt_S_0n0n);

  c14->cd();
  main14->Draw();
  ratio14->Draw();

  main14->cd();
  main14->SetTickx(1);
  main14->SetTicky(1);
  main14->SetLeftMargin(0.12);
  main14->SetBottomMargin(0.11);
  h_jtPt_L_0n0n->SetTitle(";; Counts (norm. to unity)");
  h_jtPt_L_0n0n->SetStats(0);
  h_jtPt_L_0n0n->SetMarkerColor(kRed);
  h_jtPt_L_0n0n->SetLineColor(kRed);
  h_jtPt_L_0n0n->SetMarkerStyle(kOpenCircle);
  h_jtPt_S_0n0n->SetTitle(";; Counts (norm. to unity)");
  h_jtPt_S_0n0n->SetStats(0);
  h_jtPt_S_0n0n->SetMarkerColor(kBlue);
  h_jtPt_S_0n0n->SetLineColor(kBlue);
  h_jtPt_S_0n0n->SetMarkerStyle(kOpenSquare);
  h_jtPt_L_0n0n->SetTitle(";; Counts (norm. to unity)");
  h_jtPt_L_0nXn->SetStats(0);
  h_jtPt_L_0nXn->SetMarkerColor(kRed);
  h_jtPt_S_0nXn->SetMarkerColor(kBlue);
  h_jtPt_S_0nXn->SetMarkerStyle(kFullSquare);
  h_jtPt_L_0nXn->SetMarkerStyle(kFullCircle);
  h_jtPt_L_0nXn->SetLineColor(kRed);
  h_jtPt_S_0nXn->SetLineColor(kBlue);
  h_jtPt_L_0nXn->SetLineWidth(2);
  h_jtPt_S_0nXn->SetLineWidth(2);
  // h_jtPt_L_0nXn->Scale(h_jtPt_L_0n0n->Integral()/h_jtPt_L_0nXn->Integral());
  //h_jtPt_S_0nXn->Scale(h_jtPt_S_0n0n->Integral()/h_jtPt_S_0nXn->Integral());
  h_jtPt_L_0n0n->GetXaxis()->SetLabelSize(0.00000000000000001);
  h_jtPt_L_0n0n->GetXaxis()->SetTitleSize(0.05);
  h_jtPt_L_0n0n->GetYaxis()->SetTitleSize(0.05);
  h_jtPt_L_0n0n->GetYaxis()->SetLabelSize(0.045);
  h_jtPt_L_0n0n->GetYaxis()->SetTitleOffset(1.1);
  h_jtPt_L_0n0n->GetYaxis()->SetRangeUser(0,0.25);  // gg->qq, 0nXn
  //h_jtPt_L->GetYaxis()->SetRangeUser(0,750);  // gg->qq, 0n0n
  h_jtPt_L_0n0n->Draw("p E");
  h_jtPt_S_0nXn->Draw("hist pE same");
  h_jtPt_L_0nXn->Draw("hist pE same");
  h_jtPt_S_0n0n->Draw("p E same");
  drawText(0.63, 0.6, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.63, 0.53, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.63, 0.46, "|#eta_{1,2}| < 3.0", kBlack, 31);
  drawText(0.63, 0.39, "P_{T} > Q_{T}", kBlack, 31);
  //drawLegendStr(hPythia_jtPt_L, hPythia_jtPt_S, 0.65, 0.8, 0.8, 0.875, "Leading Jet", "Subleading Jet");
  //drawLegendStr4(h_jtPt_L_0nXn, "pe", h_jtPt_L_0n0n, "pe", h_jtPt_S_0nXn, "pe", h_jtPt_S_0n0n, "pe", 0.61, 0.79, 0.725, 0.88, "0nXn Leading Jet", "0n0n Leading Jet", "0nXn Subleading Jet", "0n0n Subleading Jet");
  drawGridLegend(h_jtPt_L_0n0n, h_jtPt_L_0nXn, h_jtPt_S_0n0n, h_jtPt_S_0nXn, "#bf{Leading}", "#bf{Subleading}", "#bf{0n0n}", "#bf{0nXn}",0.7,0.7);
  drawCMS_lumi(c14);

  ratio14->cd();
  ratio14->SetTickx(1);
  ratio14->SetTicky(1);
  ratio14->SetLeftMargin(0.12);
  ratio14->SetTopMargin(0.11);
  ratio14->SetBottomMargin(0.275);
  hRatio_L->SetStats(0);
  hRatio_S->SetStats(0);
  hRatio_L->SetLineColor(kRed);
  hRatio_S->SetLineColor(kBlue);
  hRatio_L->SetMarkerColor(kRed);
  hRatio_S->SetMarkerColor(kBlue);
  hRatio_L->GetXaxis()->SetLabelSize(0.11);
  hRatio_L->GetXaxis()->SetTitleSize(0.11);  
  hRatio_L->GetXaxis()->SetTitleOffset(1.1);
  hRatio_L->GetYaxis()->SetLabelSize(0.11);
  hRatio_L->GetYaxis()->SetTitleSize(0.11);
  hRatio_L->GetYaxis()->SetTitleOffset(0.5);
  hRatio_L->GetXaxis()->SetTitle("p_{T} [GeV]");
  hRatio_L->GetYaxis()->SetTitle("0nXn / 0n0n");
  hRatio_L->Draw("hist pE");
  hRatio_S->Draw("hist pE same");
  float xmaxRatio = hRatio_L->GetXaxis()->GetXmax();
  float xminRatio = hRatio_L->GetXaxis()->GetXmin();
  TLine *lineRatio = new TLine(xminRatio,1,xmaxRatio,1);
  lineRatio->SetLineColor(kBlack);
  lineRatio->SetLineWidth(3);
  lineRatio->SetLineStyle(2); // dash
  lineRatio->Draw("LSAME");
  hRatio_L->Draw("hist pE same");
  hRatio_S->Draw("hist pE same");
  drawText(0.175, 0.75, Form("#chi^{2}/NDF=%0.2f",find_hist_chi2_ndf(h_jtPt_L_0nXn, h_jtPt_L_0n0n)), kRed, 28);
  drawText(0.175, 0.6, Form("#chi^{2}/NDF=%0.2f",find_hist_chi2_ndf(h_jtPt_S_0nXn, h_jtPt_S_0n0n)), kBlue, 28);
  c14->SaveAs((dirPath + "data_jets_0n0n_0nXn_pt.png").c_str());



  ///////////    QT and PT, 0n0n compared to 0nXn  //////////////////////
  
  TCanvas *c5 = new TCanvas("c5","Title5",800,800);
  h_PT_0nXn->SetStats(0);
  h_PT_0nXn->SetMarkerColor(kBlack);
  h_PT_0nXn->SetLineColor(kBlack);
  h_PT_0nXn->SetMarkerStyle(20);
  h_QT_0nXn->SetStats(0);
  h_QT_0nXn->SetMarkerColor(kBlack);
  h_QT_0nXn->SetLineColor(kBlack);
  h_QT_0nXn->SetMarkerStyle(21);
  //hPythia_PT->Scale(h_PT->Integral()/hPythia_PT->Integral());
  //hPythia_QT->Scale(h_QT->Integral()/hPythia_QT->Integral());
  //hPythia_QTGen->Scale(h_QT->Integral()/hPythia_QTGen->Integral());
  h_PT_0nXn->SetTitle(";P_{T} and Q_{T} [GeV]; Counts (norm. to unity)");
  h_PT_0n0n->SetStats(0);
  h_PT_0n0n->SetMarkerColor(kOrange+7);
  h_QT_0n0n->SetMarkerColor(kGreen+2);
  h_PT_0n0n->SetLineColor(kOrange+7);
  h_PT_0n0n->SetLineWidth(2);
  h_QT_0n0n->SetLineWidth(2);
  h_QT_0n0n->SetLineColor(kGreen+2);
  //h_QT_0n0n->SetMarkerSize(1);
  h_PT_0n0n->SetMarkerStyle(kFullCircle);
  h_QT_0n0n->SetMarkerStyle(kFullSquare);
  //hPythia_QTGen->SetMarkerColor(kBlack);
  //hPythia_QTGen->SetLineColor(kBlack);
  //hPythia_QTGen->SetLineWidth(3);
  h_PT_0nXn->GetXaxis()->SetTitleSize(0.05);
  h_PT_0nXn->GetYaxis()->SetTitleSize(0.05);
  h_PT_0nXn->GetYaxis()->SetTitleOffset(1.3);
  h_PT_0nXn->GetYaxis()->SetRangeUser(0,0.2); // 0nXn
  //h_PT->GetYaxis()->SetRangeUser(0,700);  // gg->qq, 0n0n
  h_PT_0nXn->Draw("p E");
  h_PT_0n0n->Draw("hist p E same");
  h_QT_0nXn->Draw("hist p E same");
  h_QT_0n0n->Draw("hist same p E");
  //hPythia_QTGen->Draw("hist same");
  //drawLegendStr4(h_PT_0n0n, "pe", h_PT_0nXn, "pe", h_QT_0n0n, "pe", h_QT_0nXn, "pe", 0.63, 0.8, 0.7, 0.875, "0n0n P_{T}", "0nXn P_{T}", "0n0n Q_{T}", "0nXn Q_{T}");
  //drawGridLegend(h_jtPt_L_0n0n, h_jtPt_L_0nXn, h_jtPt_S_0n0n, h_jtPt_S_0nXn, "Leading", "Subleading", "0n0n", "0nXn");
  drawText(0.63, 0.6, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.63, 0.54, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.63, 0.48, "|#eta_{1,2}| < 3.0", kBlack, 31);
  drawText(0.63, 0.42, "P_{T} > Q_{T}", kBlack, 31);
  drawCMS_lumi(c5);
  c5->SaveAs((dirPath + "qtpt_0n0n_0nXn.png").c_str());
  
}
