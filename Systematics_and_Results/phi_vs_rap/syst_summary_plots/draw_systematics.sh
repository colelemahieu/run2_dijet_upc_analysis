#!/bin/bash
# This script runs code to produce a summary plot showing each systematic contribution and the total systematic for dijet v2 and v4

# draw R4 rap0 systematics
root -l -b -q "drawSystematics.C(\"textFiles/jes_rapdiff_0.txt\", \"textFiles/jer_rapdiff_0.txt\", \"textFiles/jar_rapdiff_0.txt\", \"textFiles/mcStats_rapdiff_0.txt\", \"textFiles/prior_rapdiff_0.txt\", \"textFiles/trk_rapdiff_0.txt\", \"textFiles/hf_rapdiff_0.txt\", \"textFiles/it_rapdiff_0.txt\", \"Pics/systematics_rap0.png\")"
mv systematic_hists.root Files/systematic_hists_rap0.root

# draw R4 rap1 systematics
root -l -b -q "drawSystematics.C(\"textFiles/jes_rapdiff_1.txt\", \"textFiles/jer_rapdiff_1.txt\", \"textFiles/jar_rapdiff_1.txt\", \"textFiles/mcStats_rapdiff_1.txt\", \"textFiles/prior_rapdiff_1.txt\", \"textFiles/trk_rapdiff_1.txt\", \"textFiles/hf_rapdiff_1.txt\", \"textFiles/it_rapdiff_1.txt\", \"Pics/systematics_rap1.png\")"
mv systematic_hists.root Files/systematic_hists_rap1.root

root -l -b -q "drawSystematics2.C(\"Files/systematic_hists_rap0.root\", \"Files/systematic_hists_rap1.root\")"
mv Pics/systematics_3panel.pdf Pics/systematics_2panel_v2.pdf

# v4 rap0 systematics
root -l -b -q "drawSystematics.C(\"textFiles/v4_jes_rapdiff_0.txt\", \"textFiles/v4_jer_rapdiff_0.txt\", \"textFiles/v4_jar_rapdiff_0.txt\", \"textFiles/v4_mcStats_rapdiff_0.txt\", \"textFiles/v4_prior_rapdiff_0.txt\", \"textFiles/v4_trk_rapdiff_0.txt\", \"textFiles/v4_hf_rapdiff_0.txt\", \"textFiles/v4_it_rapdiff_0.txt\", \"Pics/systematics_v4_rap0.png\")"
mv systematic_hists.root Files/v4_systematic_hists_rap0.root

# v4 rap1 systematics
root -l -b -q "drawSystematics.C(\"textFiles/v4_jes_rapdiff_1.txt\", \"textFiles/v4_jer_rapdiff_1.txt\", \"textFiles/v4_jar_rapdiff_1.txt\", \"textFiles/v4_mcStats_rapdiff_1.txt\", \"textFiles/v4_prior_rapdiff_1.txt\", \"textFiles/v4_trk_rapdiff_1.txt\", \"textFiles/v4_hf_rapdiff_1.txt\", \"textFiles/v4_it_rapdiff_1.txt\", \"Pics/systematics_v4_rap1.png\")"
mv systematic_hists.root Files/v4_systematic_hists_rap1.root

root -l -b -q "drawSystematics2.C(\"Files/v4_systematic_hists_rap0.root\", \"Files/v4_systematic_hists_rap1.root\")"
mv Pics/systematics_3panel.pdf Pics/systematics_2panel_v4.pdf
