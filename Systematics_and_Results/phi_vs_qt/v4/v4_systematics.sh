#!/bin/bash
# This script runs code to calculate systematics, add them in quadrature, and produce result plots for v4 vs QT
# Note: 'ac' refers to acceptance correction

# files (unf and gen)
fileUnf_R2="Files/fit_v2_dataUnf_R2.root"
fileUnf_R2_ac="Files/fit_v2_dataUnf_R2_ac.root"
fileUnf_R4="Files/fit_v2_dataUnf.root"
fileUnf_R4_ac="Files/fit_v2_dataUnf_ac.root"
fileUnf_R4_0n0n="Files/fit_v2_dataUnf_0n0n.root"
fileUnf_R4_0n0n_ac="Files/fit_v2_dataUnf_0n0n_ac.root"
fileUnf_R4_noZDC="Files/fit_v2_noZDC.root"
fileUnf_R6="Files/fit_v2_dataUnf_R6.root"
fileUnf_R6_ac="Files/fit_v2_dataUnf_R6_ac.root"
fileUnf_R6_0n0n="Files/fit_v2_dataUnf_R6_0n0n.root"

# files (jes)
fileJESup_R4="Files/fit_v2_jesUp_corr.root"
fileJESnom_R4="Files/fit_v2_jecNom_R4.root"
fileJESdown_R4="Files/fit_v2_jesDown_corr.root"

# files (jer)
fileJERdown_R4="Files/fit_v2_jerDown_corr.root"
fileJERnom_R4="Files/fit_v2_jecNom_R4.root"
fileJERup_R4="Files/fit_v2_jerUp_corr.root"

# files (jar)
fileJAR_R2="Files/fit_v2_jar_R2.root"
fileJAR_R4="Files/fit_v2_jar_R4.root"
fileJAR_R6="Files/fit_v2_jar.root"

# files (prior)
filePrior_R2="Files/fit_v2_prior_R2.root"
filePrior_R4="Files/fit_v2_prior.root"
filePrior_0n0n="Files/fit_v2_prior_0n0n.root"
filePrior_R6="Files/fit_v2_prior_R6.root"

# file (mc stat)
fileHalf1_R2="Files/fit_v2_half1_dataR2.root"
fileHalf2_R2="Files/fit_v2_half2_dataR2.root"
fileHalf1_R4="Files/fit_v2_half1_dataR4.root"
fileHalf2_R4="Files/fit_v2_half2_dataR4.root"
fileHalf1_0n0n="Files/fit_v2_half1_data0n0n.root"
fileHalf2_0n0n="Files/fit_v2_half2_data0n0n.root"
fileHalf1_R6="Files/fit_v2_half1_dataR6.root"
fileHalf2_R6="Files/fit_v2_half2_dataR6.root"

# files (rapUp, rapDown)
filerapgapUp="Files/fit_v2_rapUp.root"
filerapgapDown="Files/fit_v2_rapDown.root"
fileHF="Files/fit_v2_hf.root"

# R2 (rapUp, rapDown)
filerapgapUp_R2="Files/fit_v2_r2_rapUp.root"
filerapgapDown_R2="Files/fit_v2_r2_rapDown.root"
fileHF_R2="Files/fit_v2_r2_hf.root"

# R6 (rapUp, rapDown)
filerapgapUp_R6="Files/fit_v2_r6_rapUp.root"
filerapgapDown_R6="Files/fit_v2_r6_rapDown.root"
fileHF_R6="Files/fit_v2_r6_hf.root"

# iterations
file2it_R4="Files/fit_v2_2.root"
file3it_R4="Files/fit_v2_3.root"
file2it_R2="Files/fit_v2_r2_2.root"
file3it_R2="Files/fit_v2_r2_3.root"
file2it_R6="Files/fit_v2_r6_2.root"
file3it_R6="Files/fit_v2_r6_3.root"


# extract v4 from 2D histograms

# R2 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R2\")"
mv extracted_histFit.root Files/gen_r2_v4.root
# R4 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R4\")"
mv extracted_histFit.root Files/gen_r4_v4.root
# R6 GEN
root -l -b -q "grab_v2_from_2D_gen.C(\"$fileUnf_R6\")"
mv extracted_histFit.root Files/gen_r6_v4.root


# R2 UNFOLD
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R2\")"
mv extracted_histFit.root Files/unf_r2_v4.root
# R4 UNFOLD 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_0n0n\")"
mv extracted_histFit.root Files/unf_r4_0n0n_v4.root
# R4 UNFOLD
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4\")"
mv extracted_histFit.root Files/unf_r4_v4.root
# R6 UNFOLD
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R6\")"
mv extracted_histFit.root Files/unf_r6_v4.root


# R2 acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R2_ac\")"
mv extracted_histFit.root Files/unf_r2_v4_ac.root
# R4 acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_ac\")"
mv extracted_histFit.root Files/unf_r4_v4_ac.root
# R4 0n0n acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R4_0n0n_ac\")"
mv extracted_histFit.root Files/unf_r4_0n0n_v4_ac.root
# R6 acceptance
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileUnf_R6_ac\")"
mv extracted_histFit.root Files/unf_r6_v4_ac.root


# R4 JES UP
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESup_R4\")"
mv extracted_histFit.root Files/JES_up_r4_v4.root
# R4 JES NOM
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESnom_R4\")"
mv extracted_histFit.root Files/JES_nom_r4_v4.root
# R4 JES DOWN
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJESdown_R4\")"
mv extracted_histFit.root Files/JES_down_r4_v4.root

# R4 JER UP
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERup_R4\")"
mv extracted_histFit.root Files/JER_up_r4_v4.root

# R4 JER NOM
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERnom_R4\")"
mv extracted_histFit.root Files/JER_nom_r4_v4.root

# R4 JER DOWN
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJERdown_R4\")"
mv extracted_histFit.root Files/JER_down_r4_v4.root

# R2 JAR
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJAR_R2\")"
mv extracted_histFit.root Files/JAR_r2_v4.root
# R4 JAR
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJAR_R4\")"
mv extracted_histFit.root Files/JAR_r4_v4.root
# R6 JAR
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileJAR_R6\")"
mv extracted_histFit.root Files/JAR_r6_v4.root

# R2 PRIOR
root -l -b -q "grab_v2_from_2D_unf.C(\"$filePrior_R2\")"
mv extracted_histFit.root Files/prior_r2_v4.root
# R4 PRIOR
root -l -b -q "grab_v2_from_2D_unf.C(\"$filePrior_R4\")"
mv extracted_histFit.root Files/prior_r4_v4.root
# R4 PRIOR 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$filePrior_0n0n\")"
mv extracted_histFit.root Files/prior_0n0n_v4.root
# R6 PRIOR
root -l -b -q "grab_v2_from_2D_unf.C(\"$filePrior_R6\")"
mv extracted_histFit.root Files/prior_r6_v4.root


# MC Stat R2
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf1_R2\")"
mv extracted_histFit.root Files/mcStat1_r2_v4.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf2_R2\")"
mv extracted_histFit.root Files/mcStat2_r2_v4.root
# MC Stat R4
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf1_R4\")"
mv extracted_histFit.root Files/mcStat1_r4_v4.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf2_R4\")"
mv extracted_histFit.root Files/mcStat2_r4_v4.root
# MC Stat 0n0n
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf1_0n0n\")"
mv extracted_histFit.root Files/mcStat1_0n0n_v4.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf2_0n0n\")"
mv extracted_histFit.root Files/mcStat2_0n0n_v4.root
# MC Stat R6
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf1_R6\")"
mv extracted_histFit.root Files/mcStat1_r6_v4.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHalf2_R6\")"
mv extracted_histFit.root Files/mcStat2_r6_v4.root


# R4 rapgapUp
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapUp\")"
mv extracted_histFit.root Files/unf_r4_v4_rapgapUp.root
# R4 rapgapDown
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapDown\")"
mv extracted_histFit.root Files/unf_r4_v4_rapgapDown.root
# R4 hf
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHF\")"
mv extracted_histFit.root Files/unf_r4_v4_hf.root
# R2 rapgapUp
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapUp_R2\")"
mv extracted_histFit.root Files/unf_r2_v4_rapgapUp.root
# R2 rapgapDown
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapDown_R2\")"
mv extracted_histFit.root Files/unf_r2_v4_rapgapDown.root
# R2 hf
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHF_R2\")"
mv extracted_histFit.root Files/unf_r2_v4_hf.root
# R6 rapgapUp
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapUp_R6\")"
mv extracted_histFit.root Files/unf_r6_v4_rapgapUp.root
# R6 rapgapDown
root -l -b -q "grab_v2_from_2D_unf.C(\"$filerapgapDown_R6\")"
mv extracted_histFit.root Files/unf_r6_v4_rapgapDown.root
# R6 hf
root -l -b -q "grab_v2_from_2D_unf.C(\"$fileHF_R6\")"
mv extracted_histFit.root Files/unf_r6_v4_hf.root


# iterations
#r4
root -l -b -q "grab_v2_from_2D_unf.C(\"$file2it_R4\")"
mv extracted_histFit.root Files/unf_r4_v4_2iterations.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$file3it_R4\")"
mv extracted_histFit.root Files/unf_r4_v4_3iterations.root
#r2
root -l -b -q "grab_v2_from_2D_unf.C(\"$file2it_R2\")"
mv extracted_histFit.root Files/unf_r2_v4_2iterations.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$file3it_R2\")"
mv extracted_histFit.root Files/unf_r2_v4_3iterations.root
#r6
root -l -b -q "grab_v2_from_2D_unf.C(\"$file2it_R6\")"
mv extracted_histFit.root Files/unf_r6_v4_2iterations.root
root -l -b -q "grab_v2_from_2D_unf.C(\"$file3it_R6\")"
mv extracted_histFit.root Files/unf_r6_v4_3iterations.root


# compare v4 systematics plots
root -l -b -q "v4_systematics.C()"
