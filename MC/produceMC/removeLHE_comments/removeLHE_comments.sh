#!/bin/bash

index=$(( 1 + ${1}))
cd /eos/cms/store/group/phys_heavyions/clemahie/LHE_files

if test -f "/eos/cms/store/group/phys_heavyions/clemahie/LHE_files/pythia_${index}.lhe"; then
    python3 removeLHE_comments.py pythia_${index}.lhe
fi

