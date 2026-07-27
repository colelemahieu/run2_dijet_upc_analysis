// drawSystematics2.C (rapidity)

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



void pad2(TH1F *h_JES_rap0, TH1F *h_JER_rap0, TH1F *h_JAR_rap0, TH1F *h_LSR_rap0, TH1F *h_Prior_rap0, TH1F *h_trkGap_rap0, TH1F *h_HF_rap0, TH1F *h_ITER_rap0, TH1F *h_total_rap0, TH1F *h_JES_rap1, TH1F *h_JER_rap1, TH1F *h_JAR_rap1, TH1F *h_LSR_rap1, TH1F *h_Prior_rap1, TH1F *h_trkGap_rap1, TH1F *h_HF_rap1, TH1F *h_ITER_rap1, TH1F *h_total_rap1, const char *titleX, const char *titleY, const char *name, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80)
{
  // settings for hists
  h_JES_rap0->SetLineColor(kRed);
  h_JER_rap0->SetLineColor(kOrange+7);
  h_JAR_rap0->SetLineColor(kYellow+2);
  h_LSR_rap0->SetLineColor(kGreen+2);
  h_Prior_rap0->SetLineColor(kCyan+1);
  h_trkGap_rap0->SetLineColor(kBlue);
  h_HF_rap0->SetLineColor(kViolet);
  h_ITER_rap0->SetLineColor(kPink+7);
  h_total_rap0->SetLineColor(kBlack);
  h_JES_rap0->SetLineWidth(2);
  h_JER_rap0->SetLineWidth(2);
  h_JAR_rap0->SetLineWidth(2);
  h_LSR_rap0->SetLineWidth(2);
  h_Prior_rap0->SetLineWidth(2);
  h_trkGap_rap0->SetLineWidth(2);
  h_HF_rap0->SetLineWidth(2);
  h_ITER_rap0->SetLineWidth(2);
  h_total_rap0->SetLineWidth(2);
  h_JES_rap1->SetLineColor(kRed);
  h_JER_rap1->SetLineColor(kOrange+7);
  h_JAR_rap1->SetLineColor(kYellow+2);
  h_LSR_rap1->SetLineColor(kGreen+2);
  h_Prior_rap1->SetLineColor(kCyan+1);
  h_trkGap_rap1->SetLineColor(kBlue);
  h_HF_rap1->SetLineColor(kViolet);
  h_ITER_rap1->SetLineColor(kPink+7);
  h_total_rap1->SetLineColor(kBlack);
  h_JES_rap1->SetLineWidth(2);
  h_JER_rap1->SetLineWidth(2);
  h_JAR_rap1->SetLineWidth(2);
  h_LSR_rap1->SetLineWidth(2);
  h_Prior_rap1->SetLineWidth(2);
  h_trkGap_rap1->SetLineWidth(2);
  h_HF_rap1->SetLineWidth(2);
  h_ITER_rap1->SetLineWidth(2);
  h_total_rap1->SetLineWidth(2);

  
  // Plotting
  gStyle->SetOptStat(0);
  TString uniqueCanvasName = Form("canvas_%p", h_total_rap0);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",1200,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.01,0.5,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p2","p2",0.5,0.01,0.99,0.99,0); p2->Draw();
  p1->SetRightMargin(0.03);
  p2->SetLeftMargin(0.03);
 

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  p1->cd();
  p1->SetLeftMargin(0.175);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h_JES_rap0->SetStats(0);
  h_JES_rap0->GetYaxis()->SetRangeUser(yMinimum,yMaximum);
  h_JES_rap0->GetXaxis()->SetLabelSize(0.05);
  h_JES_rap0->GetXaxis()->SetTitle(titleX);
  h_JES_rap0->GetXaxis()->SetTitleSize(0.045);
  h_JES_rap0->GetXaxis()->SetTitleOffset(1.1);
  h_JES_rap0->GetYaxis()->SetTitle(titleY);
  h_JES_rap0->GetYaxis()->SetTitleSize(0.055);
  h_JES_rap0->GetYaxis()->SetLabelSize(0.055);
  h_JES_rap0->GetYaxis()->SetTitleOffset(1.35);
  //h1->GetYaxis()->SetNdivisions(707);
  //h1->SetTitle("");
  //h1b->SetTitle("");
  h_JES_rap0->SetTitle(" ");
  h_JES_rap0->Draw("hist");
  h_JER_rap0->Draw("hist same");
  h_JAR_rap0->Draw("hist same");
  h_LSR_rap0->Draw("hist same");
  h_Prior_rap0->Draw("hist same");
  h_trkGap_rap0->Draw("hist same");
  h_HF_rap0->Draw("hist same");
  h_ITER_rap0->Draw("hist same");
  h_total_rap0->Draw("hist same");
  drawLegendStr9(h_JES_rap0, h_JER_rap0, h_JAR_rap0, h_LSR_rap0, h_Prior_rap0, h_trkGap_rap0, h_HF_rap0, h_ITER_rap0, h_total_rap0, 0.2, 0.55, 0.5, 0.85, "JES", "JER", "JAR", "LSR", "Prior", "Tracker Gap", "HF", "Iterations", "Total");
  drawText(.6, .825, "0 < Q_{T} < 12 GeV", kBlack, 28);
  drawText(.8, .775, "0nXn", kBlack, 28);
  drawText(.8, .725, "r = 0.4", kBlack, 28);


  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h_JES_rap1->SetStats(0);
  h_JES_rap1->GetYaxis()->SetRangeUser(yMinimum,yMaximum);
  h_JES_rap1->GetXaxis()->SetLabelSize(0.05);
  h_JES_rap1->GetYaxis()->SetLabelSize(0.0000000000001);
  h_JES_rap1->SetTitle("");
  h_JES_rap1->Draw("hist");
  h_JER_rap1->Draw("hist same");
  h_JAR_rap1->Draw("hist same");
  h_LSR_rap1->Draw("hist same");
  h_Prior_rap1->Draw("hist same");
  h_trkGap_rap1->Draw("hist same");
  h_HF_rap1->Draw("hist same");
  h_ITER_rap1->Draw("hist same");
  h_total_rap1->Draw("hist same");
  drawText(.525, .825, "12 < Q_{T} < 40 GeV", kBlack, 28);
  
  titlePad->cd();
  drawText(.1, .915, "#bf{CMS} #it{Preliminary}", kBlack, 28);
  drawText(0.66, 0.915, "PbPb #sqrt{s_{_{NN}}} = 5.02 TeV; (2018)", kBlack, 28);
  

  canvas->SaveAs(name);
  delete canvas;
}



void drawSystematics2(string systRap0_string, string systRap1_string)
{
  // input files
  TFile *filerap0 = new TFile(systRap0_string.c_str());
  TFile *filerap1 = new TFile(systRap1_string.c_str());

  // grab syst hists
  TH1F *h_JES_rap0 = (TH1F*)filerap0->Get("h_JES");
  TH1F *h_JER_rap0 = (TH1F*)filerap0->Get("h_JER");
  TH1F *h_JAR_rap0 = (TH1F*)filerap0->Get("h_JAR");
  TH1F *h_LSR_rap0 = (TH1F*)filerap0->Get("h_LSR");
  TH1F *h_Prior_rap0 = (TH1F*)filerap0->Get("h_prior");
  TH1F *h_trkGap_rap0 = (TH1F*)filerap0->Get("h_trkGap");
  TH1F *h_HF_rap0 = (TH1F*)filerap0->Get("h_HF");
  TH1F *h_ITER_rap0 = (TH1F*)filerap0->Get("h_ITER");
  TH1F *h_total_rap0 = (TH1F*)filerap0->Get("h_total");

  TH1F *h_JES_rap1 = (TH1F*)filerap1->Get("h_JES");
  TH1F *h_JER_rap1 = (TH1F*)filerap1->Get("h_JER");
  TH1F *h_JAR_rap1 = (TH1F*)filerap1->Get("h_JAR");
  TH1F *h_LSR_rap1 = (TH1F*)filerap1->Get("h_LSR");
  TH1F *h_Prior_rap1 = (TH1F*)filerap1->Get("h_prior");
  TH1F *h_trkGap_rap1 = (TH1F*)filerap1->Get("h_trkGap");
  TH1F *h_HF_rap1 = (TH1F*)filerap1->Get("h_HF");
  TH1F *h_ITER_rap1 = (TH1F*)filerap1->Get("h_ITER");
  TH1F *h_total_rap1 = (TH1F*)filerap1->Get("h_total");

  
  

  pad2(h_JES_rap0, h_JER_rap0, h_JAR_rap0, h_LSR_rap0, h_Prior_rap0, h_trkGap_rap0, h_HF_rap0, h_ITER_rap0, h_total_rap0, h_JES_rap1, h_JER_rap1, h_JAR_rap1, h_LSR_rap1, h_Prior_rap1, h_trkGap_rap1, h_HF_rap1, h_ITER_rap1, h_total_rap1, "                         y'", "Contribution to systematics (10^{-2})", "Pics/systematics_3panel.pdf", 0 ,7);
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
