// AN_resolution.C
// This code makes resolution plots for the analysis note
// ran with run_ANresolution.sh

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
#include "/home/colelemahieu/Research2023/Run2/RapidityAnalysis/nicePlotting.h"
using namespace std;


void AN_resolution(string genPythiaFile, string recoPythiaFile, string dataFile)
{
  // Jet Files
  TFile *genPythia = new TFile(genPythiaFile.c_str());
  TFile *recoPythia = new TFile(recoPythiaFile.c_str());
  TFile *data = new TFile(dataFile.c_str());
  TFile *resolutions = new TFile("angles.root");
  
  // directory to write to
  string dirPath = "forAN/Res/";

  // Pythia Reco Histograms
  TH1F *h_jetPhi = (TH1F*)recoPythia->Get("h_phiRes");
  TH1F *h_jetEta = (TH1F*)recoPythia->Get("h_etaRes");
  TH1F *h_qtRes = (TH1F*)recoPythia->Get("h_qtRes");
  TH1F *h_qtRes_x = (TH1F*)recoPythia->Get("h_qtRes_x");
  TH1F *h_qtRes_x_1 = (TH1F*)recoPythia->Get("h_qtRes_x_1");
  TH1F *h_qtRes_x_2 = (TH1F*)recoPythia->Get("h_qtRes_x_2");
  TH1F *h_qtRes_x_3 = (TH1F*)recoPythia->Get("h_qtRes_x_3");
  TH1F *h_qtRes_x_4 = (TH1F*)recoPythia->Get("h_qtRes_x_4");
  TH1F *h_qtRes_x_5 = (TH1F*)recoPythia->Get("h_qtRes_x_5");
  TH1F *h_qtRes_y = (TH1F*)recoPythia->Get("h_qtRes_y");
  TH1F *h_qtRes_y_1 = (TH1F*)recoPythia->Get("h_qtRes_y_1");
  TH1F *h_qtRes_y_2 = (TH1F*)recoPythia->Get("h_qtRes_y_2");
  TH1F *h_qtRes_y_3 = (TH1F*)recoPythia->Get("h_qtRes_y_3");
  TH1F *h_qtRes_y_4 = (TH1F*)recoPythia->Get("h_qtRes_y_4");
  TH1F *h_qtRes_y_5 = (TH1F*)recoPythia->Get("h_qtRes_y_5");
  TH1F *h_dijetRap = (TH1F*)recoPythia->Get("h_dijetEtaRes");
  TH2F *h2_dijetRap = (TH2F*)recoPythia->Get("h2_dijetRap_Res");
  TH2F *h2_dijetRapPrime = (TH2F*)recoPythia->Get("h2_dijetRapPrime_Res");

  // Resolutions Histograms
  TH1F *h_phiPT_res = (TH1F*)resolutions->Get("h_PTphi_res");
  TH1F *h_phiQT_res = (TH1F*)resolutions->Get("h_QTphi_res");
  TH1F *h_phiPTQT_res = (TH1F*)resolutions->Get("h_trigPhi_diffPi");
  //TH1F *h_cos_res = (TH1F*)resolutions->Get("h_cosRes");
  TH1F *h_cos_res = (TH1F*)recoPythia->Get("h_PhiRes"); // plot phi res instead
  TH1F *h_cos_ratio = (TH1F*)resolutions->Get("h_recogen_cos");
  TH1F *h_qt_ratio = (TH1F*)resolutions->Get("h_recogen_qt");
  TH1F *h_qtx_ratio = (TH1F*)resolutions->Get("h_recogen_qtx");
  TH1F *h_qty_ratio = (TH1F*)resolutions->Get("h_recogen_qty");

  /////////////////// jet phi resolution ///////////////////////
  makeResolution_histogramPhi(h_jetPhi, "gen #phi_{jet} - reco #phi_{jet} [radians]", "Counts", (dirPath + "jetPhi_res.png").c_str(),-1.5,1.5,false);


  ////////////////// jet eta resolution ////////////////////////
  makeResolution_histogramEta(h_jetEta, "gen #eta_{jet} - reco #eta_{jet}", "Counts", (dirPath + "jetEta_res.png").c_str(),-1.5,1.5,false);


  ////////////////// qt resolution ////////////////////////
  makeResolution_histogram(h_qtRes, "gen Q_{T} - reco Q_{T} [GeV]", "Counts", (dirPath + "qt_res.png").c_str(),-20,20);
  
  ///////////////// qt x and y res /////////////////////////////
  makeResolution_histogram(h_qtRes_x, "gen Q_{T_{X}} - reco Q_{T_{X}} [GeV]", "Counts", (dirPath + "qtX_res.png").c_str(),-20,20);
  makeResolution_histogram(h_qtRes_y, "gen Q_{T_{Y}} - reco Q_{T_{Y}} [GeV]", "Counts", (dirPath + "qtY_res.png").c_str(),-20,20);

  // all 5
  makeResolution_histogram5(h_qtRes_x_1, h_qtRes_x_2, h_qtRes_x_3, h_qtRes_x_4, h_qtRes_x_5, "gen Q_{T_{X}} - reco Q_{T_{X}} [GeV]", "Counts", (dirPath + "qtX_5_res.png").c_str(),-20,20);
  makeResolution_histogram5(h_qtRes_y_1, h_qtRes_y_2, h_qtRes_y_3, h_qtRes_y_4, h_qtRes_y_5, "gen Q_{T_{Y}} - reco Q_{T_{Y}} [GeV]", "Counts", (dirPath + "qtY_5_res.png").c_str(),-20,20);


  ///////////////// dijet rap resolution ////////////////////////////
  makeResolution_histogram(h_dijetRap, "gen y_{dijet} - reco y_{dijet}", "Counts", (dirPath + "dijetRap_res.png").c_str(),-1.5,1.5);


  //////////////// dijet 2d rap /////////////////////////////////////
  makeResolution_histogram2d(h2_dijetRap, "gen y_{dijet}", "reco y_{dijet}", (dirPath + "dijetRap_2Dres.png").c_str());


  //////////////// dijet 2d rap prime /////////////////////////////////////
  makeResolution_histogram2d(h2_dijetRapPrime, "gen y'_{dijet}", "reco y'_{dijet}", (dirPath + "dijetRapPrime_2Dres.png").c_str());


  ////////////////// phi PT resolution //////////////////////////////////
  makeResolution_histogram(h_phiPT_res, "gen #phi_{#vec{P_{T}}}  - reco #phi_{#vec{P_{T}}}  [radians]", "Counts", (dirPath + "phiPT_res.png").c_str(), -3.2,3.2);


  ////////////////// phi QT resolution //////////////////////////////////
  makeResolution_histogram(h_phiQT_res, "gen #phi_{#vec{Q_{T}}}  - reco #phi_{#vec{Q_{T}}}  [radians]", "Counts", (dirPath + "phiQT_res.png").c_str(),-3.2,3,2);
  
  
  ////////////////// phi QTPT resolution //////////////////////////////////
  makeResolution_histogram(h_phiPTQT_res, "gen #phi_{#vec{Q_{T}},#vec{P_{T}}}  - reco #phi_{#vec{Q_{T}},#vec{P_{T}}}  [radians]", "Counts", (dirPath + "phiQTPT_res.png").c_str(),-3.2,3.2);

  ///////////////////// cos2phi resolution //////////////////////////////////
  makeResolution_histogram(h_cos_res, "gen cos(2#phi_{#vec{Q_{T}},#vec{P_{T}}})  - reco cos(2#phi_{#vec{Q_{T}},#vec{P_{T}}})", "Counts", (dirPath + "cos_res.png").c_str(),-2.2,2.2);
  //makeResolution_histogram(h_cos_res, "gen #phi_{#vec{Q_{T}},#vec{P_{T}}} - reco #phi_{#vec{Q_{T}},#vec{P_{T}}}", "Counts", (dirPath + "phiQTPT_res.png").c_str(),-3.145,3.145, false);


  
  ////////////////////// plot ratios as well //////////////////////////


  ///////////////////// cos2phi ratio //////////////////////////////////
  makeResolution_histogram(h_cos_ratio, "reco cos(2#phi_{#vec{Q_{T}},#vec{P_{T}}}) / gen cos(2#phi_{#vec{Q_{T}},#vec{P_{T}}})", "Counts", (dirPath + "cos_ratio.png").c_str(),-5,5);

  ///////////////////// qt ratio //////////////////////////////////
  makeResolution_histogram(h_qt_ratio, "reco Q_{T} / gen  Q_{T}", "Counts", (dirPath + "qt_ratio.png").c_str(),-2,5);

  ///////////////////// qtx ratio //////////////////////////////////
  makeResolution_histogram(h_qtx_ratio, "reco Q_{T_{X}} / gen Q_{T_{X}} ", "Counts", (dirPath + "qtx_ratio.png").c_str(),-3,5);

  ///////////////////// qty ratio //////////////////////////////////
  makeResolution_histogram(h_qty_ratio, "reco Q_{T_{Y}} / gen Q_{T_{Y}} ", "Counts", (dirPath + "qty_ratio.png").c_str(),-3,5);
  
}
