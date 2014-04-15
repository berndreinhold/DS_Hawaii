#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
sys.argv.append( '-b' ) #batch mode, or call as: python main_script.py -b
#import MCTuning_FusedSilicaUVAbs as MCT
import MCTuningBase as MCT
#import MCTuning_WLSEfficiency as MCT
#python main_script.py |& tee /scratch/darkside/reinhol1/GridSteelRindScale/83mKr_GridSteelRindScale_output.log &

#ToDo:
#- submit jobs to Fermigrid
#- integrate into SAM

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    batch = 1
    code_dir = "/ds50/app/user/reinhol1/work/DS_Hawaii/MCTuningCode"
    g4ds_dir = "/ds50/app/user/reinhol1/work//montecarlo/g4ds/"
    output_dir = "/scratch/darkside/reinhol1/" #good for local testing
    if batch:
        if not os.getenv("CONDOR_DIR_whatever"):
            print "$CONDOR_DIR_whatever variable not available. Is this python program not used in batch mode, maybe?!"
            os._exit(-1)
        else:
            output_dir = os.getenv("CONDOR_DIR_whatever")

        
    #x = MCT.MCTuning_FusedSilicaUVAbs("83mKr", 1e4)
    x = MCT.MCTuning("83mKr", output_dir, code_dir, g4ds_dir, 1e4)
    #x = MCT.MCTuning_WLSEfficiency("83mKr", output_dir, code_dir, 1e4)
    x.loop_1par() #switch on and off certain analysis steps in the MCTuningBase.py

    #x = MCT.MCTuning_FusedSilicaUVAbs("Optical", 1e6)
    #x = MCT.MCTuning("Optical", output_dir, code_dir, g4ds_dir, 1e6)
    #x = MCT.MCTuning_WLSEfficiency("Optical", output_dir, code_dir, 1e6)
    #x.loop_1par() 

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()
