// compareSystematics.C (rapidity)
// This code:
// -calculates systematics and adds them in quadrature
// -makes systematics plots for the analysis note
// -makes result plots for v2=<cos(2phi)> vs rapidity and v4=<cos(4phi)> vs rapidity

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
#include "nicePlotting.h"
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
  
  //  TH1F *h_residual = new TH1F(*makeResidual_histogram(h1,h2));
  TH1F *h_residual = (TH1F*)h1->Clone("h_residual");
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



void compareSystematics()
{
  // Read Files
  TFile *fileGen_rap0 = new TFile("Files/gen_v2_rap0.root");
  TFile *fileGen_rap1 = new TFile("Files/gen_v2_rap1.root");
  TFile *fileGen_rap0_cut = new TFile("Files/gen_v2_rap0_cut.root");
  TFile *fileGen_rap1_cut = new TFile("Files/gen_v2_rap1_cut.root");
  TFile *fileUnf_rap0 = new TFile("Files/unf_r4_v2_rap0.root");
  TFile *fileUnf_rap1 = new TFile("Files/unf_r4_v2_rap1.root");
  TFile *fileUnf_rap0_ac = new TFile("Files/unf_r4_v2_rap0_ac.root");
  TFile *fileUnf_rap1_ac = new TFile("Files/unf_r4_v2_rap1_ac.root");
  TFile *fileUnf_rap0_orig = new TFile("Files/unf_r4_v2_orig_rap0.root");
  TFile *fileUnf_rap1_orig = new TFile("Files/unf_r4_v2_orig_rap1.root");
  TFile *fileUnf_rap0_cut = new TFile("Files/unf_r4_v2_rap0_cut.root");
  TFile *fileUnf_rap1_cut = new TFile("Files/unf_r4_v2_rap1_cut.root");
  TFile *fileJESup_rap0 = new TFile("Files/JESup_v2_rap0.root");
  TFile *fileJESup_rap1 = new TFile("Files/JESup_v2_rap1.root");
  TFile *fileJESnom_rap0 = new TFile("Files/JESnom_v2_rap0.root");
  TFile *fileJESnom_rap1 = new TFile("Files/JESnom_v2_rap1.root");
  TFile *fileJESdown_rap0 = new TFile("Files/JESdown_v2_rap0.root");
  TFile *fileJESdown_rap1 = new TFile("Files/JESdown_v2_rap1.root");
  TFile *fileJERup_rap0 = new TFile("Files/JERup_v2_rap0.root");
  TFile *fileJERup_rap1 = new TFile("Files/JERup_v2_rap1.root");
  TFile *fileJERnom_rap0 = new TFile("Files/JERnom_v2_rap0.root");
  TFile *fileJERnom_rap1 = new TFile("Files/JERnom_v2_rap1.root");
  TFile *fileJERdown_rap0 = new TFile("Files/JERdown_v2_rap0.root");
  TFile *fileJERdown_rap1 = new TFile("Files/JERdown_v2_rap1.root");
  TFile *fileJAR_rap0 = new TFile("Files/JAR_v2_rap0.root");
  TFile *fileJAR_rap1 = new TFile("Files/JAR_v2_rap1.root");
  TFile *fileJER = new TFile("Files/JER_v2.root");
  TFile *filePrior_rap0 = new TFile("Files/prior_v2_rap0.root");
  TFile *filePrior_rap1 = new TFile("Files/prior_v2_rap1.root");
  TFile *filemcStat1_rap0 = new TFile("Files/mcStat1_v2_rap0.root");
  TFile *filemcStat2_rap0 = new TFile("Files/mcStat2_v2_rap0.root");
  TFile *filemcStat1_rap1 = new TFile("Files/mcStat1_v2_rap1.root");
  TFile *filemcStat2_rap1 = new TFile("Files/mcStat2_v2_rap1.root");
  TFile *fileRapUp_rap0 = new TFile("Files/v2_rapUp_rap0.root");
  TFile *fileRapDown_rap0 = new TFile("Files/v2_rapDown_rap0.root");
  TFile *fileRapUp_rap1 = new TFile("Files/v2_rapUp_rap1.root");
  TFile *fileRapDown_rap1 = new TFile("Files/v2_rapDown_rap1.root");
  TFile *fileHF_rap0 = new TFile("Files/v2_hf_rap0.root");
  TFile *fileHF_rap1 = new TFile("Files/v2_hf_rap1.root");
  TFile *fileIt2_rap0 = new TFile("Files/v2_It2_rap0.root");
  TFile *fileIt3_rap0 = new TFile("Files/v2_It3_rap0.root");
  TFile *fileIt2_rap1 = new TFile("Files/v2_It2_rap1.root");
  TFile *fileIt3_rap1 = new TFile("Files/v2_It3_rap1.root");
  // 2D distributions (misses)
  TFile *file2D_rap0 = new TFile("unfolded2D_phiRapidity_full_rap0_ac.root");
  TFile *file2D_rap1 = new TFile("unfolded2D_phiRapidity_full_rap1_ac.root");
  // misses
  TH1F *h2_misses_rap0 = (TH1F*)file2D_rap0->Get("h2_miss");
  TH1F *h2_misses_rap1 = (TH1F*)file2D_rap1->Get("h2_miss");

  // v2
  TH1F *v2_gen_0 = (TH1F*)fileGen_rap0->Get("h_v2_qt0");
  TH1F *v2_gen_1 = (TH1F*)fileGen_rap1->Get("h_v2_qt1");
  TH1F *v2_gen_0_cut = (TH1F*)fileGen_rap0_cut->Get("h_v2_qt0");
  TH1F *v2_gen_1_cut = (TH1F*)fileGen_rap1_cut->Get("h_v2_qt1");
  TH1F *v2_unf_0 = (TH1F*)fileUnf_rap0->Get("h_v2_qt0");
  TH1F *v2_unf_1 = (TH1F*)fileUnf_rap1->Get("h_v2_qt1");
  TH1F *v2_unf_0_ac = (TH1F*)fileUnf_rap0_ac->Get("h_v2_qt0");
  TH1F *v2_unf_1_ac = (TH1F*)fileUnf_rap1_ac->Get("h_v2_qt1");
  TH1F *v2_unf_orig_0 = (TH1F*)fileUnf_rap0_orig->Get("h_v2_qt0");
  TH1F *v2_unf_orig_1 = (TH1F*)fileUnf_rap1_orig->Get("h_v2_qt1");
  TH1F *v2_unf_0_cut = (TH1F*)fileUnf_rap0_cut->Get("h_v2_qt0");
  TH1F *v2_unf_1_cut = (TH1F*)fileUnf_rap1_cut->Get("h_v2_qt1");
  TH1F *v2_jesUp_0 = (TH1F*)fileJESup_rap0->Get("h_v2_qt0");
  TH1F *v2_jesUp_1 = (TH1F*)fileJESup_rap1->Get("h_v2_qt1");
  TH1F *v2_jesNom_0 = (TH1F*)fileJESnom_rap0->Get("h_v2_qt0");
  TH1F *v2_jesNom_1 = (TH1F*)fileJESnom_rap1->Get("h_v2_qt1");
  TH1F *v2_jesDown_0 = (TH1F*)fileJESdown_rap0->Get("h_v2_qt0");
  TH1F *v2_jesDown_1 = (TH1F*)fileJESdown_rap1->Get("h_v2_qt1");
  TH1F *v2_jerUp_0 = (TH1F*)fileJERup_rap0->Get("h_v2_qt0");
  TH1F *v2_jerUp_1 = (TH1F*)fileJERup_rap1->Get("h_v2_qt1");
  TH1F *v2_jerNom_0 = (TH1F*)fileJERnom_rap0->Get("h_v2_qt0");
  TH1F *v2_jerNom_1 = (TH1F*)fileJERnom_rap1->Get("h_v2_qt1");
  TH1F *v2_jerDown_0 = (TH1F*)fileJERdown_rap0->Get("h_v2_qt0");
  TH1F *v2_jerDown_1 = (TH1F*)fileJERdown_rap1->Get("h_v2_qt1");
  TH1F *v2_jar_0 = (TH1F*)fileJAR_rap0->Get("h_v2_qt0");
  TH1F *v2_jar_1 = (TH1F*)fileJAR_rap1->Get("h_v2_qt1");
  TH1F *v2_jer_0 = (TH1F*)fileJER->Get("h_v2_qt0");
  TH1F *v2_jer_1 = (TH1F*)fileJER->Get("h_v2_qt1");
  TH1F *v2_prior_0 = (TH1F*)filePrior_rap0->Get("h_v2_qt0");
  TH1F *v2_prior_1 = (TH1F*)filePrior_rap1->Get("h_v2_qt1");
  TH1F *v2_mcStat1_0 = (TH1F*)filemcStat1_rap0->Get("h_v2_qt0");
  TH1F *v2_mcStat2_0 = (TH1F*)filemcStat2_rap0->Get("h_v2_qt0");
  TH1F *v2_mcStat1_1 = (TH1F*)filemcStat1_rap1->Get("h_v2_qt1");
  TH1F *v2_mcStat2_1 = (TH1F*)filemcStat2_rap1->Get("h_v2_qt1");
  TH1F *v2_rapup_0 = (TH1F*)fileRapUp_rap0->Get("h_v2_qt0");
  TH1F *v2_rapdown_0 = (TH1F*)fileRapDown_rap0->Get("h_v2_qt0");
  TH1F *v2_rapup_1 = (TH1F*)fileRapUp_rap1->Get("h_v2_qt1");
  TH1F *v2_rapdown_1 = (TH1F*)fileRapDown_rap1->Get("h_v2_qt1");
  TH1F *v2_hf_0 = (TH1F*)fileHF_rap0->Get("h_v2_qt0");
  TH1F *v2_hf_1 = (TH1F*)fileHF_rap1->Get("h_v2_qt1");
  TH1F *v2_It2_0 = (TH1F*)fileIt2_rap0->Get("h_v2_qt0");
  TH1F *v2_It3_0 = (TH1F*)fileIt3_rap0->Get("h_v2_qt0");
  TH1F *v2_It2_1 = (TH1F*)fileIt2_rap1->Get("h_v2_qt1");
  TH1F *v2_It3_1 = (TH1F*)fileIt3_rap1->Get("h_v2_qt1");
 

  // v4
  TH1F *v4_gen_0 = (TH1F*)fileGen_rap0->Get("h_v4_qt0");
  TH1F *v4_gen_1 = (TH1F*)fileGen_rap1->Get("h_v4_qt1");
  TH1F *v4_unf_0 = (TH1F*)fileUnf_rap0->Get("h_v4_qt0");
  TH1F *v4_unf_1 = (TH1F*)fileUnf_rap1->Get("h_v4_qt1");
  TH1F *v4_unf_0_ac = (TH1F*)fileUnf_rap0_ac->Get("h_v4_qt0");
  TH1F *v4_unf_1_ac = (TH1F*)fileUnf_rap1_ac->Get("h_v4_qt1");
  TH1F *v4_jesUp_0 = (TH1F*)fileJESup_rap0->Get("h_v4_qt0");
  TH1F *v4_jesUp_1 = (TH1F*)fileJESup_rap1->Get("h_v4_qt1");
  TH1F *v4_jesDown_0 = (TH1F*)fileJESdown_rap0->Get("h_v4_qt0");
  TH1F *v4_jesDown_1 = (TH1F*)fileJESdown_rap1->Get("h_v4_qt1");
  TH1F *v4_jerUp_0 = (TH1F*)fileJERup_rap0->Get("h_v4_qt0");
  TH1F *v4_jerUp_1 = (TH1F*)fileJERup_rap1->Get("h_v4_qt1");
  TH1F *v4_jerDown_0 = (TH1F*)fileJERdown_rap0->Get("h_v4_qt0");
  TH1F *v4_jerDown_1 = (TH1F*)fileJERdown_rap1->Get("h_v4_qt1");
  TH1F *v4_jar_0 = (TH1F*)fileJAR_rap0->Get("h_v4_qt0");
  TH1F *v4_jar_1 = (TH1F*)fileJAR_rap1->Get("h_v4_qt1");
  TH1F *v4_jer_0 = (TH1F*)fileJER->Get("h_v4_qt0");
  TH1F *v4_jer_1 = (TH1F*)fileJER->Get("h_v4_qt1");
  TH1F *v4_prior_0 = (TH1F*)filePrior_rap0->Get("h_v4_qt0");
  TH1F *v4_prior_1 = (TH1F*)filePrior_rap1->Get("h_v4_qt1");
  TH1F *v4_mcStat1_0 = (TH1F*)filemcStat1_rap0->Get("h_v4_qt0");
  TH1F *v4_mcStat2_0 = (TH1F*)filemcStat2_rap0->Get("h_v4_qt0");
  TH1F *v4_mcStat1_1 = (TH1F*)filemcStat1_rap1->Get("h_v4_qt1");
  TH1F *v4_mcStat2_1 = (TH1F*)filemcStat2_rap1->Get("h_v4_qt1");
  TH1F *v4_rapup_0 = (TH1F*)fileRapUp_rap0->Get("h_v4_qt0");
  TH1F *v4_rapdown_0 = (TH1F*)fileRapDown_rap0->Get("h_v4_qt0");
  TH1F *v4_rapup_1 = (TH1F*)fileRapUp_rap1->Get("h_v4_qt1");
  TH1F *v4_rapdown_1 = (TH1F*)fileRapDown_rap1->Get("h_v4_qt1");
  TH1F *v4_hf_0 = (TH1F*)fileHF_rap0->Get("h_v4_qt0");
  TH1F *v4_hf_1 = (TH1F*)fileHF_rap1->Get("h_v4_qt1");
  TH1F *v4_It2_0 = (TH1F*)fileIt2_rap0->Get("h_v4_qt0");
  TH1F *v4_It3_0 = (TH1F*)fileIt3_rap0->Get("h_v4_qt0");
  TH1F *v4_It2_1 = (TH1F*)fileIt2_rap1->Get("h_v4_qt1");
  TH1F *v4_It3_1 = (TH1F*)fileIt3_rap1->Get("h_v4_qt1");


  // Systematics Plots
  // JES up
  makeNiceResidual_syst(v2_jesNom_0, v2_jesUp_0, "y'", "<cos(2#phi)>", "Nominal Result", "JES up Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_jesUp_qt0.png",-0.05,0.45);
  makeNiceResidual_syst(v2_jesNom_1, v2_jesUp_1, "y'", "<cos(2#phi)>", "Nominal Result", "JES up Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_jesUp_qt1.png",-0.05,0.45);
  // JES down
  makeNiceResidual_syst(v2_jesNom_0, v2_jesDown_0, "y'", "<cos(2#phi)>", "Nominal Result", "JES down Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_jesDown_qt0.png",-0.05,0.45);
  makeNiceResidual_syst(v2_jesNom_1, v2_jesDown_1, "y'", "<cos(2#phi)>", "Nominal Result", "JES Down Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_jesDown_qt1.png",-0.05,0.45);
   // JER up
  makeNiceResidual_syst(v2_jerNom_0, v2_jerUp_0, "y'", "<cos(2#phi)>", "Nominal Result", "JER up Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_jerUp_qt0.png",-0.1,0.45);
  makeNiceResidual_syst(v2_jerNom_1, v2_jerUp_1, "y'", "<cos(2#phi)>", "Nominal Result", "JER up Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_jerUp_qt1.png",-0.1,0.45);
  // JER down
  makeNiceResidual_syst(v2_jerNom_0, v2_jerDown_0, "y'", "<cos(2#phi)>", "Nominal Result", "JER down Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_jerDown_qt0.png",-0.1,0.45);
  makeNiceResidual_syst(v2_jerNom_1, v2_jerDown_1, "y'", "<cos(2#phi)>", "Nominal Result", "JER Down Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_jerDown_qt1.png",-0.1,0.45);
  // JAR
  makeNiceResidual_syst(v2_unf_0, v2_jar_0, "y'", "<cos(2#phi)>", "Nominal Result", "JAR Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_jar_qt0.png",0,0.45);
  makeNiceResidual_syst(v2_unf_1, v2_jar_1, "y'", "<cos(2#phi)>", "Nominal Result", "JAR Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_jar_qt1.png",0,0.45);
  // PRIOR
  makeNiceResidual_syst(v2_unf_0, v2_prior_0, "y'", "<cos(2#phi)>", "Nominal Result", "Prior Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_prior_qt0.png",-0.1,0.45);
  makeNiceResidual_syst(v2_unf_1, v2_prior_1, "y'", "<cos(2#phi)>", "Nominal Result", "Prior Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_prior_qt1.png",-0.5,0.9);
  // MC STATS
  makeNiceResidual_syst(v2_mcStat1_0, v2_mcStat2_0, "y'", "<cos(2#phi)>", "Data unfolded MC half 1", "Data unfolded MC half 2","0 GeV < Q_{T} < 12 GeV", "Pics/unf_mcStats_qt0.png",0,0.45);
  makeNiceResidual_syst(v2_mcStat1_1, v2_mcStat2_1, "y'", "<cos(2#phi)>", "Data unfolded MC half 1", "Data unfolded MC half 2","12 GeV < Q_{T} < 40 GeV", "Pics/unf_mcStats_qt1.png",-0.1,0.45);
  // RAP up
  makeNiceResidual_syst(v2_unf_0, v2_rapup_0, "y'", "<cos(2#phi)>", "Nominal Result", "Rap Up Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_rapup_qt0.png",0,0.45);
  makeNiceResidual_syst(v2_unf_1, v2_rapup_1, "y'", "<cos(2#phi)>", "Nominal Result", "Rap Up Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_rapup_qt1.png",0,0.45);
  // RAP down
  makeNiceResidual_syst(v2_unf_0, v2_rapdown_0, "y'", "<cos(2#phi)>", "Nominal Result", "Rap Down Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_rapdown_qt0.png",0,0.45);
  makeNiceResidual_syst(v2_unf_1, v2_rapdown_1, "y'", "<cos(2#phi)>", "Nominal Result", "Rap Down Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_rapdown_qt1.png",0,0.45);
  // HF
  makeNiceResidual_syst(v2_unf_0, v2_hf_0, "y'", "<cos(2#phi)>", "Nominal Result", "HF Result","0 GeV < Q_{T} < 12 GeV", "Pics/unf_hf_qt0.png",0,0.45);
  makeNiceResidual_syst(v2_unf_1, v2_hf_1, "y'", "<cos(2#phi)>", "Nominal Result", "HF Result","12 GeV < Q_{T} < 40 GeV", "Pics/unf_hf_qt1.png",0,0.45);
  

  // v4 Systematics Plots
  // JAR
  makeNiceResidual_syst(v4_unf_0, v4_jar_0, "y'", "<cos(4#phi)>", "Nominal Result", "JAR Result","0 GeV < Q_{T} < 12 GeV", "Pics/v4_unf_jar_qt0.png",-0.2,0.2);
  makeNiceResidual_syst(v4_unf_1, v4_jar_1, "y'", "<cos(4#phi)>", "Nominal Result", "JAR Result","12 GeV < Q_{T} < 40 GeV", "Pics/v4_unf_jar_qt1.png",-0.2,0.2);
  // JER
  makeNiceResidual_syst(v4_unf_0, v4_jer_0, "y'", "<cos(4#phi)>", "Nominal Result", "JER Result","0 GeV < Q_{T} < 12 GeV", "Pics/v4_unf_jer_qt0.png",-0.2,0.2);
  makeNiceResidual_syst(v4_unf_1, v4_jer_1, "y'", "<cos(4#phi)>", "Nominal Result", "JER Result","12 GeV < Q_{T} < 40 GeV", "Pics/v4_unf_jer_qt1.png",-0.2,0.2);


  // text files to store systematics for each bin
  // v2
  ofstream outfile_jes_0("textFiles/jes_rapdiff_0.txt"), outfile_jar_0("textFiles/jar_rapdiff_0.txt"), outfile_jer_0("textFiles/jer_rapdiff_0.txt"), outfile_mcStats_0("textFiles/mcStats_rapdiff_0.txt"), outfile_prior_0("textFiles/prior_rapdiff_0.txt"), outfile_hf_0("textFiles/hf_rapdiff_0.txt"), outfile_trk_0("textFiles/trk_rapdiff_0.txt"), outfile_it_0("textFiles/it_rapdiff_0.txt");
  ofstream outfile_jes_1("textFiles/jes_rapdiff_1.txt"), outfile_jar_1("textFiles/jar_rapdiff_1.txt"), outfile_jer_1("textFiles/jer_rapdiff_1.txt"), outfile_mcStats_1("textFiles/mcStats_rapdiff_1.txt"), outfile_prior_1("textFiles/prior_rapdiff_1.txt"), outfile_hf_1("textFiles/hf_rapdiff_1.txt"), outfile_trk_1("textFiles/trk_rapdiff_1.txt"), outfile_it_1("textFiles/it_rapdiff_1.txt");
  // v4
  ofstream v4file_jes_0("textFiles/v4_jes_rapdiff_0.txt"), v4file_jar_0("textFiles/v4_jar_rapdiff_0.txt"), v4file_jer_0("textFiles/v4_jer_rapdiff_0.txt"), v4file_mcStats_0("textFiles/v4_mcStats_rapdiff_0.txt"), v4file_prior_0("textFiles/v4_prior_rapdiff_0.txt"), v4file_hf_0("textFiles/v4_hf_rapdiff_0.txt"), v4file_trk_0("textFiles/v4_trk_rapdiff_0.txt"),  v4file_it_0("textFiles/v4_it_rapdiff_0.txt");
  ofstream v4file_jes_1("textFiles/v4_jes_rapdiff_1.txt"), v4file_jar_1("textFiles/v4_jar_rapdiff_1.txt"), v4file_jer_1("textFiles/v4_jer_rapdiff_1.txt"), v4file_mcStats_1("textFiles/v4_mcStats_rapdiff_1.txt"), v4file_prior_1("textFiles/v4_prior_rapdiff_1.txt"), v4file_hf_1("textFiles/v4_hf_rapdiff_1.txt"), v4file_trk_1("textFiles/v4_trk_rapdiff_1.txt"), v4file_it_1("textFiles/v4_it_rapdiff_1.txt");

  // loop through histogram bins
  // v2
  float raw_content_0=0, unf_content_0=0, nomJES_content_0, nomJER_content_0=0, jesUp_content_0=0, jesDown_content_0=0,jerUp_content_0=0, jerDown_content_0=0, jar_content_0=0, jer_content_0=0, hf_content_0=0, trkUp_content_0=0, trkDown_content_0=0;
  float raw_content_1=0, unf_content_1=0, nomJES_content_1, nomJER_content_1=0, jesUp_content_1=0, jesDown_content_1=0,jerUp_content_1=0, jerDown_content_1=0, jar_content_1=0, jer_content_1=0, hf_content_1=0, trkUp_content_1=0, trkDown_content_1=0;
  float prior_content_0=0, prior_content_1=0;
  float it2_content_0=0, it2_content_1=0, it3_content_0=0, it3_content_1=0;
  float mcStats1_content_0=0, mcStats2_content_0=0, mcStats1_content_1=0, mcStats2_content_1=0; 
  float total_sys_0=0, jesUp_avgMag_0=0, jesDown_avgMag_0=0, jerUp_avgMag_0=0, jerDown_avgMag_0=0, jar_avgMag_0=0, jer_avgMag_0=0, prior_avgMag_0=0, hf_avgMag_0=0, trkUp_avgMag_0=0, trkDown_avgMag_0=0, total_sys_1=0, nc_avgMag_1=0, jesUp_avgMag_1=0, jesDown_avgMag_1=0, jerUp_avgMag_1=0, jerDown_avgMag_1=0, jar_avgMag_1=0, jer_avgMag_1=0, prior_avgMag_1=0, hf_avgMag_1=0, trkUp_avgMag_1=0, trkDown_avgMag_1=0;
  float mcStats_avgMag_0=0, mcStats_avgMag_1=0;
  float it_avgMag_0=0, it_avgMag_1=0;
  float jesUp_Diff_0=0, jesDown_Diff_0=0, jerUp_Diff_0=0, jerDown_Diff_0=0, jar_Diff_0=0, jer_Diff_0=0, prior_Diff_0=0, hf_Diff_0=0, trkUp_Diff_0=0, trkDown_Diff_0=0, jesUp_Diff_1=0, jesDown_Diff_1=0, jerUp_Diff_1=0, jerDown_Diff_1=0, jar_Diff_1=0, jer_Diff_1=0, prior_Diff_1=0, hf_Diff_1=0, trkUp_Diff_1=0, trkDown_Diff_1=0;
  float mcStats_Diff_0=0, mcStats_Diff_1=0;
  float it_Diff_0=0, it_Diff_1=0;
  // v4
  float raw_content_0_v4=0, unf_content_0_v4=0, jesUp_content_0_v4=0, jesDown_content_0_v4=0,jerUp_content_0_v4=0, jerDown_content_0_v4=0, jar_content_0_v4=0, jer_content_0_v4=0;
  float raw_content_1_v4=0, unf_content_1_v4=0, jesUp_content_1_v4=0, jesDown_content_1_v4=0,jerUp_content_1_v4=0, jerDown_content_1_v4=0, jar_content_1_v4=0, jer_content_1_v4=0;
  float prior_content_0_v4=0, prior_content_1_v4=0;
  float it2_content_0_v4=0, it2_content_1_v4=0, it3_content_0_v4=0, it3_content_1_v4=0;
  float hf_content_0_v4=0, trkUp_content_0_v4=0, trkDown_content_0_v4=0, hf_content_1_v4=0, trkUp_content_1_v4=0, trkDown_content_1_v4=0;
  float mcStats1_content_0_v4=0, mcStats2_content_0_v4=0, mcStats1_content_1_v4=0, mcStats2_content_1_v4=0; 
  float total_sys_0_v4=0, jesUp_avgMag_0_v4=0, jesDown_avgMag_0_v4=0, jerUp_avgMag_0_v4=0, jerDown_avgMag_0_v4=0, jar_avgMag_0_v4=0, jer_avgMag_0_v4=0, total_sys_1_v4=0, jesUp_avgMag_1_v4=0, jesDown_avgMag_1_v4=0, jerUp_avgMag_1_v4=0, jerDown_avgMag_1_v4=0, jar_avgMag_1_v4=0, jer_avgMag_1_v4=0;
  float prior_avgMag_0_v4=0, prior_avgMag_1_v4=0;
  float hf_avgMag_0_v4=0, trkUp_avgMag_0_v4=0, trkDown_avgMag_0_v4=0, hf_avgMag_1_v4=0, trkUp_avgMag_1_v4=0, trkDown_avgMag_1_v4=0;
  float mcStats_avgMag_0_v4=0, mcStats_avgMag_1_v4=0;
  float it_avgMag_0_v4=0, it_avgMag_1_v4=0;
  float jesUp_Diff_0_v4=0, jesDown_Diff_0_v4=0, jerUp_Diff_0_v4=0, jerDown_Diff_0_v4=0, jar_Diff_0_v4=0, jer_Diff_0_v4=0, nc_Diff_1_v4=0, jesUp_Diff_1_v4=0, jesDown_Diff_1_v4=0, jerUp_Diff_1_v4=0, jerDown_Diff_1_v4=0, jar_Diff_1_v4=0, jer_Diff_1_v4=0;
  float hf_Diff_0_v4=0, trkUp_Diff_0_v4=0, trkDown_Diff_0_v4=0, hf_Diff_1_v4=0, trkUp_Diff_1_v4=0, trkDown_Diff_1_v4=0; 
  float prior_Diff_0_v4=0, prior_Diff_1_v4=0;
  float mcStats_Diff_0_v4=0, mcStats_Diff_1_v4=0;
  float it_Diff_0_v4=0, it_Diff_1_v4=0;

  // printing multiplier
  float multiplier=100;

  int binNumber = v2_unf_0->GetNbinsX();
  for (int iBin=1; iBin<binNumber+1; iBin++)
    {
      // v2 get contents
      //raw_content=h_v2_raw->GetBinContent(iBin);
      unf_content_0=v2_unf_0->GetBinContent(iBin), unf_content_1=v2_unf_1->GetBinContent(iBin);
      nomJES_content_0=v2_jesNom_0->GetBinContent(iBin), nomJER_content_0=v2_jerNom_0->GetBinContent(iBin);
      nomJES_content_1=v2_jesNom_1->GetBinContent(iBin), nomJER_content_1=v2_jerNom_1->GetBinContent(iBin);
      jesUp_content_0=v2_jesUp_0->GetBinContent(iBin), jesUp_content_1=v2_jesUp_1->GetBinContent(iBin);
      jesDown_content_0=v2_jesDown_0->GetBinContent(iBin), jesDown_content_1=v2_jesDown_1->GetBinContent(iBin);
      jerUp_content_0=v2_jerUp_0->GetBinContent(iBin), jerUp_content_1=v2_jerUp_1->GetBinContent(iBin);
      jerDown_content_0=v2_jerDown_0->GetBinContent(iBin), jerDown_content_1=v2_jerDown_1->GetBinContent(iBin);
      jar_content_0=v2_jar_0->GetBinContent(iBin), jar_content_1=v2_jar_1->GetBinContent(iBin);
      jer_content_0=v2_jer_0->GetBinContent(iBin), jer_content_1=v2_jer_1->GetBinContent(iBin);
      prior_content_0=v2_prior_0->GetBinContent(iBin), prior_content_1=v2_prior_1->GetBinContent(iBin);
      mcStats1_content_0=v2_mcStat1_0->GetBinContent(iBin), mcStats2_content_0=v2_mcStat2_0->GetBinContent(iBin), mcStats1_content_1=v2_mcStat1_1->GetBinContent(iBin), mcStats2_content_1=v2_mcStat2_1->GetBinContent(iBin);
      hf_content_0=v2_hf_0->GetBinContent(iBin), hf_content_1=v2_hf_1->GetBinContent(iBin);
      trkUp_content_0=v2_rapup_0->GetBinContent(iBin), trkDown_content_0=v2_rapdown_0->GetBinContent(iBin), trkUp_content_1=v2_rapup_1->GetBinContent(iBin), trkDown_content_1=v2_rapdown_1->GetBinContent(iBin);
      it2_content_0=v2_It2_0->GetBinContent(iBin), it3_content_0=v2_It3_0->GetBinContent(iBin);
      it2_content_1=v2_It2_1->GetBinContent(iBin), it3_content_1=v2_It3_1->GetBinContent(iBin);

      // get differences
      //jesUp_Diff_0=unf_content_0-jesUp_content_0, jesUp_Diff_1=unf_content_1-jesUp_content_1;
      //jesDown_Diff_0=unf_content_0-jesDown_content_0, jesDown_Diff_1=unf_content_1-jesDown_content_1;
      //jerUp_Diff_0=unf_content_0-jerUp_content_0, jerUp_Diff_1=unf_content_1-jerUp_content_1;
      //jerDown_Diff_0=unf_content_0-jerDown_content_0, jerDown_Diff_1=unf_content_1-jerDown_content_1;
      jesUp_Diff_0=nomJES_content_0-jesUp_content_0, jesUp_Diff_1=nomJES_content_1-jesUp_content_1;
      jesDown_Diff_0=nomJES_content_0-jesDown_content_0, jesDown_Diff_1=nomJES_content_1-jesDown_content_1;
      jerUp_Diff_0=nomJER_content_0-jerUp_content_0, jerUp_Diff_1=nomJER_content_1-jerUp_content_1;
      jerDown_Diff_0=nomJER_content_0-jerDown_content_0, jerDown_Diff_1=nomJER_content_1-jerDown_content_1;
      jar_Diff_0=unf_content_0-jar_content_0, jar_Diff_1=unf_content_1-jar_content_1;
      jer_Diff_0=unf_content_0-jer_content_0, jer_Diff_1=unf_content_1-jer_content_1;
      prior_Diff_0=unf_content_0-prior_content_0, prior_Diff_1=unf_content_1-prior_content_1;
      mcStats_Diff_0=mcStats1_content_0-mcStats2_content_0, mcStats_Diff_1=mcStats1_content_1-mcStats2_content_1;
      hf_Diff_0=unf_content_0-hf_content_0, hf_Diff_1=unf_content_1-hf_content_1;
      trkUp_Diff_0=unf_content_0-trkUp_content_0, trkDown_Diff_0=unf_content_0-trkDown_content_0, trkUp_Diff_1=unf_content_1-trkUp_content_1, trkDown_Diff_1=unf_content_1-trkDown_content_1;
      it_Diff_0=it2_content_0-it3_content_0, it_Diff_1=it2_content_1-it3_content_1;


      // write out to file
      outfile_jes_0 << fixed << setprecision(1) << multiplier*(fabs(jesUp_Diff_0)+fabs(jesDown_Diff_0))/2 << endl, outfile_jes_1 << fixed << setprecision(1) << multiplier*(fabs(jesUp_Diff_1)+fabs(jesDown_Diff_1))/2 << endl;
      outfile_jer_0 << fixed << setprecision(1) << multiplier*(fabs(jerUp_Diff_0)+fabs(jerDown_Diff_0))/2 << endl, outfile_jer_1 << fixed << setprecision(1) << multiplier*(fabs(jerUp_Diff_1)+fabs(jerDown_Diff_1))/2 << endl;
      outfile_jar_0 << fixed << setprecision(1) << multiplier*jar_Diff_0 << endl, outfile_jar_1 << fixed << setprecision(1) << multiplier*jar_Diff_1 << endl;
      outfile_prior_0 << fixed << setprecision(1) << multiplier*prior_Diff_0 << endl, outfile_prior_1 << fixed << setprecision(1) << multiplier*prior_Diff_1 << endl;
      outfile_mcStats_0 << fixed << setprecision(1) << multiplier*mcStats_Diff_0 << endl, outfile_mcStats_1 << fixed << setprecision(1) << multiplier*mcStats_Diff_1 << endl;
      outfile_hf_0 << fixed << setprecision(1) << multiplier*hf_Diff_0 << endl, outfile_hf_1 << fixed << setprecision(1) << multiplier*hf_Diff_1 << endl;
      outfile_trk_0 << fixed << setprecision(1) << multiplier*(trkUp_Diff_0+trkDown_Diff_0)/2 << endl, outfile_trk_1 << fixed << setprecision(1) << multiplier*(trkUp_Diff_1+trkDown_Diff_1)/2 << endl;
      outfile_it_0 << fixed << setprecision(1) << multiplier*it_Diff_0 << endl, outfile_it_1 << fixed << setprecision(1) << multiplier*it_Diff_1 << endl;
      
      

      // avg Magnitudes
      jesUp_avgMag_0=jesUp_avgMag_0+fabs(jesUp_Diff_0), jesUp_avgMag_1=jesUp_avgMag_1+fabs(jesUp_Diff_1);
      jesDown_avgMag_0=jesDown_avgMag_0+fabs(jesDown_Diff_0), jesDown_avgMag_1=jesDown_avgMag_1+fabs(jesDown_Diff_1);
      jerUp_avgMag_0=jerUp_avgMag_0+fabs(jerUp_Diff_0), jerUp_avgMag_1=jerUp_avgMag_1+fabs(jerUp_Diff_1);
      jerDown_avgMag_0=jerDown_avgMag_0+fabs(jerDown_Diff_0), jerDown_avgMag_1=jerDown_avgMag_1+fabs(jerDown_Diff_1);
      jar_avgMag_0=jar_avgMag_0+fabs(jar_Diff_0), jar_avgMag_1=jar_avgMag_1+fabs(jar_Diff_1);
      jer_avgMag_0=jer_avgMag_0+fabs(jer_Diff_0), jer_avgMag_1=jer_avgMag_1+fabs(jer_Diff_1);
      prior_avgMag_0=prior_avgMag_0+fabs(prior_Diff_0), prior_avgMag_1=prior_avgMag_1+fabs(prior_Diff_1);
      mcStats_avgMag_0=mcStats_avgMag_0+fabs(mcStats_Diff_0), mcStats_avgMag_1=mcStats_avgMag_1+fabs(mcStats_Diff_1);
      hf_avgMag_0=hf_avgMag_0+fabs(hf_Diff_0), hf_avgMag_1=hf_avgMag_1+fabs(hf_Diff_1);
      trkUp_avgMag_0=trkUp_avgMag_0+fabs(trkUp_Diff_0), trkDown_avgMag_0=trkDown_avgMag_0+fabs(trkDown_Diff_0);
      trkUp_avgMag_1=trkUp_avgMag_1+fabs(trkUp_Diff_1), trkDown_avgMag_1=trkDown_avgMag_1+fabs(trkDown_Diff_1);
      it_avgMag_0=it_avgMag_0+fabs(it_Diff_0), it_avgMag_1=it_avgMag_1+fabs(it_Diff_1); 
      


      // v4
      //raw_content=h_v2_raw->GetBinContent(iBin);
      unf_content_0_v4=v4_unf_0->GetBinContent(iBin), unf_content_1_v4=v4_unf_1->GetBinContent(iBin);
      jesUp_content_0_v4=v4_jesUp_0->GetBinContent(iBin), jesUp_content_1_v4=v4_jesUp_1->GetBinContent(iBin);
      jesDown_content_0_v4=v4_jesDown_0->GetBinContent(iBin), jesDown_content_1_v4=v4_jesDown_1->GetBinContent(iBin);
      jerUp_content_0_v4=v4_jerUp_0->GetBinContent(iBin), jerUp_content_1_v4=v4_jerUp_1->GetBinContent(iBin);
      jerDown_content_0_v4=v4_jerDown_0->GetBinContent(iBin), jerDown_content_1_v4=v4_jerDown_1->GetBinContent(iBin);
      jar_content_0_v4=v4_jar_0->GetBinContent(iBin), jar_content_1_v4=v4_jar_1->GetBinContent(iBin);
      jer_content_0_v4=v4_jer_0->GetBinContent(iBin), jer_content_1_v4=v4_jer_1->GetBinContent(iBin);
      prior_content_0_v4=v4_prior_0->GetBinContent(iBin), prior_content_1_v4=v4_prior_1->GetBinContent(iBin);
      mcStats1_content_0_v4=v4_mcStat1_0->GetBinContent(iBin), mcStats2_content_0_v4=v4_mcStat2_0->GetBinContent(iBin), mcStats1_content_1_v4=v4_mcStat1_1->GetBinContent(iBin), mcStats2_content_1_v4=v4_mcStat2_1->GetBinContent(iBin);
      hf_content_0_v4=v4_hf_0->GetBinContent(iBin), hf_content_1_v4=v4_hf_1->GetBinContent(iBin);
      trkUp_content_0_v4=v4_rapup_0->GetBinContent(iBin), trkDown_content_0_v4=v4_rapdown_0->GetBinContent(iBin), trkUp_content_1_v4=v4_rapup_1->GetBinContent(iBin), trkDown_content_1_v4=v4_rapdown_1->GetBinContent(iBin);
      it2_content_0_v4=v4_It2_0->GetBinContent(iBin), it3_content_0_v4=v4_It3_0->GetBinContent(iBin);
      it2_content_1_v4=v4_It2_1->GetBinContent(iBin), it3_content_1_v4=v4_It3_1->GetBinContent(iBin);

      // v4 differences
      jesUp_Diff_0_v4=unf_content_0_v4-jesUp_content_0_v4, jesUp_Diff_1_v4=unf_content_1_v4-jesUp_content_1_v4;
      jesDown_Diff_0_v4=unf_content_0_v4-jesDown_content_0_v4, jesDown_Diff_1_v4=unf_content_1_v4-jesDown_content_1_v4;
      jerUp_Diff_0_v4=unf_content_0_v4-jerUp_content_0_v4, jerUp_Diff_1_v4=unf_content_1_v4-jerUp_content_1_v4;
      jerDown_Diff_0_v4=unf_content_0_v4-jerDown_content_0_v4, jerDown_Diff_1_v4=unf_content_1_v4-jerDown_content_1_v4;
      jar_Diff_0_v4=unf_content_0_v4-jar_content_0_v4, jar_Diff_1_v4=unf_content_1_v4-jar_content_1_v4;
      jer_Diff_0_v4=unf_content_0_v4-jer_content_0_v4, jer_Diff_1_v4=unf_content_1_v4-jer_content_1_v4;
      prior_Diff_0_v4=unf_content_0_v4-prior_content_0_v4, prior_Diff_1_v4=unf_content_1_v4-prior_content_1_v4;
      mcStats_Diff_0_v4=mcStats1_content_0_v4-mcStats2_content_0_v4, mcStats_Diff_1_v4=mcStats1_content_1_v4-mcStats2_content_1_v4;
      hf_Diff_0_v4=unf_content_0_v4-hf_content_0_v4, hf_Diff_1_v4=unf_content_1_v4-hf_content_1_v4;
      trkUp_Diff_0_v4=unf_content_0_v4-trkUp_content_0_v4, trkDown_Diff_0_v4=unf_content_0_v4-trkDown_content_0_v4, trkUp_Diff_1_v4=unf_content_1_v4-trkUp_content_1_v4, trkDown_Diff_1_v4=unf_content_1_v4-trkDown_content_1_v4;
      it_Diff_0_v4=it2_content_0_v4-it3_content_0_v4, it_Diff_1_v4=it2_content_1_v4-it3_content_1_v4;

      // v4 write out
      v4file_jes_0 << fixed << setprecision(1) << multiplier*(fabs(jesUp_Diff_0_v4)+fabs(jesDown_Diff_0_v4))/2 << endl, v4file_jes_1 << fixed << setprecision(1) << multiplier*(fabs(jesUp_Diff_1_v4)-fabs(jesDown_Diff_1_v4))/2 << endl;
      v4file_jer_0 << fixed << setprecision(1) << multiplier*(fabs(jerUp_Diff_0_v4)+fabs(jerDown_Diff_0_v4))/2 << endl, v4file_jer_1 << fixed << setprecision(1) << multiplier*(fabs(jerUp_Diff_1_v4)-fabs(jerDown_Diff_1_v4))/2 << endl;
      v4file_jar_0 << fixed << setprecision(1) << multiplier*jar_Diff_0_v4 << endl, v4file_jar_1 << fixed << setprecision(1) << multiplier*jar_Diff_1_v4 << endl;
      v4file_prior_0 << fixed << setprecision(1) << multiplier*prior_Diff_0_v4 << endl, v4file_prior_1 << fixed << setprecision(1) << multiplier*prior_Diff_1_v4 << endl;
      v4file_mcStats_0 << fixed << setprecision(1) << multiplier*mcStats_Diff_0_v4 << endl, v4file_mcStats_1 << fixed << setprecision(1) << multiplier*mcStats_Diff_1_v4 << endl;
      v4file_hf_0 << fixed << setprecision(1) << multiplier*hf_Diff_0_v4 << endl, v4file_hf_1 << fixed << setprecision(1) << multiplier*hf_Diff_1_v4 << endl;
      v4file_trk_0 << fixed << setprecision(1) << multiplier*(fabs(trkUp_Diff_0_v4)+fabs(trkDown_Diff_0_v4))/2 << endl, v4file_trk_1 << fixed << setprecision(1) << multiplier*(fabs(trkUp_Diff_1_v4)+fabs(trkDown_Diff_1_v4))/2 << endl;
      v4file_it_0 << fixed << setprecision(1) << multiplier*it_Diff_0_v4 << endl, v4file_it_1 << fixed << setprecision(1) << multiplier*it_Diff_1_v4 << endl;

      // v4 avg magnitudes
      jesUp_avgMag_0_v4=jesUp_avgMag_0_v4+fabs(jesUp_Diff_0_v4), jesUp_avgMag_1_v4=jesUp_avgMag_1_v4+fabs(jesUp_Diff_1_v4);
      jerUp_avgMag_0_v4=jerUp_avgMag_0_v4+fabs(jerUp_Diff_0_v4), jerUp_avgMag_1_v4=jerUp_avgMag_1_v4+fabs(jerUp_Diff_1_v4);
      jar_avgMag_0_v4=jar_avgMag_0_v4+fabs(jar_Diff_0_v4), jar_avgMag_1_v4=jar_avgMag_1_v4+fabs(jar_Diff_1_v4);
      jer_avgMag_0_v4=jer_avgMag_0_v4+fabs(jer_Diff_0_v4), jer_avgMag_1_v4=jer_avgMag_1_v4+fabs(jer_Diff_1_v4);
      prior_avgMag_0_v4=prior_avgMag_0_v4+fabs(prior_Diff_0_v4), prior_avgMag_1_v4=prior_avgMag_1_v4+fabs(prior_Diff_1_v4);
      mcStats_avgMag_0_v4=mcStats_avgMag_0_v4+fabs(mcStats_Diff_0_v4), mcStats_avgMag_1_v4=mcStats_avgMag_1_v4+fabs(mcStats_Diff_1_v4);
      hf_avgMag_0_v4=hf_avgMag_0_v4+fabs(hf_Diff_0_v4), hf_avgMag_1_v4=hf_avgMag_1_v4+fabs(hf_Diff_1_v4);
      trkUp_avgMag_0_v4=trkUp_avgMag_0_v4+fabs(trkUp_Diff_0_v4), trkDown_avgMag_0_v4=trkDown_avgMag_0_v4+fabs(trkDown_Diff_0_v4);
      trkUp_avgMag_1_v4=trkUp_avgMag_1_v4+fabs(trkUp_Diff_1_v4), trkDown_avgMag_1_v4=trkDown_avgMag_1_v4+fabs(trkDown_Diff_1_v4);
      it_avgMag_0_v4=it_avgMag_0_v4+fabs(it_Diff_0_v4), it_avgMag_1_v4=it_avgMag_1_v4+fabs(it_Diff_1_v4);
      
      

    } // end bin


  // calculate avg bin systematics
  // v2
  jesUp_avgMag_0=jesUp_avgMag_0/binNumber, jesUp_avgMag_1=jesUp_avgMag_1/binNumber;
  jesDown_avgMag_0=jesDown_avgMag_0/binNumber, jesDown_avgMag_1=jesDown_avgMag_1/binNumber;
  jerUp_avgMag_0=jerUp_avgMag_0/binNumber, jerUp_avgMag_1=jerUp_avgMag_1/binNumber;
  jerDown_avgMag_0=jerDown_avgMag_0/binNumber, jerDown_avgMag_1=jerDown_avgMag_1/binNumber;
  float jes_total_avgMag_0=(jesUp_avgMag_0+jesDown_avgMag_0)/2, jes_total_avgMag_1=(jesUp_avgMag_1+jesDown_avgMag_1)/2;
  float jer_total_avgMag_0=(jerUp_avgMag_0+jerDown_avgMag_0)/2, jer_total_avgMag_1=(jerUp_avgMag_1+jerDown_avgMag_1)/2;
  jar_avgMag_0=jar_avgMag_0/binNumber, jar_avgMag_1=jar_avgMag_1/binNumber;
  jer_avgMag_0=jer_avgMag_0/binNumber, jer_avgMag_1=jer_avgMag_1/binNumber;
  prior_avgMag_0=prior_avgMag_0/binNumber, prior_avgMag_1=prior_avgMag_1/binNumber;
  mcStats_avgMag_0=mcStats_avgMag_0/binNumber, mcStats_avgMag_1=mcStats_avgMag_1/binNumber;
  hf_avgMag_0=hf_avgMag_0/binNumber, hf_avgMag_1=hf_avgMag_1/binNumber;
  it_avgMag_0=it_avgMag_0/binNumber, it_avgMag_1=it_avgMag_1/binNumber;
  trkUp_avgMag_0=trkUp_avgMag_0/binNumber, trkDown_avgMag_0=trkDown_avgMag_0/binNumber;
  trkUp_avgMag_1=trkUp_avgMag_1/binNumber, trkDown_avgMag_1=trkDown_avgMag_1/binNumber;
  float trk_total_avgMag_0=(trkUp_avgMag_0+trkDown_avgMag_0)/2, trk_total_avgMag_1=(trkUp_avgMag_1+trkDown_avgMag_1)/2;
  float rapgap_total_0=sqrt(hf_avgMag_0*hf_avgMag_0+trk_total_avgMag_0*trk_total_avgMag_0), rapgap_total_1=sqrt(hf_avgMag_1*hf_avgMag_1+trk_total_avgMag_1*trk_total_avgMag_1); 
  
  total_sys_0=sqrt((it_avgMag_0*it_avgMag_0+jes_total_avgMag_0*jes_total_avgMag_0+jer_total_avgMag_0*jer_total_avgMag_0+jar_avgMag_0*jar_avgMag_0+mcStats_avgMag_0*mcStats_avgMag_0/2+prior_avgMag_0*prior_avgMag_0+rapgap_total_0*rapgap_total_0));
  total_sys_1=sqrt((it_avgMag_1*it_avgMag_1+jes_total_avgMag_1*jes_total_avgMag_1+jer_total_avgMag_1*jer_total_avgMag_1+jar_avgMag_1*jar_avgMag_1+mcStats_avgMag_1*mcStats_avgMag_1/2+prior_avgMag_1*prior_avgMag_1+rapgap_total_1*rapgap_total_1));
  

  cout << "jes_avgMag=" << jes_total_avgMag_0 << " and jar_avgMag=" << jar_avgMag_0 << " and prior_avgMag_0=" << prior_avgMag_0 << " and totalBin0=" << total_sys_0 << endl;
  cout << "jes_avgMag=" << jes_total_avgMag_1 << " and jar_avgMag=" << jar_avgMag_1 << " and prior_avgMag_1=" << prior_avgMag_1 << " and totalBin1=" << total_sys_1 << endl;
  cout << "hf_avgMag_0=" << hf_avgMag_0 << " and hf_avgMag_1=" << hf_avgMag_1 << endl;
  cout << "it_avgMag_0=" << it_avgMag_0 << " and it_avgMag_1=" << it_avgMag_1 << endl;
  cout << "trkUp_avgMag_0=" << trkUp_avgMag_0 << ", trkDown_avgMag_0=" << trkDown_avgMag_0 << " and trkUp_avgMag_1=" << trkUp_avgMag_1 << ", trkDown_avgMag_1=" << trkDown_avgMag_1 << endl;
  cout << "trk_total_avgMag_0=" << trk_total_avgMag_0 << " and trk_total_avgMag_1=" << trk_total_avgMag_1 << endl;
  cout << "total rapgap_0=" << rapgap_total_0 << " and total rapgap_1=" << rapgap_total_1 << endl;
  cout << "total_sys_0=" << total_sys_0 << " and total_sys_1=" << total_sys_1 << endl;
  

 
  
  // two panel Plots
  pad4_2_rapidity(v2_unf_0_cut, v2_unf_1_cut, v2_gen_0_cut, v2_gen_1_cut, "y'", "<cos(2#phi)>", "Data", "Pythia8", "Pics/unf_gen_qt_twoPanel_cut.png", total_sys_0, total_sys_1, -0.02, 0.45, -0.15, 0.30);
  // unf no ac
  pad4_2_rapidity(v2_unf_0, v2_unf_1, v2_gen_0, v2_gen_1, "y'", "<cos(2#phi)>", "Data", "Pythia8", "Pics/unf_gen_qt_twoPanel_noAC.png", total_sys_0, total_sys_1, -0.02, 0.45, -0.15, 0.30);
  // orig
  pad4_2_rapidity(v2_unf_orig_0, v2_unf_orig_1, v2_gen_0, v2_gen_1, "dijet y'", "<cos(2#phi)>", "Data", "Pythia8", "Pics/unf_gen_qt_twoPanel_orig.png", total_sys_0, total_sys_1, -0.02, 0.45, -0.24, 0.24);
  // ac
  pad4_2_rapidity(v2_unf_0_ac, v2_unf_1_ac, v2_gen_0, v2_gen_1, "dijet y'", "#LTcos(2#phi)#GT", "Data", "Pythia8", "Pics/unf_gen_qt_twoPanel.pdf", total_sys_0, total_sys_1, 0.005, 0.31, -0.24, 0.24);



  // v4 avg bin systematics
  jesUp_avgMag_0_v4=jesUp_avgMag_0_v4/binNumber, jesUp_avgMag_1_v4=jesUp_avgMag_1_v4/binNumber;
  jesDown_avgMag_0_v4=jesDown_avgMag_0_v4/binNumber, jesDown_avgMag_1_v4=jesDown_avgMag_1_v4/binNumber;
  jerUp_avgMag_0_v4=jerUp_avgMag_0_v4/binNumber, jerUp_avgMag_1_v4=jerUp_avgMag_1_v4/binNumber;
  jerDown_avgMag_0_v4=jerDown_avgMag_0_v4/binNumber, jerDown_avgMag_1_v4=jerDown_avgMag_1_v4/binNumber;
  float jes_total_avgMag_0_v4=(jesUp_avgMag_0_v4+jesDown_avgMag_0_v4)/2, jes_total_avgMag_1_v4=(jesUp_avgMag_1_v4+jesDown_avgMag_1_v4)/2;
  float jer_total_avgMag_0_v4=(jerUp_avgMag_0_v4+jerDown_avgMag_0_v4)/2, jer_total_avgMag_1_v4=(jerUp_avgMag_1_v4+jerDown_avgMag_1_v4)/2;
  jar_avgMag_0_v4=jar_avgMag_0_v4/binNumber, jar_avgMag_1_v4=jar_avgMag_1_v4/binNumber;
  jer_avgMag_0_v4=jer_avgMag_0_v4/binNumber, jer_avgMag_1_v4=jer_avgMag_1_v4/binNumber;
  prior_avgMag_0_v4=prior_avgMag_0_v4/binNumber, prior_avgMag_1_v4=prior_avgMag_1_v4/binNumber;
  mcStats_avgMag_0_v4=mcStats_avgMag_0_v4/binNumber, mcStats_avgMag_1_v4=mcStats_avgMag_1_v4/binNumber;
  hf_avgMag_0_v4=hf_avgMag_0_v4/binNumber, hf_avgMag_1_v4=hf_avgMag_1_v4/binNumber;
  it_avgMag_0_v4=it_avgMag_0_v4/binNumber, it_avgMag_1_v4=it_avgMag_1_v4/binNumber;
  trkUp_avgMag_0_v4=trkUp_avgMag_0_v4/binNumber, trkDown_avgMag_0_v4=trkDown_avgMag_0_v4/binNumber;
  trkUp_avgMag_1_v4=trkUp_avgMag_1_v4/binNumber, trkDown_avgMag_1_v4=trkDown_avgMag_1_v4/binNumber;
  float trk_total_avgMag_0_v4=(trkUp_avgMag_0_v4+trkDown_avgMag_0_v4)/2, trk_total_avgMag_1_v4=(trkUp_avgMag_1_v4+trkDown_avgMag_1_v4)/2;
  float rapgap_total_0_v4=sqrt(hf_avgMag_0_v4*hf_avgMag_0_v4+trk_total_avgMag_0_v4*trk_total_avgMag_0_v4), rapgap_total_1_v4=sqrt(hf_avgMag_1_v4*hf_avgMag_1_v4+trk_total_avgMag_1_v4*trk_total_avgMag_1_v4); 
  
  total_sys_0_v4=sqrt((it_avgMag_0_v4*it_avgMag_0_v4+jes_total_avgMag_0_v4*jes_total_avgMag_0_v4+jer_total_avgMag_0_v4*jer_total_avgMag_0_v4+jar_avgMag_0_v4*jar_avgMag_0_v4+mcStats_avgMag_0_v4*mcStats_avgMag_0_v4+prior_avgMag_0_v4*prior_avgMag_0_v4+rapgap_total_0_v4*rapgap_total_0_v4));
  total_sys_1_v4=sqrt((it_avgMag_1_v4*it_avgMag_1_v4+jes_total_avgMag_1_v4*jes_total_avgMag_1_v4+jer_total_avgMag_1_v4*jer_total_avgMag_1_v4+jar_avgMag_1_v4*jar_avgMag_1_v4+mcStats_avgMag_1_v4*mcStats_avgMag_1_v4+prior_avgMag_1_v4*prior_avgMag_1_v4+rapgap_total_1_v4*rapgap_total_1_v4));

  cout << "v4 rapgap_total_0_v4=" << rapgap_total_0_v4 << "v4 rapgap_total_1_v4=" << rapgap_total_1_v4 << endl;
  cout << "v4 prior_avgMag=" << prior_avgMag_0_v4 << "v4 prior_avgMag=" << prior_avgMag_1_v4 << endl;
  cout << "v4 jar_avgMag=" << jar_avgMag_0_v4 << " and v4 totalBin0=" << total_sys_0_v4 << endl;
  cout << "v4 jar_avgMag=" << jar_avgMag_1_v4 << " and v4 totalBin1=" << total_sys_1_v4 << endl;
  cout << "v4 it_avgMag_0=" << it_avgMag_0_v4 << endl;
  cout << "v4 it_avgMag_1=" << it_avgMag_1_v4 << endl;
  

  // plots with systematics
  pad4_2_rapidity(v4_unf_0_ac, v4_unf_1_ac, v4_gen_0, v4_gen_1, "dijet y'", "#LTcos(4#phi)#GT", "Data", "Pythia8", "Pics/v4_unf_gen_qt_twoPanel.pdf", total_sys_0_v4, total_sys_1_v4, -0.16, 0.125, -0.12, 0.12);


  // new systematics
  TH1F *h_JES = new TH1F("h_JES","h_JES",2,0,2);
  TH1F *h_JER = new TH1F("h_JER","h_JER",2,0,2);
  TH1F *h_JAR = new TH1F("h_JAR","h_JAR",2,0,2);
  TH1F *h_LSR = new TH1F("h_LSR","h_LSR",2,0,2);
  TH1F *h_Prior = new TH1F("h_Prior","h_Prior",2,0,2);
  TH1F *h_trkGap = new TH1F("h_trkGap","h_trkGap",2,0,2);
  TH1F *h_HF = new TH1F("h_HF","h_HF",2,0,2);
  TH1F *h_ITER = new TH1F("h_ITER","h_ITER",2,0,2);
  TH1F *h_total = new TH1F("h_total","h_total",2,0,2);
  // fill bins rap0, rap1
  h_JES->SetBinContent(1, jes_total_avgMag_0), h_JES->SetBinContent(2, jes_total_avgMag_1);
  h_JER->SetBinContent(1, jer_total_avgMag_0), h_JER->SetBinContent(2, jer_total_avgMag_1);
  h_JAR->SetBinContent(1, jar_avgMag_0), h_JAR->SetBinContent(2, jar_avgMag_1);
  h_LSR->SetBinContent(1, mcStats_avgMag_0/sqrt(2)), h_LSR->SetBinContent(2, mcStats_avgMag_1/sqrt(2));
  h_Prior->SetBinContent(1, prior_avgMag_0), h_Prior->SetBinContent(2, prior_avgMag_1);
  h_trkGap->SetBinContent(1, trk_total_avgMag_0), h_trkGap->SetBinContent(2, trk_total_avgMag_1);
  h_HF->SetBinContent(1, hf_avgMag_0), h_HF->SetBinContent(2, hf_avgMag_1);
  h_ITER->SetBinContent(1, it_avgMag_0), h_ITER->SetBinContent(2, it_avgMag_1);
  h_total->SetBinContent(1, total_sys_0), h_total->SetBinContent(2, total_sys_1);

  // plot v2 rapidity systematics
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
  xAxis->SetBinLabel(1, "0 < Q_{T} < 12 GeV");
  xAxis->SetBinLabel(2, "12 < Q_{T} < 40 GeV");
  h_total->SetTitle("");
  h_total->GetYaxis()->SetTitle("contribution to systematics (10^{-2})");
  h_total->GetYaxis()->SetRangeUser(0,0.06);
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
  c3->SaveAs("Pics/systematics_rapidity_v2.pdf");




  // new systematics v4
  TH1F *h_JES_v4 = new TH1F("h_JES_v4","h_JES_v4",2,0,2);
  TH1F *h_JER_v4 = new TH1F("h_JER_v4","h_JER_v4",2,0,2);
  TH1F *h_JAR_v4 = new TH1F("h_JAR_v4","h_JAR_v4",2,0,2);
  TH1F *h_LSR_v4 = new TH1F("h_LSR_v4","h_LSR_v4",2,0,2);
  TH1F *h_Prior_v4 = new TH1F("h_Prior_v4","h_Prior_v4",2,0,2);
  TH1F *h_trkGap_v4 = new TH1F("h_trkGap_v4","h_trkGap_v4",2,0,2);
  TH1F *h_HF_v4 = new TH1F("h_HF_v4","h_HF_v4",2,0,2);
  TH1F *h_ITER_v4 = new TH1F("h_ITER_v4","h_ITER_v4",2,0,2);
  TH1F *h_total_v4 = new TH1F("h_total_v4","h_total_v4",2,0,2);
  // fill bins rap0, rap1
  h_JES_v4->SetBinContent(1, jes_total_avgMag_0_v4), h_JES_v4->SetBinContent(2, jes_total_avgMag_1_v4);
  h_JER_v4->SetBinContent(1, jer_total_avgMag_0_v4), h_JER_v4->SetBinContent(2, jer_total_avgMag_1_v4);
  h_JAR_v4->SetBinContent(1, jar_avgMag_0_v4), h_JAR_v4->SetBinContent(2, jar_avgMag_1_v4);
  h_LSR_v4->SetBinContent(1, mcStats_avgMag_0_v4/sqrt(2)), h_LSR_v4->SetBinContent(2, mcStats_avgMag_1_v4/sqrt(2));
  h_Prior_v4->SetBinContent(1, prior_avgMag_0_v4), h_Prior_v4->SetBinContent(2, prior_avgMag_1_v4);
  h_trkGap_v4->SetBinContent(1, trk_total_avgMag_0_v4), h_trkGap_v4->SetBinContent(2, trk_total_avgMag_1_v4);
  h_HF_v4->SetBinContent(1, hf_avgMag_0_v4), h_HF_v4->SetBinContent(2, hf_avgMag_1_v4);
  h_ITER_v4->SetBinContent(1, it_avgMag_0_v4), h_ITER_v4->SetBinContent(2, it_avgMag_1_v4);
  h_total_v4->SetBinContent(1, total_sys_0_v4), h_total_v4->SetBinContent(2, total_sys_1_v4);

  // plot v2 rapidity systematics
  auto *c4 = new TCanvas("c4", "c4",900,900);
  c4->SetLeftMargin(0.13);
  c4->SetTicks(1,1);
  // color
  h_JES_v4->SetLineColor(kRed);
  h_JER_v4->SetLineColor(kOrange+7);
  h_JAR_v4->SetLineColor(kYellow+2);
  h_LSR_v4->SetLineColor(kGreen+2);
  h_Prior_v4->SetLineColor(kCyan+1);
  h_trkGap_v4->SetLineColor(kBlue);
  h_HF_v4->SetLineColor(kViolet);
  h_ITER_v4->SetLineColor(kPink+7);
  h_total_v4->SetLineColor(kBlack);
  // line width
  h_JES_v4->SetLineWidth(3);
  h_JER_v4->SetLineWidth(3);
  h_JAR_v4->SetLineWidth(3);
  h_LSR_v4->SetLineWidth(3);
  h_Prior_v4->SetLineWidth(3);
  h_trkGap_v4->SetLineWidth(3);
  h_HF_v4->SetLineWidth(3);
  h_ITER_v4->SetLineWidth(3);
  h_total_v4->SetLineWidth(3);
  // draw
  h_total_v4->GetXaxis()->SetLabelSize(0.05);
  TAxis *xAxis2 = h_total_v4->GetXaxis();
  xAxis2->SetBinLabel(1, "0 < Q_{T} < 12 GeV");
  xAxis2->SetBinLabel(2, "12 < Q_{T} < 40 GeV");
  h_total_v4->SetTitle("");
  h_total_v4->GetYaxis()->SetTitle("contribution to systematics (10^{-2})");
  h_total_v4->GetYaxis()->SetRangeUser(0,0.06);
  h_total_v4->Draw("hist");
  h_JES_v4->Draw("hist same");
  h_JER_v4->Draw("hist same");
  h_JAR_v4->Draw("hist same");
  h_LSR_v4->Draw("hist same");
  h_Prior_v4->Draw("hist same");
  h_trkGap_v4->Draw("hist same");
  h_HF_v4->Draw("hist same");
  h_ITER_v4->Draw("hist same");
  drawLegendStr9(h_JES_v4, h_JER_v4, h_JAR_v4, h_LSR_v4, h_Prior_v4, h_trkGap_v4, h_HF_v4, h_ITER_v4, h_total_v4, 0.25, 0.825, 0.725, 0.855, "JES", "JER", "JAR", "LSR", "Prior", "Tracker gap", "HF", "Iterations", "Total",3);
  drawText(.13, .915, "#bf{CMS} #it{work in progress}", kBlack, 28);
  drawText(0.53, 0.915, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);
  c4->SaveAs("Pics/systematics_rapidity_v4.pdf");

  // draw misses
  auto *c5 = new TCanvas("c5", "c5",900,900);
  c5->SetRightMargin(0.14);
  h2_misses_rap0->SetStats(0);
  h2_misses_rap0->SetTitle(";dijet y;#phi [radians]");
  h2_misses_rap0->Draw("colz");
  c5->SaveAs("Pics/misses_rap0.png");
  auto *c6 = new TCanvas("c6", "c6",900,900);
  c6->SetRightMargin(0.14);
  h2_misses_rap1->SetStats(0);
  h2_misses_rap1->SetTitle(";dijet y;#phi [radians]");
  h2_misses_rap1->Draw("colz");
  c6->SaveAs("Pics/misses_rap1.png");
 
}
