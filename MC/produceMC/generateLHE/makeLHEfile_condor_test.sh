#!/bin/bash

index=$((1 + ${1}))
export LD_LIBRARY_PATH=/afs/cern.ch/user/c/clemahie/Pythia8p311/pythia8311/lib:$LD_LIBRARY_PATH

/afs/cern.ch/user/c/clemahie/Pythia8p311/pythia8311/examples/main70 "/eos/cms/store/group/phys_heavyions/clemahie/LHE_files/pythia_${index}.lhe"
