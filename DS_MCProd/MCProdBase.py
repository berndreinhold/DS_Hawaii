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
        self._par1 = self._job_index+1000
        self._par1_format="%d"
        self._valuelist_all=[self._par1]

        self._heprandomseed=self._par1


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def loop(self):
        #called after _parameters()
        self._sJobLabel_Prefix= "CopperRings_SourceHolder_opticsOn_center+26mm_" + self._par1_name
        format_string = "%s_"
        format_string += self._par1_format
        self._sJobLabel = format_string % (self._sJobLabel_Prefix, self._par1)
        print "sJobLabel: ", self._sJobLabel
        self._G4DS() #after sJobLabel is setup
        self._G4ROOTER()
