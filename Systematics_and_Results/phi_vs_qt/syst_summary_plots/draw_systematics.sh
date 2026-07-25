#!/bin/bash
# This script runs code to produce a summary plot showing each systematic contribution and the total systematic for dijet v2 and v4

# draw R4 QT systematics
root -l -b -q "drawSystematics.C(\"textFiles/jes_diff.txt\", \"textFiles/jer_diff.txt\", \"textFiles/jar_diff.txt\", \"textFiles/mcStats_diff.txt\", \"textFiles/prior_diff.txt\", \"textFiles/trk_diff.txt\", \"textFiles/hf_diff.txt\", \"textFiles/it_diff.txt\", \"Pics/systematics_R4.png\")"
mv systematic_hists.root Files/systematic_hists_r4.root

# draw R2 QT systematics
root -l -b -q "drawSystematics.C(\"textFiles/jes_diff.txt\", \"textFiles/jer_diff.txt\", \"textFiles/jar_diff_r2.txt\", \"textFiles/mcStats_diff_r2.txt\", \"textFiles/prior_diff_r2.txt\", \"textFiles/trk_diff_r2.txt\", \"textFiles/hf_diff_r2.txt\", \"textFiles/it_diff_r2.txt\", \"Pics/systematics_R2.png\")"
mv systematic_hists.root Files/systematic_hists_r2.root

# draw R6 QT systematics
root -l -b -q "drawSystematics.C(\"textFiles/jes_diff.txt\", \"textFiles/jer_diff.txt\", \"textFiles/jar_diff_r6.txt\", \"textFiles/mcStats_diff_r6.txt\", \"textFiles/prior_diff_r6.txt\", \"textFiles/trk_diff_r6.txt\", \"textFiles/hf_diff_r6.txt\", \"textFiles/it_diff_r6.txt\", \"Pics/systematics_R6.png\")"
mv systematic_hists.root Files/systematic_hists_r6.root


root -l -b -q "drawSystematics2.C()"



# v4

# draw v4 R4 QT systematics
root -l -b -q "drawSystematics.C(\"textFiles/v4_jes_diff.txt\", \"textFiles/v4_jer_diff.txt\", \"textFiles/v4_jar_diff.txt\", \"textFiles/v4_mcStats_diff.txt\", \"textFiles/v4_prior_diff.txt\", \"textFiles/v4_trk_diff.txt\", \"textFiles/v4_hf_diff.txt\", \"textFiles/v4_it_diff.txt\", \"Pics/v4_systematics_R4.png\")"
mv systematic_hists.root Files/systematic_hists_r4_v4.root

# draw v4 R2 QT systematics
root -l -b -q "drawSystematics.C(\"textFiles/v4_jes_diff.txt\", \"textFiles/v4_jer_diff.txt\", \"textFiles/v4_jar_diff_r2.txt\", \"textFiles/v4_mcStats_diff_r2.txt\", \"textFiles/v4_prior_diff_r2.txt\", \"textFiles/v4_trk_diff_r2.txt\", \"textFiles/v4_hf_diff_r2.txt\", \"textFiles/v4_it_diff_r2.txt\", \"Pics/v4_systematics_R2.png\")"
mv systematic_hists.root Files/systematic_hists_r2_v4.root

# draw v4 R6 QT systematics
root -l -b -q "drawSystematics.C(\"textFiles/v4_jes_diff.txt\", \"textFiles/v4_jer_diff.txt\", \"textFiles/v4_jar_diff_r6.txt\", \"textFiles/v4_mcStats_diff_r6.txt\", \"textFiles/v4_prior_diff_r6.txt\", \"textFiles/v4_trk_diff_r6.txt\", \"textFiles/v4_hf_diff_r6.txt\", \"textFiles/v4_it_diff_r6.txt\", \"Pics/v4_systematics_R6.png\")"
mv systematic_hists.root Files/systematic_hists_r6_v4.root


root -l -b -q "drawSystematics2_v4.C()"
