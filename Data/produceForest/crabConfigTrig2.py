# this contains the settings for the CRAB jobs processing HIRun2018A-PbPb18_MiniAODv1-v1

from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = True
#config.General.requestName = 'HiForest_PbPb_Run2018_ak2'
config.General.requestName = 'HiForest_PbPb_Run2018_ak4'
#config.General.requestName = 'HiForest_PbPb_Run2018_ak6'
#config.General.requestName = 'HiForest_PbPb_Run2018_ak8'

config.section_('JobType')
config.JobType.psetName = 'forest_miniAOD_run2_DATA.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['HiForestMiniAOD.root']
config.JobType.pyCfgParams = ['noprint']
config.JobType.numCores = 8
config.JobType.maxMemoryMB = 18000
config.JobType.maxJobRuntimeMin=190

config.section_('Data')
config.Data.inputDataset = '/HIForward/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions18/HI/PromptReco/Cert_326381-327564_HI_PromptReco_Collisions18_JSON_HF_and_MuonPhys.txt'

config.Data.publication = False
config.Data.publishDBS = 'phys03'
config.Data.unitsPerJob = 1
config.Data.splitting = 'FileBased'
config.Data.ignoreLocality = True

#config.Data.outputDatasetTag = 'HiForward_Hiforest_PbPb_Run2018_ak2'
config.Data.outputDatasetTag = 'HiForward_Hiforest_PbPb_Run2018_ak4'
#config.Data.outputDatasetTag = 'HiForward_Hiforest_PbPb_Run2018_ak6'
#config.Data.outputDatasetTag = 'HiForward_Hiforest_PbPb_Run2018_ak8'
config.section_('User')
config.section_('Site')
#config.Site.blacklist = ["T2_DE_RWTH"]
config.Site.whitelist = ["T2_CH_CERN"]
config.Site.storageSite = 'T3_CH_CERNBOX'
