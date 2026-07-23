#!/bin/bash

dirR2="MinBias_PbPb_5p36TeV_Hydjet_mini_R2_Run2/240913_204835"

dirR4="PbPb_5p02TeV_mini_R4_Run2/MC/240816_132444" # r4 Pythia sample1
#dirR4="PbPb_5p02TeV_mini_R4_Run2/MC/251214_184903" # r4 Pythia sample2
#dirR4="PbPb_5p02TeV_mini_R4_Run2/MC/251222_032551" # r4 Pythia sample3
#dirR4="PbPb_5p02TeV_mini_R4_Run2/MC/251229_154102" # r4 Pythia sample4
#dirR4="PbPb_5p02TeV_mini_R4_Run2/MC/260103_234356" # r4 Pythia sample5

dirR6="PbPb_5p02TeV_mini_R6_Run2/MC/240916_011403"

if [ ${1} -lt 10 ] 
then
	path="/eos/cms/store/group/phys_heavyions/clemahie/Forest_test/pythiaForest/${dirR4}/000${1}"
        echo "made it here"
else
	path="/eos/cms/store/group/phys_heavyions/clemahie/Forest_test/pythiaDigi/${dirR4}/00${1}"
fi


outPath="/eos/cms/store/group/phys_heavyions/clemahie/miniAOD_r4_reco_1_${1}.root"

if test -d "${path}"; then
    echo "made it to running the script"
    root -b -l -q "/afs/cern.ch/user/c/clemahie/MC_MINIAOD_Forest/CMSSW_11_2_1_patch2/src/HeavyIonsAnalysis/Configuration/test/miniAOD_mcSkim.C(\"${path}/HiForestMiniAOD_*.root\", \"${outPath}\")"
fi





