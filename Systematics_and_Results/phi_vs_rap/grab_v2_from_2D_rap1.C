// grab_v2_from_2D_rap1.C
// This script takes in a 2D hist (phi vs rapidity) named h2_unf and uses a fit to extract the v2 value from each bin in rapidity. The output is a 5-bin 1D histogram 

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



void grab_v2_from_2D_rap1(string file_string)
{
  // Read File
  TFile *file = new TFile(file_string.c_str());

  // histograms and fits
  TH1F *h_phi[5];
  TF1 *fit[5];
  
 
      for (int rapBin=0; rapBin<5; rapBin++)
	{
	  h_phi[rapBin] = new TH1F(Form("h_phi_%i",rapBin), Form("h_phi_%i",rapBin), 12,-TMath::Pi(),TMath::Pi());
	  fit[rapBin] = new TF1(Form("fit_%i",rapBin), "([0]/(2*3.141593))*(1+2*([1]*cos(2*x)+[2]*cos(4*x)))",-TMath::Pi(),TMath::Pi());
	  fit[rapBin]->SetParLimits(1,-1,1);
	  fit[rapBin]->SetParLimits(2,-1,1);
	}
    


  // New ROOT file
  TFile newfile("extracted_histFit.root","recreate");
  // v2 histogram
  const int nBins=5;
  float edges[nBins+1]= {-2.5,0.0,0.5,1.0,1.5,2.5};
  TH1F *h_v2_qt1 = new TH1F("h_v2_qt1","h_v2_qt1", nBins, edges);
  TH1F *h_v4_qt1 = new TH1F("h_v4_qt1","h_v4_qt1", nBins, edges);

  
  // loop through histograms
  TH2D *h2_phi12_rap_qt = (TH2D*)file->Get("h2_unf");

  // loop through histogram bins
  for (int rapBin=1; rapBin<6; rapBin++)
    {
      for (int phiBin=1; phiBin<13; phiBin++)
	{
	  h_phi[rapBin-1]->SetBinContent(phiBin, h2_phi12_rap_qt->GetBinContent(rapBin, phiBin));
	} // end phiBin

      h_phi[rapBin-1]->Scale(1/h_phi[rapBin-1]->Integral());
      h_phi[rapBin-1]->Fit(fit[rapBin-1],"BI");

      h_v2_qt1->SetBinContent(rapBin, fit[rapBin-1]->GetParameter(1));
      h_v2_qt1->SetBinError(rapBin, fit[rapBin-1]->GetParError(1));
      h_v4_qt1->SetBinContent(rapBin, fit[rapBin-1]->GetParameter(2));
      h_v4_qt1->SetBinError(rapBin, fit[rapBin-1]->GetParError(2));
	

    } // end rapBin



  h_v2_qt1->Write();
  h_v4_qt1->Write();
  newfile.Write();
  
}
