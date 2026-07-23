# this runs the CRAB jobs producing MC Forest files 

from CRABClient.UserUtilities import config
config = config()
                       
config.section_('General')
#config.General.requestName ='MinBias_PbPb_5p36TeV_Hydjet_mini_R2_Run2'
config.General.requestName ='MinBias_PbPb_5p36TeV_Hydjet_mini_R4_Run2'
#config.General.requestName ='MinBias_PbPb_5p36TeV_Hydjet_mini_R6_Run2'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'forest_miniAOD_112X_MC.py'
config.JobType.numCores = 4
config.JobType.maxMemoryMB = 10000
config.JobType.allowUndistributedCMSSW =True

config.section_('Data')
config.Data.inputDBS = 'phys03'
config.Data.userInputFiles = open('inputFile_Forest.txt').readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/group/phys_heavyions/clemahie/Forest_test/'    
config.Data.allowNonValidInputDataset = True
config.Data.publication = True
config.Data.outputPrimaryDataset = 'pythiaForest'

#config.General.requestName ='MinBias_PbPb_5p02TeV_ggqq_mini_R2_Run2'
#config.General.requestName ='MinBias_PbPb_5p02TeV_ggqq_mini_R6_Run2'
config.General.requestName ='MinBias_PbPb_5p02TeV_ggqq_mini_R4_Run2'
config.Site.storageSite = 'T2_CH_CERN'
config.Site.whitelist = ['T2_CH_CERN']










