// drawSystematics2_v4.C
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
  legend->SetTextSize(0.05);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }



void pad3(TH1F *h_JES_R2, TH1F *h_JER_R2, TH1F *h_JAR_R2, TH1F *h_LSR_R2, TH1F *h_Prior_R2, TH1F *h_trkGap_R2, TH1F *h_HF_R2, TH1F *h_ITER_R2, TH1F *h_total_R2, TH1F *h_JES_R4, TH1F *h_JER_R4, TH1F *h_JAR_R4, TH1F *h_LSR_R4, TH1F *h_Prior_R4, TH1F *h_trkGap_R4, TH1F *h_HF_R4, TH1F *h_ITER_R4, TH1F *h_total_R4, TH1F *h_JES_R6, TH1F *h_JER_R6, TH1F *h_JAR_R6, TH1F *h_LSR_R6, TH1F *h_Prior_R6, TH1F *h_trkGap_R6, TH1F *h_HF_R6, TH1F *h_ITER_R6, TH1F *h_total_R6, const char *titleX, const char *titleY, const char *name, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80)
{
  // settings for hists
  h_JES_R2->SetLineColor(kRed);
  h_JER_R2->SetLineColor(kOrange+7);
  h_JAR_R2->SetLineColor(kYellow+2);
  h_LSR_R2->SetLineColor(kGreen+2);
  h_Prior_R2->SetLineColor(kCyan+1);
  h_trkGap_R2->SetLineColor(kBlue);
  h_HF_R2->SetLineColor(kViolet);
  h_ITER_R2->SetLineColor(kPink+7);
  h_total_R2->SetLineColor(kBlack);
  h_JES_R2->SetLineWidth(2);
  h_JER_R2->SetLineWidth(2);
  h_JAR_R2->SetLineWidth(2);
  h_LSR_R2->SetLineWidth(2);
  h_Prior_R2->SetLineWidth(2);
  h_trkGap_R2->SetLineWidth(2);
  h_HF_R2->SetLineWidth(2);
  h_ITER_R2->SetLineWidth(2);
  h_total_R2->SetLineWidth(2);
  h_JES_R4->SetLineColor(kRed);
  h_JER_R4->SetLineColor(kOrange+7);
  h_JAR_R4->SetLineColor(kYellow+2);
  h_LSR_R4->SetLineColor(kGreen+2);
  h_Prior_R4->SetLineColor(kCyan+1);
  h_trkGap_R4->SetLineColor(kBlue);
  h_HF_R4->SetLineColor(kViolet);
  h_ITER_R4->SetLineColor(kPink+7);
  h_total_R4->SetLineColor(kBlack);
  h_JES_R4->SetLineWidth(2);
  h_JER_R4->SetLineWidth(2);
  h_JAR_R4->SetLineWidth(2);
  h_LSR_R4->SetLineWidth(2);
  h_Prior_R4->SetLineWidth(2);
  h_trkGap_R4->SetLineWidth(2);
  h_HF_R4->SetLineWidth(2);
  h_ITER_R4->SetLineWidth(2);
  h_total_R4->SetLineWidth(2);
  h_JES_R6->SetLineColor(kRed);
  h_JER_R6->SetLineColor(kOrange+7);
  h_JAR_R6->SetLineColor(kYellow+2);
  h_LSR_R6->SetLineColor(kGreen+2);
  h_Prior_R6->SetLineColor(kCyan+1);
  h_trkGap_R6->SetLineColor(kBlue);
  h_HF_R6->SetLineColor(kViolet);
  h_ITER_R6->SetLineColor(kPink+7);
  h_total_R6->SetLineColor(kBlack);
  h_JES_R6->SetLineWidth(2);
  h_JER_R6->SetLineWidth(2);
  h_JAR_R6->SetLineWidth(2);
  h_LSR_R6->SetLineWidth(2);
  h_Prior_R6->SetLineWidth(2);
  h_trkGap_R6->SetLineWidth(2);
  h_HF_R6->SetLineWidth(2);
  h_ITER_R6->SetLineWidth(2);
  h_total_R6->SetLineWidth(2);
  
  // Plotting
  gStyle->SetOptStat(0);
  TString uniqueCanvasName = Form("canvas_%p", h_total_R4);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",1200,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.01,0.36,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p2","p2",0.36,0.01,0.66,0.99,0); p2->Draw();
  TPad* p3 = new TPad("p3","p3",0.66,0.01,0.99,0.99,0); p3->Draw();
  p1->SetRightMargin(0.025);
  p2->SetLeftMargin(0.025), p2->SetRightMargin(0.025);
  p3->SetLeftMargin(0.025);
 

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  p1->cd();
  p1->SetLeftMargin(0.175);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h_JES_R2->SetStats(0);
  h_JES_R2->GetYaxis()->SetRangeUser(yMinimum,yMaximum);
  h_JES_R2->GetXaxis()->SetLabelSize(0.05);
  h_JES_R2->GetXaxis()->SetTitle(titleX);
  h_JES_R2->GetXaxis()->SetTitleSize(0.045);
  h_JES_R2->GetXaxis()->SetTitleOffset(1.1);
  h_JES_R2->GetYaxis()->SetTitle(titleY);
  h_JES_R2->GetYaxis()->SetTitleSize(0.055);
  h_JES_R2->GetYaxis()->SetLabelSize(0.06);
  h_JES_R2->GetYaxis()->SetTitleOffset(1.35);
  //h1->GetYaxis()->SetNdivisions(707);
  //h1->SetTitle("");
  //h1b->SetTitle("");
  h_JES_R2->SetTitle(" ");
  h_JES_R2->Draw("hist");
  h_JER_R2->Draw("hist same");
  h_JAR_R2->Draw("hist same");
  h_LSR_R2->Draw("hist same");
  h_Prior_R2->Draw("hist same");
  h_trkGap_R2->Draw("hist same");
  h_HF_R2->Draw("hist same");
  h_ITER_R2->Draw("hist same");
  h_total_R2->Draw("hist same");
  drawLegendStr9(h_JES_R2, h_JER_R2, h_JAR_R2, h_LSR_R2, h_Prior_R2, h_trkGap_R2, h_HF_R2, h_ITER_R2, h_total_R2, 0.2, 0.55, 0.5, 0.85, "JES", "JER", "JAR", "LSR", "Prior", "Trk Gap", "HF", "ITER", "total systematics");
  drawText(.625, .79, "r=0.2", kBlack, 28);


  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h_JES_R4->SetStats(0);
  h_JES_R4->GetYaxis()->SetRangeUser(yMinimum,yMaximum);
  h_JES_R4->GetXaxis()->SetLabelSize(0.05);
  h_JES_R4->GetYaxis()->SetLabelSize(0.0000000000001);
  h_JES_R4->SetTitle("");
  h_JES_R4->Draw("hist");
  h_JER_R4->Draw("hist same");
  h_JAR_R4->Draw("hist same");
  h_LSR_R4->Draw("hist same");
  h_Prior_R4->Draw("hist same");
  h_trkGap_R4->Draw("hist same");
  h_HF_R4->Draw("hist same");
  h_ITER_R4->Draw("hist same");
  h_total_R4->Draw("hist same");
  drawText(.425, .79, "r=0.4", kBlack, 28);
  drawText(.425, .915, "0nXn", kBlack, 29);


  p3->cd();
  p3->SetTickx(1);
  p3->SetTicky(1);
  h_JES_R6->SetStats(0);
  h_JES_R6->GetYaxis()->SetRangeUser(yMinimum,yMaximum);
  h_JES_R6->GetXaxis()->SetLabelSize(0.05);
  h_JES_R6->GetYaxis()->SetLabelSize(0.0000000000001);
  h_JES_R6->SetTitle("");
  h_JES_R6->Draw("hist");
  h_JER_R6->Draw("hist same");
  h_JAR_R6->Draw("hist same");
  h_LSR_R6->Draw("hist same");
  h_Prior_R6->Draw("hist same");
  h_trkGap_R6->Draw("hist same");
  h_HF_R6->Draw("hist same");
  h_ITER_R6->Draw("hist same");
  h_total_R6->Draw("hist same");
  drawText(.45, .79, "r=0.6", kBlack, 28);

  
  titlePad->cd();
  drawText(.075, .915, "#bf{CMS} #it{Preliminary}", kBlack, 28);
  drawText(0.675, 0.915, "PbPb: #sqrt{s_{NN}} = 5.02 TeV (2018)", kBlack, 28);
  

  canvas->SaveAs(name);
  delete canvas;
}



void drawSystematics2_v4()
{
  // input files
  TFile *fileR2 = new TFile("Files/systematic_hists_r2_v4.root");
  TFile *fileR4 = new TFile("Files/systematic_hists_r4_v4.root");
  TFile *fileR6 = new TFile("Files/systematic_hists_r6_v4.root");

  // grab syst hists
  TH1F *h_JES_R2 = (TH1F*)fileR2->Get("h_JES");
  TH1F *h_JER_R2 = (TH1F*)fileR2->Get("h_JER");
  TH1F *h_JAR_R2 = (TH1F*)fileR2->Get("h_JAR");
  TH1F *h_LSR_R2 = (TH1F*)fileR2->Get("h_LSR");
  TH1F *h_Prior_R2 = (TH1F*)fileR2->Get("h_prior");
  TH1F *h_trkGap_R2 = (TH1F*)fileR2->Get("h_trkGap");
  TH1F *h_HF_R2 = (TH1F*)fileR2->Get("h_HF");
  TH1F *h_ITER_R2 = (TH1F*)fileR2->Get("h_ITER");
  TH1F *h_total_R2 = (TH1F*)fileR2->Get("h_total");

  TH1F *h_JES_R4 = (TH1F*)fileR4->Get("h_JES");
  TH1F *h_JER_R4 = (TH1F*)fileR4->Get("h_JER");
  TH1F *h_JAR_R4 = (TH1F*)fileR4->Get("h_JAR");
  TH1F *h_LSR_R4 = (TH1F*)fileR4->Get("h_LSR");
  TH1F *h_Prior_R4 = (TH1F*)fileR4->Get("h_prior");
  TH1F *h_trkGap_R4 = (TH1F*)fileR4->Get("h_trkGap");
  TH1F *h_HF_R4 = (TH1F*)fileR4->Get("h_HF");
  TH1F *h_ITER_R4 = (TH1F*)fileR4->Get("h_ITER");
  TH1F *h_total_R4 = (TH1F*)fileR4->Get("h_total");

  TH1F *h_JES_R6 = (TH1F*)fileR6->Get("h_JES");
  TH1F *h_JER_R6 = (TH1F*)fileR6->Get("h_JER");
  TH1F *h_JAR_R6 = (TH1F*)fileR6->Get("h_JAR");
  TH1F *h_LSR_R6 = (TH1F*)fileR6->Get("h_LSR");
  TH1F *h_Prior_R6 = (TH1F*)fileR6->Get("h_prior");
  TH1F *h_trkGap_R6 = (TH1F*)fileR6->Get("h_trkGap");
  TH1F *h_HF_R6 = (TH1F*)fileR6->Get("h_HF");
  TH1F *h_ITER_R6 = (TH1F*)fileR6->Get("h_ITER");
  TH1F *h_total_R6 = (TH1F*)fileR6->Get("h_total");
  

  pad3(h_JES_R2, h_JER_R2, h_JAR_R2, h_LSR_R2, h_Prior_R2, h_trkGap_R2, h_HF_R2, h_ITER_R2, h_total_R2, h_JES_R4, h_JER_R4, h_JAR_R4, h_LSR_R4, h_Prior_R4, h_trkGap_R4, h_HF_R4, h_ITER_R4, h_total_R4, h_JES_R6, h_JER_R6, h_JAR_R6, h_LSR_R6, h_Prior_R6, h_trkGap_R6, h_HF_R6, h_ITER_R6, h_total_R6, "                         Q_{T} [GeV]", "<cos(4#phi)> difference per bin (10^{-2})", "Pics/systematics_3panel_v4.pdf", 0 ,22);
  // plot
  /*TCanvas *c1 = new TCanvas("c1","c1",900,900);
  h_JES->SetLineColor(kRed);
  h_JER->SetLineColor(kOrange+7);
  h_JAR->SetLineColor(kYellow+2);
  h_LSR->SetLineColor(kGreen+2);
  h_Prior->SetLineColor(kCyan+1);
  h_trkGap->SetLineColor(kBlue);
  h_HF->SetLineColor(kViolet);
  h_ITER->SetLineColor(kPink+7);
  h_total->SetLineColor(kBlack);
  h_JES->SetLineWidth(2);
  h_JER->SetLineWidth(2);
  h_JAR->SetLineWidth(2);
  h_LSR->SetLineWidth(2);
  h_Prior->SetLineWidth(2);
  h_trkGap->SetLineWidth(2);
  h_HF->SetLineWidth(2);
  h_ITER->SetLineWidth(2);
  h_total->SetLineWidth(2);
  h_JES->SetStats(0);
  h_JES->GetYaxis()->SetRangeUser(0,16);
  h_JES->SetTitle(";Q_{T} [GeV]; <cos(2#phi)> difference per bin (10^{-2});");
  h_JES->Draw("hist");
  h_JER->Draw("hist same");
  h_JAR->Draw("hist same");
  h_LSR->Draw("hist same");
  h_Prior->Draw("hist same");
  h_trkGap->Draw("hist same");
  h_HF->Draw("hist same");
  h_ITER->Draw("hist same");
  h_total->Draw("hist same");
  drawLegendStr9(h_JES, h_JER, h_JAR, h_LSR, h_Prior, h_trkGap, h_HF, h_ITER, h_total, 0.15, 0.4, 0.6, 0.85, "JES", "JER", "JAR", "LSR", "Prior", "Trk Gap", "HF", "ITER", "total systematics");
  c1->SaveAs(outputName.c_str());*/
  
}
