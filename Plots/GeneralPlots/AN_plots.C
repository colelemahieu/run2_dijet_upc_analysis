// AN_plots.C
// This code produces general plots for the Analysis Note

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

void drawLegendNoise(TH1 *h1, TH1 *h2, float x1, float x2, float y1, float y2, string text1, string text2, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "le");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "lep");
  //legend->SetTextSize(0.055);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }



void nice_hist2D(TH2 *h2, const char *titleX, const char *titleY, const char *name)
{
  TString uniqueCanvasName = Form("canvas_%p", h2);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
  canvas->SetLeftMargin(0.16);
  canvas->SetRightMargin(0.2);
  h2->SetStats(0);
  h2->SetTitle("");
  h2->GetXaxis()->SetTitle(titleX);
  h2->GetXaxis()->SetTitleSize(0.05);
  h2->GetXaxis()->SetTitleOffset(0.82);
  h2->GetYaxis()->SetTitle(titleY);
  h2->GetYaxis()->SetTitleSize(0.05);
  h2->GetYaxis()->SetTitleOffset(0.75);
  h2->Draw("colz");
  //drawText(0.16, 0.915, "#bf{CMS} #it{Preliminary}", kBlack, 26);
  //drawText(0.45, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  canvas->SaveAs(name);
  delete canvas;
}



void AN_plots(string genPythiaFile, string recoPythiaFile, string dataFile, string unfoldedFile_rap0, string unfoldedFile_rap1)
{
  
  // Read in Files
  TFile *genPythia = new TFile(genPythiaFile.c_str());
  TFile *recoPythia = new TFile(recoPythiaFile.c_str());
  TFile *data = new TFile(dataFile.c_str());
  TFile *data0n0n = new TFile("Files/allPlots_R4_0n0n.root");
  TFile *unfolded = new TFile(unfoldedFile_rap0.c_str());
  TFile *unfolded_rap1 = new TFile(unfoldedFile_rap1.c_str());
  TFile *noise = new TFile("../noisePlots.root");
  TFile *vtx_noCut = new TFile("/home/colelemahieu/View/cutPlots/vtxPlot_justFilters.root");
  TFile *vtx_cut = new TFile("/home/colelemahieu/View/cutPlots/vtxPlot_allCondor_cuts.root");
  TFile *nJets_cut = new TFile("/home/colelemahieu/View/cutPlots/nJetsPlot.root");
  TFile *nJets_cut_pythia = new TFile("/home/colelemahieu/View/cutPlots/nJetsPlot_pythia.root");
  TFile *zdc_vtxCut = new TFile("/home/colelemahieu/View/cutPlots/zdcPlots.root");
  TFile *jetEtaCut = new TFile("/home/colelemahieu/View/cutPlots/jetEtaPlot.root");

  
  // directory to write to
  string dirPath = "forAN/";

  
  // Data Histograms
  TH2F *h2_QTPT = (TH2F*)data->Get("h2_QTPT");
  TH2F *h2_rapgaps_0nXn = (TH2F*)data->Get("h2_rapgaps_0nXn");
  TH2F *h2_rapgaps_Xn0n = (TH2F*)data->Get("h2_rapgaps_Xn0n");
  TH1F *h_heP_2p8 = (TH1F*)data->Get("h_heP_2p8");
  TH1F *h_heM_2p8 = (TH1F*)data->Get("h_heM_2p8");
  TH1F *h_eeP_2p8 = (TH1F*)data->Get("h_eeP_2p8");
  TH1F *h_eeM_2p8 = (TH1F*)data->Get("h_eeM_2p8");
  TH2F *h2_phi12_rap_qt0_data = (TH2F*)data->Get("h2_phi12_rap_qt0");
  TH2F *h2_phi12_rap_qt1_data = (TH2F*)data->Get("h2_phi12_rap_qt1");
  TH2D *h2_cosQTPT_QT_mpi_data = (TH2D*)data0n0n->Get("h2_cosQTPT_QT_mpi");
  TH1F *h_bjorkenX = (TH1F*)data->Get("h_bjorkenX");

  // Noise Histogram
  TH1F *h_pfle_HEp_2p8 = (TH1F*)noise->Get("h_pfle_HEp_2p8");
  TH1F *h_pfle_HEm_2p8 = (TH1F*)noise->Get("h_pfle_HEm_2p8");
  TH1F *h_pfle_EEp_2p8 = (TH1F*)noise->Get("h_pfle_EEp_2p8");
  TH1F *h_pfle_EEm_2p8 = (TH1F*)noise->Get("h_pfle_EEm_2p8");

  // vtx Cut
  TH1F *h_vtx_noCut = (TH1F*)vtx_noCut->Get("h_vtx");
  TH1F *h_vtx = (TH1F*)vtx_cut->Get("h_vtx");
  TH1F *h_vtx_reco = (TH1F*)recoPythia->Get("h_zvtx");

  // nJets Cut
  TH1F *h_nJets = (TH1F*)nJets_cut->Get("h_nJets_cut");
  TH1F *h_nJets_pythia = (TH1F*)nJets_cut_pythia->Get("h_nJets_cut");

  // ZDC vtx Cut
  TH1F *h_zdcPlus_vtx = (TH1F*)zdc_vtxCut->Get("h_zdcPlus");
  TH1F *h_zdcMinus_vtx = (TH1F*)zdc_vtxCut->Get("h_zdcMinus");

  // jet eta Cut
  TH1F *h_jetEtaCut = (TH1F*)jetEtaCut->Get("h_jetEta");


  // Unfolded Histograms
  TH2F *h2_phi12_rap_qt0_unf = (TH2F*)unfolded->Get("h2_phi12_rap_qt0");
  TH2F *h2_phi12_rap_qt1_unf = (TH2F*)unfolded->Get("h2_phi12_rap_qt1");


  // Gen Histograms
  TH2F *h2_phi12_rap_qt0_gen = (TH2F*)genPythia->Get("h2_phi12_rap_qt0");
  TH2F *h2_phi12_rap_qt1_gen = (TH2F*)genPythia->Get("h2_phi12_rap_qt1");


  // Pythia Reco Histograms
  TH2F *h2_Pythia_QTPT = (TH2F*)recoPythia->Get("h2_QTPT");
  TH2F *h2_Pythia_rapgaps_Xn0n = (TH2F*)recoPythia->Get("h2_rapgaps_Xn0n");
  TH2D *h2_cosQTPT_QT_mpi_reco = (TH2D*)recoPythia->Get("h2_cosQTPT_QT_mpi");



  //////////////////////////// z vtx no cuts ///////////////////////////////////////////
  TCanvas *c14 = new TCanvas("c14","Title",800,800);
  c14->SetTickx(1);
  c14->SetTicky(1);
  c14->SetLogy();
  c14->SetLeftMargin(0.12);
  h_vtx_noCut->SetStats(0);
  h_vtx_noCut->SetTitle(";Z vertex [cm]; Counts");
  h_vtx_noCut->GetXaxis()->SetTitleSize(0.05);
  h_vtx_noCut->GetXaxis()->SetTitleOffset(0.9);
  h_vtx_noCut->GetYaxis()->SetTitleSize(0.05);
  h_vtx_noCut->GetYaxis()->SetTitleOffset(1.25);
  h_vtx_noCut->GetYaxis()->SetRangeUser(1,7500000);
  h_vtx_noCut->Draw();
  drawDashLine(-20, 0, -20, 7500000);
  drawDashLine(20, 0, 20, 7500000);
  drawText(0.115, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.52, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c14->SaveAs((dirPath + "vtx_noCuts.png").c_str());


  //////////////////////////// z vtx  ///////////////////////////////////////////////////
  TCanvas *c11 = new TCanvas("c11","Title",800,800);
  c11->SetTickx(1);
  c11->SetTicky(1);
  c11->SetLogy();
  c11->SetLeftMargin(0.12);
  h_vtx->SetStats(0);
  h_vtx_reco->Scale(h_vtx->Integral()/h_vtx_reco->Integral());
  h_vtx_reco->SetLineColor(kRed);
  h_vtx->SetTitle(";Z vertex [cm]; Counts");
  h_vtx->GetXaxis()->SetTitleSize(0.05);
  h_vtx->GetXaxis()->SetTitleOffset(0.9);
  h_vtx->GetYaxis()->SetTitleSize(0.05);
  h_vtx->GetYaxis()->SetTitleOffset(1.25);
  h_vtx->GetYaxis()->SetRangeUser(1,7500000);
  h_vtx->Draw();
  h_vtx_reco->Draw("hist same");
  drawLegendStr(h_vtx, h_vtx_reco, 0.175,0.84,0.75,0.85,"data", "Pythia reco");
  drawText(0.175, 0.68, "|vtx_{z}| < 20 cm", kBlack, 30);
  drawText(0.175, 0.62, "0nXn or Xn0n", kBlack, 30);
  drawText(0.175, 0.56, "skip nJet=0,1", kBlack, 30);
  drawText(0.175, 0.50, "|#eta_{jets}| < 3.0", kBlack, 30);
  drawText(0.175, 0.44, "p_{T,1} > 30 GeV", kBlack, 30);
  drawText(0.175, 0.38, "p_{T,2} > 20 GeV", kBlack, 30);
  drawText(0.115, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.52, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c11->SaveAs((dirPath + "vtx_cut.png").c_str());



  /////////////////////// ZDC Minus and Plus Cut ////////////////////////////////////////////////
  TCanvas *c9 = new TCanvas("c9","Title",800,800);
  c9->SetTickx(1);
  c9->SetTicky(1);
  c9->SetLogy();
  c9->SetLeftMargin(0.12);
  float zdcm_max=h_zdcMinus_vtx->GetMaximum();
  h_zdcMinus_vtx->SetStats(0);
  h_zdcMinus_vtx->SetTitle(";ZDC- Energy [GeV]; Counts");
  h_zdcMinus_vtx->GetXaxis()->SetTitleSize(0.05);
  h_zdcMinus_vtx->GetXaxis()->SetTitleOffset(0.9);
  h_zdcMinus_vtx->GetYaxis()->SetTitleSize(0.05);
  h_zdcMinus_vtx->GetYaxis()->SetTitleOffset(1.1);
  h_zdcMinus_vtx->GetYaxis()->SetRangeUser(2000,2000000);
  h_zdcMinus_vtx->Draw();
  drawDashLine(1200, 0, 1200, 2000000);
  drawText(0.4, 0.8, "|vtx_{z}| < 20 cm", kBlack, 32);
  drawText(0.4, 0.74, "PF ch. hadron > 1", kBlack, 32);
  drawText(0.115, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.52, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c9->SaveAs((dirPath + "zdcMinus_cuts.png").c_str());

  TCanvas *c10 = new TCanvas("c10","Title",800,800);
  c10->SetTickx(1);
  c10->SetTicky(1);
  c10->SetLogy();
  c10->SetLeftMargin(0.12);
  h_zdcPlus_vtx->SetStats(0);
  float zdcp_max=h_zdcPlus_vtx->GetMaximum();
  h_zdcPlus_vtx->SetTitle(";ZDC+ Energy [GeV]; Counts");
  h_zdcPlus_vtx->GetXaxis()->SetTitleSize(0.05);
  h_zdcPlus_vtx->GetXaxis()->SetTitleOffset(0.9);
  h_zdcPlus_vtx->GetYaxis()->SetTitleSize(0.05);
  h_zdcPlus_vtx->GetYaxis()->SetTitleOffset(1.1);
  h_zdcPlus_vtx->GetYaxis()->SetRangeUser(2000,1000000);
  h_zdcPlus_vtx->Draw();
  drawDashLine(1200, 0, 1200, 1000000);
  drawText(0.4, 0.8, "|vtx_{z}| < 20 cm", kBlack, 32);
  drawText(0.4, 0.74, "PF ch. hadron > 1", kBlack, 32);
  drawText(0.115, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.55, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c10->SaveAs((dirPath + "zdcPlus_cuts.png").c_str());



  ///////////////////////// nJets cut ////////////////////////////////////////////////
  TCanvas *c12 = new TCanvas("c12","Title",800,800);
  c12->SetTickx(1);
  c12->SetTicky(1);
  c12->SetLeftMargin(0.12);
  h_nJets->SetStats(0);
  h_nJets->SetTitle(";Number of jets; Counts");
  h_nJets->GetXaxis()->SetTitleSize(0.05);
  h_nJets->GetXaxis()->SetTitleOffset(0.9);
  h_nJets->GetYaxis()->SetTitleSize(0.05);
  h_nJets->GetYaxis()->SetTitleOffset(1.25);
  h_nJets->GetYaxis()->SetRangeUser(0,1300000);
  h_nJets->Draw();
  drawDashLine(2, 0, 2, 1300000);
  drawText(0.51, 0.82, "|vtx_{z}| < 20 cm", kBlack, 32);
  drawText(0.51, 0.76, "PF ch. hadron > 1", kBlack, 32);
  drawText(0.51, 0.70, "0nXn or Xn0n", kBlack, 32);
  drawText(0.115, 0.95, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.52, 0.95, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c12->SaveAs((dirPath + "nJets_cut.png").c_str());



  ///////////////////////// nJets cut pythia ////////////////////////////////////////////////
  TCanvas *c125 = new TCanvas("c125","Title",800,800);
  c125->SetTickx(1);
  c125->SetTicky(1);
  c125->SetLeftMargin(0.12);
  h_nJets_pythia->SetStats(0);
  h_nJets_pythia->SetTitle(";Number of jets; Counts");
  h_nJets_pythia->GetXaxis()->SetTitleSize(0.05);
  h_nJets_pythia->GetXaxis()->SetTitleOffset(0.9);
  h_nJets_pythia->GetYaxis()->SetTitleSize(0.05);
  h_nJets_pythia->GetYaxis()->SetTitleOffset(1.25);
  h_nJets_pythia->GetYaxis()->SetRangeUser(0,4750000);
  h_nJets_pythia->Draw();
  drawDashLine(2, 0, 2, 4750000);
  drawText(0.51, 0.82, "Pythia", kBlack, 32);
  drawText(0.51, 0.76, "|vtx_{z}| < 20 cm", kBlack, 32);
  drawText(0.51, 0.70, "PF ch. hadron > 1", kBlack, 32);
  drawText(0.115, 0.95, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.52, 0.95, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c125->SaveAs((dirPath + "nJets_cut_pythia.png").c_str());



  ///////////////////////// jet eta cut ////////////////////////////////////////////////
  TCanvas *c13 = new TCanvas("c13","Title",800,800);
  c13->SetTickx(1);
  c13->SetTicky(1);
  c13->SetLeftMargin(0.15);
  h_jetEtaCut->SetStats(0);
  h_jetEtaCut->SetTitle(";Jet_{leading, subleading} #eta; Counts");
  h_jetEtaCut->GetXaxis()->SetTitleSize(0.05);
  h_jetEtaCut->GetXaxis()->SetTitleOffset(0.9);
  h_jetEtaCut->GetYaxis()->SetTitleSize(0.05);
  h_jetEtaCut->GetYaxis()->SetTitleOffset(1.5);
  h_jetEtaCut->GetYaxis()->SetRangeUser(0,35000);
  h_jetEtaCut->Draw();
  drawDashLine(-3.0, 0, -3.0, 35000);
  drawDashLine(3.0, 0, 3.0, 35000);
  drawText(0.38, 0.84, "|vtx_{z}| < 20 cm", kBlack, 31);
  drawText(0.38, 0.79, "PF ch. hadron > 1", kBlack, 31);
  drawText(0.38, 0.75, "0nXn or Xn0n", kBlack, 31);
  drawText(0.38, 0.70, "skip nJet=0,1", kBlack, 31);
  drawText(0.15, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.52, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c13->SaveAs((dirPath + "jetEta_cut.png").c_str());


  

  //////////////////////// 2D PT vs QT /////////////////////////////////////////////////
  

  TCanvas *c1 = new TCanvas("c1","Title",800,800);
  c1->SetLeftMargin(0.12);
  h2_QTPT->SetTitle(";Q_{T} [GeV]; P_{T} [GeV]");
  h2_QTPT->GetXaxis()->SetTitleSize(0.05);
  h2_QTPT->GetXaxis()->SetTitleOffset(0.87);
  h2_QTPT->GetYaxis()->SetTitleSize(0.05);
  h2_QTPT->GetYaxis()->SetTitleOffset(1.1);
  h2_QTPT->SetStats(0);
  h2_QTPT->Draw("colz");
  // shade 
  double ymin = h2_QTPT->GetYaxis()->GetXmin(); 
  double x[4] = {20, 40, 40, 20};
  double y[4] = {20, 40, ymin, ymin};
  TGraph *shade = new TGraph(4, x, y);
  shade->SetFillColorAlpha(kGray+1, 0.6); 
  shade->SetLineColorAlpha(0, 0);         
  shade->Draw("F same");
  drawRedDashLine(20, 20, 40, 40);
  drawText(0.11, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.52, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c1->SaveAs((dirPath + "qtpt_2h.png").c_str());

  
  TCanvas *c2 = new TCanvas("c2","Title",800,800);
  c2->SetLeftMargin(0.12);
  c2->SetRightMargin(0.12);
  h2_Pythia_QTPT->SetTitle(";Q_{T} [GeV]; P_{T} [GeV]");
  h2_Pythia_QTPT->GetXaxis()->SetTitleSize(0.05);
  h2_Pythia_QTPT->GetXaxis()->SetTitleOffset(0.87);
  h2_Pythia_QTPT->GetYaxis()->SetTitleSize(0.05);
  h2_Pythia_QTPT->GetYaxis()->SetTitleOffset(1.1);
  h2_Pythia_QTPT->SetStats(0);
  h2_Pythia_QTPT->Draw("colz");
  shade->Draw("F same");
  drawRedDashLine(20, 20, 40, 40);
  drawText(0.11, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.52, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c2->SaveAs((dirPath + "qtpt_2h_Pythia.png").c_str());


  
  /////////////////////// rapidity gaps 2D Hist ///////////////////////////////////////

  TCanvas *c4 = new TCanvas("c4","Title",800,800);
  c4->SetRightMargin(0.12);
  c4->SetLogz();
  h2_rapgaps_0nXn->SetStats(0);
  h2_rapgaps_0nXn->SetTitle(";0nXn: #Delta#eta-;0nXn: #Delta#eta+");
  h2_rapgaps_0nXn->GetXaxis()->SetTitleSize(0.05);
  h2_rapgaps_0nXn->GetXaxis()->SetTitleOffset(0.85);
  h2_rapgaps_0nXn->GetYaxis()->SetTitleSize(0.05);
  h2_rapgaps_0nXn->GetYaxis()->SetTitleOffset(0.85);
  h2_rapgaps_0nXn->Draw("colz");
  drawText(0.65, 0.75, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.65, 0.69, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.65, 0.63, "|#eta_{jets}| < 3.0", kBlack, 31);
  drawDashLine(1.8,0,1.8,5);
  drawText(0.11, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.50, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c4->SaveAs((dirPath + "rapgaps_0nXn.png").c_str());

  
  TCanvas *c5 = new TCanvas("c5","Title",800,800);
  c5->SetRightMargin(0.12);
  c5->SetLogz();
  h2_rapgaps_Xn0n->SetStats(0);
  h2_rapgaps_Xn0n->SetTitle(";Xn0n: #Delta#eta-;Xn0n: #Delta#eta+");
  h2_rapgaps_Xn0n->GetXaxis()->SetTitleSize(0.05);
  h2_rapgaps_Xn0n->GetXaxis()->SetTitleOffset(0.85);
  h2_rapgaps_Xn0n->GetYaxis()->SetTitleSize(0.05);
  h2_rapgaps_Xn0n->GetYaxis()->SetTitleOffset(0.85);
  h2_rapgaps_Xn0n->Draw("colz");
  drawText(0.65, 0.75, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.65, 0.69, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.65, 0.63, "|#eta_{jets}| < 3.0", kBlack, 31);
  drawDashLine(0,1.8,5,1.8);
  drawText(0.11, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.50, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c5->SaveAs((dirPath + "rapgaps_Xn0n.png").c_str());


  TCanvas *c6 = new TCanvas("c6","Title",800,800);
  c6->SetRightMargin(0.13);
  //c6->SetLogz();
  h2_Pythia_rapgaps_Xn0n->SetStats(0);
  h2_Pythia_rapgaps_Xn0n->SetTitle(";Xn0n: #Delta#eta-;Xn0n: #Delta#eta+");
  h2_Pythia_rapgaps_Xn0n->SetTitle(";Xn0n: #Delta#eta-;Xn0n: #Delta#eta+");
  h2_Pythia_rapgaps_Xn0n->GetXaxis()->SetTitleSize(0.05);
  h2_Pythia_rapgaps_Xn0n->GetXaxis()->SetTitleOffset(0.85);
  h2_Pythia_rapgaps_Xn0n->GetYaxis()->SetTitleSize(0.05);
  h2_Pythia_rapgaps_Xn0n->GetYaxis()->SetTitleOffset(0.85);
  h2_Pythia_rapgaps_Xn0n->Draw("colz");
  drawText(0.65, 0.75, "p_{T,1} > 30 GeV", kBlack, 31);
  drawText(0.65, 0.69, "p_{T,2} > 20 GeV", kBlack, 31);
  drawText(0.65, 0.63, "|#eta_{jets}| < 3.0", kBlack, 31);
  drawDashLine(0,1.8,5,1.8);
  drawText(0.11, 0.915, "#bf{CMS} #it{Internal}", kBlack, 26);
  drawText(0.50, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 26);
  c6->SaveAs((dirPath + "rapgaps_pythia.png").c_str());


  /////////////////// EE+ CUT  ///////////////////////////////////////
  TCanvas *c8 = new TCanvas("c8","Title",800,800);
  c8->SetTickx(1);
  c8->SetTicky(1);
  c8->SetLogy();
  h_pfle_EEp_2p8->SetLineColor(kBlack);
  h_pfle_EEp_2p8->Scale(1/h_pfle_EEp_2p8->Integral());
  h_pfle_EEp_2p8->SetStats(0);
  h_eeP_2p8->SetLineColor(kRed);
  h_eeP_2p8->SetMarkerColor(kRed);
  h_eeP_2p8->SetMarkerStyle(kFullDotLarge);
  h_eeP_2p8->Scale(1/h_eeP_2p8->Integral());
  h_eeP_2p8->SetStats(0);
  h_eeP_2p8->GetXaxis()->SetTitleSize(0.05);
  h_eeP_2p8->GetXaxis()->SetTitleOffset(0.9);
  h_eeP_2p8->GetYaxis()->SetTitleSize(0.05);
  h_eeP_2p8->GetYaxis()->SetTitleOffset(1.1);
  h_eeP_2p8->SetTitle(";Photon PF Cand. Leading E [GeV]; Norm. Counts");
  //h_eeP_2p8->GetYaxis()->SetRangeUser(0,1.2);
  h_eeP_2p8->Draw("hist pE");
  h_pfle_EEp_2p8->Draw("hist sameE");
  drawText(.65, .825,"2.8<#eta<3.0",kBlack,32);
  drawLegendStr(h_pfle_EEp_2p8, h_eeP_2p8, 0.575, 0.85, 0.7, 0.8,"2018 HIEmptyBX", "2018 UPC Xn0n");
  drawText(0.45, 0.6, "99% noise th.",kBlack,28);
  drawDashLine(16.2, 0, 16.2, 1.8);
  drawCMS_p(c8);
  c8->SaveAs((dirPath + "eeP_cut.png").c_str());

  /////////////////// EE- CUT  ///////////////////////////////////////
  TCanvas *c8m = new TCanvas("c8m","Title",800,800);
  c8m->SetTickx(1);
  c8m->SetTicky(1);
  c8m->SetLogy();
  h_pfle_EEm_2p8->SetLineColor(kBlack);
  h_pfle_EEm_2p8->Scale(1/h_pfle_EEm_2p8->Integral());
  h_pfle_EEm_2p8->SetStats(0);
  h_eeM_2p8->SetLineColor(kRed);
  h_eeM_2p8->SetMarkerColor(kRed);
  h_eeM_2p8->SetMarkerStyle(kFullDotLarge);
  h_eeM_2p8->Scale(1/h_eeM_2p8->Integral());
  h_eeM_2p8->SetStats(0);
  h_eeM_2p8->GetXaxis()->SetTitleSize(0.05);
  h_eeM_2p8->GetXaxis()->SetTitleOffset(0.9);
  h_eeM_2p8->GetYaxis()->SetTitleSize(0.05);
  h_eeM_2p8->GetYaxis()->SetTitleOffset(1.1);
  h_eeM_2p8->SetTitle(";Photon PF Cand. Leading E [GeV]; Norm. Counts");
  //h_eeP_2p8->GetYaxis()->SetRangeUser(0,1.2);
  h_eeM_2p8->Draw("hist pE");
  h_pfle_EEm_2p8->Draw("hist sameE");
  drawText(.65, .825,"-3.0<#eta<-2.8",kBlack,32);
  drawLegendStr(h_pfle_EEm_2p8, h_eeM_2p8, 0.575, 0.85, 0.7, 0.8,"2018 HIEmptyBX", "2018 UPC 0nXn");
  drawText(0.5, 0.45, "99% noise th.",kBlack,28);
  drawDashLine(19, 0, 19, 1.8);
  drawCMS_p(c8m);
  c8m->SaveAs((dirPath + "eeM_cut.png").c_str());
  

  //////////////////  HE+ CUT  ///////////////////////////////////////
  TCanvas *c7 = new TCanvas("c7","Title",800,800);
  c7->SetTickx(1);
  c7->SetTicky(1);
  h_pfle_HEp_2p8->Scale(1/h_pfle_HEp_2p8->Integral());
  h_pfle_HEp_2p8->SetLineColor(kBlack);
  h_heP_2p8->Scale(1/h_heP_2p8->Integral());
  h_heP_2p8->SetLineColor(kRed);
  h_heP_2p8->SetMarkerColor(kRed);
  h_heP_2p8->SetMarkerStyle(kFullDotLarge);
  h_heP_2p8->SetStats(0);
  h_heP_2p8->SetTitle(";Hadronic PF Cand. Leading E [GeV]; Norm. Counts");
  h_heP_2p8->GetXaxis()->SetTitleSize(0.05);
  h_heP_2p8->GetXaxis()->SetTitleOffset(0.9);
  h_heP_2p8->GetYaxis()->SetTitleSize(0.05);
  h_heP_2p8->GetYaxis()->SetTitleOffset(1.1);
  h_heP_2p8->GetYaxis()->SetRangeUser(0,0.395);
  h_heP_2p8->Draw("hist pE");
  h_pfle_HEp_2p8->Draw("hist sameE");
  drawText(.65, .825,"2.8<#eta<3.0",kBlack,32);
  drawText(.34, .6,"99% noise th.",kBlack,32);
  drawDashLine(1.06, 0, 1.06, 0.395);
  drawLegendNoise(h_pfle_HEp_2p8, h_heP_2p8, 0.575, 0.85, 0.7, 0.8, "2018 HIEmptyBX", "2018 UPC Xn0n");
  drawCMS_p(c7);
  c7->SaveAs((dirPath + "heP_cut.png").c_str());

  //////////////////  HE- CUT  ///////////////////////////////////////
  TCanvas *c7m = new TCanvas("c7m","Title",800,800);
  c7m->SetTickx(1);
  c7m->SetTicky(1);
  h_pfle_HEm_2p8->Scale(1/h_pfle_HEm_2p8->Integral());
  h_pfle_HEm_2p8->SetLineColor(kBlack);
  h_heM_2p8->Scale(1/h_heM_2p8->Integral());
  h_heM_2p8->SetLineColor(kRed);
  h_heM_2p8->SetMarkerColor(kRed);
  h_heM_2p8->SetMarkerStyle(kFullDotLarge);
  h_heM_2p8->SetStats(0);
  h_heM_2p8->SetTitle(";Hadronic PF Cand. Leading E [GeV]; Norm. Counts");
  h_heM_2p8->GetXaxis()->SetTitleSize(0.05);
  h_heM_2p8->GetXaxis()->SetTitleOffset(0.9);
  h_heM_2p8->GetYaxis()->SetTitleSize(0.05);
  h_heM_2p8->GetYaxis()->SetTitleOffset(1.1);
  h_heM_2p8->GetYaxis()->SetRangeUser(0,0.395);
  h_heM_2p8->Draw("hist pE");
  h_pfle_HEm_2p8->Draw("hist sameE");
  drawText(.65, .825,"-3.0<#eta<-2.8",kBlack,32);
  drawText(.34, .6,"99% noise th.",kBlack,32);
  drawDashLine(1.1, 0, 1.1, 0.395);
  drawLegendNoise(h_pfle_HEm_2p8, h_heM_2p8, 0.575, 0.85, 0.7, 0.8, "2018 HIEmptyBX", "2018 UPC 0nXn");
  drawCMS_p(c7m);
  c7m->SaveAs((dirPath + "heM_cut.png").c_str());



  ///////////////////////// bjorkenX ////////////////////////////////////////////////
  TCanvas *c17 = new TCanvas("c17","Title",800,800);
  c17->SetTickx(1);
  c17->SetTicky(1);
  c17->SetLeftMargin(0.12);
  c17->SetLogx();
  h_bjorkenX->SetStats(0);
  h_bjorkenX->SetTitle(";Bjorken x; Counts");
  h_bjorkenX->GetXaxis()->SetTitleSize(0.05);
  h_bjorkenX->GetXaxis()->SetTitleOffset(0.9);
  h_bjorkenX->GetYaxis()->SetTitleSize(0.05);
  h_bjorkenX->GetYaxis()->SetTitleOffset(1.25);
  h_bjorkenX->Draw();
  //drawText(0.2, 0.82, "|vtx_{z}| < 20 cm", kBlack, 32);
  //drawText(0.2, 0.76, "PF ch. hadron > 1", kBlack, 32);
  //drawText(0.2, 0.70, "0nXn or Xn0n", kBlack, 32);
  //drawText(0.115, 0.91, "#bf{CMS} #it{Preliminary}", kBlack, 26);
  // drawText(0.57, 0.91, "PbPb #sqrt{s}=5.02 TeV; 2018", kBlack, 26);
  c17->SaveAs((dirPath + "bjorkenX.png").c_str());




  ////////////////// GEN 2D phi vs rap' ///////////////////////////////
  nice_hist2D(h2_phi12_rap_qt0_gen, "y'", "#phi_{#vec{Q_{T}},#vec{P_{T}}} [radians]", (dirPath + "gen_phi_rap_qt0.png").c_str());
  nice_hist2D(h2_phi12_rap_qt1_gen, "y'", "#phi_{#vec{Q_{T}},#vec{P_{T}}} [radians]", (dirPath + "gen_phi_rap_qt1.png").c_str());


  ///////////////// DATA 2D phi vs rap' ///////////////////////////////
  nice_hist2D(h2_phi12_rap_qt0_data, "y'", "#phi_{#vec{Q_{T}},#vec{P_{T}}} [radians]", (dirPath + "data_phi_rap_qt0.png").c_str());
  nice_hist2D(h2_phi12_rap_qt1_data, "y'", "#phi_{#vec{Q_{T}},#vec{P_{T}}} [radians]", (dirPath + "data_phi_rap_qt1.png").c_str());

  /////////////// DATA 2D cos2phi vs QT  /////////////////////////////////
  auto *c15 = new TCanvas("c15","Title",900,900);
  c15->SetLeftMargin(0.16);
  c15->SetRightMargin(0.12);
  c15->SetLogz();
  h2_cosQTPT_QT_mpi_data->SetStats(0);
  h2_cosQTPT_QT_mpi_data->SetTitle("");
  h2_cosQTPT_QT_mpi_data->GetXaxis()->SetTitle("Q_{T} [GeV]");
  h2_cosQTPT_QT_mpi_data->GetXaxis()->SetTitleSize(0.05);
  h2_cosQTPT_QT_mpi_data->GetXaxis()->SetTitleOffset(0.82);
  h2_cosQTPT_QT_mpi_data->GetYaxis()->SetTitle("cos(2#phi)");
  h2_cosQTPT_QT_mpi_data->GetYaxis()->SetTitleSize(0.05);
  h2_cosQTPT_QT_mpi_data->GetYaxis()->SetTitleOffset(1.1);
  h2_cosQTPT_QT_mpi_data->Draw("colz");
  drawText(0.425, 0.915, "R = 0.4", kBlack, 35);
  drawText(0.16, 0.915, "0n0n", kBlack, 38);
  //drawText(0.16, 0.915, "#bf{CMS} #it{work in progress}", kBlack, 28);
  //drawText(0.55, 0.915, "PbPb #sqrt{s}=5.02 TeV; 2018", kBlack, 28);
  c15->SaveAs((dirPath + "data0n0n_cos2phi_qt.png").c_str());

  /////////////// RECO 2D cos2phi vs QT  /////////////////////////////////
  auto *c16 = new TCanvas("c16","Title",900,900);
  c16->SetLeftMargin(0.16);
  c16->SetRightMargin(0.125);
  h2_cosQTPT_QT_mpi_reco->SetStats(0);
  h2_cosQTPT_QT_mpi_reco->SetTitle("");
  h2_cosQTPT_QT_mpi_reco->GetXaxis()->SetTitle("Q_{T} [GeV]");
  h2_cosQTPT_QT_mpi_reco->GetXaxis()->SetTitleSize(0.05);
  h2_cosQTPT_QT_mpi_reco->GetXaxis()->SetTitleOffset(0.82);
  h2_cosQTPT_QT_mpi_reco->GetYaxis()->SetTitle("cos(2#phi_{#vec{Q_{T}},#vec{P_{T}}})");
  h2_cosQTPT_QT_mpi_reco->GetYaxis()->SetTitleSize(0.05);
  h2_cosQTPT_QT_mpi_reco->GetYaxis()->SetTitleOffset(1.3);
  h2_cosQTPT_QT_mpi_reco->Draw("colz");
  drawText(0.16, 0.915, "#bf{CMS} #it{work in progress}", kBlack, 28);
  drawText(0.55, 0.915, "PbPb #sqrt{s}=5.02 TeV; 2018", kBlack, 28);
  c16->SaveAs((dirPath + "reco_cos2phi_qt.png").c_str());


  ///////////////// UNFOLDED 2D phi vs rap' //////////////////////////////
  nice_hist2D(h2_phi12_rap_qt0_unf, "y'", "#phi_{#vec{Q_{T}},#vec{P_{T}}} [radians]", (dirPath + "unf_phi_rap_qt0.png").c_str());
  nice_hist2D(h2_phi12_rap_qt1_unf, "y'", "#phi_{#vec{Q_{T}},#vec{P_{T}}} [radians]", (dirPath + "unf_phi_rap_qt1.png").c_str());
  
}
