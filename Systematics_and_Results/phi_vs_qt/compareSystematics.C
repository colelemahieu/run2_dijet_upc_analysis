// compareSystematics.C
// This code:
// -calculates systematics and adds them in quadrature
// -makes systematics plots for the analysis note
// -makes result plots for v2=<cos(2phi)> vs qt

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
#include "TGraph.h"
#include "TF1.h"
#include "TPad.h"
#include "TLorentzVector.h"
#include "/home/colelemahieu/Research2023/Run2/RapidityAnalysis/nicePlotting.h"
using namespace std;

// plotting functions
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
  drawText(0.51, 0.915, "PbPb: #sqrt{s_{NN}} = 5.02 TeV (2018)", kBlack, 28);
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
 
  drawText(.125, .915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.515, 0.915, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);
  drawLegendStr(h1, h2, 0.15, 0.4, 0.7, 0.875, label1, label2);
  drawText(0.75, 0.81, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h2)), kBlack, 34);
  drawText(0.75, 0.73, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h2)), kBlack, 34);

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
  //h_residual->GetYaxis()->SetRangeUser(0-yFactor, yFactor);
  h_residual->GetYaxis()->SetRangeUser(-0.2, 0.35);
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



void makeNiceResidual_systematics_0n0n(TH1F *h1, TH1F *h2, const char *titleX, const char *titleY, string label1, string label2, const char *name, const char *residual, float totalSys, float totalSys_0n0n, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80){
  
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
  main->SetBottomMargin(0.13);
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
  h1->GetYaxis()->SetLabelSize(0.05);
  h1->GetYaxis()->SetTitleOffset(0.75);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(2);
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(2);
  h2->SetMarkerStyle(21);
  h2->SetMarkerColor(kBlue);
  h2->SetLineColor(kBlue);
  h1->SetTitle("");
  h2->SetTitle("");
  h1->Draw("hist pE");
  h2->Draw("same pE");
  // systematics
  double syst_error = totalSys, syst_error_0n0n = totalSys_0n0n;
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h1->GetBinContent(i), binContent2 = h2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-syst_error, yLow2 = binContent2-syst_error_0n0n;
        double yHigh = binContent+syst_error, yHigh2 = binContent2+syst_error_0n0n;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
	TBox* box2 = new TBox(xLow, yLow2, xHigh, yHigh2);
        box2->SetFillColorAlpha(kBlue, 0.3); 
        box2->SetLineWidth(0);               
        box2->Draw("SAME");
	
    }
 
  drawText(.13, .915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.52, 0.915, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);
  drawLegendStr(h1, h2, 0.15, 0.4, 0.7, 0.875, label1, label2);
  //drawText(0.17, 0.64, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h2)), kBlack, 34);
  //drawText(0.17, 0.64, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h2)), kBlack, 34);

  ratio->cd();
  ratio->SetTopMargin(0.045);
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
  h_residual->GetYaxis()->SetLabelSize(0.11);
  h_residual->GetYaxis()->SetTitleSize(0.17);
  h_residual->GetYaxis()->SetRangeUser(-0.9, 0.45);
  h_residual->GetYaxis()->SetNdivisions(303);
  h_residual->GetXaxis()->SetTitle(titleX);
  h_residual->GetXaxis()->SetLabelSize(0.11);
  h_residual->GetYaxis()->SetTitle(residual);
  h_residual->GetYaxis()->SetTitleSize(0.17);
  h_residual->GetYaxis()->SetTitleOffset(0.35);
  h_residual->SetMarkerSize(2);
  h_residual->SetLineWidth(2);
  ratio->SetBottomMargin(0.275);
  //float excelErrors[5] = {0.075,0.037,0.14,0.16,0.54};
  float excelErrors[5] = {0.037,0.037,0.037,0.037,0.037};
  h_residual->Draw("same hist p");
  // systematics
  double syst_res = sqrt(totalSys*totalSys + totalSys*totalSys);
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        //double yResLow = resContent-syst_res;
        //double yResHigh = resContent+syst_res;
	double yResLow = resContent-excelErrors[i-1];
        double yResHigh = resContent+excelErrors[i-1];

        // Create and draw the box for this bin
        TBox* boxRes = new TBox(xLow, yResLow, xHigh, yResHigh);
        boxRes->SetFillColorAlpha(kBlack, 0.3); 
        boxRes->SetLineWidth(0);               
        boxRes->Draw("SAME");	
    }

  float xmax = h_residual->GetXaxis()->GetXmax();
  float xmin = h_residual->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,0,xmax,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h_residual->Draw("same hist pE");
  drawText(0.17, 0.81, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h2)), kBlack, 34);

  canvas->SaveAs(name);
  delete canvas;
}


void compareSystematics()
{
  // Read Files
  TFile *fileGen_R2 = new TFile("Files/gen_r2_v2.root");
  TFile *fileGen_R4 = new TFile("Files/gen_r4_v2.root");
  TFile *fileGen_R4_gg = new TFile("Files/gen_r4_v2_gg.root");
  TFile *fileGen_R6 = new TFile("Files/gen_r6_v2.root");
  TFile *fileReco_R4_gg = new TFile("Files/reco_r4_v2_gg.root");
  TFile *fileReco_R4 = new TFile("Files/reco_r4_v2.root");
  TFile *fileUnf_R2 = new TFile("Files/unf_r2_v2.root");
  TFile *fileUnf_R4 = new TFile("Files/unf_r4_v2.root");
  TFile *fileUnf_R4_0n0n = new TFile("Files/unf_r4_0n0n_v2.root");
  TFile *fileUnf_R4_0n0n_gg = new TFile("Files/unf_r4_0n0n_gg_v2.root");
  TFile *fileUnf_R4_noZDC = new TFile("Files/unf_r4_noZDC_v2.root");
  TFile *fileUnf_R6 = new TFile("Files/unf_r6_v2.root");
  TFile *fileUnf_R2_ac = new TFile("Files/unf_r2_v2_ac.root");
  TFile *fileUnf_R4_ac = new TFile("Files/unf_r4_v2_ac.root");
  TFile *fileUnf_R4_0n0n_ac = new TFile("Files/unf_r4_0n0n_v2_ac.root");
  TFile *fileUnf_R4_0n0n_gg_ac = new TFile("Files/unf_r4_0n0n_gg_v2_ac.root");
  TFile *fileUnf_R6_ac = new TFile("Files/unf_r6_v2_ac.root");
  TFile *fileUnf_R2_orig = new TFile("Files/unf_r2_v2_orig.root");
  TFile *fileUnf_R4_orig = new TFile("Files/unf_r4_v2_orig.root");
  TFile *fileUnf_R4_0n0n_orig = new TFile("Files/unf_r4_0n0n_v2_orig.root");
  TFile *fileUnf_R6_orig = new TFile("Files/unf_r6_v2_orig.root");
  TFile *fileUnf_R6_0n0n_orig = new TFile("Files/unf_r6_0n0n_v2_orig.root");
  TFile *fileJESup = new TFile("Files/JES_up_r4_v2.root");
  TFile *fileJESnom = new TFile("Files/JES_nom_r4_v2.root");
  TFile *fileJESdown = new TFile("Files/JES_down_r4_v2.root");
  TFile *fileJESup_0n0n = new TFile("Files/JES_up_0n0n_v2.root");
  TFile *fileJESnom_0n0n = new TFile("Files/JES_nom_0n0n_v2.root");
  TFile *fileJESdown_0n0n = new TFile("Files/JES_down_0n0n_v2.root");
  TFile *fileJERup = new TFile("Files/JER_up_r4_v2.root");
  TFile *fileJERnom = new TFile("Files/JER_nom_r4_v2.root");
  TFile *fileJERdown = new TFile("Files/JER_down_r4_v2.root");
  TFile *fileJERup_0n0n = new TFile("Files/JER_up_0n0n_v2.root");
  TFile *fileJERnom_0n0n = new TFile("Files/JER_nom_0n0n_v2.root");
  TFile *fileJERdown_0n0n = new TFile("Files/JER_down_0n0n_v2.root");
  TFile *fileJAR_R2 = new TFile("Files/JAR_r2_v2.root");
  TFile *fileJAR_R4 = new TFile("Files/JAR_r4_v2.root");
  TFile *fileJAR_R6 = new TFile("Files/JAR_r6_v2.root");
  TFile *fileJAR_0n0n = new TFile("Files/JAR_0n0n_v2.root");
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
  TFile *fileRapup_0n0n = new TFile("Files/unf_0n0n_v2_rapgapUp.root");
  TFile *fileRapdown_0n0n = new TFile("Files/unf_0n0n_v2_rapgapDown.root");
  TFile *fileHF_0n0n = new TFile("Files/unf_0n0n_v2_hf.root");
  TFile *fileRapup_R2 = new TFile("Files/unf_r2_v2_rapgapUp.root");
  TFile *fileRapdown_R2 = new TFile("Files/unf_r2_v2_rapgapDown.root");
  TFile *fileHF_R2 = new TFile("Files/unf_r2_v2_hf.root");
  TFile *fileRapup_R6 = new TFile("Files/unf_r6_v2_rapgapUp.root");
  TFile *fileRapdown_R6 = new TFile("Files/unf_r6_v2_rapgapDown.root");
  TFile *fileHF_R6 = new TFile("Files/unf_r6_v2_hf.root");
  TFile *file2it_R4 = new TFile("Files/unf_r4_v2_2iterations.root");
  TFile *file3it_R4 = new TFile("Files/unf_r4_v2_3iterations.root");
  TFile *file2it_0n0n = new TFile("Files/unf_0n0n_v2_2iterations.root");
  TFile *file3it_0n0n = new TFile("Files/unf_0n0n_v2_3iterations.root");
  TFile *file2it_R2 = new TFile("Files/unf_r2_v2_2iterations.root");
  TFile *file3it_R2 = new TFile("Files/unf_r2_v2_3iterations.root");
  TFile *file2it_R6 = new TFile("Files/unf_r6_v2_2iterations.root");
  TFile *file3it_R6 = new TFile("Files/unf_r6_v2_3iterations.root");
  // dPphi cuts
  TFile *fileGen_R2_cut = new TFile("Files/gen_r2_v2_cut.root");
  TFile *fileGen_R4_cut = new TFile("Files/gen_r4_v2_cut.root");
  TFile *fileGen_R6_cut = new TFile("Files/gen_r6_v2_cut.root");
  TFile *fileR2_cut = new TFile("Files/unf_r2_v2_cut.root");
  TFile *fileR4_cut = new TFile("Files/unf_r4_v2_cut.root");
  TFile *fileR4_0n0n_cut = new TFile("Files/unf_r4_0n0n_v2_cut.root");
  TFile *fileR6_cut = new TFile("Files/unf_r6_v2_cut.root");
  // R4 file for response matrix slice
  TFile *fileR4_slice = new TFile("Files/fit_v2_responseSlice.root");
  // R2,R4,R6 misses
  TFile *fileR2_2D = new TFile("Files/fit_v2_full_R2_ac.root");
  TFile *fileR4_2D = new TFile("Files/fit_v2_full_ac.root");
  TFile *fileR6_2D = new TFile("Files/fit_v2_full_R6_ac.root");

  // 2D histograms
  TH2F *h2_miss_r2 = (TH2F*)fileR2_2D->Get("h2_miss");
  TH2F *h2_miss_r4 = (TH2F*)fileR4_2D->Get("h2_miss");
  TH2F *h2_miss_r6 = (TH2F*)fileR6_2D->Get("h2_miss");

  // v2
  TH1F *v2_gen_R2 = (TH1F*)fileGen_R2->Get("h_v2");
  TH1F *v2_gen_R4 = (TH1F*)fileGen_R4->Get("h_v2");
  TH1F *v2_gen_R4_gg = (TH1F*)fileGen_R4_gg->Get("h_v2");
  TH1F *v2_gen_R6 = (TH1F*)fileGen_R6->Get("h_v2");
  TH1F *v2_reco_R4_gg = (TH1F*)fileReco_R4_gg->Get("h_v2");
  TH1F *v2_reco_R4 = (TH1F*)fileReco_R4->Get("h_v2");
  TH1F *v2_unf_R2 = (TH1F*)fileUnf_R2->Get("h_v2");
  TH1F *v2_unf_R4 = (TH1F*)fileUnf_R4->Get("h_v2");
  TH1F *v2_unf_R4_0n0n = (TH1F*)fileUnf_R4_0n0n->Get("h_v2");
  TH1F *v2_unf_R4_0n0n_gg = (TH1F*)fileUnf_R4_0n0n_gg->Get("h_v2");
  TH1F *v2_unf_R4_noZDC = (TH1F*)fileUnf_R4_noZDC->Get("h_v2");
  TH1F *v2_unf_R6 = (TH1F*)fileUnf_R6->Get("h_v2");
  TH1F *v2_unf_R2_ac = (TH1F*)fileUnf_R2_ac->Get("h_v2");
  TH1F *v2_unf_R4_ac = (TH1F*)fileUnf_R4_ac->Get("h_v2");
  TH1F *v2_unf_R4_0n0n_ac = (TH1F*)fileUnf_R4_0n0n_ac->Get("h_v2");
  TH1F *v2_unf_R4_0n0n_gg_ac = (TH1F*)fileUnf_R4_0n0n_gg_ac->Get("h_v2");
  TH1F *v2_unf_R6_ac = (TH1F*)fileUnf_R6_ac->Get("h_v2");
  TH1F *v2_unf_R2_orig = (TH1F*)fileUnf_R2_orig->Get("h_v2");
  TH1F *v2_unf_R4_orig = (TH1F*)fileUnf_R4_orig->Get("h_v2");
  TH1F *v2_unf_R4_0n0n_orig = (TH1F*)fileUnf_R4_0n0n_orig->Get("h_v2");
  TH1F *v2_unf_R6_orig = (TH1F*)fileUnf_R6_orig->Get("h_v2");
  TH1F *v2_unf_R6_0n0n_orig = (TH1F*)fileUnf_R6_0n0n_orig->Get("h_v2");
  TH1F *v2_jesUp_R4 = (TH1F*)fileJESup->Get("h_v2");
  TH1F *v2_jesNom_R4 = (TH1F*)fileJESnom->Get("h_v2");
  TH1F *v2_jesDown_R4 = (TH1F*)fileJESdown->Get("h_v2");
  TH1F *v2_jesUp_0n0n = (TH1F*)fileJESup_0n0n->Get("h_v2");
  TH1F *v2_jesNom_0n0n = (TH1F*)fileJESnom_0n0n->Get("h_v2");
  TH1F *v2_jesDown_0n0n = (TH1F*)fileJESdown_0n0n->Get("h_v2");
  TH1F *v2_jerUp_R4 = (TH1F*)fileJERup->Get("h_v2");
  TH1F *v2_jerNom_R4 = (TH1F*)fileJERnom->Get("h_v2");
  TH1F *v2_jerDown_R4 = (TH1F*)fileJERdown->Get("h_v2");
  TH1F *v2_jerUp_0n0n = (TH1F*)fileJERup_0n0n->Get("h_v2");
  TH1F *v2_jerNom_0n0n = (TH1F*)fileJERnom_0n0n->Get("h_v2");
  TH1F *v2_jerDown_0n0n = (TH1F*)fileJERdown_0n0n->Get("h_v2");
  TH1F *v2_jar_R2 = (TH1F*)fileJAR_R2->Get("h_v2");
  TH1F *v2_jar_R4 = (TH1F*)fileJAR_R4->Get("h_v2");
  TH1F *v2_jar_R6 = (TH1F*)fileJAR_R6->Get("h_v2");
  TH1F *v2_jar_0n0n = (TH1F*)fileJAR_0n0n->Get("h_v2");
  TH1F *v2_prior_R2 = (TH1F*)filePrior_R2->Get("h_v2");
  TH1F *v2_prior_R4 = (TH1F*)filePrior_R4->Get("h_v2");
  TH1F *v2_prior_0n0n = (TH1F*)filePrior_0n0n->Get("h_v2");
  TH1F *v2_prior_R6 = (TH1F*)filePrior_R6->Get("h_v2");
  TH1F *v2_mcStat1_R2 = (TH1F*)filemcStat1_R2->Get("h_v2");
  TH1F *v2_mcStat2_R2 = (TH1F*)filemcStat2_R2->Get("h_v2");
  TH1F *v2_mcStat1_R4 = (TH1F*)filemcStat1_R4->Get("h_v2");
  TH1F *v2_mcStat2_R4 = (TH1F*)filemcStat2_R4->Get("h_v2");
  TH1F *v2_mcStat1_0n0n = (TH1F*)filemcStat1_0n0n->Get("h_v2");
  TH1F *v2_mcStat2_0n0n = (TH1F*)filemcStat2_0n0n->Get("h_v2");
  TH1F *v2_mcStat1_R6 = (TH1F*)filemcStat1_R6->Get("h_v2");
  TH1F *v2_mcStat2_R6 = (TH1F*)filemcStat2_R6->Get("h_v2");
  TH1F *v2_rapup = (TH1F*)fileRapup->Get("h_v2");
  TH1F *v2_rapdown = (TH1F*)fileRapdown->Get("h_v2");
  TH1F *v2_hf = (TH1F*)fileHF->Get("h_v2");
  TH1F *v2_rapup_0n0n = (TH1F*)fileRapup_0n0n->Get("h_v2");
  TH1F *v2_rapdown_0n0n = (TH1F*)fileRapdown_0n0n->Get("h_v2");
  TH1F *v2_hf_0n0n = (TH1F*)fileHF_0n0n->Get("h_v2");
  TH1F *v2_rapup_R2 = (TH1F*)fileRapup_R2->Get("h_v2");
  TH1F *v2_rapdown_R2 = (TH1F*)fileRapdown_R2->Get("h_v2");
  TH1F *v2_hf_R2 = (TH1F*)fileHF_R2->Get("h_v2");
  TH1F *v2_rapup_R6 = (TH1F*)fileRapup_R6->Get("h_v2");
  TH1F *v2_rapdown_R6 = (TH1F*)fileRapdown_R6->Get("h_v2");
  TH1F *v2_hf_R6 = (TH1F*)fileHF_R6->Get("h_v2");
  TH1F *v2_2it_R4 = (TH1F*)file2it_R4->Get("h_v2");
  TH1F *v2_3it_R4 = (TH1F*)file3it_R4->Get("h_v2");
  TH1F *v2_2it_0n0n = (TH1F*)file2it_0n0n->Get("h_v2");
  TH1F *v2_3it_0n0n = (TH1F*)file3it_0n0n->Get("h_v2");
  TH1F *v2_2it_R2 = (TH1F*)file2it_R2->Get("h_v2");
  TH1F *v2_3it_R2 = (TH1F*)file3it_R2->Get("h_v2");
  TH1F *v2_2it_R6 = (TH1F*)file2it_R6->Get("h_v2");
  TH1F *v2_3it_R6 = (TH1F*)file3it_R6->Get("h_v2");
  // dPhi v2
  TH1F *v2_gen_R2_cut = (TH1F*)fileGen_R2_cut->Get("h_v2");
  TH1F *v2_gen_R4_cut = (TH1F*)fileGen_R4_cut->Get("h_v2");
  TH1F *v2_gen_R6_cut = (TH1F*)fileGen_R6_cut->Get("h_v2");
  TH1F *v2_unf_R2_cut = (TH1F*)fileR2_cut->Get("h_v2");
  TH1F *v2_unf_R4_cut = (TH1F*)fileR4_cut->Get("h_v2");
  TH1F *v2_unf_R4_0n0n_cut = (TH1F*)fileR4_0n0n_cut->Get("h_v2");
  TH1F *v2_unf_R6_cut = (TH1F*)fileR6_cut->Get("h_v2");
  // r=0.4 response slice
  TH2F *h2_response_slice = (TH2F*)fileR4_slice->Get("h2_responseSlice");

  // set sumW2
  v2_jesNom_R4->Sumw2();
  v2_jesUp_R4->Sumw2();
  v2_jesDown_R4->Sumw2();

  
  // systematics plots for Analysis Note
  // JES up R4
  makeNiceResidual_syst(v2_jesNom_R4, v2_jesUp_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JES Up Result","", "Pics/unf_jesUp.png",0,0.6);
  // JES nom R4
  makeNiceResidual_syst(v2_unf_R4, v2_jesNom_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JES Nom Result","", "Pics/unf_jesNom.png",0,0.6);
  // JES down R4
  makeNiceResidual_syst(v2_jesNom_R4, v2_jesDown_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JES Down Result","", "Pics/unf_jesDown.png",0,0.6);
   // JER up
  makeNiceResidual_syst(v2_jerNom_R4, v2_jerUp_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JER Up Result","", "Pics/unf_jerUp.png",0,0.6);
  // JER down
  makeNiceResidual_syst(v2_jerNom_R4, v2_jerDown_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JER Down Result","", "Pics/unf_jerDown.png",0,0.6);
  // JAR R2
  makeNiceResidual_syst(v2_unf_R2, v2_jar_R2, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JAR Result","", "Pics/unf_jar_r2.png",0,0.8);
  // JAR R4
  makeNiceResidual_syst(v2_unf_R4, v2_jar_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JAR Result","", "Pics/unf_jar_r4.png",0,0.6);
  // JAR R6
  makeNiceResidual_syst(v2_unf_R6, v2_jar_R6, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "JAR Result","", "Pics/unf_jar_r6.png",-0.1,0.6);
  // Prior R2
  makeNiceResidual_syst(v2_unf_R2, v2_prior_R2, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Prior Result","", "Pics/unf_prior_r2.png",0,0.7);
  // Prior R4
  makeNiceResidual_syst(v2_unf_R4, v2_prior_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Prior Result","", "Pics/unf_prior_r4.png",-0.5,0.6);
  // Prior 0n0n
  makeNiceResidual_syst(v2_unf_R4_0n0n, v2_prior_0n0n, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Prior Result","", "Pics/unf_prior_0n0n.png",0,1.0);
  // Prior R6
  makeNiceResidual_syst(v2_unf_R6, v2_prior_R6, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Prior Result","", "Pics/unf_prior_r6.png",-0.1,0.6);
  // mcStats R2
  makeNiceResidual_syst(v2_mcStat1_R2, v2_mcStat2_R2, "Q_{T} [GeV]", "<cos(2#phi)>", "Data unfolded with MC half 1", "Data unfolded with MC half 2","", "Pics/unf_mcStats_r2.png",0,0.7);
  // mcStats R4
  makeNiceResidual_syst(v2_mcStat1_R4, v2_mcStat2_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Data unfolded with MC half 1", "Data unfolded with MC half 2","", "Pics/unf_mcStats_r4.png",0,0.7);
  // mcStats 0n0n
  makeNiceResidual_syst(v2_mcStat1_0n0n, v2_mcStat2_0n0n, "Q_{T} [GeV]", "<cos(2#phi)>", "Data unfolded with MC half 1", "Data unfolded with MC half 2","", "Pics/unf_mcStats_0n0n.png",0,1.0);
  // mcStats R6
  makeNiceResidual_syst(v2_mcStat1_R6, v2_mcStat2_R6, "Q_{T} [GeV]", "<cos(2#phi)>", "Data unfolded with MC half 1", "Data unfolded with MC half 2","", "Pics/unf_mcStats_r6.png",-0.1,0.7);
  // RAP UP
  makeNiceResidual_syst(v2_unf_R4, v2_rapup, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Rap Up Result","", "Pics/unf_rapUp.png",-0.1,0.6);
  makeNiceResidual_syst(v2_unf_R2, v2_rapup_R2, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Rap Up Result","", "Pics/unf_rapUp_r2.png",-0.1,0.7);
  makeNiceResidual_syst(v2_unf_R6, v2_rapup_R6, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Rap Up Result","", "Pics/unf_rapUp_r6.png",-0.1,0.6);
  // RAP DOWN
  makeNiceResidual_syst(v2_unf_R4, v2_rapdown, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Rap Down Result","", "Pics/unf_rapDown.png",-0.1,0.6);
  makeNiceResidual_syst(v2_unf_R2, v2_rapdown_R2, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Rap Down Result","", "Pics/unf_rapDown_r2.png",-0.1,0.6);
  makeNiceResidual_syst(v2_unf_R6, v2_rapdown_R6, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "Rap Down Result","", "Pics/unf_rapDown_r6.png",-0.1,0.6);
  // HF
  makeNiceResidual_syst(v2_unf_R4, v2_hf, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "HF Result","", "Pics/unf_hf.png",-0.1,0.6);
  makeNiceResidual_syst(v2_unf_R2, v2_hf_R2, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "HF Result","", "Pics/unf_hf_R2.png",-0.1,0.75);
  makeNiceResidual_syst(v2_unf_R6, v2_hf_R6, "Q_{T} [GeV]", "<cos(2#phi)>", "Nominal Result", "HF Result","", "Pics/unf_hf_R6.png",-0.1,0.6);
  // iterations
  makeNiceResidual_syst(v2_2it_R4, v2_3it_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "2 iterations", "3 iterations","", "Pics/unf_it.png",-0.1,0.6);
  makeNiceResidual_syst(v2_2it_R2, v2_3it_R2, "Q_{T} [GeV]", "<cos(2#phi)>", "2 iterations", "3 iterations","", "Pics/unf_it_R2.png",-0.1,0.6);
  makeNiceResidual_syst(v2_2it_R6, v2_3it_R6, "Q_{T} [GeV]", "<cos(2#phi)>", "2 iterations", "3 iterations","", "Pics/unf_it_R6.png",-0.1,0.6);

  // compare Gens
  makeNiceResidual_syst(v2_gen_R4, v2_gen_R4_gg, "Q_{T} [GeV]", "<cos(2#phi)>", "Gen gq->qq", "Gen gg->qq","", "Pics/compare_gens.png",0,1.2);
  // compare Recos
  makeNiceResidual_syst(v2_reco_R4, v2_reco_R4_gg, "Q_{T} [GeV]", "<cos(2#phi)>", "Reco gq->qq", "Reco gg->qq","", "Pics/compare_recos.png",0,1.2);
 


  // text files to store systematics for each bin
  ofstream outfile_prior_r2("textFiles/prior_diff_r2.txt"), outfile_mcStats_r2("textFiles/mcStats_diff_r2.txt"), outfile_jar_r2("textFiles/jar_diff_r2.txt"), outfile_jer_r2("textFiles/jer_diff_r2.txt"), outfile_trk_r2("textFiles/trk_diff_r2.txt"), outfile_hf_r2("textFiles/hf_diff_r2.txt"), outfile_it_r2("textFiles/it_diff_r2.txt");
  ofstream outfile_prior_r6("textFiles/prior_diff_r6.txt"), outfile_mcStats_r6("textFiles/mcStats_diff_r6.txt"), outfile_jar_r6("textFiles/jar_diff_r6.txt"), outfile_jer_r6("textFiles/jer_diff_r6.txt"), outfile_trk_r6("textFiles/trk_diff_r6.txt"), outfile_hf_r6("textFiles/hf_diff_r6.txt"), outfile_it_r6("textFiles/it_diff_r6.txt");
  ofstream outfile_jes("textFiles/jes_diff.txt"), outfile_prior("textFiles/prior_diff.txt"), outfile_mcStats("textFiles/mcStats_diff.txt"), outfile_jar("textFiles/jar_diff.txt"), outfile_jer("textFiles/jer_diff.txt"), outfile_trk("textFiles/trk_diff.txt"), outfile_hf("textFiles/hf_diff.txt"), outfile_it("textFiles/it_diff.txt");

  // loop through histogram bins
  float unf_content=0, unf_0n0n_content=0, nomJES_content=0, nomJER_content=0, jesUp_content=0, jesDown_content=0, jerUp_content=0, jerDown_content=0, jar_content=0, jer_content=0, trkUp_content=0, trkDown_content=0, hf_content=0, twoIt_content=0, threeIt_content=0;
  float nomJES_content_0n0n=0, nomJER_content_0n0n=0, jesUp_content_0n0n=0, jesDown_content_0n0n=0, jerUp_content_0n0n=0, jerDown_content_0n0n=0, jar_content_0n0n=0, trkUp_content_0n0n=0, trkDown_content_0n0n=0, hf_content_0n0n=0, twoIt_content_0n0n=0, threeIt_content_0n0n=0;
  float unf_content_R2=0, jar_content_R2=0, jer_content_R2=0, trkUp_content_R2=0, trkDown_content_R2=0, hf_content_R2=0, twoIt_content_R2=0, threeIt_content_R2=0;
  float unf_content_R6=0, jar_content_R6=0, jer_content_R6=0, trkUp_content_R6=0, trkDown_content_R6=0, hf_content_R6=0, twoIt_content_R6=0, threeIt_content_R6=0;
  float prior_content_R2=0, prior_content_R4=0, prior_content_0n0n=0, prior_content_R6=0;
  float mcStats1_content_R2=0, mcStats2_content_R2=0, mcStats1_content_R4=0, mcStats2_content_R4=0, mcStats1_content_0n0n=0, mcStats2_content_0n0n=0, mcStats1_content_R6=0, mcStats2_content_R6=0; 
  float jesUp_Diff=0, jesDown_Diff=0, jerUp_Diff=0, jerDown_Diff=0, jar_Diff=0, jer_Diff=0, trkUp_Diff=0, trkDown_Diff=0, hf_Diff=0, itDiff=0;
  float jesUp_Diff_0n0n=0, jesDown_Diff_0n0n=0, jerUp_Diff_0n0n=0, jerDown_Diff_0n0n=0, jar_Diff_0n0n=0, jer_Diff_0n0n=0, trkUp_Diff_0n0n=0, trkDown_Diff_0n0n=0, hf_Diff_0n0n=0, itDiff_0n0n=0;
  float jar_Diff_R2=0, jer_Diff_R2=0, jar_Diff_R6=0, jer_Diff_R6=0, trkUp_Diff_R2=0, trkDown_Diff_R2=0, hf_Diff_R2=0, itDiff_R2=0, trkUp_Diff_R6=0, trkDown_Diff_R6=0, hf_Diff_R6=0, itDiff_R6=0;
  float prior_Diff_R2=0, prior_Diff_R4=0, prior_Diff_0n0n=0, prior_Diff_R6=0;
  float mcStats_Diff_R2=0, mcStats_Diff_R4=0, mcStats_Diff_0n0n=0, mcStats_Diff_R6=0; 
  float total_sys=0, total_sys_0n0n=0, jesUp_avgMag=0, jesDown_avgMag=0, jerUp_avgMag=0, jerDown_avgMag=0, jar_avgMag=0, jer_avgMag=0, it_avgMag=0, jesUp_avgMag_0n0n=0, jesDown_avgMag_0n0n=0, jerUp_avgMag_0n0n=0, jerDown_avgMag_0n0n=0, jar_avgMag_0n0n=0, jer_avgMag_0n0n=0, trkUp_avgMag_0n0n=0, trkDown_avgMag_0n0n=0, hf_avgMag_0n0n=0, it_avgMag_0n0n=0;
  float total_sys_R2=0, jar_avgMag_R2=0, jer_avgMag_R2=0, trkUp_avgMag=0, trkDown_avgMag=0, hf_avgMag=0, total_sys_R6=0, jar_avgMag_R6=0, jer_avgMag_R6=0, trkUp_avgMag_R2=0, trkDown_avgMag_R2=0, hf_avgMag_R2=0, it_avgMag_R2=0, trkUp_avgMag_R6=0, trkDown_avgMag_R6=0, hf_avgMag_R6=0, it_avgMag_R6=0;
  float prior_avgMag_R2=0, prior_avgMag_R4=0, prior_avgMag_0n0n=0, prior_avgMag_R6=0;
  float mcStats_avgMag_R2=0, mcStats_avgMag_R4=0, mcStats_avgMag_0n0n=0, mcStats_avgMag_R6=0;
  int binNumber = v2_unf_R4->GetNbinsX();

  // printing multiplier
  float multiplier=100;

  // loop through bin differences
  for (int iBin=1; iBin<binNumber+1; iBin++)
    {
      // get contents
      unf_content=v2_unf_R4->GetBinContent(iBin), unf_0n0n_content=v2_unf_R4_0n0n->GetBinContent(iBin), unf_content_R2=v2_unf_R2->GetBinContent(iBin), unf_content_R6=v2_unf_R6->GetBinContent(iBin);
      nomJES_content=v2_jesNom_R4->GetBinContent(iBin), nomJER_content=v2_jerNom_R4->GetBinContent(iBin);
      nomJES_content_0n0n=v2_jesNom_0n0n->GetBinContent(iBin), nomJER_content_0n0n=v2_jerNom_0n0n->GetBinContent(iBin);
      jesUp_content=v2_jesUp_R4->GetBinContent(iBin), jesDown_content=v2_jesDown_R4->GetBinContent(iBin);
      jesUp_content_0n0n=v2_jesUp_0n0n->GetBinContent(iBin), jesDown_content_0n0n=v2_jesDown_0n0n->GetBinContent(iBin);
      jerUp_content=v2_jerUp_R4->GetBinContent(iBin),jerDown_content=v2_jerDown_R4->GetBinContent(iBin);
      jerUp_content_0n0n=v2_jerUp_0n0n->GetBinContent(iBin),jerDown_content_0n0n=v2_jerDown_0n0n->GetBinContent(iBin);
      jar_content=v2_jar_R4->GetBinContent(iBin), jar_content_R2=v2_jar_R2->GetBinContent(iBin), jar_content_R6=v2_jar_R6->GetBinContent(iBin);
      jar_content_0n0n=v2_jar_0n0n->GetBinContent(iBin);
      prior_content_R4=v2_prior_R4->GetBinContent(iBin), prior_content_0n0n=v2_prior_0n0n->GetBinContent(iBin), prior_content_R2=v2_prior_R2->GetBinContent(iBin), prior_content_R6=v2_prior_R6->GetBinContent(iBin);
      mcStats1_content_R2=v2_mcStat1_R2->GetBinContent(iBin), mcStats2_content_R2=v2_mcStat2_R2->GetBinContent(iBin);
      mcStats1_content_R4=v2_mcStat1_R4->GetBinContent(iBin), mcStats2_content_R4=v2_mcStat2_R4->GetBinContent(iBin);
      mcStats1_content_0n0n=v2_mcStat1_0n0n->GetBinContent(iBin), mcStats2_content_0n0n=v2_mcStat2_0n0n->GetBinContent(iBin);
      mcStats1_content_R6=v2_mcStat1_R6->GetBinContent(iBin), mcStats2_content_R6=v2_mcStat2_R6->GetBinContent(iBin);
      trkUp_content=v2_rapup->GetBinContent(iBin), trkDown_content=v2_rapdown->GetBinContent(iBin);
      trkUp_content_0n0n=v2_rapup_0n0n->GetBinContent(iBin), trkDown_content_0n0n=v2_rapdown_0n0n->GetBinContent(iBin);
      hf_content=v2_hf->GetBinContent(iBin), hf_content_0n0n=v2_hf_0n0n->GetBinContent(iBin);
      trkUp_content_R2=v2_rapup_R2->GetBinContent(iBin), trkDown_content_R2=v2_rapdown_R2->GetBinContent(iBin);
      hf_content_R2=v2_hf_R2->GetBinContent(iBin);
      trkUp_content_R6=v2_rapup_R6->GetBinContent(iBin), trkDown_content_R6=v2_rapdown_R6->GetBinContent(iBin);
      hf_content_R6=v2_hf_R6->GetBinContent(iBin);
      twoIt_content=v2_2it_R4->GetBinContent(iBin), threeIt_content=v2_3it_R4->GetBinContent(iBin);
      twoIt_content_0n0n=v2_2it_0n0n->GetBinContent(iBin), threeIt_content_0n0n=v2_3it_0n0n->GetBinContent(iBin);
      twoIt_content_R2=v2_2it_R2->GetBinContent(iBin), threeIt_content_R2=v2_3it_R2->GetBinContent(iBin);
      twoIt_content_R6=v2_2it_R6->GetBinContent(iBin), threeIt_content_R6=v2_3it_R6->GetBinContent(iBin);
         
      
      // get differences
      jesUp_Diff=nomJES_content-jesUp_content, jesDown_Diff=nomJES_content-jesDown_content;
      jesUp_Diff_0n0n=nomJES_content_0n0n-jesUp_content_0n0n, jesDown_Diff_0n0n=nomJES_content_0n0n-jesDown_content_0n0n;
      jerUp_Diff=nomJER_content-jerUp_content, jerDown_Diff=nomJER_content-jerDown_content;
      jerUp_Diff_0n0n=nomJER_content_0n0n-jerUp_content_0n0n, jerDown_Diff_0n0n=nomJER_content_0n0n-jerDown_content_0n0n;
      jar_Diff=unf_content-jar_content, jar_Diff_R2=unf_content_R2-jar_content_R2, jar_Diff_R6=unf_content_R6-jar_content_R6;
      jar_Diff_0n0n=unf_0n0n_content-jar_content_0n0n;
      prior_Diff_R4=unf_content-prior_content_R4, prior_Diff_0n0n=unf_0n0n_content-prior_content_0n0n, prior_Diff_R2=unf_content_R2-prior_content_R2, prior_Diff_R6=unf_content_R6-prior_content_R6;
      mcStats_Diff_R2=mcStats1_content_R2-mcStats2_content_R2, mcStats_Diff_R4=mcStats1_content_R4-mcStats2_content_R4, mcStats_Diff_0n0n=mcStats1_content_0n0n-mcStats2_content_0n0n, mcStats_Diff_R6=mcStats1_content_R6-mcStats2_content_R6;
      trkUp_Diff=unf_content-trkUp_content, trkDown_Diff=unf_content-trkDown_content;
      trkUp_Diff_0n0n=unf_0n0n_content-trkUp_content_0n0n, trkDown_Diff_0n0n=unf_0n0n_content-trkDown_content_0n0n;
      hf_Diff=unf_content-hf_content, hf_Diff_0n0n=unf_0n0n_content-hf_content_0n0n;
      trkUp_Diff_R2=unf_content_R2-trkUp_content_R2, trkDown_Diff_R2=unf_content_R2-trkDown_content_R2;
      hf_Diff_R2=unf_content_R2-hf_content_R2;
      trkUp_Diff_R6=unf_content_R6-trkUp_content_R6, trkDown_Diff_R6=unf_content_R6-trkDown_content_R6;
      hf_Diff_R6=unf_content_R6-hf_content_R6;
      itDiff=twoIt_content-threeIt_content, itDiff_R2=twoIt_content_R2-threeIt_content_R2, itDiff_R6=twoIt_content_R6-threeIt_content_R6;
      itDiff_0n0n=twoIt_content_0n0n-threeIt_content_0n0n;
      

      // output to file
      outfile_mcStats << fixed << setprecision(1) << mcStats_Diff_R4*multiplier/sqrt(2) << endl, outfile_mcStats_r2 << fixed << setprecision(1) << mcStats_Diff_R2*multiplier << endl, outfile_mcStats_r6 << fixed << setprecision(1) << mcStats_Diff_R6*multiplier << endl;
      outfile_prior << fixed << setprecision(1) << prior_Diff_R4*multiplier << endl, outfile_prior_r2 << fixed << setprecision(1) << prior_Diff_R2*multiplier << endl, outfile_prior_r6 << fixed << setprecision(1) << prior_Diff_R6*multiplier << endl;
      outfile_jar << fixed << setprecision(1) << jar_Diff*multiplier << endl, outfile_jar_r2 << fixed << setprecision(1) << jar_Diff_R2*multiplier << endl, outfile_jar_r6 << fixed << setprecision(1) << jar_Diff_R6*multiplier << endl;
      outfile_jes << fixed << setprecision(1) << multiplier*(fabs(jesUp_Diff)+fabs(jesDown_Diff))/2 << endl;
      outfile_jer << fixed << setprecision(1) << multiplier*(fabs(jerUp_Diff)+fabs(jerDown_Diff))/2 << endl;
      outfile_trk << fixed << setprecision(1) << multiplier*((trkUp_Diff)+(trkDown_Diff))/2 << endl;
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
      jesUp_avgMag_0n0n=jesUp_avgMag_0n0n+fabs(jesUp_Diff_0n0n), jesDown_avgMag_0n0n=jesDown_avgMag_0n0n+fabs(jesDown_Diff_0n0n);
      jerUp_avgMag=jerUp_avgMag+fabs(jerUp_Diff), jerDown_avgMag=jerDown_avgMag+fabs(jerDown_Diff);
      jerUp_avgMag_0n0n=jerUp_avgMag_0n0n+fabs(jerUp_Diff_0n0n), jerDown_avgMag_0n0n=jerDown_avgMag_0n0n+fabs(jerDown_Diff_0n0n);
      jar_avgMag=jar_avgMag+fabs(jar_Diff), jar_avgMag_R2=jar_avgMag_R2+fabs(jar_Diff_R2);
      jar_avgMag_0n0n=jar_avgMag_0n0n+fabs(jar_Diff_0n0n);
      prior_avgMag_R4=prior_avgMag_R4+fabs(prior_Diff_R4), prior_avgMag_0n0n=prior_avgMag_0n0n+fabs(prior_Diff_0n0n), prior_avgMag_R2=prior_avgMag_R2+fabs(prior_Diff_R2);
      mcStats_avgMag_R2=mcStats_avgMag_R2+fabs(mcStats_Diff_R2), mcStats_avgMag_R4=mcStats_avgMag_R4+fabs(mcStats_Diff_R4), mcStats_avgMag_0n0n=mcStats_avgMag_0n0n+fabs(mcStats_Diff_0n0n);
      trkUp_avgMag=trkUp_avgMag+fabs(trkUp_Diff), trkDown_avgMag=trkDown_avgMag+fabs(trkDown_Diff);
      trkUp_avgMag_0n0n=trkUp_avgMag_0n0n+fabs(trkUp_Diff_0n0n), trkDown_avgMag_0n0n=trkDown_avgMag_0n0n+fabs(trkDown_Diff_0n0n);
      hf_avgMag=hf_avgMag+fabs(hf_Diff), hf_avgMag_0n0n=hf_avgMag_0n0n+fabs(hf_Diff_0n0n);
      trkUp_avgMag_R2=trkUp_avgMag_R2+fabs(trkUp_Diff_R2), trkDown_avgMag_R2=trkDown_avgMag_R2+fabs(trkDown_Diff_R2);
      hf_avgMag_R2=hf_avgMag_R2+fabs(hf_Diff_R2);
      trkUp_avgMag_R6=trkUp_avgMag_R6+fabs(trkUp_Diff_R6), trkDown_avgMag_R6=trkDown_avgMag_R6+fabs(trkDown_Diff_R6);
      hf_avgMag_R6=hf_avgMag_R6+fabs(hf_Diff_R6);
      it_avgMag=it_avgMag+fabs(itDiff), it_avgMag_R2=it_avgMag_R2+fabs(itDiff_R2), it_avgMag_R6=it_avgMag_R6+fabs(itDiff_R6);
      it_avgMag_0n0n=it_avgMag_0n0n+fabs(itDiff_0n0n);

      //if (iBin<5)
	{
	  jar_avgMag_R6=jar_avgMag_R6+fabs(jar_Diff_R6);
	  prior_avgMag_R6=prior_avgMag_R6+fabs(prior_Diff_R6);
	  mcStats_avgMag_R6=mcStats_avgMag_R6+fabs(mcStats_Diff_R6);
	}
      
    } // end bin loop
  

  // calculate avg bin systematics
  jesUp_avgMag=jesUp_avgMag/binNumber, jesDown_avgMag=jesDown_avgMag/binNumber;
  jesUp_avgMag_0n0n=jesUp_avgMag_0n0n/binNumber, jesDown_avgMag_0n0n=jesDown_avgMag_0n0n/binNumber;
  jerUp_avgMag=jerUp_avgMag/binNumber, jerDown_avgMag=jerDown_avgMag/binNumber;
  jerUp_avgMag_0n0n=jerUp_avgMag_0n0n/binNumber, jerDown_avgMag_0n0n=jerDown_avgMag_0n0n/binNumber;
  jar_avgMag=jar_avgMag/binNumber, jar_avgMag_R2=jar_avgMag_R2/binNumber, jar_avgMag_R6=jar_avgMag_R6/(binNumber);
  jar_avgMag_0n0n=jar_avgMag_0n0n/binNumber;
  prior_avgMag_R4=prior_avgMag_R4/binNumber, prior_avgMag_0n0n=prior_avgMag_0n0n/binNumber, prior_avgMag_R2=prior_avgMag_R2/binNumber, prior_avgMag_R6=prior_avgMag_R6/(binNumber);
  mcStats_avgMag_R2=mcStats_avgMag_R2/binNumber, mcStats_avgMag_R4=mcStats_avgMag_R4/binNumber, mcStats_avgMag_0n0n=mcStats_avgMag_0n0n/binNumber, mcStats_avgMag_R6=mcStats_avgMag_R6/(binNumber); 
  trkUp_avgMag=trkUp_avgMag/binNumber, trkDown_avgMag=trkDown_avgMag/binNumber;
  hf_avgMag=hf_avgMag/binNumber;
  trkUp_avgMag_0n0n=trkUp_avgMag_0n0n/binNumber, trkDown_avgMag_0n0n=trkDown_avgMag_0n0n/binNumber;
  hf_avgMag_0n0n=hf_avgMag_0n0n/binNumber;
  trkUp_avgMag_R2=trkUp_avgMag_R2/binNumber, trkDown_avgMag_R2=trkDown_avgMag_R2/binNumber;
  hf_avgMag_R2=hf_avgMag_R2/binNumber;
  trkUp_avgMag_R6=trkUp_avgMag_R6/binNumber, trkDown_avgMag_R6=trkDown_avgMag_R6/binNumber;
  hf_avgMag_R6=hf_avgMag_R6/binNumber;
  it_avgMag=it_avgMag/binNumber, it_avgMag_R2=it_avgMag_R2/binNumber, it_avgMag_R6=it_avgMag_R6/binNumber;
  it_avgMag_0n0n=it_avgMag_0n0n/binNumber;
  float trk_total_avgMag=(trkUp_avgMag+trkDown_avgMag)/2;
  float trk_total_avgMag_0n0n=(trkUp_avgMag_0n0n+trkDown_avgMag_0n0n)/2;
  float trk_total_avgMag_R2=(trkUp_avgMag_R2+trkDown_avgMag_R2)/2;
  float trk_total_avgMag_R6=(trkUp_avgMag_R6+trkDown_avgMag_R6)/2;
  float rap_total=sqrt(hf_avgMag*hf_avgMag+trk_total_avgMag*trk_total_avgMag);
  float rap_total_0n0n=sqrt(hf_avgMag_0n0n*hf_avgMag_0n0n+trk_total_avgMag_0n0n*trk_total_avgMag_0n0n);
  float rap_total_R2=sqrt(hf_avgMag_R2*hf_avgMag_R2+trk_total_avgMag_R2*trk_total_avgMag_R2);
  float rap_total_R6=sqrt(hf_avgMag_R6*hf_avgMag_R6+trk_total_avgMag_R6*trk_total_avgMag_R6);
  float jes_total_avgMag=(jesUp_avgMag+jesDown_avgMag)/2, jer_total_avgMag=(jerUp_avgMag+jerDown_avgMag)/2;
  float jes_total_avgMag_0n0n=(jesUp_avgMag_0n0n+jesDown_avgMag_0n0n)/2, jer_total_avgMag_0n0n=(jerUp_avgMag_0n0n+jerDown_avgMag_0n0n)/2;
  total_sys=sqrt((it_avgMag*it_avgMag+jar_avgMag*jar_avgMag+jes_total_avgMag*jes_total_avgMag+jer_total_avgMag*jer_total_avgMag+mcStats_avgMag_R4*mcStats_avgMag_R4/2+prior_avgMag_R4*prior_avgMag_R4+rap_total*rap_total)), total_sys_R2=sqrt((it_avgMag_R2*it_avgMag_R2+jar_avgMag_R2*jar_avgMag_R2+jes_total_avgMag*jes_total_avgMag+jer_total_avgMag*jer_total_avgMag+mcStats_avgMag_R2*mcStats_avgMag_R2/2+prior_avgMag_R2*prior_avgMag_R2+rap_total_R2*rap_total_R2)), total_sys_R6=sqrt((it_avgMag_R6*it_avgMag_R6+jar_avgMag_R6*jar_avgMag+jes_total_avgMag*jes_total_avgMag+jer_total_avgMag*jer_total_avgMag+mcStats_avgMag_R6*mcStats_avgMag_R6/2+prior_avgMag_R6*prior_avgMag_R6+rap_total_R6*rap_total_R6));
  total_sys_0n0n=sqrt((it_avgMag_0n0n*it_avgMag_0n0n+jar_avgMag_0n0n*jar_avgMag_0n0n+jes_total_avgMag_0n0n*jes_total_avgMag_0n0n+jer_total_avgMag_0n0n*jer_total_avgMag_0n0n+mcStats_avgMag_0n0n*mcStats_avgMag_0n0n/2+prior_avgMag_R4*prior_avgMag_R4+rap_total_0n0n*rap_total_0n0n));

  // print off some systematics info
  cout << "prior_avgMag_R2=" << prior_avgMag_R2 << endl;
  cout << "prior_avgMag_R4=" << prior_avgMag_R4 << endl;
  cout << "prior_avgMag_R6=" << prior_avgMag_R6 << endl;
  cout << "mcStats_avgMag_R2=" << mcStats_avgMag_R2 << endl;
  cout << "mcStats_avgMag_R4=" << mcStats_avgMag_R4 << endl;
  cout << "mcStats_avgMag_R6=" << mcStats_avgMag_R6 << endl;
  cout << "it avgMag_R2 = " << it_avgMag_R2 << endl;
  cout << "it avgMag = " << it_avgMag << endl;
  cout << "it avgMag_R6 = " << it_avgMag_R6 << endl;
  cout << "jar_avgMag=" << jar_avgMag_R2 << " and totalR2=" << total_sys_R2 << endl;
  cout << "jar_avgMag=" << jar_avgMag << " and totalR4=" << total_sys << endl;
  cout << "jar_avgMag_0n0n=" << jar_avgMag_0n0n << " and totalR4 0n0n=" << total_sys_0n0n << endl;
  cout << "jar_avgMag=" << jar_avgMag_R6 << " and totalR6=" << total_sys_R6 << endl;


  // plots to compare r4 with r4 0n0n
  makeNiceResidual_systematics_0n0n(v2_unf_R4_orig, v2_unf_R4_0n0n_orig, "Q_{T} [GeV]", "<cos(2#phi)>", "r=0.4, 0nXn", "r=0.4, 0n0n", "Pics/v2_unf_r4_0n0n_orig.png","0nXn - 0n0n",total_sys,total_sys_0n0n,-0.2,1.0);
  makeNiceResidual_systematics_0n0n(v2_unf_R6_orig, v2_unf_R6_0n0n_orig, "Q_{T} [GeV]", "<cos(2#phi)>", "r=0.6, 0nXn", "r=0.6, 0n0n", "Pics/v2_unf_r6_0n0n_orig.png","0nXn - 0n0n",total_sys_R6,total_sys_R6,-0.2,1.0);
  makeNiceResidual_systematics_0n0n(v2_unf_R4_cut, v2_unf_R4_0n0n_cut, "Q_{T} [GeV]", "<cos(2#phi)>", "r=0.4, 0nXn", "r=0.4, 0n0n", "Pics/v2_unf_r4_0n0n_cut_syst.png","0nXn - 0n0n",total_sys,total_sys_0n0n,-0.2,1.0);
  makeNiceResidual_systematics_0n0n(v2_unf_R4_ac, v2_unf_R4_0n0n_ac, "Q_{T} [GeV]", "#LTcos(2#phi)#GT", "R = 0.4, 0nXn", "R = 0.4, 0n0n", "Pics/v2_unf_r4_0n0n_syst.pdf","0nXn #minus 0n0n",total_sys,total_sys_0n0n,0,0.825);
  cout << "total_sys_0n0n=" << total_sys_0n0n << endl;
  cout << "0.037/total_sys_0n0n=" << 0.037/total_sys_0n0n << endl;
  makeNiceResidual_systematics_0n0n(v2_unf_R4_ac, v2_unf_R4_0n0n_gg_ac, "Q_{T} [GeV]", "<cos(2#phi)>", "0nXn unf with Pythia:gq->qq (MC1)", "0n0n unfolded with Pythia:gg->qq (MC2)", "Pics/v2_unf_r4_0n0n_0nXn_syst.png","0nXn - 0n0n",total_sys,total_sys_0n0n,-0.1,0.75);

  // compare data unfolded with 2 MC's
  makeNiceResidual_systematics_0n0n(v2_unf_R4_0n0n_ac, v2_unf_R4_0n0n_gg_ac, "Q_{T} [GeV]", "<cos(2#phi)>", "Data unfolded, Pythia: #gammag->q#bar{q} (MC1)", "Data unfolded, Pythia: #gamma#gamma->q#bar{q} (MC2)", "Pics/unf_compareMC.png","MC1 - MC2",total_sys_0n0n,total_sys_0n0n,-0.15,1.0);

  // compare r4 with r4 noZDC
  makeNiceResidual_systematics_0n0n(v2_unf_R4, v2_unf_R4_noZDC, "Q_{T} [GeV]", "<cos(2#phi)>", "Unfolded Result, r=0.4", "Unfolded Result, r=0.4, noZDC", "Pics/v2_unf_r4_noZDC_syst.png","0nXn - 0n0n",total_sys,total_sys_0n0n,0,1.0);
  
  
  // make final r2 results plot with systematics
  makeNiceResidual_systematics(v2_unf_R2, v2_gen_R2, "Q_{T} [GeV]", "<cos(2#phi)>", "Unfolded Result, r = 0.2", "Gen Pythia, r = 0.2", "Pics/v2_unf_r2_gen_syst.png",total_sys_R2,0,0.7);

  // make final r4 results plot with systematics
  makeNiceResidual_systematics(v2_unf_R4_ac, v2_gen_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Unfolded data, r = 0.4", "Gen Pythia, r = 0.4", "Pics/v2_unf_r4_gen_syst.png",total_sys,0,0.7);
  // raw
  makeNiceResidual_systematics(v2_unf_R4_orig, v2_gen_R4, "Q_{T} [GeV]", "<cos(2#phi)>", "Raw data, r = 0.4", "Gen Pythia, r = 0.4", "Pics/v2_raw_r4_gen_syst.png",total_sys,0,0.7);
  

  // make final r6 results plot with systematics
  makeNiceResidual_systematics(v2_unf_R6, v2_gen_R6, "Q_{T} [GeV]", "<cos(2#phi)>", "Unfolded Result, r=0.6", "Gen Pythia, r = 0.6", "Pics/v2_unf_r6_gen_syst.png",total_sys_R6,-0.1,0.7);
  

  
  // make final result plot with systematics
  pad2_3(v2_unf_R2_cut, v2_unf_R4_cut, v2_unf_R6_cut, v2_gen_R2_cut, v2_gen_R4_cut, v2_gen_R6_cut, "Q_{T} [GeV]", "<cos(2#phi)>", "Data", "Pythia8", "Pics/v2_unf_twoPanel_cut_sys.png", total_sys_R2, total_sys, total_sys_R6,-0.08,0.72);
  pad2_3(v2_unf_R2_ac, v2_unf_R4_ac, v2_unf_R6_ac, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]", "#LTcos(2#phi)#GT", "Data", "Pythia8", "Pics/v2_unf_twoPanel_sys.pdf", total_sys_R2, total_sys, total_sys_R6,-0.125,0.72);

  // make row systematics 3 panel
  pad3_2(v2_unf_R2_cut, v2_unf_R4_cut, v2_unf_R6_cut, v2_gen_R2_cut, v2_gen_R4_cut, v2_gen_R6_cut, "Q_{T} [GeV]                  ", "<cos(2#phi)>", "Data", "Pythia8", "Pics/v2_unf_threePanel_cut_sys.png", total_sys_R2, total_sys, total_sys_R6,-0.1,0.9);
  pad3_2(v2_unf_R2_orig, v2_unf_R4_orig, v2_unf_R6_orig, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]                  ", "<cos(2#phi)>", "Raw Data", "Pythia8", "Pics/v2_unf_threePanel_orig.png", total_sys_R2, total_sys, total_sys_R6,-0.1,0.9);
  pad3_2(v2_unf_R2, v2_unf_R4, v2_unf_R6, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]                  ", "<cos(2#phi)>", "Data", "Pythia8", "Pics/v2_unf_threePanel_sys_noAC.png", total_sys_R2, total_sys, total_sys_R6,-0.1,0.9);
  pad3_2(v2_unf_R2_ac, v2_unf_R4_ac, v2_unf_R6_ac, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]                  ", "<cos(2#phi)>", "Data", "Pythia8", "Pics/v2_unf_threePanel_sys.pdf", total_sys_R2, total_sys, total_sys_R6,-0.1,0.95);



  // add theory lines
  TFile *fileTheory = new TFile("theoryComparison/theoryGraphs.root");
  TGraph *gr_r2 = (TGraph*)fileTheory->Get("gr_r2");
  TGraph *gr_r4 = (TGraph*)fileTheory->Get("gr_r4");
  TGraph *gr_r6 = (TGraph*)fileTheory->Get("gr_r6");
  TGraph *gr_r2_new = (TGraph*)fileTheory->Get("gr_r2_new");
  TGraph *gr_r4_new = (TGraph*)fileTheory->Get("gr_r4_new");
  TGraph *gr_r6_new = (TGraph*)fileTheory->Get("gr_r6_new");
  TGraph *gr_r2_v4 = (TGraph*)fileTheory->Get("gr_r2_v4");
  TGraph *gr_r4_v4 = (TGraph*)fileTheory->Get("gr_r4_v4");
  TGraph *gr_r6_v4 = (TGraph*)fileTheory->Get("gr_r6_v4");
  gr_r2->SetLineColor(kBlue);
  gr_r4->SetLineColor(kBlue);
  gr_r6->SetLineColor(kBlue);
  gr_r2->SetLineWidth(2);
  gr_r4->SetLineWidth(2);
  gr_r6->SetLineWidth(2);
  gr_r2_new->SetLineColor(kBlue);
  gr_r4_new->SetLineColor(kBlue);
  gr_r6_new->SetLineColor(kBlue);
  gr_r2_new->SetLineWidth(2);
  gr_r4_new->SetLineWidth(2);
  gr_r6_new->SetLineWidth(2);

  // plot
  pad3_2_theory(gr_r2, gr_r4, gr_r6, "theory 2021", v2_unf_R2_ac, v2_unf_R4_ac, v2_unf_R6_ac, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]                  ", "#LTcos(2#phi)#GT", "Data", "Pythia8", "Pics/v2_2021_theory.png", total_sys_R2, total_sys, total_sys_R6,-0.1,0.9);
  // plot newer
  pad3_2_theory(gr_r2_new, gr_r4_new, gr_r6_new, "theory 2024", v2_unf_R2_ac, v2_unf_R4_ac, v2_unf_R6_ac, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]                  ", "<cos(2#phi)>", "Data", "Pythia8", "Pics/v2_2024_theory.png", total_sys_R2, total_sys, total_sys_R6,-0.1,0.9);
  // plot both theories
  pad3_2_theories(gr_r2, gr_r4, gr_r6, gr_r2_new, gr_r4_new, gr_r6_new, "Hatta et al.", "Shao et al.", v2_unf_R2_ac, v2_unf_R4_ac, v2_unf_R6_ac, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]                  ", "#LTcos(2#phi)#GT", "Data, 0nXn", "Pythia8", "Pics/v2_theories.pdf", total_sys_R2, total_sys, total_sys_R6,-0.125,0.90);

  // zoomed in plots
  pad3_2_theoryZoomed(gr_r2, gr_r4, gr_r6, "theory 2021", v2_unf_R2_ac, v2_unf_R4_ac, v2_unf_R6_ac, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]                  ", "<cos(2#phi)>", "Data", "Pythia8", "Pics/v2_2021_theoryZoomed.png", total_sys_R2, total_sys, total_sys_R6,-0.1,0.9);
  // plot newer
  pad3_2_theoryZoomed(gr_r2_new, gr_r4_new, gr_r6_new, "theory 2024", v2_unf_R2_ac, v2_unf_R4_ac, v2_unf_R6_ac, v2_gen_R2, v2_gen_R4, v2_gen_R6, "Q_{T} [GeV]                  ", "<cos(2#phi)>", "Data", "Pythia8", "Pics/v2_2024_theoryZoomed.png", total_sys_R2, total_sys, total_sys_R6,-0.1,0.9);



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
  c3->SaveAs("Pics/systematics_radius_v2.pdf");



  
  // draw response slice
  auto *c1 = new TCanvas("c1", "c1",900,900);
  c1->SetRightMargin(0.14);
  h2_response_slice->SetStats(0);
  h2_response_slice->SetTitle(";Reco #phi [radians];Gen #phi [radians]");
  h2_response_slice->Draw("colz");
  c1->SaveAs("responseSlice_phi.png");

  // draw misses
  auto *c2 = new TCanvas("c2", "c2",900,900);
  c2->SetRightMargin(0.14);
  h2_miss_r4->SetStats(0);
  h2_miss_r4->SetTitle(";Q_{T} [GeV];#phi [radians]");
  h2_miss_r4->Draw("colz");
  c2->SaveAs("Pics/misses_r4.png");
  auto *c5 = new TCanvas("c5", "c5",900,900);
  c5->SetRightMargin(0.14);
  h2_miss_r2->SetStats(0);
  h2_miss_r2->SetTitle(";Q_{T} [GeV];#phi [radians]");
  h2_miss_r2->Draw("colz");
  c5->SaveAs("Pics/misses_r2.png");
  auto *c4 = new TCanvas("c4", "c4",900,900);
  c4->SetRightMargin(0.14);
  h2_miss_r6->SetStats(0);
  h2_miss_r6->SetTitle(";Q_{T} [GeV];#phi [radians]");
  h2_miss_r6->Draw("colz");
  c4->SaveAs("Pics/misses_r6.png");

  // write out unfolded 0n0n and 0nXn results
  TFile *file = new TFile("finalResults.root","recreate");
  v2_jar_R4->Write("v2_jar_R4");
  v2_unf_R4->Write("v2_unf_R4");
  v2_unf_R4_0n0n->Write("v2_unf_R4_0n0n");
  v2_unf_R4_noZDC->Write("v2_unf_R4_noZDC");
  file->Write();


  


  

 
}
