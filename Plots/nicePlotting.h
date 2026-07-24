// nicePlotting.h

#include <iostream>
#include <fstream>
#include <ctime>
#include "Riostream.h"
#include <TGraphAsymmErrors.h>
#include <vector>
#include <algorithm>
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
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "TVirtualFitter.h"
#include <TBox.h>


void drawText(float xp, float yp, const char *text, int textColor=kBlack, double textSize=22){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(textSize);
  tex->SetTextColor(textColor);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

void drawText_noNDC(float xp, float yp, const char *text, int textColor=kBlack, double textSize=22){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(textSize);
  tex->SetTextColor(textColor);
  tex->SetLineWidth(1);
  tex->Draw();
}

void drawLegendStr(TH1 *h1, TH1 *h2, float x1, float x2, float y1, float y2, string text1, string text2, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "lep");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "lep");
  legend->SetTextSize(0.045);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }

void drawLegendStr3(TH1 *h1, TH1 *h2, TH1 *h3, float x1, float x2, float y1, float y2, string text1, string text2, string text3, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "lep");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "lep");
  legend->AddEntry(h3, text3.c_str(), "lep");
  legend->SetTextSize(0.045);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }

void drawLegendStr3_prior(TH1 *h1, TH1 *h2, TH1 *h3, float x1, float x2, float y1, float y2, string text1, string text2, string text3, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "lep");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "lep");
  legend->AddEntry(h3, text3.c_str(), "lep");
  legend->SetTextSize(0.035);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }

void drawLegendStr4(TH1 *h1, TH1 *h2, TH1 *h3, TH1 *h4, float x1, float x2, float y1, float y2, string text1, string text2, string text3, string text4, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "lep");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "lep");
  legend->AddEntry(h3, text3.c_str(), "lep");
  legend->AddEntry(h4, text4.c_str(), "lep");
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }

void drawLegendStr5(TH1 *h1, TH1 *h2, TH1 *h3, TH1 *h4, TH1 *h5, float x1, float x2, float y1, float y2, string text1, string text2, string text3, string text4, string text5, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "lep");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "lep");
  legend->AddEntry(h3, text3.c_str(), "lep");
  legend->AddEntry(h4, text4.c_str(), "lep");
  legend->AddEntry(h5, text5.c_str(), "lep");
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }

void drawLegendSt6(TH1 *h1, TH1 *h2, TH1 *h3, TH1 *h4, TH1 *h5, TH1 *h6, float x1, float x2, float y1, float y2, string text1, string text2, string text3, string text4, string text5, string text6, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "lep");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "lep");
  legend->AddEntry(h3, text3.c_str(), "lep");
  legend->AddEntry(h4, text4.c_str(), "lep");
  legend->AddEntry(h5, text5.c_str(), "lep");
  legend->AddEntry(h6, text6.c_str(), "lep");
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }

void drawLegendProfile5(TProfile *h1, TProfile *h2, TProfile *h3, TProfile *h4, float x1, float x2, float y1, float y2, string text1, string text2, string text3, string text4, int nCol=1){
  TLegend* legend = new TLegend(x2,y2,x1,y1);
  legend->SetNColumns(nCol);
  legend->AddEntry(h1, text1.c_str(), "lep");   // l f p e
  legend->AddEntry(h2, text2.c_str(), "lep");
  legend->AddEntry(h3, text3.c_str(), "lep");
  legend->AddEntry(h4, text4.c_str(), "lep");
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  }

void nice_hist2D(TH2 *h2, const char *titleX, const char *titleY, const char *name)
{
  TString uniqueCanvasName = Form("canvas_%p", h2);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
  canvas->SetLeftMargin(0.13);
  canvas->SetRightMargin(0.13);
  h2->SetStats(0);
  h2->SetTitle("");
  h2->GetXaxis()->SetTitle(titleX);
  h2->GetYaxis()->SetTitle(titleY);
  h2->Draw("colz");
  canvas->SaveAs(name);
  delete canvas;
}

float find_hist_chi2(TH1 *h1, TH1 *h2)
{
  int binNumber = h1->GetNbinsX();
  int ndf = binNumber-1;
  float h1_value=0, h2_value=0, binDiff=0;
  float h1_error=0, h2_error=0, totError=0;
  float chi2=0, chi_num=0, chi_denom=0;

  for (int iBin=1; iBin<binNumber+1; iBin++)
    {
      h1_value=h1->GetBinContent(iBin);
      h2_value=h2->GetBinContent(iBin);
      binDiff=fabs(h1_value-h2_value);

      h1_error=h1->GetBinError(iBin);
      h2_error=h2->GetBinError(iBin);
      totError=sqrt(h1_error*h1_error + h2_error*h2_error);

      chi_num = binDiff*binDiff;
      chi_denom = totError*totError;
      chi2 = chi2 + chi_num/chi_denom;
    } // end bins loop

  return chi2;
}

float find_hist_chi2NDF(TH1 *h1, TH1 *h2)
{
  int binNumber = h1->GetNbinsX();
  int ndf = binNumber-1;
  float h1_value=0, h2_value=0, binDiff=0;
  float h1_error=0, h2_error=0, totError=0;
  float chi2=0, chi_num=0, chi_denom=0;

  for (int iBin=1; iBin<binNumber+1; iBin++)
    {
      h1_value=h1->GetBinContent(iBin);
      h2_value=h2->GetBinContent(iBin);
      binDiff=fabs(h1_value-h2_value);

      h1_error=h1->GetBinError(iBin);
      h2_error=h2->GetBinError(iBin);
      totError=sqrt(h1_error*h1_error + h2_error*h2_error);

      chi_num = binDiff*binDiff;
      chi_denom = totError*totError;
      chi2 = chi2 + chi_num/chi_denom;
    } // end bins loop

  return (chi2/ndf);
}

float find_hist_chi2_4bins(TH1 *h1, TH1 *h2)
{
  int binNumber = 4;
  int ndf = binNumber-1;
  float h1_value=0, h2_value=0, binDiff=0;
  float h1_error=0, h2_error=0, totError=0;
  float chi2=0, chi_num=0, chi_denom=0;

  for (int iBin=1; iBin<binNumber+1; iBin++)
    {
      h1_value=h1->GetBinContent(iBin);
      h2_value=h2->GetBinContent(iBin);
      binDiff=fabs(h1_value-h2_value);

      h1_error=h1->GetBinError(iBin);
      h2_error=h2->GetBinError(iBin);
      totError=sqrt(h1_error*h1_error + h2_error*h2_error);

      chi_num = binDiff*binDiff;
      chi_denom = totError*totError;
      chi2 = chi2 + chi_num/chi_denom;
    } // end bins loop

  return chi2;
}

float find_hist_chi2NDF_4bins(TH1 *h1, TH1 *h2)
{
  int binNumber = 4;
  int ndf = binNumber-1;
  float h1_value=0, h2_value=0, binDiff=0;
  float h1_error=0, h2_error=0, totError=0;
  float chi2=0, chi_num=0, chi_denom=0;

  for (int iBin=1; iBin<binNumber+1; iBin++)
    {
      h1_value=h1->GetBinContent(iBin);
      h2_value=h2->GetBinContent(iBin);
      binDiff=fabs(h1_value-h2_value);

      h1_error=h1->GetBinError(iBin);
      h2_error=h2->GetBinError(iBin);
      totError=sqrt(h1_error*h1_error + h2_error*h2_error);

      chi_num = binDiff*binDiff;
      chi_denom = totError*totError;
      chi2 = chi2 + chi_num/chi_denom;
    } // end bins loop

  return (chi2/ndf);
}

void makeResolution_histogram(TH1 *h1, const char *titleX, const char *titleY, const char *name, float xMin, float xMax, bool logScale=false)
{
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
  if (logScale==true) canvas->SetLogy();
  canvas->SetLeftMargin(0.13);
  canvas->SetBottomMargin(0.13);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  float mean = h1->GetMean();
  float sigma = h1->GetRMS();
  h1->SetStats(0);
  h1->SetTitle("");
  h1->GetXaxis()->SetTitle(titleX);
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleOffset(0.95);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleOffset(1.25);
  h1->GetXaxis()->SetRangeUser(xMin,xMax);
  h1->Draw();
  drawText(0.625, 0.8, Form("mean = %0.2f",mean), kBlack, 40);
  drawText(0.625, 0.75, Form("RMS = %0.2f",sigma), kBlack, 40);
  drawText(0.135, 0.915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.53, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 28);
  canvas->SaveAs(name);
  delete canvas;
}

void makeResolution_histogram5(TH1 *h1, TH1 *h2, TH1 *h3, TH1 *h4, TH1 *h5, const char *titleX, const char *titleY, const char *name, float xMin, float xMax, bool logScale=false)
{
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
  if (logScale==true) canvas->SetLogy();
  canvas->SetLeftMargin(0.13);
  canvas->SetBottomMargin(0.13);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  float mean1 = h1->GetMean();
  float sigma1 = h1->GetRMS();
  float sigma2 = h2->GetRMS();
  float sigma3 = h3->GetRMS();
  float sigma4 = h4->GetRMS();
  float sigma5 = h5->GetRMS();
  h1->SetStats(0);
  h1->SetTitle("");
  h1->GetXaxis()->SetTitle(titleX);
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleOffset(0.95);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleOffset(1.25);
  h1->GetXaxis()->SetRangeUser(xMin,xMax);
  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed);
  h3->SetLineColor(kGreen+3);
  h4->SetLineColor(kBlue);
  h5->SetLineColor(kViolet);
  h1->GetYaxis()->SetRangeUser(0,1500);
  h2->Scale(h1->Integral()/h2->Integral());
  h3->Scale(h1->Integral()/h3->Integral());
  h4->Scale(h1->Integral()/h4->Integral());
  h5->Scale(h1->Integral()/h5->Integral());
  h1->Draw("hist");
  h2->Draw("hist same");
  h3->Draw("hist same");
  h4->Draw("hist same");
  h5->Draw("hist same");
  //drawText(0.625, 0.8, Form("mean = %0.2f",mean), kBlack, 40);
  //drawText(0.625, 0.75, Form("RMS = %0.2f",sigma), kBlack, 40);
  TLegend* legend = new TLegend(0.875,0.875,0.145,0.7);
  //legend->SetNColumns(2);
  legend->SetTextSize(0.035);
  legend->AddEntry(h1, Form("0 GeV < Q_{T} < 8 GeV, RMS=%0.2f",sigma1), "l");   // l f p e
  legend->AddEntry(h2, Form("8 GeV < Q_{T} < 16 GeV, RMS=%0.2f",sigma2), "l");
  legend->AddEntry(h3, Form("16 GeV < Q_{T} < 24 GeV, RMS=%0.2f",sigma3), "l");
  legend->AddEntry(h4, Form("24 GeV < Q_{T} < 32 GeV, RMS=%0.2f",sigma4), "l");
  legend->AddEntry(h5, Form("32 GeV < Q_{T} < 40 GeV, RMS=%0.2f",sigma5), "l");
  legend->SetBorderSize(0);
  legend->Draw("SAME");
  drawText(0.135, 0.915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.53, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 28);
  canvas->SaveAs(name);
  delete canvas;
}

void makeResolution_histogramPhi(TH1 *h1, const char *titleX, const char *titleY, const char *name, float xMin, float xMax, bool logScale=false)
{
  // Gaussian Fit to central peak
  TF1 *gaus = new TF1("gaus","[0]*exp(-0.5*((x-[1])/[2])**2)",-0.5,0.5);
  gaus->SetParameters(3350, 0, 0.25);
  //h1->Fit(gaus, "R");
  
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
  if (logScale==true) canvas->SetLogy();
  canvas->SetLeftMargin(0.13);
  canvas->SetBottomMargin(0.13);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  float mean = h1->GetMean();
  float sigma = h1->GetRMS();
  h1->SetStats(0);
  h1->SetTitle("");
  h1->GetXaxis()->SetTitle(titleX);
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleOffset(0.95);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleOffset(1.25);
  h1->GetXaxis()->SetRangeUser(xMin,xMax);
  h1->Draw();
  drawText(0.625, 0.8, Form("mean = %0.2f",mean), kBlack, 40);
  drawText(0.625, 0.75, Form("RMS = %0.2f",sigma), kBlack, 40);
  //drawText(0.55, 0.75, Form("total RMS = %0.2f",sigma), kBlack, 40);
  //drawText(0.55, 0.7, Form("gaus fit #sigma = %0.2f",gaus->GetParameter(2)), kBlack, 40);
  drawText(0.135, 0.915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.53, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 28);
  canvas->SaveAs(name);
  delete canvas;
}

void makeResolution_histogramEta(TH1 *h1, const char *titleX, const char *titleY, const char *name, float xMin, float xMax, bool logScale=false)
{
  // Gaussian Fit to central peak
  TF1 *gaus = new TF1("gaus","[0]*exp(-0.5*((x-[1])/[2])**2)",-0.5,0.5);
  gaus->SetParameters(4425, 0, 0.25);
  //h1->Fit(gaus, "R");
  
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
  if (logScale==true) canvas->SetLogy();
  canvas->SetLeftMargin(0.13);
  canvas->SetBottomMargin(0.13);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  float mean = h1->GetMean();
  float sigma = h1->GetRMS();
  h1->SetStats(0);
  h1->SetTitle("");
  h1->GetXaxis()->SetTitle(titleX);
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleOffset(0.95);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleOffset(1.25);
  h1->GetXaxis()->SetRangeUser(xMin,xMax);
  h1->Draw();
  drawText(0.625, 0.8, Form("mean = %0.2f",mean), kBlack, 40);
  drawText(0.625, 0.75, Form("RMS = %0.2f",sigma), kBlack, 40);
  //drawText(0.55, 0.75, Form("total RMS = %0.2f",sigma), kBlack, 40);
  //drawText(0.55, 0.7, Form("gaus fit #sigma = %0.2f",gaus->GetParameter(2)), kBlack, 40);
  drawText(0.135, 0.915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.53, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 28);
  canvas->SaveAs(name);
  delete canvas;
}

void makeResolution_histogram2d(TH2 *h2, const char *titleX, const char *titleY, const char *name)
{
  TString uniqueCanvasName = Form("canvas_%p", h2);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  canvas->SetLeftMargin(0.13);
  canvas->SetRightMargin(0.13);
  h2->SetStats(0);
  h2->SetTitle("");
  h2->GetXaxis()->SetTitle(titleX);
  h2->GetXaxis()->SetTitleSize(0.05);
  h2->GetXaxis()->SetTitleOffset(0.87);
  h2->GetYaxis()->SetTitle(titleY);
  h2->GetYaxis()->SetTitleSize(0.05);
  h2->GetYaxis()->SetTitleOffset(1.15);
  h2->Draw("colz");
  drawText(0.135, 0.915, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.5, 0.915, "PbPb #sqrt{s_{NN}} = 5.02 TeV; 2018", kBlack, 28);
  canvas->SaveAs(name);
  delete canvas;
}

TH1F* makeResidual_histogram(TH1 *h1, TH1 *h2)
{
  const int binNumber = h1->GetNbinsX();
  const int xMin = h1->GetXaxis()->GetXmin();
  const int xMax = h2->GetXaxis()->GetXmax();
  vector<float> binEdges;
  for (int i=1; i<=(binNumber+1); i++)
    {
      binEdges.push_back(h1->GetBinLowEdge(i));
    }
  float h1_content=0, h2_content=0;
  float h1_error=0, h2_error=0, residual_error=0;

  TString uniqueCanvasName = Form("h_residual_%p", h2);
  TH1F *h_residual = new TH1F(uniqueCanvasName, "", binNumber, &binEdges[0]);

  // loop thru Bins
  for (int iBin=1; iBin<binNumber+1; iBin++)
    {
      h1_content=h1->GetBinContent(iBin);
      h2_content=h2->GetBinContent(iBin);

      h1_error=h1->GetBinError(iBin);
      h2_error=h2->GetBinError(iBin);
      residual_error = sqrt(h1_error*h1_error + h2_error*h2_error);
      
      
      h_residual->SetBinContent(iBin, (h1_content - h2_content));
      h_residual->SetBinError(iBin, residual_error);
    } // end bin loop

  return h_residual;
  
}

void makeNiceResidual_chi2(TH1F *h1, TH1F *h2, const char *titleX, const char *titleY, string label1, string label2, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80){
  
  TH1F *h_residual = new TH1F(*makeResidual_histogram(h1,h2));
  h_residual->SetMarkerColor(kBlack);
  h_residual->SetMarkerStyle(kFullDotLarge);

  auto *canvas = new TCanvas("canvas","Title",900,900);
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
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(0.9);
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
  drawText(.13, .915, "#bf{CMS} #it{work in progress}", kBlack, 28);
  drawText(0.6, 0.915, "PbPb: 5.02 TeV (2018)", kBlack, 28);
  drawLegendStr(h1, h2, 0.15, 0.3, 0.75, 0.875, label1, label2);
  drawText(0.1675, 0.7, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h2)), kBlack, 25);
  drawText(0.1675, 0.65, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h2)), kBlack, 25);
  //drawText(0.55, 0.8, "0 GeV < Q_{T} < 12 GeV", kBlack, 30);
  //drawText(0.55, 0.8, "12 GeV < Q_{T} < 40 GeV", kBlack, 30);
  
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
  h_residual->GetYaxis()->SetTitleOffset(0.45);
  h_residual->GetYaxis()->SetTitleSize(0.12);
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

  canvas->SaveAs("test.png");
  delete canvas;
}

void makeNiceResidual(TH1F *h1, TH1F *h2, const char *titleX, const char *titleY, string label1, string label2, const char *name, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80){
  
  TH1F *h_residual = new TH1F(*makeResidual_histogram(h1,h2));
  h_residual->SetMarkerColor(kBlack);
  h_residual->SetMarkerStyle(kFullDotLarge);

  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"Title",900,900);
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
  if (yMaximum==333) ymax = 1.9*h2->GetMaximum();
  h1->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(0.9);
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
  drawText(.13, .915, "#bf{CMS} #it{work in progress}", kBlack, 28);
  drawText(0.6, 0.915, "PbPb: 5.02 TeV (2018)", kBlack, 28);
  drawLegendStr(h1, h2, 0.15, 0.3, 0.75, 0.875, label1, label2);
  //drawText(0.55, 0.8, "0 GeV < Q_{T} < 1
  

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
  //string ratio_label=label1 + " - " + label2;
  string ratio_label="residual";
  float ymax_r = h_residual->GetMaximum();
  float ymin_r = h_residual->GetMinimum();
  float yFactor=1;
  if (fabs(ymax_r)>fabs(ymin_r)) yFactor=2*ymax_r;
  if (fabs(ymax_r)<fabs(ymin_r)) yFactor=2*fabs(ymin_r);
  h_residual->GetYaxis()->SetRangeUser(0-yFactor, yFactor);
  h_residual->GetXaxis()->SetTitle(titleX);
  h_residual->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual->GetYaxis()->SetTitleOffset(0.45);
  h_residual->GetYaxis()->SetTitleSize(0.12);
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
}

void pad3_2(TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h1b, TH1F *h2b, TH1F *h3b, const char *titleX, const char *titleY, string label1, string label2, const char *name, float total_sys_R2, float total_sys, float total_sys_R6, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80)
{
  // Residuals
  TH1D *h_residual_1 = (TH1D*)h1->Clone("h_residual_1");
  h_residual_1->Add(h1b, -1);  
  h_residual_1->SetMarkerColor(kBlack);
  h_residual_1->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_2 = (TH1D*)h2->Clone("h_residual_2");
  h_residual_2->Add(h2b, -1);  
  h_residual_2->SetMarkerColor(kBlack);
  h_residual_2->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_3 = (TH1D*)h3->Clone("h_residual_3");
  h_residual_3->Add(h3b, -1);  
  h_residual_3->SetMarkerColor(kBlack);
  h_residual_3->SetMarkerStyle(kFullDotLarge);
  

  // Plotting
  gStyle->SetOptStat(0);
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",1200,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.33,0.36,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p2","p2",0.36,0.33,0.66,0.99,0); p2->Draw();
  TPad* p3 = new TPad("p3","p3",0.66,0.33,0.99,0.99,0); p3->Draw();
  TPad* p4 = new TPad("p4","p4",0.01,0.01,0.36,0.33,0); p4->Draw();
  TPad* p5 = new TPad("p5","p5",0.36,0.01,0.66,0.33,0); p5->Draw();
  TPad* p6 = new TPad("p6","p6",0.66,0.01,0.99,0.33,0); p6->Draw();
  p1->SetRightMargin(0.025), p1->SetBottomMargin(0);
  p4->SetRightMargin(0.025), p4->SetTopMargin(0);
  p2->SetLeftMargin(0.025), p2->SetRightMargin(0.025), p2->SetBottomMargin(0);
  p5->SetLeftMargin(0.025), p5->SetRightMargin(0.025), p5->SetTopMargin(0);
  p3->SetLeftMargin(0.025), p3->SetBottomMargin(0);
  p6->SetLeftMargin(0.025), p6->SetTopMargin(0);

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  p1->cd();
  p1->SetLeftMargin(0.175);
  //main->SetBottomMargin(0.11);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h1->SetStats(0);
  h1b->SetStats(0);
  float ymax=yMaximum;
  if (yMaximum==333) ymax = 2*h2->GetMaximum();
  h1->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.08);
  h1->GetYaxis()->SetLabelSize(0.06);
  h1->GetYaxis()->SetTitleOffset(1.1);
  h1->GetYaxis()->SetNdivisions(707);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(1.5);
  h1->SetMarkerStyle(kFullDotLarge);
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h1b->SetLineWidth(2);
  h1b->SetMarkerSize(1.5);
  h1b->SetMarkerStyle(kFullSquare);
  h1b->SetMarkerColor(kRed);
  h1b->SetLineColor(kRed);
  h1->SetTitle("");
  h1b->SetTitle("");
  h1->Draw("hist pE");
  h1b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys_R2;
        double yHigh = binContent+total_sys_R2;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  drawLegendStr(h1, h1b, 0.25, 0.55, 0.675, 0.85, label1, label2);
  drawText(.625, .81, "r = 0.2", kBlack, 28);
  drawText(0.625, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h1b)), kBlack, 25);
  drawText(0.625, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h1b)), kBlack, 25);

  p4->cd();
  //ratio->SetTopMargin(0.035);
  p4->SetLeftMargin(0.175);
  p4->SetBottomMargin(0.29);
  p4->SetTickx(1);
  p4->SetTicky(1);
  h_residual_1->SetStats(0);
  h_residual_1->SetLineColor(kBlack);
  h_residual_1->GetXaxis()->SetLabelSize(0.12);
  h_residual_1->GetXaxis()->SetTitleSize(0.15);  
  h_residual_1->GetXaxis()->SetTitleOffset(0.8);
  h_residual_1->GetYaxis()->SetLabelSize(0.12);
  h_residual_1->GetYaxis()->SetTitleSize(0.04);
  h_residual_1->GetYaxis()->SetTitleOffset(1.6);
  string ratio_label="Data - MC";
  h_residual_1->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_1->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual_1->GetYaxis()->SetTitleOffset(0.5);
  h_residual_1->GetYaxis()->SetTitleSize(0.17);
  h_residual_1->GetXaxis()->SetNdivisions(707);
  h_residual_1->GetYaxis()->SetNdivisions(303);
  h_residual_1->SetMarkerSize(1.5);
  h_residual_1->SetLineWidth(2);
  h_residual_1->GetXaxis()->SetTitle("");
  h_residual_1->Draw("same hist p");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys_R2;
        double yHigh = resContent+total_sys_R2;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  float xmax = h_residual_1->GetXaxis()->GetXmax();
  float xmin = h_residual_1->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,0,xmax,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h_residual_1->Draw("same hist pE");
  

  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h2->SetStats(0);
  h2b->SetStats(0);
  h2->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h2->GetXaxis()->SetLabelSize(0.0000000000001);
  h2->GetYaxis()->SetLabelSize(0.0000000000001);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(1.5);
  h2->SetMarkerStyle(kFullDotLarge);
  h2->SetMarkerColor(kBlack);
  h2->SetLineColor(kBlack);
  h2b->SetLineWidth(2);
  h2b->SetMarkerSize(1.5);
  h2b->SetMarkerStyle(kFullSquare);
  h2b->SetMarkerColor(kRed);
  h2b->SetLineColor(kRed);
  h2->SetTitle("");
  h2b->SetTitle("");
  h2->Draw("hist pE");
  h2b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys;
        double yHigh = binContent+total_sys;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  drawText(.425, .81, "r = 0.4", kBlack, 28);
  drawText(.425, .915, "0nXn", kBlack, 29);
  drawText(0.425, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h2, h2b)), kBlack, 25);
  drawText(0.425, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h2, h2b)), kBlack, 25);

  p5->cd();
  //ratio->SetTopMargin(0.035);
  //ratio->SetLeftMargin(0.125);
  p5->SetBottomMargin(0.29);
  p5->SetTickx(1);
  p5->SetTicky(1);
  h_residual_2->SetStats(0);
  h_residual_2->SetLineColor(kBlack);
  h_residual_2->SetTitle("");
  h_residual_2->GetXaxis()->SetLabelSize(0.12);
  h_residual_2->GetXaxis()->SetTitleSize(0.15);  
  h_residual_2->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_2->GetYaxis()->SetTitleSize(0.04);
  h_residual_2->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_2->GetXaxis()->SetTitleOffset(0.9);
  h_residual_2->GetXaxis()->SetNdivisions(707);
  h_residual_2->GetXaxis()->SetTitle(titleX);
  h_residual_2->SetMarkerSize(1.5);
  h_residual_2->SetLineWidth(2);
  //ratio->SetBottomMargin(0.275);
  h_residual_2->Draw("same hist p");
  line->Draw("LSAME");
  h_residual_2->Draw("same hist pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys;
        double yHigh = resContent+total_sys;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  

  p3->cd();
  p3->SetTickx(1);
  p3->SetTicky(1);
  h3->SetStats(0);
  h3b->SetStats(0);
  h3->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h3->GetXaxis()->SetLabelSize(0.0000000000001);
  h3->GetYaxis()->SetLabelSize(0.0000000000001);
  h3->SetLineWidth(2);
  h3->SetMarkerSize(1.5);
  h3->SetMarkerStyle(kFullDotLarge);
  h3->SetMarkerColor(kBlack);
  h3->SetLineColor(kBlack);
  h3b->SetLineWidth(2);
  h3b->SetMarkerSize(1.5);
  h3b->SetMarkerStyle(kFullSquare);
  h3b->SetMarkerColor(kRed);
  h3b->SetLineColor(kRed);
  h3->SetTitle("");
  h3b->SetTitle("");
  h3->Draw("hist pE");
  h3b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys_R6;
        double yHigh = binContent+total_sys_R6;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  drawText(.45, .81, "r = 0.6", kBlack, 28);
  drawText(0.45, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h3, h3b)), kBlack, 25);
  drawText(0.45, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h3, h3b)), kBlack, 25);

  p6->cd();
  //ratio->SetTopMargin(0.035);
  //ratio->SetLeftMargin(0.125);
  p6->SetBottomMargin(0.29);
  p6->SetTickx(1);
  p6->SetTicky(1);
  h_residual_3->SetStats(0);
  h_residual_3->SetLineColor(kBlack);
  h_residual_3->GetXaxis()->SetLabelSize(0.12);
  h_residual_3->GetXaxis()->SetTitleSize(0.15);  
  h_residual_3->GetXaxis()->SetTitleOffset(0.9);
  h_residual_3->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_3->GetYaxis()->SetTitleSize(0.04);
  h_residual_3->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_3->GetXaxis()->SetTitle(titleX);
  h_residual_3->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual_3->GetYaxis()->SetTitleOffset(0.35);
  h_residual_3->GetYaxis()->SetTitleSize(0.17);
  h_residual_3->GetXaxis()->SetNdivisions(707);
  h_residual_3->SetMarkerSize(1.5);
  h_residual_3->SetLineWidth(2);
  //ratio->SetBottomMargin(0.275);
  h_residual_3->Draw("same hist p");
  line->Draw("LSAME");
  h_residual_3->GetXaxis()->SetTitle(" ");
  h_residual_3->Draw("same hist pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys_R6;
        double yHigh = resContent+total_sys_R6;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }

  titlePad->cd();
  drawText(.075, .935, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.68, 0.935, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);
  

  canvas->SaveAs(name);
  delete canvas;
}



void pad3_2_theory(TGraph *gr1, TGraph *gr2, TGraph *gr3, string graphLabel, TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h1b, TH1F *h2b, TH1F *h3b, const char *titleX, const char *titleY, string label1, string label2, const char *name, float total_sys_R2, float total_sys, float total_sys_R6, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80)
{
  // Residuals
  TH1D *h_residual_1 = (TH1D*)h1->Clone("h_residual_1");
  h_residual_1->Add(h1b, -1);  
  h_residual_1->SetMarkerColor(kBlack);
  h_residual_1->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_2 = (TH1D*)h2->Clone("h_residual_2");
  h_residual_2->Add(h2b, -1);  
  h_residual_2->SetMarkerColor(kBlack);
  h_residual_2->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_3 = (TH1D*)h3->Clone("h_residual_3");
  h_residual_3->Add(h3b, -1);  
  h_residual_3->SetMarkerColor(kBlack);
  h_residual_3->SetMarkerStyle(kFullDotLarge);
  

  // Plotting
  gStyle->SetOptStat(0);
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",1200,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.33,0.36,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p2","p2",0.36,0.33,0.66,0.99,0); p2->Draw();
  TPad* p3 = new TPad("p3","p3",0.66,0.33,0.99,0.99,0); p3->Draw();
  TPad* p4 = new TPad("p4","p4",0.01,0.01,0.36,0.33,0); p4->Draw();
  TPad* p5 = new TPad("p5","p5",0.36,0.01,0.66,0.33,0); p5->Draw();
  TPad* p6 = new TPad("p6","p6",0.66,0.01,0.99,0.33,0); p6->Draw();
  p1->SetRightMargin(0.025), p1->SetBottomMargin(0);
  p4->SetRightMargin(0.025), p4->SetTopMargin(0);
  p2->SetLeftMargin(0.025), p2->SetRightMargin(0.025), p2->SetBottomMargin(0);
  p5->SetLeftMargin(0.025), p5->SetRightMargin(0.025), p5->SetTopMargin(0);
  p3->SetLeftMargin(0.025), p3->SetBottomMargin(0);
  p6->SetLeftMargin(0.025), p6->SetTopMargin(0);

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  p1->cd();
  p1->SetLeftMargin(0.175);
  //main->SetBottomMargin(0.11);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h1->SetStats(0);
  h1b->SetStats(0);
  float ymax=yMaximum;
  if (yMaximum==333) ymax = 2*h2->GetMaximum();
  h1->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.08);
  h1->GetYaxis()->SetLabelSize(0.06);
  h1->GetYaxis()->SetTitleOffset(1.1);
  h1->GetYaxis()->SetNdivisions(707);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(1.5);
  h1->SetMarkerStyle(kFullDotLarge);
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h1b->SetLineWidth(2);
  h1b->SetMarkerSize(1.5);
  h1b->SetMarkerStyle(kFullSquare);
  h1b->SetMarkerColor(kRed);
  h1b->SetLineColor(kRed);
  h1->SetTitle("");
  h1b->SetTitle("");
  h1->Draw("hist pE");
  TLine *linetop = new TLine(0,0,40,0);
  linetop->SetLineColor(kBlack);
  linetop->SetLineWidth(1);
  linetop->SetLineStyle(2); // dash
  linetop->Draw("LSAME");
  h1b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys_R2;
        double yHigh = binContent+total_sys_R2;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr1->Draw("L SAME");
  drawLegendStr(h1, h1b, 0.2, 0.5, 0.675, 0.85, label1, label2);
  // TGraph Legend
  TLegend *leg = new TLegend(0.2, 0.36, 0.5, 0.88);
  leg->SetBorderSize(0); 
  leg->SetFillStyle(0);   
  leg->SetTextSize(0.07);
  leg->AddEntry(gr1, graphLabel.c_str(), "l");
  leg->Draw("SAME");
  drawText(.625, .81, "R = 0.2", kBlack, 28);
  //drawText(0.625, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h1b)), kBlack, 23);
  //drawText(0.625, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h1b)), kBlack, 23);

  p4->cd();
  //ratio->SetTopMargin(0.035);
  p4->SetLeftMargin(0.175);
  p4->SetBottomMargin(0.29);
  p4->SetTickx(1);
  p4->SetTicky(1);
  h_residual_1->SetStats(0);
  h_residual_1->SetLineColor(kBlack);
  h_residual_1->GetXaxis()->SetLabelSize(0.12);
  h_residual_1->GetXaxis()->SetTitleSize(0.15);  
  h_residual_1->GetXaxis()->SetTitleOffset(0.8);
  h_residual_1->GetYaxis()->SetLabelSize(0.12);
  h_residual_1->GetYaxis()->SetTitleSize(0.04);
  h_residual_1->GetYaxis()->SetTitleOffset(1.6);
  string ratio_label="Data #minus MC";
  h_residual_1->GetYaxis()->SetRangeUser(-0.3, 0.3);
  h_residual_1->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual_1->GetYaxis()->SetTitleOffset(0.5);
  h_residual_1->GetYaxis()->SetTitleSize(0.17);
  h_residual_1->GetXaxis()->SetNdivisions(707);
  h_residual_1->GetYaxis()->SetNdivisions(303);
  h_residual_1->SetMarkerSize(1.5);
  h_residual_1->SetLineWidth(2);
  h_residual_1->GetXaxis()->SetTitle("");
  h_residual_1->Draw("same hist p");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys_R2;
        double yHigh = resContent+total_sys_R2;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  float xmax = h_residual_1->GetXaxis()->GetXmax();
  float xmin = h_residual_1->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,0,xmax,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h_residual_1->Draw("same hist pE");
  drawText(0.25, 0.85, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h1b)), kBlack, 23);

  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h2->SetStats(0);
  h2b->SetStats(0);
  h2->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h2->GetXaxis()->SetLabelSize(0.0000000000001);
  h2->GetYaxis()->SetLabelSize(0.0000000000001);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(1.5);
  h2->SetMarkerStyle(kFullDotLarge);
  h2->SetMarkerColor(kBlack);
  h2->SetLineColor(kBlack);
  h2b->SetLineWidth(2);
  h2b->SetMarkerSize(1.5);
  h2b->SetMarkerStyle(kFullSquare);
  h2b->SetMarkerColor(kRed);
  h2b->SetLineColor(kRed);
  h2->SetTitle("");
  h2b->SetTitle("");
  h2->Draw("hist pE");
  linetop->Draw("LSAME");
  h2b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys;
        double yHigh = binContent+total_sys;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr2->Draw("L SAME");
  drawText(.425, .81, "R = 0.4", kBlack, 28);
  //drawText(.425, .915, "0nXn", kBlack, 29);
  //drawText(0.425, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h2, h2b)), kBlack, 23);
  //drawText(0.425, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h2, h2b)), kBlack, 23);

  p5->cd();
  //ratio->SetTopMargin(0.035);
  //ratio->SetLeftMargin(0.125);
  p5->SetBottomMargin(0.29);
  p5->SetTickx(1);
  p5->SetTicky(1);
  h_residual_2->SetStats(0);
  h_residual_2->SetLineColor(kBlack);
  h_residual_2->SetTitle("");
  h_residual_2->GetXaxis()->SetLabelSize(0.12);
  h_residual_2->GetXaxis()->SetTitleSize(0.15);  
  h_residual_2->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_2->GetYaxis()->SetTitleSize(0.04);
  h_residual_2->GetYaxis()->SetRangeUser(-0.3, 0.3);
  h_residual_2->GetXaxis()->SetTitleOffset(0.9);
  h_residual_2->GetXaxis()->SetNdivisions(707);
  h_residual_2->GetXaxis()->SetTitle(titleX);
  h_residual_2->SetMarkerSize(1.5);
  h_residual_2->SetLineWidth(2);
  //ratio->SetBottomMargin(0.275);
  h_residual_2->Draw("same hist p");
  line->Draw("LSAME");
  h_residual_2->Draw("same hist pE");
  drawText(0.125, 0.81, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h2, h2b)), kBlack, 23);
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys;
        double yHigh = resContent+total_sys;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  

  p3->cd();
  p3->SetTickx(1);
  p3->SetTicky(1);
  h3->SetStats(0);
  h3b->SetStats(0);
  h3->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h3->GetXaxis()->SetLabelSize(0.0000000000001);
  h3->GetYaxis()->SetLabelSize(0.0000000000001);
  h3->SetLineWidth(2);
  h3->SetMarkerSize(1.5);
  h3->SetMarkerStyle(kFullDotLarge);
  h3->SetMarkerColor(kBlack);
  h3->SetLineColor(kBlack);
  h3b->SetLineWidth(2);
  h3b->SetMarkerSize(1.5);
  h3b->SetMarkerStyle(kFullSquare);
  h3b->SetMarkerColor(kRed);
  h3b->SetLineColor(kRed);
  h3->SetTitle("");
  h3b->SetTitle("");
  h3->Draw("hist pE");
  linetop->Draw("LSAME");
  h3b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys_R6;
        double yHigh = binContent+total_sys_R6;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr3->Draw("L SAME");
  drawText(.45, .81, "R = 0.6", kBlack, 28);
  //drawText(0.45, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h3, h3b)), kBlack, 23);
  //drawText(0.45, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h3, h3b)), kBlack, 23);

  p6->cd();
  //ratio->SetTopMargin(0.035);
  //ratio->SetLeftMargin(0.125);
  p6->SetBottomMargin(0.29);
  p6->SetTickx(1);
  p6->SetTicky(1);
  h_residual_3->SetStats(0);
  h_residual_3->SetLineColor(kBlack);
  h_residual_3->GetXaxis()->SetLabelSize(0.12);
  h_residual_3->GetXaxis()->SetTitleSize(0.15);  
  h_residual_3->GetXaxis()->SetTitleOffset(0.9);
  h_residual_3->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_3->GetYaxis()->SetTitleSize(0.04);
  h_residual_3->GetYaxis()->SetRangeUser(-0.3, 0.3);
  h_residual_3->GetXaxis()->SetTitle(titleX);
  h_residual_3->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual_3->GetYaxis()->SetTitleOffset(0.35);
  h_residual_3->GetYaxis()->SetTitleSize(0.17);
  h_residual_3->GetXaxis()->SetNdivisions(707);
  h_residual_3->SetMarkerSize(1.5);
  h_residual_3->SetLineWidth(2);
  //ratio->SetBottomMargin(0.275);
  h_residual_3->Draw("same hist p");
  line->Draw("LSAME");
  h_residual_3->GetXaxis()->SetTitle(" ");
  h_residual_3->Draw("same hist pE");
   drawText(0.125, 0.81, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h3, h3b)), kBlack, 23);
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys_R6;
        double yHigh = resContent+total_sys_R6;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }

  titlePad->cd();
  drawText(.075, .935, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.68, 0.935, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);
  

  canvas->SaveAs(name);
  delete canvas;
}

void pad3_2_theories(TGraph *gr1, TGraph *gr2, TGraph *gr3, TGraph *gr1_b, TGraph *gr2_b, TGraph *gr3_b, string graphLabel, string graphLabel_b, TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h1b, TH1F *h2b, TH1F *h3b, const char *titleX, const char *titleY, string label1, string label2, const char *name, float total_sys_R2, float total_sys, float total_sys_R6, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80)
{
  // Residuals
  TH1D *h_residual_1 = (TH1D*)h1->Clone("h_residual_1");
  h_residual_1->Add(h1b, -1);  
  h_residual_1->SetMarkerColor(kBlack);
  h_residual_1->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_2 = (TH1D*)h2->Clone("h_residual_2");
  h_residual_2->Add(h2b, -1);  
  h_residual_2->SetMarkerColor(kBlack);
  h_residual_2->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_3 = (TH1D*)h3->Clone("h_residual_3");
  h_residual_3->Add(h3b, -1);  
  h_residual_3->SetMarkerColor(kBlack);
  h_residual_3->SetMarkerStyle(kFullDotLarge);
  

  // Plotting
  gStyle->SetOptStat(0);
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",1200,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.33,0.36,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p2","p2",0.36,0.33,0.66,0.99,0); p2->Draw();
  TPad* p3 = new TPad("p3","p3",0.66,0.33,0.99,0.99,0); p3->Draw();
  TPad* p4 = new TPad("p4","p4",0.01,0.01,0.36,0.33,0); p4->Draw();
  TPad* p5 = new TPad("p5","p5",0.36,0.01,0.66,0.33,0); p5->Draw();
  TPad* p6 = new TPad("p6","p6",0.66,0.01,0.99,0.33,0); p6->Draw();
  p1->SetRightMargin(0.025), p1->SetBottomMargin(0);
  p4->SetRightMargin(0.025), p4->SetTopMargin(0);
  p2->SetLeftMargin(0.025), p2->SetRightMargin(0.025), p2->SetBottomMargin(0);
  p5->SetLeftMargin(0.025), p5->SetRightMargin(0.025), p5->SetTopMargin(0);
  p3->SetLeftMargin(0.025), p3->SetBottomMargin(0);
  p6->SetLeftMargin(0.025), p6->SetTopMargin(0);

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  p1->cd();
  p1->SetLeftMargin(0.175);
  //main->SetBottomMargin(0.11);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h1->SetStats(0);
  h1b->SetStats(0);
  float ymax=yMaximum;
  if (yMaximum==333) ymax = 2*h2->GetMaximum();
  h1->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.08);
  h1->GetYaxis()->SetLabelSize(0.06);
  h1->GetYaxis()->SetTitleOffset(1.1);
  h1->GetYaxis()->SetNdivisions(707);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(1.5);
  h1->SetMarkerStyle(kFullDotLarge);
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h1b->SetLineWidth(2);
  h1b->SetMarkerSize(1.5);
  h1b->SetMarkerStyle(kFullSquare);
  h1b->SetMarkerColor(kRed);
  h1b->SetLineColor(kRed);
  h1->SetTitle("");
  h1b->SetTitle("");
  h1->Draw("hist pE");
  h1b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys_R2;
        double yHigh = binContent+total_sys_R2;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr1->Draw("L SAME");
  gr1_b->SetLineColor(kAzure+7);
  gr1_b->Draw("L SAME");
  drawLegendStr(h1, h1b, 0.2, 0.5, 0.675, 0.85, label1, label2);
  // TGraph Legend
  TLegend *leg = new TLegend(0.2, 0.55, 0.625, 0.68);
  leg->SetBorderSize(0); 
  leg->SetFillStyle(0);   
  leg->SetTextSize(0.06);
  leg->AddEntry(gr1, graphLabel.c_str(), "l");
  leg->AddEntry(gr1_b, graphLabel_b.c_str(), "l");
  leg->Draw("SAME");
  drawText(.625, .81, "R = 0.2", kBlack, 28);
  //drawText(0.625, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h1b)), kBlack, 23);
  //drawText(0.625, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h1b)), kBlack, 23);

  p4->cd();
  //ratio->SetTopMargin(0.035);
  p4->SetLeftMargin(0.175);
  p4->SetBottomMargin(0.29);
  p4->SetTickx(1);
  p4->SetTicky(1);
  h_residual_1->SetStats(0);
  h_residual_1->SetLineColor(kBlack);
  h_residual_1->GetXaxis()->SetLabelSize(0.12);
  h_residual_1->GetXaxis()->SetTitleSize(0.15);  
  h_residual_1->GetXaxis()->SetTitleOffset(0.8);
  h_residual_1->GetYaxis()->SetLabelSize(0.12);
  h_residual_1->GetYaxis()->SetTitleSize(0.04);
  h_residual_1->GetYaxis()->SetTitleOffset(1.6);
  string ratio_label="Data #minus MC";
  h_residual_1->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_1->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual_1->GetYaxis()->SetTitleOffset(0.5);
  h_residual_1->GetYaxis()->SetTitleSize(0.17);
  h_residual_1->GetXaxis()->SetNdivisions(707);
  h_residual_1->GetYaxis()->SetNdivisions(303);
  h_residual_1->SetMarkerSize(1.5);
  h_residual_1->SetLineWidth(2);
  h_residual_1->GetXaxis()->SetTitle("");
  h_residual_1->Draw("same hist p");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys_R2;
        double yHigh = resContent+total_sys_R2;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  float xmax = h_residual_1->GetXaxis()->GetXmax();
  float xmin = h_residual_1->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,0,xmax,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h_residual_1->Draw("same hist pE");
  drawText(0.25, 0.85, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h1b)), kBlack, 23);

  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h2->SetStats(0);
  h2b->SetStats(0);
  h2->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h2->GetXaxis()->SetLabelSize(0.0000000000001);
  h2->GetYaxis()->SetLabelSize(0.0000000000001);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(1.5);
  h2->SetMarkerStyle(kFullDotLarge);
  h2->SetMarkerColor(kBlack);
  h2->SetLineColor(kBlack);
  h2b->SetLineWidth(2);
  h2b->SetMarkerSize(1.5);
  h2b->SetMarkerStyle(kFullSquare);
  h2b->SetMarkerColor(kRed);
  h2b->SetLineColor(kRed);
  h2->SetTitle("");
  h2b->SetTitle("");
  h2->Draw("hist pE");
  h2b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys;
        double yHigh = binContent+total_sys;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr2->Draw("L SAME");
  gr2_b->SetLineColor(kAzure+7);
  gr2_b->Draw("L SAME");
  drawText(.425, .81, "R = 0.4", kBlack, 28);
  //drawText(.425, .915, "0nXn", kBlack, 29);
  //drawText(0.425, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h2, h2b)), kBlack, 23);
  //drawText(0.425, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h2, h2b)), kBlack, 23);

  p5->cd();
  //ratio->SetTopMargin(0.035);
  //ratio->SetLeftMargin(0.125);
  p5->SetBottomMargin(0.29);
  p5->SetTickx(1);
  p5->SetTicky(1);
  h_residual_2->SetStats(0);
  h_residual_2->SetLineColor(kBlack);
  h_residual_2->SetTitle("");
  h_residual_2->GetXaxis()->SetLabelSize(0.12);
  h_residual_2->GetXaxis()->SetTitleSize(0.15);  
  h_residual_2->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_2->GetYaxis()->SetTitleSize(0.04);
  h_residual_2->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_2->GetXaxis()->SetTitleOffset(0.9);
  h_residual_2->GetXaxis()->SetNdivisions(707);
  h_residual_2->GetXaxis()->SetTitle(titleX);
  h_residual_2->SetMarkerSize(1.5);
  h_residual_2->SetLineWidth(2);
  //ratio->SetBottomMargin(0.275);
  h_residual_2->Draw("same hist p");
  line->Draw("LSAME");
  h_residual_2->Draw("same hist pE");
  drawText(0.125, 0.81, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h2, h2b)), kBlack, 23);
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys;
        double yHigh = resContent+total_sys;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  

  p3->cd();
  p3->SetTickx(1);
  p3->SetTicky(1);
  h3->SetStats(0);
  h3b->SetStats(0);
  h3->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h3->GetXaxis()->SetLabelSize(0.0000000000001);
  h3->GetYaxis()->SetLabelSize(0.0000000000001);
  h3->SetLineWidth(2);
  h3->SetMarkerSize(1.5);
  h3->SetMarkerStyle(kFullDotLarge);
  h3->SetMarkerColor(kBlack);
  h3->SetLineColor(kBlack);
  h3b->SetLineWidth(2);
  h3b->SetMarkerSize(1.5);
  h3b->SetMarkerStyle(kFullSquare);
  h3b->SetMarkerColor(kRed);
  h3b->SetLineColor(kRed);
  h3->SetTitle("");
  h3b->SetTitle("");
  h3->Draw("hist pE");
  h3b->Draw("same pE");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys_R6;
        double yHigh = binContent+total_sys_R6;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr3->Draw("L SAME");
  gr3_b->SetLineColor(kAzure+7);
  gr3_b->SetLineStyle(10);
  gr3_b->Draw("L SAME");
  drawText(.45, .81, "R = 0.6", kBlack, 28);
  //drawText(0.45, 0.74, Form("#chi^{2}=%0.2f",find_hist_chi2(h3, h3b)), kBlack, 23);
  //drawText(0.45, 0.67, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h3, h3b)), kBlack, 23);

  p6->cd();
  //ratio->SetTopMargin(0.035);
  //ratio->SetLeftMargin(0.125);
  p6->SetBottomMargin(0.29);
  p6->SetTickx(1);
  p6->SetTicky(1);
  h_residual_3->SetStats(0);
  h_residual_3->SetLineColor(kBlack);
  h_residual_3->GetXaxis()->SetLabelSize(0.12);
  h_residual_3->GetXaxis()->SetTitleSize(0.15);  
  h_residual_3->GetXaxis()->SetTitleOffset(0.9);
  h_residual_3->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_3->GetYaxis()->SetTitleSize(0.04);
  h_residual_3->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_3->GetXaxis()->SetTitle(titleX);
  h_residual_3->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual_3->GetYaxis()->SetTitleOffset(0.35);
  h_residual_3->GetYaxis()->SetTitleSize(0.17);
  h_residual_3->GetXaxis()->SetNdivisions(707);
  h_residual_3->SetMarkerSize(1.5);
  h_residual_3->SetLineWidth(2);
  //ratio->SetBottomMargin(0.275);
  h_residual_3->Draw("same hist p");
  line->Draw("LSAME");
  h_residual_3->GetXaxis()->SetTitle(" ");
  h_residual_3->Draw("same hist pE");
  drawText(0.125, 0.81, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h3, h3b)), kBlack, 23);
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys_R6;
        double yHigh = resContent+total_sys_R6;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }

  titlePad->cd();
  drawText(.075, .935, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.68, 0.935, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);

  canvas->SaveAs(name);
  delete canvas;
}

void pad2_3(TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h1b, TH1F *h2b, TH1F *h3b, const char *titleX, const char *titleY, string label1, string label2, const char *name, float total_sys_R2, float total_sys, float total_sys_R6, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80)
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
  h1->GetYaxis()->SetTitleOffset(1.1);
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitleOffset(0.9);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(2);
  h1->SetMarkerStyle(kFullDotLarge);
  h1->SetMarkerColor(kRed);
  h1->SetLineColor(kRed);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(2);
  h2->SetMarkerStyle(kFullDotLarge);
  h2->SetMarkerColor(kBlue);
  h2->SetLineColor(kBlue);
  h3->SetLineWidth(2);
  h3->SetMarkerSize(2);
  h3->SetMarkerStyle(kFullDotLarge);
  h3->SetMarkerColor(kViolet);
  h3->SetLineColor(kViolet);
  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h1->Draw("hist pE");
  h2->Draw("hist same pE");
  TLine *line = new TLine(0,0,40,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h3->Draw("hist same pE");
  // draw Systematic Errors
  double syst_error = total_sys_R2;
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
        box->SetFillColorAlpha(kRed, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  syst_error = total_sys;
  for (int i=1; i<=h2->GetNbinsX(); ++i) {
        double binCenter = h2->GetBinCenter(i);
        double binWidth = h2->GetBinWidth(i)/2;
        double binContent = h2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-syst_error;
        double yHigh = binContent+syst_error;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlue, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  syst_error = total_sys_R6;
  for (int i=1; i<=h3->GetNbinsX(); ++i) {
        double binCenter = h3->GetBinCenter(i);
        double binWidth = h3->GetBinWidth(i)/2;
        double binContent = h3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-syst_error;
        double yHigh = binContent+syst_error;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kViolet, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  drawText(0.5, 0.825, "0nXn Data", kBlack, 28);
  drawLegendStr3(h1, h2, h3, 0.2, 0.45, 0.675, 0.86, "R = 0.2", "R = 0.4", "R = 0.6");

  
  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h1b->SetStats(0);
  h1b->GetXaxis()->SetLabelSize(0.04);
  h1b->GetYaxis()->SetRangeUser(yMinimum,yMaximum);
  h1b->GetYaxis()->SetLabelSize(0.0000000000001);
  h1b->SetMarkerColor(kRed);
  h1b->SetLineColor(kRed);
  h1b->SetMarkerStyle(kFullSquare);
  h2b->SetMarkerColor(kBlue);
  h2b->SetLineColor(kBlue);
  h2b->SetMarkerStyle(kFullSquare);
  h3b->SetMarkerColor(kViolet);
  h3b->SetLineColor(kViolet);
  h3b->SetMarkerStyle(kFullSquare);
  h1b->Draw("hist pe");
  h2b->Draw("hist pe same");
  line->Draw("LSAME");
  h3b->Draw("hist pe same"); 
  drawText(0.35, 0.825, "Pythia8", kBlack, 28);
  //line->Draw("LSAME");
   

  titlePad->cd();
  drawText(.1, .91, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.62, 0.91, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);
  drawText(0.46, 0.02, titleX, kBlack, 28);
  
  canvas->SaveAs(name);
  delete canvas;
}

void pad3_2_theoryZoomed(TGraph *gr1, TGraph *gr2, TGraph *gr3, string graphLabel, TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h1b, TH1F *h2b, TH1F *h3b, const char *titleX, const char *titleY, string label1, string label2, const char *name, float total_sys_R2, float total_sys, float total_sys_R6, float yMinimum=0, float yMaximum=333, float x1=0.60, float x2=0.80, float y1=0.65, float y2=0.80)
{
  // Residuals
  TH1D *h_residual_1 = (TH1D*)h1->Clone("h_residual_1");
  h_residual_1->Add(h1b, -1);  
  h_residual_1->SetMarkerColor(kBlack);
  h_residual_1->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_2 = (TH1D*)h2->Clone("h_residual_2");
  h_residual_2->Add(h2b, -1);  
  h_residual_2->SetMarkerColor(kBlack);
  h_residual_2->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_3 = (TH1D*)h3->Clone("h_residual_3");
  h_residual_3->Add(h3b, -1);  
  h_residual_3->SetMarkerColor(kBlack);
  h_residual_3->SetMarkerStyle(kFullDotLarge);
  

  // Plotting
  gStyle->SetOptStat(0);
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",1200,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.33,0.36,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p2","p2",0.36,0.33,0.66,0.99,0); p2->Draw();
  TPad* p3 = new TPad("p3","p3",0.66,0.33,0.99,0.99,0); p3->Draw();
  TPad* p4 = new TPad("p4","p4",0.01,0.01,0.36,0.33,0); p4->Draw();
  TPad* p5 = new TPad("p5","p5",0.36,0.01,0.66,0.33,0); p5->Draw();
  TPad* p6 = new TPad("p6","p6",0.66,0.01,0.99,0.33,0); p6->Draw();
  p1->SetRightMargin(0.025), p1->SetBottomMargin(0);
  p4->SetRightMargin(0.025), p4->SetTopMargin(0);
  p2->SetLeftMargin(0.025), p2->SetRightMargin(0.025), p2->SetBottomMargin(0);
  p5->SetLeftMargin(0.025), p5->SetRightMargin(0.025), p5->SetTopMargin(0);
  p3->SetLeftMargin(0.025), p3->SetBottomMargin(0);
  p6->SetLeftMargin(0.025), p6->SetTopMargin(0);

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  p1->cd();
  p1->SetLeftMargin(0.175);
  //main->SetBottomMargin(0.11);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h1->SetStats(0);
  h1b->SetStats(0);
  float ymax=yMaximum;
  if (yMaximum==333) ymax = 2*h2->GetMaximum();
  h1->GetXaxis()->SetRangeUser(0,16);
  h1->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.08);
  h1->GetYaxis()->SetLabelSize(0.06);
  h1->GetYaxis()->SetTitleOffset(1.1);
  h1->GetYaxis()->SetNdivisions(707);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(1.5);
  h1->SetMarkerStyle(kFullDotLarge);
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h1b->SetLineWidth(2);
  h1b->SetMarkerSize(1.5);
  h1b->SetMarkerStyle(kFullSquare);
  h1b->SetMarkerColor(kRed);
  h1b->SetLineColor(kRed);
  h1->SetTitle("");
  h1b->SetTitle("");
  h1->Draw("hist pE");
  h1b->Draw("same pE");
  // systematics
  for (int i=1; i<=2; ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys_R2;
        double yHigh = binContent+total_sys_R2;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr1->Draw("L SAME");
  drawLegendStr(h1, h1b, 0.25, 0.5, 0.675, 0.85, label1, label2);
  // TGraph Legend
  TLegend *leg = new TLegend(0.25, 0.36, 0.5, 0.88);
  leg->SetBorderSize(0); 
  leg->SetFillStyle(0);   
  leg->SetTextSize(0.07);
  leg->AddEntry(gr1, graphLabel.c_str(), "l");
  leg->Draw("SAME");
  drawText(.625, .79, "r=0.2", kBlack, 28);

  p4->cd();
  //ratio->SetTopMargin(0.035);
  p4->SetLeftMargin(0.175);
  p4->SetBottomMargin(0.29);
  p4->SetTickx(1);
  p4->SetTicky(1);
  h_residual_1->SetStats(0);
  h_residual_1->SetLineColor(kBlack);
  h_residual_1->GetXaxis()->SetLabelSize(0.12);
  h_residual_1->GetXaxis()->SetTitleSize(0.15);  
  h_residual_1->GetXaxis()->SetTitleOffset(0.8);
  h_residual_1->GetYaxis()->SetLabelSize(0.12);
  h_residual_1->GetYaxis()->SetTitleSize(0.04);
  h_residual_1->GetYaxis()->SetTitleOffset(1.6);
  string ratio_label="data - MC";
  h_residual_1->GetXaxis()->SetRangeUser(0,16);
  h_residual_1->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_1->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual_1->GetYaxis()->SetTitleOffset(0.5);
  h_residual_1->GetYaxis()->SetTitleSize(0.17);
  h_residual_1->GetXaxis()->SetNdivisions(707);
  h_residual_1->GetYaxis()->SetNdivisions(303);
  h_residual_1->SetMarkerSize(1.5);
  h_residual_1->SetLineWidth(2);
  h_residual_1->GetXaxis()->SetTitle("");
  h_residual_1->Draw("same hist p");
  // systematics
  for (int i=1; i<=2; ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys_R2;
        double yHigh = resContent+total_sys_R2;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  float xmax = h_residual_1->GetXaxis()->GetXmax();
  float xmin = h_residual_1->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,0,16,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h_residual_1->Draw("same hist pE");
  

  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h2->SetStats(0);
  h2b->SetStats(0);
  h2->GetXaxis()->SetRangeUser(0,16);
  h2->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h2->GetXaxis()->SetLabelSize(0.0000000000001);
  h2->GetYaxis()->SetLabelSize(0.0000000000001);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(1.5);
  h2->SetMarkerStyle(kFullDotLarge);
  h2->SetMarkerColor(kBlack);
  h2->SetLineColor(kBlack);
  h2b->SetLineWidth(2);
  h2b->SetMarkerSize(1.5);
  h2b->SetMarkerStyle(kFullSquare);
  h2b->SetMarkerColor(kRed);
  h2b->SetLineColor(kRed);
  h2->SetTitle("");
  h2b->SetTitle("");
  h2->Draw("hist pE");
  h2b->Draw("same pE");
  // systematics
  for (int i=1; i<=2; ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys;
        double yHigh = binContent+total_sys;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr2->Draw("L SAME");
  drawText(.425, .79, "r=0.4", kBlack, 28);
  drawText(.425, .915, "0nXn", kBlack, 29);

  p5->cd();
  //ratio->SetTopMargin(0.035);
  //ratio->SetLeftMargin(0.125);
  p5->SetBottomMargin(0.29);
  p5->SetTickx(1);
  p5->SetTicky(1);
  h_residual_2->SetStats(0);
  h_residual_2->SetLineColor(kBlack);
  h_residual_2->SetTitle("");
  h_residual_2->GetXaxis()->SetRangeUser(0,16);
  h_residual_2->GetXaxis()->SetLabelSize(0.12);
  h_residual_2->GetXaxis()->SetTitleSize(0.15);  
  h_residual_2->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_2->GetYaxis()->SetTitleSize(0.04);
  h_residual_2->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_2->GetXaxis()->SetTitleOffset(0.9);
  h_residual_2->GetXaxis()->SetNdivisions(707);
  h_residual_2->GetXaxis()->SetTitle(titleX);
  h_residual_2->SetMarkerSize(1.5);
  h_residual_2->SetLineWidth(2);
  //ratio->SetBottomMargin(0.275);
  h_residual_2->Draw("same hist p");
  line->Draw("LSAME");
  h_residual_2->Draw("same hist pE");
  // systematics
  for (int i=1; i<=2; ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys;
        double yHigh = resContent+total_sys;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  

  p3->cd();
  p3->SetTickx(1);
  p3->SetTicky(1);
  h3->SetStats(0);
  h3b->SetStats(0);
  h3->GetXaxis()->SetRangeUser(0,16);
  h3->GetYaxis()->SetRangeUser(yMinimum,ymax);
  h3->GetXaxis()->SetLabelSize(0.0000000000001);
  h3->GetYaxis()->SetLabelSize(0.0000000000001);
  h3->SetLineWidth(2);
  h3->SetMarkerSize(1.5);
  h3->SetMarkerStyle(kFullDotLarge);
  h3->SetMarkerColor(kBlack);
  h3->SetLineColor(kBlack);
  h3b->SetLineWidth(2);
  h3b->SetMarkerSize(1.5);
  h3b->SetMarkerStyle(kFullSquare);
  h3b->SetMarkerColor(kRed);
  h3b->SetLineColor(kRed);
  h3->SetTitle("");
  h3b->SetTitle("");
  h3->Draw("hist pE");
  h3b->Draw("same pE");
  // systematics
  for (int i=1; i<=2; ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-total_sys_R6;
        double yHigh = binContent+total_sys_R6;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  gr3->Draw("L SAME");
  drawText(.45, .79, "r=0.6", kBlack, 28);

  p6->cd();
  //ratio->SetTopMargin(0.035);
  //ratio->SetLeftMargin(0.125);
  p6->SetBottomMargin(0.29);
  p6->SetTickx(1);
  p6->SetTicky(1);
  h_residual_3->GetXaxis()->SetRangeUser(0,16);
  h_residual_3->SetStats(0);
  h_residual_3->SetLineColor(kBlack);
  h_residual_3->GetXaxis()->SetLabelSize(0.12);
  h_residual_3->GetXaxis()->SetTitleSize(0.15);  
  h_residual_3->GetXaxis()->SetTitleOffset(0.9);
  h_residual_3->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_3->GetYaxis()->SetTitleSize(0.04);
  h_residual_3->GetYaxis()->SetRangeUser(-0.2, 0.3);
  h_residual_3->GetXaxis()->SetTitle(titleX);
  h_residual_3->GetYaxis()->SetTitle(ratio_label.c_str());
  h_residual_3->GetYaxis()->SetTitleOffset(0.35);
  h_residual_3->GetYaxis()->SetTitleSize(0.17);
  h_residual_3->GetXaxis()->SetNdivisions(707);
  h_residual_3->SetMarkerSize(1.5);
  h_residual_3->SetLineWidth(2);
  //ratio->SetBottomMargin(0.275);
  h_residual_3->Draw("same hist p");
  line->Draw("LSAME");
  h_residual_3->GetXaxis()->SetTitle(" ");
  h_residual_3->Draw("same hist pE");
  // systematics
  for (int i=1; i<=2; ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_3->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-total_sys_R6;
        double yHigh = resContent+total_sys_R6;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }

  titlePad->cd();
  drawText(.075, .935, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.7, 0.935, "PbPb: #sqrt{s}=5.02 TeV (2018)", kBlack, 28);
  

  canvas->SaveAs(name);
  delete canvas;
}

// new 
void pad4_2_rapidity(TH1F *h1, TH1F *h2, TH1F *h1b, TH1F *h2b, const char *titleX, const char *titleY, string label1, string label2, const char *name, float total_sys_0, float total_sys_1, float yMin=0, float yMax=333, float yMin_res=-1, float yMax_res=1)
{
  // Residuals
  TH1D *h_residual_1 = (TH1D*)h1->Clone("h_residual_1");
  h_residual_1->Add(h1b, -1);  
  h_residual_1->SetMarkerColor(kBlack);
  h_residual_1->SetMarkerStyle(kFullDotLarge);
  TH1D *h_residual_2 = (TH1D*)h2->Clone("h_residual_2");
  h_residual_2->Add(h2b, -1);  
  h_residual_2->SetMarkerColor(kBlack);
  h_residual_2->SetMarkerStyle(kFullDotLarge);
  

  // Plotting
  gStyle->SetOptStat(0);
  TString uniqueCanvasName = Form("canvas_%p", h1);
  auto *canvas = new TCanvas(uniqueCanvasName,"title",1200,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.33,0.50,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p2","p2",0.50,0.33,0.99,0.99,0); p2->Draw();
  TPad* p3 = new TPad("p3","p3",0.01,0.01,0.50,0.33,0); p3->Draw();
  TPad* p4 = new TPad("p4","p4",0.50,0.01,0.99,0.33,0); p4->Draw();
  p1->SetRightMargin(0.0275), p1->SetBottomMargin(0);
  p3->SetRightMargin(0.0275), p3->SetTopMargin(0);
  p2->SetLeftMargin(0.0275), p2->SetBottomMargin(0);
  p4->SetLeftMargin(0.0275), p4->SetTopMargin(0);

  TPad *titlePad = new TPad("all","all",0,0,1,1);
  titlePad->SetFillStyle(4000); 
  titlePad->Draw();

  p1->cd();
  p1->SetLeftMargin(0.175);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h1->SetStats(0);
  h1b->SetStats(0);
  h1->GetXaxis()->SetLabelSize(0.0000000000001);
  h1->GetYaxis()->SetTitle(titleY);
  h1->GetYaxis()->SetTitleSize(0.08);
  h1->GetYaxis()->SetLabelSize(0.06);
  h1->GetYaxis()->SetTitleOffset(0.75);
  h1->GetYaxis()->SetNdivisions(707);
  h1->SetLineWidth(2);
  h1->SetMarkerSize(2);
  h1->SetMarkerStyle(kFullDotLarge);
  h1->SetMarkerColor(kBlack);
  h1->SetLineColor(kBlack);
  h1b->SetLineWidth(2);
  h1b->SetMarkerSize(2);
  h1b->SetMarkerStyle(kFullSquare);
  h1b->SetMarkerColor(kRed);
  h1b->SetLineColor(kRed);
  h1->GetYaxis()->SetRangeUser(yMin,yMax);
  h1->SetTitle("");
  h1b->SetTitle("");
  h1->Draw("hist pE");
  h1b->Draw("same pE");
  // systematics
  double syst_error_0 = total_sys_0;
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double binContent = h1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-syst_error_0;
        double yHigh = binContent+syst_error_0;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
 
  drawLegendStr(h1, h1b, 0.2, 0.4, 0.65, 0.875, label1, label2);
  drawText(0.215, 0.58, "R = 0.4", kBlack, 26);
  drawText(0.5, 0.775, "0 GeV < Q_{T} < 12 GeV", kBlack, 28);
  //drawText(0.775, 0.68, Form("#chi^{2}=%0.2f",find_hist_chi2(h1, h1b)), kBlack, 28);
  //drawText(0.775, 0.60, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h1b)), kBlack, 28);
  

  
  p2->cd();
  p2->SetTickx(1);
  p2->SetTicky(1);
  h2->SetStats(0);
  h2b->SetStats(0);
  h2->GetXaxis()->SetLabelSize(0.0000000000001);
  h2->GetYaxis()->SetLabelSize(0.0000000000001);
  h2->GetYaxis()->SetTitleSize(0.08);
  h2->GetYaxis()->SetTitleOffset(0.75);
  h2->SetLineWidth(2);
  h2->SetMarkerSize(2);
  h2->SetMarkerStyle(kFullDotLarge);
  h2->SetMarkerColor(kBlack);
  h2->SetLineColor(kBlack);
  h2b->SetLineWidth(2);
  h2b->SetMarkerSize(2);
  h2b->SetMarkerStyle(kFullSquare);
  h2b->SetMarkerColor(kRed);
  h2b->SetLineColor(kRed);
  h2->GetYaxis()->SetRangeUser(yMin,yMax);
  h2->SetTitle("");
  h2b->SetTitle("");
  h2->Draw("hist pE");
  h2b->Draw("same pE");

  // systematics
  double syst_error_1 = total_sys_1;
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h2->GetBinCenter(i);
        double binWidth = h2->GetBinWidth(i)/2;
        double binContent = h2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = binContent-syst_error_1;
        double yHigh = binContent+syst_error_1;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
  drawText(0.40, 0.775, "12 GeV < Q_{T} < 40 GeV", kBlack, 28);
  //drawText(0.675, 0.68, Form("#chi^{2}=%0.2f",find_hist_chi2(h2, h2b)), kBlack, 28);
  //drawText(0.675, 0.60, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h2, h2b)), kBlack, 28);

  p3->cd();
  p3->SetTickx(1);
  p3->SetTicky(1);
  p3->SetLeftMargin(0.175);
  p3->SetBottomMargin(0.275);
  h_residual_1->SetStats(0);
  h_residual_1->SetLineColor(kBlack);
  h_residual_1->SetTitle("");
  h_residual_1->GetXaxis()->SetLabelSize(0.11);
  h_residual_1->GetXaxis()->SetTitleSize(0.15);  
  h_residual_1->GetXaxis()->SetTitleOffset(0.8);
  h_residual_1->GetYaxis()->SetTitle("Data #minus MC");
  h_residual_1->GetYaxis()->SetNdivisions(303);
  h_residual_1->GetYaxis()->SetLabelSize(0.12);
  h_residual_1->GetYaxis()->SetTitleSize(0.17);
  h_residual_1->GetYaxis()->SetRangeUser(yMin_res, yMax_res);
  h_residual_1->GetYaxis()->SetTitleOffset(0.35);
  h_residual_1->SetMarkerSize(2);
  h_residual_1->SetLineWidth(2);
  p3->SetBottomMargin(0.275);
  h_residual_1->Draw("same hist p");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i);
        double binWidth = h1->GetBinWidth(i)/2;
        double resContent = h_residual_1->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-syst_error_0;
        double yHigh = resContent+syst_error_0;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
 
  
  float xmax = h_residual_1->GetXaxis()->GetXmax();
  float xmin = h_residual_1->GetXaxis()->GetXmin();
  TLine *line = new TLine(xmin,0,xmax,0);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);
  line->SetLineStyle(2); // dash
  line->Draw("LSAME");
  h_residual_1->Draw("same hist pE");
  drawText(0.22, 0.8, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h1, h1b)), kBlack, 28);

  p4->cd();
  p4->SetTickx(1);
  p4->SetTicky(1);
  //p4->SetTopMargin(0.035);
  //p4->SetLeftMargin(0.125);
  p4->SetBottomMargin(0.275);
  h_residual_2->SetStats(0);
  h_residual_2->SetLineColor(kBlack);
  h_residual_2->SetTitle("");
  h_residual_2->GetXaxis()->SetLabelSize(0.11);
  h_residual_2->GetXaxis()->SetTitleSize(0.15);  
  h_residual_2->GetXaxis()->SetTitleOffset(0.8);
  h_residual_2->GetYaxis()->SetNdivisions(303);
  h_residual_2->GetYaxis()->SetLabelSize(0.09);
  h_residual_2->GetYaxis()->SetTitleSize(0.17);
  h_residual_2->GetYaxis()->SetRangeUser(yMin_res, yMax_res);
  h_residual_2->GetYaxis()->SetLabelSize(0.0000000000001);
  h_residual_2->GetYaxis()->SetTitleOffset(0.35);
  h_residual_2->SetMarkerSize(2);
  h_residual_2->SetLineWidth(2);
  p4->SetBottomMargin(0.275);
  h_residual_2->Draw("same hist p");
  // systematics
  for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double binCenter = h2->GetBinCenter(i);
        double binWidth = h2->GetBinWidth(i)/2;
        double resContent = h_residual_2->GetBinContent(i);

        // Define the box range for systematic uncertainties
        double xLow = binCenter-binWidth;
        double xHigh = binCenter+binWidth;
        double yLow = resContent-syst_error_1;
        double yHigh = resContent+syst_error_1;

        // Create and draw the box for this bin
        TBox* box = new TBox(xLow, yLow, xHigh, yHigh);
        box->SetFillColorAlpha(kBlack, 0.3); 
        box->SetLineWidth(0);               
        box->Draw("SAME");
    }
 

  line->Draw("LSAME");
  h_residual_2->Draw("same hist pE");
  drawText(0.075, 0.80, Form("#chi^{2}_{#nu}=%0.2f",find_hist_chi2NDF(h2, h2b)), kBlack, 28);

  titlePad->cd();
  drawText(.1, .935, "#bf{CMS} #it{Internal}", kBlack, 28);
  drawText(0.66, 0.935, "PbPb: #sqrt{s_{_{NN}}} = 5.02 TeV (2018)", kBlack, 28);
  drawText(0.50, 0.02, titleX, kBlack, 28);
  drawText(0.475, 0.93, "0nXn", kBlack, 29);

  canvas->SaveAs(name);
  delete canvas;
}
