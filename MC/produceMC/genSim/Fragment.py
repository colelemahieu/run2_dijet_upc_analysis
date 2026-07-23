# this is the Fragment used in the genSim MC step

import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Pythia8CommonSettings_cfi import *


externalLHEProducer = cms.EDProducer("ExternalLHEProducer",
    args = cms.vstring('/afs/cern.ch/user/c/clemahie/gammaUPC_test/GGToJJ_madgraphLO_el8_amd64_gcc10_CMSSW_12_4_8_tarball.tar.xz'),
    nEvents = cms.untracked.uint32(10),
    numberOfParameters = cms.uint32(1),
    outputFile = cms.string('cmsgrid_final.lhe'),
    scriptName = cms.FileInPath('GeneratorInterface/LHEInterface/data/run_generic_tarball_cvmfs.sh')
)



generator = cms.EDFilter("Pythia8HadronizerFilter",
    					maxEventsToPrint = cms.untracked.int32(1), 
    					pythiaPylistVerbosity = cms.untracked.int32(1),
    					filterEfficiency = cms.untracked.double(1.0),
    					pythiaHepMCVerbosity = cms.untracked.bool(False),
    					comEnergy = cms.double(5020.),
    					PythiaParameters = cms.PSet(
        						parameterSets = cms.vstring('skip_hadronization'),
        						skip_hadronization = cms.vstring('ProcessLevel:all = off',
            							'Check:event = off')
    )
    
)
