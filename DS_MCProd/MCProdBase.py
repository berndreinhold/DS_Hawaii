#!/usr/bin/python

import sys
import os
import string
import MCTuningBase

class MCProdBase(MCTuningBase.MCTuning):
    """
    produce MC of Ar39 or Co57 or something else (set in main_script_prod.py)
    """

    #def __init__(self): #see base class

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% depends on the actual parameter
    def _parameters(self):
        #parameters:
        self._par1_name="RandomSeed"
        self._par1 = self._job_index+1001
        #self._par1 = self._job_index+950
        self._par1_format="%d"
        self._valuelist_all=[self._par1]

        self._heprandomseed=self._par1


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def loop(self):
        #called after _parameters()
        try:
            self._sJobLabel_Prefix=os.environ["JOB_LABEL"]+"_"+self._par1_name
        except KeyError:
            print "environmental variable $JOB_LABEL not set"
            self._sJobLabel_Prefix= "CopperRings_SourceHolder_opticsOn_NO_JOB_LABEL_var_" + self._par1_name

        format_string = "%s_"
        format_string += self._par1_format
        self._sJobLabel = format_string % (self._sJobLabel_Prefix, self._par1)
        print "sJobLabel: ", self._sJobLabel
        self._G4DS() #after sJobLabel is setup
        self._G4ROOTER()
