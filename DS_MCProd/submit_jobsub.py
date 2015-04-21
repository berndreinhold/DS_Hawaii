#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
#sys.argv.append( '-b' ) #batch mode, or call as: python main_script.py -b
#sys.argv.append( '-u' ) #stackoverflow.com/questions/107705/disable-output-buffering
#import MCTuningBase as MCT

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#example: category: CalibData, joblabel: CopperRings_SourceHolder_opticsOn_center+26mm
#category is for output
def config_setup(category,joblabel):

    #mkdir output directory:
    try:
        os.system("mkdir /pnfs/darkside/scratch/users/%s/%s/%s/" % (os.environ["USER"],category,joblabel))
        os.system("chmod g+w /pnfs/darkside/scratch/users/%s/%s/%s/" % (os.environ["USER"], category, joblabel))

        #make directory for job files
        os.system("mkdir /ds50/data/user/${USER}/DS_CONDOR/%s/" % (category))
        os.system("mkdir /ds50/data/user/${USER}/DS_CONDOR/%s/%s/" % (category, joblabel))

        #transfer job files, these are all run on the worker node
        os.system("cp /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/main_script_prod.py /ds50/data/user/${USER}/DS_CONDOR/%s/%s/" % (category, joblabel))
        os.system("cp /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/MCProdBase.py /ds50/data/user/${USER}/DS_CONDOR/%s/%s/" % (category, joblabel))
        os.system("cp /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/MCTuningBase.py /ds50/data/user/${USER}/DS_CONDOR/%s/%s/" % (category, joblabel))
        os.system("cp /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/Util.py /ds50/data/user/${USER}/DS_CONDOR/%s/%s/" % (category, joblabel))
        os.system("cp /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/mac/*.mac /ds50/data/user/${USER}/DS_CONDOR/%s/%s/" % (category, joblabel)) #should copy all mac files
    except:
        e = sys.exc_info()[0]
        print "Error: %s" % e 
        raise


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    #configure correctly: just get the number of jobs and the parameter
    #x = MCT.MCTuning("83Kr",1e4)
    #nJobs = x.NJobs()
    #nJobs = 1 #for testing

    os.environ['JOB_LABEL']="CopperRings_SourceHolder_opticsOn_center+40mm";
    config_setup("CalibData", os.environ['JOB_LABEL'])

    #parameters = "-e P1_NAME"
    #parameters = ""
    #submission_string = "jobsub -g -M --OS=SL6 -N %d --opportunistic -d whatever %s /ds50/data/user/reinhol1/work/test_MCTuning/%s/ /ds50/app/user/reinhol1/work/DS_Hawaii/MCTuningCode/main_script.sh" % (nJobs, parameters,x._par1_name)
    #submission_string = "jobsub_submit -G darkside -M --OS=SL5,SL6 -N 2 -d DS_MCProd /pnfs/darkside/scratch/users/reinhol1/Ar39/ --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file:///ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/main_script.sh"
    #submission_string = "jobsub_submit -G darkside -M --OS=SL6 -N 10 -d DS_MCProd /pnfs/darkside/scratch/users/reinhol1/CalibData/ --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file:///ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/main_script.sh"
    submission_string = "jobsub_submit -G darkside -M --OS=SL6 -N 1 -e JOB_LABEL -d DS_MCProd /pnfs/darkside/scratch/users/reinhol1/CalibData/%s --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file:///ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/main_script.sh" % os.environ['JOB_LABEL']
    #main_script.sh can still be called from DS_Hawaii/DS_MCProd, since it is picking the right job label via environmental variable.


    #don't use the -v (verbose) option anymore
    print submission_string
    os.system(submission_string)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()

#submission_string = "jobsub -g -M --OS=SL6 --opportunistic -f /scratch/darkside/reinhol1/test_condor/Optical_FusedSilicaUVAbs_1.6e-04.root -d whatever /scratch/darkside/reinhol1/test_condor/ IO_test.py"
    #--append_condor_requirements '(Disk >= N)

