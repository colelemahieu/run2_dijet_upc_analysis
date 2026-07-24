#!/bin/bash
# This script runs code to calculate systematics, add them in quadrature, and produce result plots
# Note: 'ac' refers to acceptance correction

# files (unf and gen)
fileUnf_R2="Files/fit_v2_full_r2.root"
fileUnf_R2_ac="Files/fit_v2_full_R2_ac.root"
fileUnf_R4="Files/fit_v2_full.root"
fileUnf_R4_ac="Files/fit_v2_full_ac.root"
fileUnf_R4_0n0n="Files/fit_v2_dataUnf_0n0n.root"
fileUnf_R4_0n0n_ac="Files/fit_v2_full_0n0n_ac.root"
fileUnf_R4_noZDC="Files/fit_v2_noZDC.root"
fileUnf_R6="Files/fit_v2_full_r6.root"
fileUnf_R6_ac="Files/fit_v2_full_R6_ac.root"
fileUnf_R6_0n0n="Files/fit_v2_dataUnf_R6_0n0n.root"
fileUnf_gg_ac="Files/fit_v2_dataUnf_ggqq_ac.root"
fileUnf_gg="Files/fit_v2_dataUnf_ggqq.root"

# files with 5pi/6 cut
fileUnf_R2_cut="Files/fit_v2_cut_R2.root"
fileUnf_R4_cut="Files/fit_v2_cut_R4.root"
fileUnf_R4_0n0n_cut="Files/fit_v2_cut_0n0n.root"
fileUnf_R6_cut="Files/fit_v2_cut_R6.root"

# files (jes)
fileJESup_R4="Files/fit_v2_full_jesUp.root"
fileJESnom_R4="Files/fit_v2_jecNom_full.root"
fileJESdown_R4="Files/fit_v2_full_jesDown.root"
fileJESup_0n0n="Files/fit_v2_jesUp_0n0n.root"
fileJESnom_0n0n="Files/fit_v2_jecNom_0n0n.root"
fileJESdown_0n0n="Files/fit_v2_jesDown_0n0n.root"

# files (jer)
fileJERdown_R4="Files/fit_v2_full_jerDown.root"
fileJERnom_R4="Files/fit_v2_jecNom_full.root"
fileJERup_R4="Files/fit_v2_full_jerUp.root"
fileJERdown_0n0n="Files/fit_v2_jerDown_0n0n.root"
fileJERnom_0n0n="Files/fit_v2_jecNom_0n0n.root"
fileJERup_0n0n="Files/fit_v2_jerUp_0n0n.root"

# files (jar)
fileJAR_R2="Files/fit_v2_full_jar_R2.root"
fileJAR_R4="Files/fit_v2_full_jar_R4.root"
fileJAR_R6="Files/fit_v2_full_jar_R6.root"
fileJAR_0n0n="Files/fit_v2_jar_0n0n.root"

# files (prior)
filePrior_R2="Files/fit_v2_full_prior_r2.root"
filePrior_R4="Files/fit_v2_full_prior_r4.root"
filePrior_0n0n="Files/fit_v2_prior_0n0n.root"
filePrior_R6="Files/fit_v2_full_prior_r6.root"

# files (mc stat)
fileHalf1_R2="Files/fit_v2_full_half1_r2.root"
fileHalf2_R2="Files/fit_v2_full_half2_r2.root"
fileHalf1_R4="Files/fit_v2_full_half1.root"
fileHalf2_R4="Files/fit_v2_full_half2.root"
fileHalf1_0n0n="Files/fit_v2_full_0n0n_half1.root"
fileHalf2_0n0n="Files/fit_v2_full_0n0n_half2.root"
fileHalf1_R6="Files/fit_v2_full_half1_r6.root"
fileHalf2_R6="Files/fit_v2_full_half2_r6.root"

# files (rapUp, rapDown)
filerapgapUp="Files/fit_v2_full_rapUp_r4.root"
filerapgapDown="Files/fit_v2_full_rapDown_r4.root"
fileHF="Files/fit_v2_full_hf_r4.root"
fileHF_0n0n="Files/fit_v2_0n0n_hf.root"
filerapgapUp_0n0n="Files/fit_v2_0n0n_rapUp.root"
filerapgapDown_0n0n="Files/fit_v2_0n0n_rapDown.root"

# R2 files (rapUp, rapDown)
filerapgapUp_R2="Files/fit_v2_full_rapUp_r2.root"
filerapgapDown_R2="Files/fit_v2_full_rapUp_r2.root"
fileHF_R2="Files/fit_v2_full_hf_r2.root"

# R6 files (rapUp, rapDown)
filerapgapUp_R6="Files/fit_v2_full_rapUp_r6.root"
filerapgapDown_R6="Files/fit_v2_full_rapDown_r6.root"
fileHF_R6="Files/fit_v2_full_hf_r6.root"

# files (iterations)
file2it_R4="Files/fit_v2_full_2.root" 
file3it_R4="Files/fit_v2_full_3.root"
file2it_0n0n="Files/fit_v2_0n0n_2.root"
file3it_0n0n="Files/fit_v2_0n0n_3.root"
file2it_R2="Files/fit_v2_full_2_r2.root"
file3it_R2="Files/fit_v2_full_3_r2.root"
file2it_R6="Files/fit_v2_full_2_r6.root"
file3it_R6="Files/fit_v2_full_3_r6.root"

# extract v2 from 2D histograms

# R2 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R2\")"
mv extracted_histFit.root Files/gen_r2_v2.root
# R4 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R4_ac\")"
mv extracted_histFit.root Files/gen_r4_v2.root
# R4 GEN 0n0n gg
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_gg\")"
mv extracted_histFit.root Files/gen_r4_v2_gg.root
# R6 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R6\")"
mv extracted_histFit.root Files/gen_r6_v2.root

# dPHI R2 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R2_cut\")"
mv extracted_histFit.root Files/gen_r2_v2_cut.root
# dPHI R4 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R4_cut\")"
mv extracted_histFit.root Files/gen_r4_v2_cut.root
# dPHI R6 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R6_cut\")"
mv extracted_histFit.root Files/gen_r6_v2_cut.root

# R2 UNFOLD
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R2\")"
mv extracted_histFit.root Files/unf_r2_v2.root
# R4 UNFOLD 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_0n0n\")"
mv extracted_histFit.root Files/unf_r4_0n0n_v2.root 
# R4 UNFOLD
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4\")"
mv extracted_histFit.root Files/unf_r4_v2.root
# R4 UNFOLD noZDC
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_noZDC\")"
mv extracted_histFit.root Files/unf_r4_noZDC_v2.root
# R4 ggqq UNFOLD 0n0n 
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_gg\")"
mv extracted_histFit.root Files/unf_r4_0n0n_gg_v2.root
# R6 UNFOLD
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R6\")"
mv extracted_histFit.root Files/unf_r6_v2.root

# R2 original
root -l -b -q "grab_v2_from_2D_orig.C(\"$fileUnf_R2\")"
mv extracted_histFit.root Files/unf_r2_v2_orig.root
# R4 original
root -l -b -q "grab_v2_from_2D_orig.C(\"$fileUnf_R4\")"
mv extracted_histFit.root Files/unf_r4_v2_orig.root
# R6 original
root -l -b -q "grab_v2_from_2D_orig.C(\"$fileUnf_R6\")"
mv extracted_histFit.root Files/unf_r6_v2_orig.root
# R4 0n0n original
root -l -b -q "grab_v2_from_2D_orig.C(\"$fileUnf_R4_0n0n\")"
mv extracted_histFit.root Files/unf_r4_0n0n_v2_orig.root
# R6 0n0n original
root -l -b -q "grab_v2_from_2D_orig.C(\"$fileUnf_R6_0n0n\")"
mv extracted_histFit.root Files/unf_r6_0n0n_v2_orig.root

# R2 acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R2_ac\")"
mv extracted_histFit.root Files/unf_r2_v2_ac.root
# R4 acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_ac\")"
mv extracted_histFit.root Files/unf_r4_v2_ac.root
# R4 0n0n acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_0n0n_ac\")"
mv extracted_histFit.root Files/unf_r4_0n0n_v2_ac.root
# R4 ggqq UNFOLD 0n0n acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_gg_ac\")"
mv extracted_histFit.root Files/unf_r4_0n0n_gg_v2_ac.root
# R6 acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R6_ac\")"
mv extracted_histFit.root Files/unf_r6_v2_ac.root


# R4 RECO
root -l -b -q "grab_v2_from_2D_reco.C(\"$fileUnf_R4\")"
mv extracted_histFit.root Files/reco_r4_v2.root
# RECO R4 gg -> qq
root -l -b -q "grab_v2_from_2D_reco.C(\"$fileUnf_gg\")"
mv extracted_histFit.root Files/reco_r4_v2_gg.root


# R2 dPhi
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R2_cut\")"
mv extracted_histFit.root Files/unf_r2_v2_cut.root
# R4 dPhi
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_cut\")"
mv extracted_histFit.root Files/unf_r4_v2_cut.root
# R4 0n0n dPhi
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_0n0n_cut\")"
mv extracted_histFit.root Files/unf_r4_0n0n_v2_cut.root
# R6 dPhi
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R6_cut\")"
mv extracted_histFit.root Files/unf_r6_v2_cut.root


# R4 JES UP
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESup_R4\")"
mv extracted_histFit.root Files/JES_up_r4_v2.root
# R4 JES NOM
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESnom_R4\")"
mv extracted_histFit.root Files/JES_nom_r4_v2.root
# R4 JES DOWN
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESdown_R4\")"
mv extracted_histFit.root Files/JES_down_r4_v2.root

# 0n0n JES UP
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESup_0n0n\")"
mv extracted_histFit.root Files/JES_up_0n0n_v2.root
# 0n0n JES NOM
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESnom_0n0n\")"
mv extracted_histFit.root Files/JES_nom_0n0n_v2.root
# 0n0n JES DOWN
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESdown_0n0n\")"
mv extracted_histFit.root Files/JES_down_0n0n_v2.root

# R4 JER UP
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERup_R4\")"
mv extracted_histFit.root Files/JER_up_r4_v2.root
# R4 JER NOM
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERnom_R4\")"
mv extracted_histFit.root Files/JER_nom_r4_v2.root
# R4 JER DOWN
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERdown_R4\")"
mv extracted_histFit.root Files/JER_down_r4_v2.root

# 0n0n JER UP
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERup_0n0n\")"
mv extracted_histFit.root Files/JER_up_0n0n_v2.root
# 0n0n JER NOM
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERnom_0n0n\")"
mv extracted_histFit.root Files/JER_nom_0n0n_v2.root
# 0n0n JER DOWN
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERdown_0n0n\")"
mv extracted_histFit.root Files/JER_down_0n0n_v2.root

# R2 JAR
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJAR_R2\")"
mv extracted_histFit.root Files/JAR_r2_v2.root
# R4 JAR
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJAR_R4\")"
mv extracted_histFit.root Files/JAR_r4_v2.root
# R6 JAR
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJAR_R6\")"
mv extracted_histFit.root Files/JAR_r6_v2.root
# 0n0n JAR
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJAR_0n0n\")"
mv extracted_histFit.root Files/JAR_0n0n_v2.root

# R2 PRIOR
root -l -b -q "grab_v2_from_2D_unf.C(\"$filePrior_R2\")"
mv extracted_histFit.root Files/prior_r2_v2.root
# R4 PRIOR
root -l -b -q "grab_v2_from_2D_unf.C(\"$filePrior_R4\")"
mv extracted_histFit.root Files/prior_r4_v2.root
# R4 PRIOR 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$filePrior_0n0n\")"
mv extracted_histFit.root Files/prior_0n0n_v2.root
# R6 PRIOR
root -l -b -q "grab_v2_from_2D_unf.C(\"$filePrior_R6\")"
mv extracted_histFit.root Files/prior_r6_v2.root

# MC Stat R2
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf1_R2\")"
mv extracted_histFit.root Files/mcStat1_r2_v2.root 
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf2_R2\")"
mv extracted_histFit.root Files/mcStat2_r2_v2.root 
# MC Stat R4
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf1_R4\")"
mv extracted_histFit.root Files/mcStat1_r4_v2.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf2_R4\")"
mv extracted_histFit.root Files/mcStat2_r4_v2.root
# MC Stat 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf1_0n0n\")"
mv extracted_histFit.root Files/mcStat1_0n0n_v2.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf2_0n0n\")"
mv extracted_histFit.root Files/mcStat2_0n0n_v2.root
# MC Stat R6
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf1_R6\")"
mv extracted_histFit.root Files/mcStat1_r6_v2.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf2_R6\")"
mv extracted_histFit.root Files/mcStat2_r6_v2.root

# R4 rapgapUp
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapUp\")"
mv extracted_histFit.root Files/unf_r4_v2_rapgapUp.root
# R4 rapgapDown
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapDown\")"
mv extracted_histFit.root Files/unf_r4_v2_rapgapDown.root
# R4 hf
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHF\")"
mv extracted_histFit.root Files/unf_r4_v2_hf.root
# R2 rapgapUp
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapUp_R2\")"
mv extracted_histFit.root Files/unf_r2_v2_rapgapUp.root
# R2 rapgapDown
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapDown_R2\")"
mv extracted_histFit.root Files/unf_r2_v2_rapgapDown.root
# R2 hf
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHF_R2\")"
mv extracted_histFit.root Files/unf_r2_v2_hf.root
# R6 rapgapUp
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapUp_R6\")"
mv extracted_histFit.root Files/unf_r6_v2_rapgapUp.root
# R6 rapgapDown
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapDown_R6\")"
mv extracted_histFit.root Files/unf_r6_v2_rapgapDown.root
# R6 hf
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHF_R6\")"
mv extracted_histFit.root Files/unf_r6_v2_hf.root
# R4 rapgapUp 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapUp_0n0n\")"
mv extracted_histFit.root Files/unf_0n0n_v2_rapgapUp.root
# R4 rapgapDown 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapDown_0n0n\")"
mv extracted_histFit.root Files/unf_0n0n_v2_rapgapDown.root
# R4 hf 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHF_0n0n\")"
mv extracted_histFit.root Files/unf_0n0n_v2_hf.root


# iterations
#r4
root -l -b -q "grab_v2_from_2D_unf.C(\"$file2it_R4\")"
mv extracted_histFit.root Files/unf_r4_v2_2iterations.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$file3it_R4\")"
mv extracted_histFit.root Files/unf_r4_v2_3iterations.root
#r2
root -l -b -q "grab_v2_from_2D_unf.C(\"$file2it_R2\")"
mv extracted_histFit.root Files/unf_r2_v2_2iterations.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$file3it_R2\")"
mv extracted_histFit.root Files/unf_r2_v2_3iterations.root
#r6
root -l -b -q "grab_v2_from_2D_unf.C(\"$file2it_R6\")"
mv extracted_histFit.root Files/unf_r6_v2_2iterations.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$file3it_R6\")"
mv extracted_histFit.root Files/unf_r6_v2_3iterations.root
#0n0n 
root -l -b -q "grab_v2_from_2D_unf.C(\"$file2it_0n0n\")"
mv extracted_histFit.root Files/unf_0n0n_v2_2iterations.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$file3it_0n0n\")"
mv extracted_histFit.root Files/unf_0n0n_v2_3iterations.root

# compare systematics plots
root -l -b -q "compareSystematics.C()"
