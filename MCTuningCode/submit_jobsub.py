#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
sys.argv.append( '-b' ) #batch mode, or call as: python main_script.py -b


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    #submission_string = "jobsub -g -M --OS=SL6 --opportunistic -f /scratch/darkside/reinhol1/test_condor/Optical_FusedSilicaUVAbs_1.6e-04.root -d whatever /scratch/darkside/reinhol1/test_condor/ IO_test.py"
    submission_string = "jobsub -g -T -M --OS=SL6 --opportunistic -d whatever /ds50/data/user/reinhol1/work/test_MCTuning/ /ds50/app/user/reinhol1/work/DS_Hawaii/MCTuningCode/main_script.sh"
    print submission_string
    os.system(submission_string)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()
