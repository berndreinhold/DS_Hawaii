#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
sys.argv.append( '-b' ) #batch mode, or call as: python main_script.py -b
#import MCTuning_FusedSilicaUVAbs as MCT
import MCTuningBase as MCT
#python main_script.py &> FusedSilicaUVAbs_output.log &

#ToDo:
#- submit jobs to Fermigrid
#- integrate into SAM

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    #x = MCT.MCTuning_FusedSilicaUVAbs()
    x = MCT.MCTuning()
    print x.__doc__
    x.loop_1par() #switch on and off certain analysis steps in the MCTuningBase.py

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()
