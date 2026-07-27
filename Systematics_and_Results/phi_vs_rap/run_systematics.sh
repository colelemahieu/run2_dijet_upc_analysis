#!/bin/bash
# This script runs code to calculate systematics, add them in quadrature, and produce result plots for v2 vs rapidity
# Note: 'ac' refers to acceptance correction

# file
fileUnf_rap0="unfolded2D_phiRapidity_full_rap0.root"
fileUnf_rap0_ac="unfolded2D_phiRapidity_full_rap0_ac.root"
fileUnf_rap0_cut="unfolded2D_phiRapidity_data_rap0_cut.root"
fileUnf_rap1="unfolded2D_phiRapidity_full_rap1.root"
fileUnf_rap1_ac="unfolded2D_phiRapidity_full_rap1_ac.root"
#fileUnf_rap1_ac="unfolded2D_phiRapidity_0n0n_rap1.root"
fileUnf_rap1_cut="unfolded2D_phiRapidity_data_rap1_cut.root"
fileJESup_rap0="unfolded2D_phiRapidity_JESup_full_rap0.root"
fileJESup_rap1="unfolded2D_phiRapidity_JESup_full_rap1.root"
fileJESnom_rap0="unfolded2D_phiRapidity_JECnom_full_rap0.root"
fileJESnom_rap1="unfolded2D_phiRapidity_JECnom_full_rap1.root"
fileJESdown_rap0="unfolded2D_phiRapidity_JESdown_full_rap0.root"
fileJESdown_rap1="unfolded2D_phiRapidity_JESdown_full_rap1.root"
fileJERup_rap0="unfolded2D_phiRapidity_JERup_full_rap0.root"
fileJERup_rap1="unfolded2D_phiRapidity_JERup_full_rap1.root"
fileJERnom_rap0="unfolded2D_phiRapidity_JECnom_full_rap0.root"
fileJERnom_rap1="unfolded2D_phiRapidity_JECnom_full_rap1.root"
fileJERdown_rap0="unfolded2D_phiRapidity_JERdown_full_rap0.root"
fileJERdown_rap1="unfolded2D_phiRapidity_JERdown_full_rap1.root"
fileJAR_rap0="unfolded2D_phiRapidity_JAR_full_rap0.root"
fileJAR_rap1="unfolded2D_phiRapidity_JAR_full_rap1.root"
filePrior_rap0="unfolded2D_phiRapidity_full_prior_rap0.root"
filePrior_rap1="unfolded2D_phiRapidity_full_prior_rap1.root"
filemcStat1_rap0="unfolded2D_phiRapidity_full_half1_rap0.root"
filemcStat2_rap0="unfolded2D_phiRapidity_full_half2_rap0.root"
filemcStat1_rap1="unfolded2D_phiRapidity_full_half1_rap1.root"
filemcStat2_rap1="unfolded2D_phiRapidity_full_half2_rap1.root"
fileRapUp_rap0="unfolded2D_phiRapidity_full_rapUp_rap0.root"
fileRapDown_rap0="unfolded2D_phiRapidity_full_rapDown_rap0.root"
fileRapUp_rap1="unfolded2D_phiRapidity_full_rapUp_rap1.root"
fileRapDown_rap1="unfolded2D_phiRapidity_full_rapDown_rap1.root"
fileHF_rap0="unfolded2D_phiRapidity_full_hf_rap0.root"
fileHF_rap1="unfolded2D_phiRapidity_full_hf_rap1.root"
fileIt2_rap0="unfolded2D_phiRapidity_full_rap0_2.root"
fileIt3_rap0="unfolded2D_phiRapidity_full_rap0_3.root"
fileIt2_rap1="unfolded2D_phiRapidity_full_rap1_2.root"
fileIt3_rap1="unfolded2D_phiRapidity_full_rap1_3.root"

# extract v2 and v4 from 2D histograms
# GEN
root -l -b -q "grab_v2_from_2D_gen_rap0.C(\"$fileUnf_rap0\")"
mv extracted_histFit.root Files/gen_v2_rap0.root
root -l -b -q "grab_v2_from_2D_gen_rap1.C(\"$fileUnf_rap1\")"
mv extracted_histFit.root Files/gen_v2_rap1.root
# GEN, CUT
root -l -b -q "grab_v2_from_2D_gen_rap0.C(\"$fileUnf_rap0_cut\")"
mv extracted_histFit.root Files/gen_v2_rap0_cut.root
root -l -b -q "grab_v2_from_2D_gen_rap1.C(\"$fileUnf_rap1_cut\")"
mv extracted_histFit.root Files/gen_v2_rap1_cut.root
# R4 
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileUnf_rap0\")"
mv extracted_histFit.root Files/unf_r4_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileUnf_rap1\")"
mv extracted_histFit.root Files/unf_r4_v2_rap1.root
# originial
root -l -b -q "grab_v2_from_2D_orig_rap0.C(\"$fileUnf_rap0_ac\")"
mv extracted_histFit.root Files/unf_r4_v2_orig_rap0.root
root -l -b -q "grab_v2_from_2D_orig_rap1.C(\"$fileUnf_rap1_ac\")"
mv extracted_histFit.root Files/unf_r4_v2_orig_rap1.root
# R4, acceptance
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileUnf_rap0_ac\")"
mv extracted_histFit.root Files/unf_r4_v2_rap0_ac.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileUnf_rap1_ac\")"
mv extracted_histFit.root Files/unf_r4_v2_rap1_ac.root
# R4, dPhi cut
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileUnf_rap0_cut\")"
mv extracted_histFit.root Files/unf_r4_v2_rap0_cut.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileUnf_rap1_cut\")"
mv extracted_histFit.root Files/unf_r4_v2_rap1_cut.root
# JES up 
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileJESup_rap0\")"
mv extracted_histFit.root Files/JESup_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileJESup_rap1\")"
mv extracted_histFit.root Files/JESup_v2_rap1.root
# JES nom
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileJESnom_rap0\")"
mv extracted_histFit.root Files/JESnom_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileJESnom_rap1\")"
mv extracted_histFit.root Files/JESnom_v2_rap1.root
# JES down
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileJESdown_rap0\")"
mv extracted_histFit.root Files/JESdown_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileJESdown_rap1\")"
mv extracted_histFit.root Files/JESdown_v2_rap1.root
# JER up 
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileJERup_rap0\")"
mv extracted_histFit.root Files/JERup_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileJERup_rap1\")"
mv extracted_histFit.root Files/JERup_v2_rap1.root
# JER nom
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileJERnom_rap0\")"
mv extracted_histFit.root Files/JERnom_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileJERnom_rap1\")"
mv extracted_histFit.root Files/JERnom_v2_rap1.root
# JER down
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileJERdown_rap0\")"
mv extracted_histFit.root Files/JERdown_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileJERdown_rap1\")"
mv extracted_histFit.root Files/JERdown_v2_rap1.root
# JAR 
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileJAR_rap0\")"
mv extracted_histFit.root Files/JAR_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileJAR_rap1\")"
mv extracted_histFit.root Files/JAR_v2_rap1.root
# PRIOR
root -l -b -q "grab_v2_from_2D_rap0.C(\"$filePrior_rap0\")"
mv extracted_histFit.root Files/prior_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$filePrior_rap1\")"
mv extracted_histFit.root Files/prior_v2_rap1.root
# MC STAT RAP
root -l -b -q "grab_v2_from_2D_rap0.C(\"$filemcStat1_rap0\")"
mv extracted_histFit.root Files/mcStat1_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap0.C(\"$filemcStat2_rap0\")"
mv extracted_histFit.root Files/mcStat2_v2_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$filemcStat1_rap1\")"
mv extracted_histFit.root Files/mcStat1_v2_rap1.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$filemcStat2_rap1\")"
mv extracted_histFit.root Files/mcStat2_v2_rap1.root
# RAP UP, DOWN
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileRapUp_rap0\")"
mv extracted_histFit.root Files/v2_rapUp_rap0.root
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileRapDown_rap0\")"
mv extracted_histFit.root Files/v2_rapDown_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileRapUp_rap1\")"
mv extracted_histFit.root Files/v2_rapUp_rap1.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileRapDown_rap1\")"
mv extracted_histFit.root Files/v2_rapDown_rap1.root
# HF
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileHF_rap0\")"
mv extracted_histFit.root Files/v2_hf_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileHF_rap1\")"
mv extracted_histFit.root Files/v2_hf_rap1.root
# ITER
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileIt2_rap0\")"
mv extracted_histFit.root Files/v2_It2_rap0.root
root -l -b -q "grab_v2_from_2D_rap0.C(\"$fileIt3_rap0\")"
mv extracted_histFit.root Files/v2_It3_rap0.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileIt2_rap1\")"
mv extracted_histFit.root Files/v2_It2_rap1.root
root -l -b -q "grab_v2_from_2D_rap1.C(\"$fileIt3_rap1\")"
mv extracted_histFit.root Files/v2_It3_rap1.root



# compare systematics plots
root -l -b -q "compareSystematics.C()"



