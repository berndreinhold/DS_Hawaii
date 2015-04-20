#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
#sys.argv.append( '-b' ) #batch mode, or call as: python main_script.py -b
#sys.argv.append( '-u' ) #stackoverflow.com/questions/107705/disable-output-buffering
#import MCTuningBase as MCT


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    #configure correctly: just get the number of jobs and the parameter
    #x = MCT.MCTuning("83Kr",1e4)
    #nJobs = x.NJobs()
    #nJobs = 1 #for testing

    #mkdir:
    #os.system("mkdir /ds50/data/user/reinhol1/work/test_MCTuning/%s/" % x._par1_name)
    #os.system("chmod g+w /ds50/data/user/reinhol1/work/test_MCTuning/%s/" % x._par1_name)
    
    #os.environ['P1_NAME']=x._par1_name
    #parameters = "-e P1_NAME"
    parameters = ""
    #submission_string = "jobsub -g -M --OS=SL6 -N %d --opportunistic -d whatever %s /ds50/data/user/reinhol1/work/test_MCTuning/%s/ /ds50/app/user/reinhol1/work/DS_Hawaii/MCTuningCode/main_script.sh" % (nJobs, parameters,x._par1_name)
    #submission_string = "jobsub_submit -G darkside -M --OS=SL5,SL6 -N 2 -d DS_MCProd /pnfs/darkside/scratch/users/reinhol1/Ar39/ --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file:///ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/main_script.sh"
    submission_string = "jobsub_submit -G darkside -M --OS=SL6 -N 10 -d DS_MCProd /pnfs/darkside/scratch/users/reinhol1/CalibData/ --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file:///ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/main_script.sh"
    #don't use the -v (verbose) option anymore
    print submission_string
    os.system(submission_string)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()

#submission_string = "jobsub -g -M --OS=SL6 --opportunistic -f /scratch/darkside/reinhol1/test_condor/Optical_FusedSilicaUVAbs_1.6e-04.root -d whatever /scratch/darkside/reinhol1/test_condor/ IO_test.py"
    #--append_condor_requirements '(Disk >= N)
