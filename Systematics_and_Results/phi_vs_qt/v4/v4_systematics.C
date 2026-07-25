// v4_systematics.C
// This code:
// -calculates systematics and adds them in quadrature
// -makes systematics plots
// -makes result plots for v4=<cos(4phi)> vs qt

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

void makeNiceResidual_syst(TH1F *h1, TH1F *h2, const char *titleX, const char *titleY, string label1, string label2, const char *qtLabel, const char *name, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80){
  
  //TH1F *h_residual = new TH1F(*makeResidual_histogram(h1,h2));
  
  TH1D *h_residual = (TH1D*)h1->Clone("h_residual");
  h_residual->Add(h2, -1);
  
  h_residual->SetMarkerColor(kBlack);
  h_residual->SetMarkerStyle(kFullDotLarge);

  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",900,900);
  TPad *main = new TPad("main", "new pad", 0.01, 0.315, 0.99, 0.99);
  TPad *ratio = new TPad("ratio", "new pad 2", 0.01, 0.1, 0.99, 0.38);

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  canvas->cd();
  main->Draw();
  ratio->Draw();

  main->cd();
  main->SetLeftMargin(0.125);
  main->SetBottomMargin(0.11);
  main->SetTickx(1);
  main->SetTicky(1);
  h1->SetStats(0);
  h2->SetStats(0);
  float ymax=yMaximum;
  if (yMaximum==333) ymax = 2*h2->GetMaximum();
  h1->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.08);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(0.75);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(2);
  h1->SetMarkerStyle(kFullDotLarge);
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(2);
  h2->SetMarkerStyle(kFullDotLarge);
  h2->SetMarkerColor(kRed);
  h2->SetLineColor(kRed);
  h1->SetTitle("");
  h2->SetTitle("");
  h1->Draw("hist pE");
  h2->Draw("same pE");
  drawText(.13, .915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.55, 0.915, "PbPb: #sqrt{s}=5.02 TeV (2018)", kBlack, 28);
  drawLegendStr(h1, h2, 0.15, 0.3, 0.75, 0.875, label1, label2);
  drawText(0.175, 0.7, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h2)), kBlack, 32);
  drawText(0.175, 0.65, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h2)), kBlack, 32);
  drawText(0.55, 0.8, qtLabel, kBlack, 32);

  ratio->cd();
  ratio->SetTopMargin(0.035);
  ratio->SetLeftMargin(0.125);
  ratio->SetBottomMargin(0.275);
  ratio->SetTickx(1);
  ratio->SetTicky(1);
  h_residual->SetStats(0);
  h_residual->SetLineColor(kBlack);
  h_residual->SetTitle("");
  h_residual->GetXaxis()->SetLabelSize(0.10);
  h_residual->GetXaxis()->SetTitleSize(0.15);  
  h_residual->GetXaxis()->SetTitleOffset(0.75);
  h_residual->GetYaxis()->SetLabelSize(0.09);
  h_residual->GetYaxis()->SetTitleSize(0.04);
  string ratio_label="residual";
  float ymax_r = h_residual->GetMaximum();
  float ymin_r = h_residual->GetMinimum();
  float yFactor=1;
  if (fabs(ymax_r)>fabs(ymin_r)) yFactor=3*ymax_r;
  if (fabs(ymax_r)<fabs(ymin_r)) yFactor=3*fabs(ymin_r);
  h_residual->GetYaxis()->SetRangeUser(0-yFactor, yFactor);
  h_residual->GetXaxis()->SetTitle(titleX);
  h_residual->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual->GetYaxis()->SetTitleOffset(0.35);
  h_residual->GetYaxis()->SetTitleSize(0.17);
  h_residual->SetMarkerSize(2);
  h_residual->SetLineWidth(2);
  ratio->SetBottomMargin(0.275);
  h_residual->Draw("same hist p");

  float xmax = h_residual->GetXaxis()->GetXmax();
  float xmin = h_residual->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,0,xmax,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h_residual->Draw("same hist pE");

  canvas->SaveAs(name);
  delete canvas;
}


void makeNiceResidual_systematics(TH1F *h1, TH1F *h2, const char *titleX, const char *titleY, string label1, string label2, const char *name, float totalSys, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80){
  
  TH1F *h_residual = new TH1F(*makeResidual_histogram(h1,h2));
  h_residual->SetMarkerColor(kBlack);
  h_residual->SetMarkerStyle(kFullDotLarge);

  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",900,900);
  TPad *main = new TPad("main", "new pad", 0.01, 0.315, 0.99, 0.99);
  TPad *ratio = new TPad("ratio", "new pad 2", 0.01, 0.1, 0.99, 0.38);

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  canvas->cd();
  main->Draw();
  ratio->Draw();

  main->cd();
  main->SetLeftMargin(0.125);
  main->SetBottomMargin(0.11);
  main->SetTickx(1);
  main->SetTicky(1);
  h1->SetStats(0);
  h2->SetStats(0);
  float ymax=yMaximum;
  if (yMaximum==333) ymax = 2*h2->GetMaximum();
  h1->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.08);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(0.75);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(2);
  h1->SetMarkerStyle(kFullDotLarge);
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(2);
  h2->SetMarkerStyle(kFullDotLarge);
  h2->SetMarkerColor(kRed);
  h2->SetLineColor(kRed);
  h1->SetTitle("");
  h2->SetTitle("");
  h1->Draw("hist pE");
  h2->Draw("same pE");
  // systematics
  double syst_error = totalSys;
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-syst_error;
        double yHigh = binContent+syst_error;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
 
  drawText(.13, .915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.55, 0.915, "PbPb: #sqrt{s}=5.02 TeV (2018)", kBlack, 28);
  drawLegendStr(h1, h2, 0.15, 0.4, 0.7, 0.875, label1, label2);
  //drawText(0.6, 0.81, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h2)), kBlack, 34);
  //drawText(0.6, 0.73, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h2)), kBlack, 34);

  ratio->cd();
  ratio->SetTopMargin(0.035);
  ratio->SetLeftMargin(0.125);
  ratio->SetBottomMargin(0.275);
  ratio->SetTickx(1);
  ratio->SetTicky(1);
  h_residual->SetStats(0);
  h_residual->SetLineColor(kBlack);
  h_residual->SetTitle("");
  h_residual->GetXaxis()->SetLabelSize(0.18);
  h_residual->GetXaxis()->SetTitleSize(0.15);  
  h_residual->GetXaxis()->SetTitleOffset(0.8);
  h_residual->GetYaxis()->SetLabelSize(0.09);
  h_residual->GetYaxis()->SetTitleSize(0.17);
  string ratio_label="residual";
  float ymax_r = h_residual->GetMaximum();
  float ymin_r = h_residual->GetMinimum();
  float yFactor=1;
  if (fabs(ymax_r)>fabs(ymin_r)) yFactor=3*ymax_r;
  if (fabs(ymax_r)<fabs(ymin_r)) yFactor=3*fabs(ymin_r);
  h_residual->GetYaxis()->SetRangeUser(0-yFactor, yFactor);
  h_residual->GetXaxis()->SetTitle(titleX);
  h_residual->GetXaxis()->SetLabelSize(0.10);
  h_residual->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual->GetYaxis()->SetTitleSize(0.17);
  h_residual->GetYaxis()->SetTitleOffset(0.35);
  h_residual->SetMarkerSize(2);
  h_residual->SetLineWidth(2);
  ratio->SetBottomMargin(0.275);
  h_residual->Draw("same hist p");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-syst_error;
        double yHigh = resContent+syst_error;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
 

  float xmax = h_residual->GetXaxis()->GetXmax();
  float xmin = h_residual->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,0,xmax,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h_residual->Draw("same hist pE");

  canvas->SaveAs(name);
  delete canvas;
}



void v4_systematics()
{
  // Read Files
  TFile *fileGen_R2 = new TFile("Files/gen_r2_v2.root");
  TFile *fileGen_R4 = new TFile("Files/gen_r4_v2.root");
  TFile *fileGen_R6 = new TFile("Files/gen_r6_v2.root");
  TFile *fileUnf_R2 = new TFile("Files/unf_r2_v2.root");
  TFile *fileUnf_R4 = new TFile("Files/unf_r4_v2.root");
  TFile *fileUnf_R4_0n0n = new TFile("Files/unf_r4_0n0n_v2.root");
  TFile *fileUnf_R6 = new TFile("Files/unf_r6_v2.root");
  TFile *fileUnf_R2_ac = new TFile("Files/unf_r2_v2_ac.root");
  TFile *fileUnf_R4_ac = new TFile("Files/unf_r4_v2_ac.root");
  TFile *fileUnf_R4_0n0n_ac = new TFile("Files/unf_r4_0n0n_v2_ac.root");
  TFile *fileUnf_R6_ac = new TFile("Files/unf_r6_v2_ac.root");
  TFile *fileJESup = new TFile("Files/JES_up_r4_v2.root");
  TFile *fileJESnom = new TFile("Files/JES_nom_r4_v2.root");
  TFile *fileJESdown = new TFile("Files/JES_down_r4_v2.root");
  TFile *fileJERup = new TFile("Files/JER_up_r4_v2.root");
  TFile *fileJERnom = new TFile("Files/JER_nom_r4_v2.root");
  TFile *fileJERdown = new TFile("Files/JER_down_r4_v2.root");
  TFile *fileJAR_R2 = new TFile("Files/JAR_r2_v2.root");
  TFile *fileJAR_R4 = new TFile("Files/JAR_r4_v2.root");
  TFile *fileJAR_R6 = new TFile("Files/JAR_r6_v2.root");
  TFile *filePrior_R2 = new TFile("Files/prior_r2_v2.root");
  TFile *filePrior_R4 = new TFile("Files/prior_r4_v2.root");
  TFile *filePrior_0n0n = new TFile("Files/prior_0n0n_v2.root");
  TFile *filePrior_R6 = new TFile("Files/prior_r6_v2.root");
  TFile *filemcStat1_R2 = new TFile("Files/mcStat1_r2_v2.root");
  TFile *filemcStat2_R2 = new TFile("Files/mcStat2_r2_v2.root");
  TFile *filemcStat1_R4 = new TFile("Files/mcStat1_r4_v2.root");
  TFile *filemcStat2_R4 = new TFile("Files/mcStat2_r4_v2.root");
  TFile *filemcStat1_0n0n = new TFile("Files/mcStat1_0n0n_v2.root");
  TFile *filemcStat2_0n0n = new TFile("Files/mcStat2_0n0n_v2.root");
  TFile *filemcStat1_R6 = new TFile("Files/mcStat1_r6_v2.root");
  TFile *filemcStat2_R6 = new TFile("Files/mcStat2_r6_v2.root");
  TFile *fileRapup = new TFile("Files/unf_r4_v2_rapgapUp.root");
  TFile *fileRapdown = new TFile("Files/unf_r4_v2_rapgapDown.root");
  TFile *fileHF = new TFile("Files/unf_r4_v2_hf.root");
  TFile *fileRapup_R2 = new TFile("Files/unf_r2_v2_rapgapUp.root");
  TFile *fileRapdown_R2 = new TFile("Files/unf_r2_v2_rapgapDown.root");
  TFile *fileHF_R2 = new TFile("Files/unf_r2_v2_hf.root");
  TFile *fileRapup_R6 = new TFile("Files/unf_r6_v2_rapgapUp.root");
  TFile *fileRapdown_R6 = new TFile("Files/unf_r6_v2_rapgapDown.root");
  TFile *fileHF_R6 = new TFile("Files/unf_r6_v2_hf.root");
  TFile *file2it_R4 = new TFile("Files/unf_r4_v2_2iterations.root");
  TFile *file3it_R4 = new TFile("Files/unf_r4_v2_3iterations.root");
  TFile *file2it_R2 = new TFile("Files/unf_r2_v2_2iterations.root");
  TFile *file3it_R2 = new TFile("Files/unf_r2_v2_3iterations.root");
  TFile *file2it_R6 = new TFile("Files/unf_r6_v2_2iterations.root");
  TFile *file3it_R6 = new TFile("Files/unf_r6_v2_3iterations.root");
 
  // v4
  TH1F *v4_gen_R2 = (TH1F*)fileGen_R2->Get("h_v4");
  TH1F *v4_gen_R4 = (TH1F*)fileGen_R4->Get("h_v4");
  TH1F *v4_gen_R6 = (TH1F*)fileGen_R6->Get("h_v4");
  TH1F *v4_unf_R2 = (TH1F*)fileUnf_R2->Get("h_v4");
  TH1F *v4_unf_R4 = (TH1F*)fileUnf_R4->Get("h_v4");
  TH1F *v4_unf_R4_0n0n = (TH1F*)fileUnf_R4_0n0n->Get("h_v4");
  TH1F *v4_unf_R6 = (TH1F*)fileUnf_R6->Get("h_v4");
  TH1F *v4_unf_R2_ac = (TH1F*)fileUnf_R2_ac->Get("h_v4");
  TH1F *v4_unf_R4_ac = (TH1F*)fileUnf_R4_ac->Get("h_v4");
  TH1F *v4_unf_R4_0n0n_ac = (TH1F*)fileUnf_R4_0n0n_ac->Get("h_v4");
  TH1F *v4_unf_R6_ac = (TH1F*)fileUnf_R6_ac->Get("h_v4");
  TH1F *v4_jesUp_R4 = (TH1F*)fileJESup->Get("h_v4");
  TH1F *v4_jesNom_R4 = (TH1F*)fileJESnom->Get("h_v4");
  TH1F *v4_jesDown_R4 = (TH1F*)fileJESdown->Get("h_v4");
  TH1F *v4_jerUp_R4 = (TH1F*)fileJERup->Get("h_v4");
  TH1F *v4_jerNom_R4 = (TH1F*)fileJERnom->Get("h_v4");
  TH1F *v4_jerDown_R4 = (TH1F*)fileJERdown->Get("h_v4");
  TH1F *v4_jar_R2 = (TH1F*)fileJAR_R2->Get("h_v4");
  TH1F *v4_jar_R4 = (TH1F*)fileJAR_R4->Get("h_v4");
  TH1F *v4_jar_R6 = (TH1F*)fileJAR_R6->Get("h_v4");
  TH1F *v4_prior_R2 = (TH1F*)filePrior_R2->Get("h_v4");
  TH1F *v4_prior_R4 = (TH1F*)filePrior_R4->Get("h_v4");
  TH1F *v4_prior_0n0n = (TH1F*)filePrior_0n0n->Get("h_v4");
  TH1F *v4_prior_R6 = (TH1F*)filePrior_R6->Get("h_v4");
  TH1F *v4_mcStat1_R2 = (TH1F*)filemcStat1_R2->Get("h_v4");
  TH1F *v4_mcStat2_R2 = (TH1F*)filemcStat2_R2->Get("h_v4");
  TH1F *v4_mcStat1_R4 = (TH1F*)filemcStat1_R4->Get("h_v4");
  TH1F *v4_mcStat2_R4 = (TH1F*)filemcStat2_R4->Get("h_v4");
  TH1F *v4_mcStat1_0n0n = (TH1F*)filemcStat1_0n0n->Get("h_v4");
  TH1F *v4_mcStat2_0n0n = (TH1F*)filemcStat2_0n0n->Get("h_v4");
  TH1F *v4_mcStat1_R6 = (TH1F*)filemcStat1_R6->Get("h_v4");
  TH1F *v4_mcStat2_R6 = (TH1F*)filemcStat2_R6->Get("h_v4");
  TH1F *v4_rapup = (TH1F*)fileRapup->Get("h_v4");
  TH1F *v4_rapdown = (TH1F*)fileRapdown->Get("h_v4");
  TH1F *v4_hf = (TH1F*)fileHF->Get("h_v4");
  TH1F *v4_rapup_R2 = (TH1F*)fileRapup_R2->Get("h_v4");
  TH1F *v4_rapdown_R2 = (TH1F*)fileRapdown_R2->Get("h_v4");
  TH1F *v4_hf_R2 = (TH1F*)fileHF_R2->Get("h_v4");
  TH1F *v4_rapup_R6 = (TH1F*)fileRapup_R6->Get("h_v4");
  TH1F *v4_rapdown_R6 = (TH1F*)fileRapdown_R6->Get("h_v4");
  TH1F *v4_hf_R6 = (TH1F*)fileHF_R6->Get("h_v4");
  TH1F *v4_2it_R4 = (TH1F*)file2it_R4->Get("h_v4");
  TH1F *v4_3it_R4 = (TH1F*)file3it_R4->Get("h_v4");
  TH1F *v4_2it_R2 = (TH1F*)file2it_R2->Get("h_v4");
  TH1F *v4_3it_R2 = (TH1F*)file3it_R2->Get("h_v4");
  TH1F *v4_2it_R6 = (TH1F*)file2it_R6->Get("h_v4");
  TH1F *v4_3it_R6 = (TH1F*)file3it_R6->Get("h_v4");
 

  // set sumW2
  v4_jesNom_R4->Sumw2();
  v4_jesUp_R4->Sumw2();
  v4_jesDown_R4->Sumw2();


  // make v4 systematic plots
  // JES up R4
  makeNiceResidual_syst(v4_jesNom_R4, v4_jesUp_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JES Up Result","", "Pics/v4_jesUp.png",0,0.6);
  // JES nom R4
  makeNiceResidual_syst(v4_unf_R4, v4_jesNom_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JES Nom Result","", "Pics/v4_jesNom.png",0,0.6);
  // JES down R4
  makeNiceResidual_syst(v4_jesNom_R4, v4_jesDown_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JES Down Result","", "Pics/v4_jesDown.png",0,0.6);
   // JER up
  makeNiceResidual_syst(v4_jerNom_R4, v4_jerUp_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JER Up Result","", "Pics/v4_jerUp.png",0,0.6);
  // JER down
  makeNiceResidual_syst(v4_jerNom_R4, v4_jerDown_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JER Down Result","", "Pics/v4_jerDown.png",0,0.6);
  // JAR R4
  makeNiceResidual_syst(v4_unf_R4, v4_jar_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JAR Result","", "Pics/v4_jar_r4.png",0,0.6);
  // Prior R4
  makeNiceResidual_syst(v4_unf_R4, v4_prior_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Prior Result","", "Pics/v4_prior_r4.png",0,0.6);
  // mcStats R4
  makeNiceResidual_syst(v4_mcStat1_R4, v4_mcStat2_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Data unfolded with MC half 1", "Data unfolded with MC half 2","", "Pics/v4_mcStats_r4.png",0,0.7);
  // RAP UP
  makeNiceResidual_syst(v4_unf_R4, v4_rapup, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Rap Up Result","", "Pics/v4_rapUp.png",-0.1,0.6);
  // RAP DOWN
  makeNiceResidual_syst(v4_unf_R4, v4_rapdown, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Rap Down Result","", "Pics/v4_rapDown.png",-0.1,0.6);
  // HF
  makeNiceResidual_syst(v4_unf_R4, v4_hf, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "HF Result","", "Pics/v4_hf.png",-0.1,0.6);
  // iterations
  makeNiceResidual_syst(v4_2it_R4, v4_3it_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "2 iterations", "3 iterations","", "Pics/v4_it.png",-0.1,0.6);



  // text files to store systematics for each bin
  ofstream outfile_prior_r2("textFiles/v4_prior_diff_r2.txt"), outfile_mcStats_r2("textFiles/v4_mcStats_diff_r2.txt"), outfile_jar_r2("textFiles/v4_jar_diff_r2.txt"), outfile_jer_r2("textFiles/v4_jer_diff_r2.txt"), outfile_trk_r2("textFiles/v4_trk_diff_r2.txt"), outfile_hf_r2("textFiles/v4_hf_diff_r2.txt"), outfile_it_r2("textFiles/v4_it_diff_r2.txt");
  ofstream outfile_prior_r6("textFiles/v4_prior_diff_r6.txt"), outfile_mcStats_r6("textFiles/v4_mcStats_diff_r6.txt"), outfile_jar_r6("textFiles/v4_jar_diff_r6.txt"), outfile_jer_r6("textFiles/v4_jer_diff_r6.txt"), outfile_trk_r6("textFiles/v4_trk_diff_r6.txt"), outfile_hf_r6("textFiles/v4_hf_diff_r6.txt"), outfile_it_r6("textFiles/v4_it_diff_r6.txt");
  ofstream outfile_jes("textFiles/v4_jes_diff.txt"), outfile_prior("textFiles/v4_prior_diff.txt"), outfile_mcStats("textFiles/v4_mcStats_diff.txt"), outfile_jar("textFiles/v4_jar_diff.txt"), outfile_jer("textFiles/v4_jer_diff.txt"), outfile_trk("textFiles/v4_trk_diff.txt"), outfile_hf("textFiles/v4_hf_diff.txt"), outfile_it("textFiles/v4_it_diff.txt");

  
  

  // loop through histogram bins
  float unf_content=0, nomJES_content=0, nomJER_content=0, jesUp_content=0, jesDown_content=0, jerUp_content=0, jerDown_content=0, jar_content=0, jer_content=0, trkUp_content=0, trkDown_content=0, hf_content=0, twoIt_content=0, threeIt_content=0;
  float unf_content_R2=0, jar_content_R2=0, trkUp_content_R2=0, trkDown_content_R2=0, hf_content_R2=0, twoIt_content_R2=0, threeIt_content_R2=0, unf_content_R6=0, jar_content_R6=0, trkUp_content_R6=0, trkDown_content_R6=0, hf_content_R6=0, twoIt_content_R6=0, threeIt_content_R6=0;
  float prior_content_R4=0, prior_content_R2=0, prior_content_R6=0;
  float mcStats1_content_R4=0, mcStats2_content_R4=0, mcStats1_content_R2=0, mcStats2_content_R2=0, mcStats1_content_R6=0, mcStats2_content_R6=0; 
  float jesUp_Diff=0, jesDown_Diff=0, jerUp_Diff=0, jerDown_Diff=0, jar_Diff=0, jer_Diff=0, trkUp_Diff=0, trkDown_Diff=0, hf_Diff=0, itDiff=0;
  float jar_Diff_R2=0, trkUp_Diff_R2=0, trkDown_Diff_R2=0, hf_Diff_R2=0, itDiff_R2=0, jar_Diff_R6=0, trkUp_Diff_R6=0, trkDown_Diff_R6=0, hf_Diff_R6=0, itDiff_R6=0;
  float prior_Diff_R4=0, prior_Diff_R2=0, prior_Diff_R6=0;
  float mcStats_Diff_R4=0, mcStats_Diff_R2=0, mcStats_Diff_R6=0; 
  float total_sys=0, jesUp_avgMag=0, jesDown_avgMag=0, jerUp_avgMag=0, jerDown_avgMag=0, jar_avgMag=0, jer_avgMag=0, it_avgMag=0;
  float total_sys_R2=0, jar_avgMag_R2=0, it_avgMag_R2=0, total_sys_R6=0, jar_avgMag_R6=0, it_avgMag_R6=0;
  float trkUp_avgMag=0, trkDown_avgMag=0, hf_avgMag=0;
  float prior_avgMag_R4=0;
  float mcStats_avgMag_R4=0;
  float trkUp_avgMag_R2=0, trkDown_avgMag_R2=0, hf_avgMag_R2=0, prior_avgMag_R2=0, mcStats_avgMag_R2=0, trkUp_avgMag_R6=0, trkDown_avgMag_R6=0, hf_avgMag_R6=0, prior_avgMag_R6=0, mcStats_avgMag_R6=0;
  int binNumber = v4_unf_R4->GetNbinsX();

  // printing multiplier
  float multiplier=100;

  // loop through bin differences
  for (int iBin=1; iBin<binNumber+1; iBin++)
    {
      // get contents
      unf_content=v4_unf_R4->GetBinContent(iBin), unf_content_R2=v4_unf_R2->GetBinContent(iBin), unf_content_R6=v4_unf_R6->GetBinContent(iBin);
      nomJES_content=v4_jesNom_R4->GetBinContent(iBin), nomJER_content=v4_jerNom_R4->GetBinContent(iBin);
      jesUp_content=v4_jesUp_R4->GetBinContent(iBin), jesDown_content=v4_jesDown_R4->GetBinContent(iBin);
      jerUp_content=v4_jerUp_R4->GetBinContent(iBin),jerDown_content=v4_jerDown_R4->GetBinContent(iBin);
      jar_content=v4_jar_R4->GetBinContent(iBin), jar_content_R2=v4_jar_R2->GetBinContent(iBin), jar_content_R6=v4_jar_R6->GetBinContent(iBin);
      prior_content_R4=v4_prior_R4->GetBinContent(iBin), prior_content_R2=v4_prior_R2->GetBinContent(iBin), prior_content_R6=v4_prior_R6->GetBinContent(iBin);
      mcStats1_content_R4=v4_mcStat1_R4->GetBinContent(iBin), mcStats2_content_R4=v4_mcStat2_R4->GetBinContent(iBin), mcStats1_content_R2=v4_mcStat1_R2->GetBinContent(iBin), mcStats2_content_R2=v4_mcStat2_R2->GetBinContent(iBin), mcStats1_content_R6=v4_mcStat1_R6->GetBinContent(iBin), mcStats2_content_R6=v4_mcStat2_R6->GetBinContent(iBin);
      trkUp_content=v4_rapup->GetBinContent(iBin), trkDown_content=v4_rapdown->GetBinContent(iBin), trkUp_content_R2=v4_rapup_R2->GetBinContent(iBin), trkDown_content_R2=v4_rapdown_R2->GetBinContent(iBin), trkUp_content_R6=v4_rapup_R6->GetBinContent(iBin), trkDown_content_R6=v4_rapdown_R6->GetBinContent(iBin);
      hf_content=v4_hf->GetBinContent(iBin), hf_content_R2=v4_hf_R2->GetBinContent(iBin), hf_content_R6=v4_hf_R6->GetBinContent(iBin);
      twoIt_content=v4_2it_R4->GetBinContent(iBin), threeIt_content=v4_3it_R4->GetBinContent(iBin), twoIt_content_R2=v4_2it_R2->GetBinContent(iBin), threeIt_content_R2=v4_3it_R2->GetBinContent(iBin), twoIt_content_R6=v4_2it_R6->GetBinContent(iBin), threeIt_content_R6=v4_3it_R6->GetBinContent(iBin);
      
         
      // get differences
      jesUp_Diff=nomJES_content-jesUp_content, jesDown_Diff=nomJES_content-jesDown_content;
      jerUp_Diff=nomJER_content-jerUp_content, jerDown_Diff=nomJER_content-jerDown_content;
      jar_Diff=unf_content-jar_content, jar_Diff_R2=unf_content_R2-jar_content_R2, jar_Diff_R6=unf_content_R6-jar_content_R6;
      prior_Diff_R4=unf_content-prior_content_R4, prior_Diff_R2=unf_content_R2-prior_content_R2, prior_Diff_R6=unf_content_R6-prior_content_R6;
      mcStats_Diff_R4=mcStats1_content_R4-mcStats2_content_R4, mcStats_Diff_R2=mcStats1_content_R2-mcStats2_content_R2, mcStats_Diff_R6=mcStats1_content_R6-mcStats2_content_R6;
      trkUp_Diff=unf_content-trkUp_content, trkDown_Diff=unf_content-trkDown_content, trkUp_Diff_R2=unf_content_R2-trkUp_content_R2, trkDown_Diff_R2=unf_content_R2-trkDown_content_R2, trkUp_Diff_R6=unf_content_R6-trkUp_content_R6, trkDown_Diff_R6=unf_content_R6-trkDown_content_R6;
      hf_Diff=unf_content-hf_content, hf_Diff_R2=unf_content_R2-hf_content_R2, hf_Diff_R6=unf_content_R6-hf_content_R6;
      itDiff=twoIt_content-threeIt_content, itDiff_R2=twoIt_content_R2-threeIt_content_R2, itDiff_R6=twoIt_content_R6-threeIt_content_R6;


      // output to file
      outfile_mcStats << fixed << setprecision(1) << mcStats_Diff_R4*multiplier << endl, outfile_mcStats_r2 << fixed << setprecision(1) << mcStats_Diff_R2*multiplier << endl, outfile_mcStats_r6 << fixed << setprecision(1) << mcStats_Diff_R6*multiplier << endl;
      outfile_prior << fixed << setprecision(1) << prior_Diff_R4*multiplier << endl, outfile_prior_r2 << fixed << setprecision(1) << prior_Diff_R2*multiplier << endl, outfile_prior_r6 << fixed << setprecision(1) << prior_Diff_R6*multiplier << endl;
      outfile_jar << fixed << setprecision(1) << jar_Diff*multiplier << endl, outfile_jar_r2 << fixed << setprecision(1) << jar_Diff_R2*multiplier << endl, outfile_jar_r6 << fixed << setprecision(1) << jar_Diff_R6*multiplier << endl;
      outfile_jes << fixed << setprecision(1) << multiplier*(fabs(jesUp_Diff)+fabs(jesDown_Diff))/2 << endl;
      outfile_jer << fixed << setprecision(1) << multiplier*(fabs(jerUp_Diff)+fabs(jerDown_Diff))/2 << endl;
      outfile_trk << fixed << setprecision(1) << multiplier*(fabs(trkUp_Diff)+fabs(trkDown_Diff))/2 << endl;
      outfile_hf << fixed << setprecision(1) << hf_Diff*multiplier << endl;
      outfile_trk_r2 << fixed << setprecision(1) << multiplier*(fabs(trkUp_Diff_R2)+fabs(trkDown_Diff_R2))/2 << endl;
      outfile_hf_r2 << fixed << setprecision(1) << multiplier*hf_Diff_R2 << endl;
      outfile_trk_r6 << fixed << setprecision(1) << multiplier*(fabs(trkUp_Diff_R6)+fabs(trkDown_Diff_R6))/2 << endl;
      outfile_hf_r6 << fixed << setprecision(1) << multiplier*hf_Diff_R6 << endl;
      outfile_it << fixed << setprecision(1) << itDiff*multiplier << endl;
      outfile_it_r2 << fixed << setprecision(1) << itDiff_R2*multiplier << endl;
      outfile_it_r6 << fixed << setprecision(1) << itDiff_R6*multiplier << endl;
      
     
      // sum bin Differences
      jesUp_avgMag=jesUp_avgMag+fabs(jesUp_Diff), jesDown_avgMag=jesDown_avgMag+fabs(jesDown_Diff);
      jerUp_avgMag=jerUp_avgMag+fabs(jerUp_Diff), jerDown_avgMag=jerDown_avgMag+fabs(jerDown_Diff);
      jar_avgMag=jar_avgMag+fabs(jar_Diff), jar_avgMag_R2=jar_avgMag_R2+fabs(jar_Diff_R2), jar_avgMag_R6=jar_avgMag_R6+fabs(jar_Diff_R6);
      prior_avgMag_R4=prior_avgMag_R4+fabs(prior_Diff_R4), prior_avgMag_R2=prior_avgMag_R2+fabs(prior_Diff_R2), prior_avgMag_R6=prior_avgMag_R6+fabs(prior_Diff_R6);
      mcStats_avgMag_R4=mcStats_avgMag_R4+fabs(mcStats_Diff_R4), mcStats_avgMag_R2=mcStats_avgMag_R2+fabs(mcStats_Diff_R2), mcStats_avgMag_R6=mcStats_avgMag_R6+fabs(mcStats_Diff_R6);
      trkUp_avgMag=trkUp_avgMag+fabs(trkUp_Diff), trkDown_avgMag=trkDown_avgMag+fabs(trkDown_Diff), trkUp_avgMag_R2=trkUp_avgMag_R2+fabs(trkUp_Diff_R2), trkDown_avgMag_R2=trkDown_avgMag_R2+fabs(trkDown_Diff_R2), trkUp_avgMag_R6=trkUp_avgMag_R6+fabs(trkUp_Diff_R6), trkDown_avgMag_R6=trkDown_avgMag_R6+fabs(trkDown_Diff_R6);
      hf_avgMag=hf_avgMag+fabs(hf_Diff), hf_avgMag_R2=hf_avgMag_R2+fabs(hf_Diff_R2), hf_avgMag_R6=hf_avgMag_R6+fabs(hf_Diff_R6);
      it_avgMag=it_avgMag+fabs(itDiff), it_avgMag_R2=it_avgMag_R2+fabs(itDiff_R2), it_avgMag_R6=it_avgMag_R6+fabs(itDiff_R6);

    
      
    } // end bin loop
  

  // calculate avg bin systematics
  jesUp_avgMag=jesUp_avgMag/binNumber, jesDown_avgMag=jesDown_avgMag/binNumber;
  jerUp_avgMag=jerUp_avgMag/binNumber, jerDown_avgMag=jerDown_avgMag/binNumber;
  jar_avgMag=jar_avgMag/binNumber, jar_avgMag_R2=jar_avgMag_R2/binNumber, jar_avgMag_R6=jar_avgMag_R6/binNumber;
  prior_avgMag_R4=prior_avgMag_R4/binNumber, prior_avgMag_R2=prior_avgMag_R2/binNumber, prior_avgMag_R6=prior_avgMag_R6/binNumber;
  mcStats_avgMag_R4=mcStats_avgMag_R4/binNumber, mcStats_avgMag_R2=mcStats_avgMag_R2/binNumber, mcStats_avgMag_R6=mcStats_avgMag_R6/binNumber; 
  trkUp_avgMag=trkUp_avgMag/binNumber, trkDown_avgMag=trkDown_avgMag/binNumber, trkUp_avgMag_R2=trkUp_avgMag_R2/binNumber, trkDown_avgMag_R2=trkDown_avgMag_R2/binNumber, trkUp_avgMag_R6=trkUp_avgMag_R6/binNumber, trkDown_avgMag_R6=trkDown_avgMag_R6/binNumber;
  hf_avgMag=hf_avgMag/binNumber, hf_avgMag_R2=hf_avgMag_R2/binNumber, hf_avgMag_R6=hf_avgMag_R6/binNumber;
  it_avgMag=it_avgMag/binNumber, it_avgMag_R2=it_avgMag_R2/binNumber, it_avgMag_R6=it_avgMag_R6/binNumber;
  float trk_total_avgMag=(trkUp_avgMag+trkDown_avgMag)/2, trk_total_avgMag_R2=(trkUp_avgMag_R2+trkDown_avgMag_R2)/2, trk_total_avgMag_R6=(trkUp_avgMag_R6+trkDown_avgMag_R6)/2;
  float rap_total=sqrt(hf_avgMag*hf_avgMag+trk_total_avgMag*trk_total_avgMag), rap_total_R2=sqrt(hf_avgMag_R2*hf_avgMag_R2+trk_total_avgMag_R2*trk_total_avgMag_R2), rap_total_R6=sqrt(hf_avgMag_R6*hf_avgMag_R6+trk_total_avgMag_R6*trk_total_avgMag_R6);
  float jes_total_avgMag=(jesUp_avgMag+jesDown_avgMag)/2, jer_total_avgMag=(jerUp_avgMag+jerDown_avgMag)/2;
  total_sys=sqrt((it_avgMag*it_avgMag+jar_avgMag*jar_avgMag+jes_total_avgMag*jes_total_avgMag+jer_total_avgMag*jer_total_avgMag+mcStats_avgMag_R4*mcStats_avgMag_R4/2+prior_avgMag_R4*prior_avgMag_R4+rap_total*rap_total));
  total_sys_R2=sqrt((it_avgMag_R2*it_avgMag_R2+jar_avgMag_R2*jar_avgMag_R2+jes_total_avgMag*jes_total_avgMag+jer_total_avgMag*jer_total_avgMag+mcStats_avgMag_R2*mcStats_avgMag_R2/2+prior_avgMag_R2*prior_avgMag_R2+rap_total_R2*rap_total_R2));
  total_sys_R6=sqrt((it_avgMag_R6*it_avgMag_R6+jar_avgMag_R6*jar_avgMag_R6+jes_total_avgMag*jes_total_avgMag+jer_total_avgMag*jer_total_avgMag+mcStats_avgMag_R6*mcStats_avgMag_R6/2+prior_avgMag_R6*prior_avgMag_R6+rap_total_R6*rap_total_R6));
 
  

  cout << "prior_avgMag_R4=" << prior_avgMag_R4 << endl;
  cout << "mcStats_avgMag_R4=" << mcStats_avgMag_R4 << endl;
  cout << "it avgMag = " << it_avgMag << endl;
  cout << "jar_avgMag=" << jar_avgMag << " and totalR4=" << total_sys << endl;


  // make final r2,r4,r6 results plot with systematics
  makeNiceResidual_systematics(v4_unf_R4_ac, v4_gen_R4, "Q_{T} [GeV]", "<cos(4#phi)>", "Unfolded Result, r=0.4", "Gen Pythia, r=0.4", "Pics/v4_unf_r4_gen_syst.png",total_sys,-0.2,0.25);
  makeNiceResidual_systematics(v4_unf_R2_ac, v4_gen_R2, "Q_{T} [GeV]", "<cos(4#phi)>", "Unfolded Result, r=0.4", "Gen Pythia, r=0.2", "Pics/v4_unf_r2_gen_syst.png",total_sys,-0.2,0.25);
  makeNiceResidual_systematics(v4_unf_R6_ac, v4_gen_R6, "Q_{T} [GeV]", "<cos(4#phi)>", "Unfolded Result, r=0.4", "Gen Pythia, r=0.6", "Pics/v4_unf_r6_gen_syst.png",total_sys,-0.2,0.25);

  // make v4 3-panel
 pad3_2(v4_unf_R2_ac, v4_unf_R4_ac, v4_unf_R6_ac, v4_gen_R2, v4_gen_R4, v4_gen_R6, "Q_{T} [GeV]                  ", "<cos(4#phi)>", "Data", "Pythia8", "Pics/v4_unf_threePanel_sys.pdf", total_sys_R2, total_sys, total_sys_R6,-0.3,0.5);


 // make v4 3-panel theory
 TFile *fileTheory = new TFile("theoryComparison/theoryGraphs.root");
  TGraph *gr_r2 = (TGraph*)fileTheory->Get("gr_r2");
  TGraph *gr_r4 = (TGraph*)fileTheory->Get("gr_r4");
  TGraph *gr_r6 = (TGraph*)fileTheory->Get("gr_r6");
  TGraph *gr_r2_v4 = (TGraph*)fileTheory->Get("gr_r2_v4");
  TGraph *gr_r4_v4 = (TGraph*)fileTheory->Get("gr_r4_v4");
  TGraph *gr_r6_v4 = (TGraph*)fileTheory->Get("gr_r6_v4");
  gr_r2_v4->SetLineColor(kBlue);
  gr_r4_v4->SetLineColor(kBlue);
  gr_r6_v4->SetLineColor(kBlue);
  gr_r2_v4->SetLineWidth(2);
  gr_r4_v4->SetLineWidth(2);
  gr_r6_v4->SetLineWidth(2);
  pad3_2_theory(gr_r2_v4, gr_r4_v4, gr_r6_v4, "Hatta et al.", v4_unf_R2_ac, v4_unf_R4_ac, v4_unf_R6_ac, v4_gen_R2, v4_gen_R4, v4_gen_R6, "Q_{T} [GeV]                  ", "#LTcos(4#phi)#GT", "Data, 0nXn", "Pythia8", "Pics/v4_2021_theory.pdf", total_sys_R2, total_sys, total_sys_R6,-0.3,0.5);
  pad3_2_theoryZoomed(gr_r2_v4, gr_r4_v4, gr_r6_v4, "theory 2021", v4_unf_R2_ac, v4_unf_R4_ac, v4_unf_R6_ac, v4_gen_R2, v4_gen_R4, v4_gen_R6, "Q_{T} [GeV]                  ", "<cos(4#phi)>", "Data", "Pythia8", "Pics/v4_2021_theoryZoomed.png", total_sys_R2, total_sys, total_sys_R6,-0.3,0.4);
  // theories
  



  // new systematics plot
  TH1F *h_JES = new TH1F("h_JES","h_JES",3,0,3);
  TH1F *h_JER = new TH1F("h_JER","h_JER",3,0,3);
  TH1F *h_JAR = new TH1F("h_JAR","h_JAR",3,0,3);
  TH1F *h_LSR = new TH1F("h_LSR","h_LSR",3,0,3);
  TH1F *h_Prior = new TH1F("h_Prior","h_Prior",3,0,3);
  TH1F *h_trkGap = new TH1F("h_trkGap","h_trkGap",3,0,3);
  TH1F *h_HF = new TH1F("h_HF","h_HF",3,0,3);
  TH1F *h_ITER = new TH1F("h_ITER","h_ITER",3,0,3);
  TH1F *h_total = new TH1F("h_total","h_total",3,0,3);
  // fill bins with 0.2, 0.4, 0.6
  h_JES->SetBinContent(1,jes_total_avgMag), h_JES->SetBinContent(2,jes_total_avgMag), h_JES->SetBinContent(3,jes_total_avgMag);
  h_JER->SetBinContent(1,jer_total_avgMag), h_JER->SetBinContent(2,jer_total_avgMag), h_JER->SetBinContent(3,jer_total_avgMag);
  h_JAR->SetBinContent(1, jar_avgMag_R2), h_JAR->SetBinContent(2, jar_avgMag), h_JAR->SetBinContent(3, jar_avgMag_R6);
  h_LSR->SetBinContent(1, mcStats_avgMag_R2/sqrt(2)), h_LSR->SetBinContent(2, mcStats_avgMag_R4/sqrt(2)), h_LSR->SetBinContent(3, mcStats_avgMag_R6/sqrt(2));
  h_Prior->SetBinContent(1,prior_avgMag_R2), h_Prior->SetBinContent(2,prior_avgMag_R4), h_Prior->SetBinContent(3,prior_avgMag_R6);
  h_trkGap->SetBinContent(1,trk_total_avgMag_R2), h_trkGap->SetBinContent(2,trk_total_avgMag), h_trkGap->SetBinContent(3,trk_total_avgMag_R6);
  h_HF->SetBinContent(1,hf_avgMag_R2), h_HF->SetBinContent(2,hf_avgMag), h_HF->SetBinContent(3,hf_avgMag_R6);
  h_ITER->SetBinContent(1,it_avgMag_R2), h_ITER->SetBinContent(1,it_avgMag), h_ITER->SetBinContent(3,it_avgMag_R6);
  h_total->SetBinContent(1,total_sys_R2), h_total->SetBinContent(2,total_sys), h_total->SetBinContent(3,total_sys_R6);

  auto *c3 = new TCanvas("c3", "c3",900,900);
  c3->SetLeftMargin(0.13);
  c3->SetTicks(1,1);
  // color
  h_JES->SetLineColor(kRed);
  h_JER->SetLineColor(kOrange+7);
  h_JAR->SetLineColor(kYellow+2);
  h_LSR->SetLineColor(kGreen+2);
  h_Prior->SetLineColor(kCyan+1);
  h_trkGap->SetLineColor(kBlue);
  h_HF->SetLineColor(kViolet);
  h_ITER->SetLineColor(kPink+7);
  h_total->SetLineColor(kBlack);
  // line width
  h_JES->SetLineWidth(3);
  h_JER->SetLineWidth(3);
  h_JAR->SetLineWidth(3);
  h_LSR->SetLineWidth(3);
  h_Prior->SetLineWidth(3);
  h_trkGap->SetLineWidth(3);
  h_HF->SetLineWidth(3);
  h_ITER->SetLineWidth(3);
  h_total->SetLineWidth(3);
  // draw
  h_total->GetXaxis()->SetLabelSize(0.05);
  TAxis *xAxis = h_total->GetXaxis();
  xAxis->SetBinLabel(1, "r = 0.2");
  xAxis->SetBinLabel(2, "r = 0.4");
  xAxis->SetBinLabel(3, "r = 0.6");
  h_total->SetTitle("");
  h_total->GetYaxis()->SetTitle("contribution to systematics (10^{-2})");
  h_total->GetYaxis()->SetRangeUser(0,0.07);
  h_total->Draw("hist");
  h_JES->Draw("hist same");
  h_JER->Draw("hist same");
  h_JAR->Draw("hist same");
  h_LSR->Draw("hist same");
  h_Prior->Draw("hist same");
  h_trkGap->Draw("hist same");
  h_HF->Draw("hist same");
  h_ITER->Draw("hist same");
  drawLegendStr9(h_JES, h_JER, h_JAR, h_LSR, h_Prior, h_trkGap, h_HF, h_ITER, h_total, 0.25, 0.825, 0.725, 0.855, "JES", "JER", "JAR", "LSR", "Prior", "Tracker gap", "HF", "Iterations", "Total",3);
  drawText(.13, .915, "#bf{CMS} #it{work in progress}", kBlack, 28);
  drawText(0.53, 0.915, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);
  c3->SaveAs("Pics/systematics_radius_v4.pdf");
}
