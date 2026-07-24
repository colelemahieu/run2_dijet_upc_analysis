// grab_v2_from_2D_unf.C (qt)
// This script takes in a 2D hist (phi vs QT) named h2_unf and uses a fit to extract the v2 value from each bin in QT. The output is a 5-bin 1D histogram 

#include <iostream>
#include <cstdlib>
#include <fstream>
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
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "/home/colelemahieu/Research2023/commonUtility.h"
using namespace std;



void grab_v2_from_2D_unf(string file_string)
{
  // Read File
  TFile *file = new TFile(file_string.c_str());
  TH2D *h2_unf = (TH2D*)file->Get("h2_unf");


  // histograms and fits
  TH1F *h_phi[5];
  TF1 *fit[5];
  
  for (int qtBin=0; qtBin<5; qtBin++)
    {
      h_phi[qtBin] = new TH1F(Form("h_phi_%i",qtBin), Form("h_phi_%i",qtBin), 12,-TMath::Pi(),TMath::Pi());
      fit[qtBin] = new TF1(Form("fit_%i",qtBin), "([0]/(2*3.141593))*(1+2*([1]*cos(2*x)+[2]*cos(4*x)))",-TMath::Pi(),TMath::Pi());
      fit[qtBin]->SetParLimits(1,-1,1);
      fit[qtBin]->SetParLimits(2,-1,1);
    }
    

  // New ROOT file
  TFile newfile("extracted_histFit.root","recreate");
  // v2 histogram
  const int nBins=5;
  float edges[nBins+1]= {0,8,16,24,32,40};
  TH1F *h_v2 = new TH1F("h_v2","h_v2", nBins, edges);
  TH1F *h_v4 = new TH1F("h_v4","h_v4", nBins, edges);

  

  // loop through histogram bins
  for (int qtBin=1; qtBin<6; qtBin++)
    {
      for (int phiBin=1; phiBin<13; phiBin++)
	{
	  h_phi[qtBin-1]->SetBinContent(phiBin, h2_unf->GetBinContent(qtBin, phiBin));
	  
	} // end phiBin

	  h_phi[qtBin-1]->Scale(1/h_phi[qtBin-1]->Integral());
	  h_phi[qtBin-1]->Fit(fit[qtBin-1],"BI");
	 

	  // Write fits and hists to new ROOT file
	  h_v2->SetBinContent(qtBin, fit[qtBin-1]->GetParameter(1));
	  h_v2->SetBinError(qtBin, fit[qtBin-1]->GetParError(1));
	  h_v4->SetBinContent(qtBin, fit[qtBin-1]->GetParameter(2));
	  h_v4->SetBinError(qtBin, fit[qtBin-1]->GetParError(2));
	    
	  
	} // end qtBin


     

  h_v2->Write("h_v2");
  h_v4->Write("h_v4");
  newfile.Write();
  
}
