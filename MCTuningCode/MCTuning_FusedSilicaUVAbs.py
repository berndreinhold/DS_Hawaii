#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
import MCTuningBase

class MCTuning_FusedSilicaUVAbs(MCTuningBase.MCTuning):
    """
    produce MC with varying parameters and analyse based on Paolo Agnes' code
    in this case FusedSilicaUVAbs is modified
    """

    #def __init__(self): #see base class

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% depends on the actual parameter
    def _parameters(self):
        #parameters:
        self._par1_name="FusedSilicaUVAbs"
        self._par1_min = 1e-8
        self._par1_max = 1e-1
        self._par1_step=5
        self._par1_linlog="log" # "lin" and "log" as possible values
        self._par1_format="%.1e"
        self._fill_valuelist()

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def _DSOptics(self, par1_currentvalue):
        """
        here the DSOptics.dat file is modified and stored in a different location. An environmental variable is set, so that g4ds finds this modified DSOptics.dat file.
        in this case FusedSilicaUVAbs is modified

        """

        #sJobLabel is set in loop()
        self._sDSOpticsFile = "%s/DSOptics_%s.dat" % (self._output_dir, self._sJobLabel)
        print "sDSOpticsFile: ", self._sDSOpticsFile
        f = open(self._sDSOpticsFile, 'w') #output DSOptics.dat file, containing the varied parameters 

        #modify the DSOptics.dat according to relevant variable changes
        fDSOpticsInputFile = open("%s/../data/detector/DSOptics.dat" % self._g4ds_dir)

        #search and replace relevant lines
        for line in fDSOpticsInputFile:
            if line.startswith(self._par1_name): 
                line="%s = %f\n" % (self._par1_name, par1_currentvalue)
                print "### modified line: ### ", line,
            #print line,
            f.write(line)

        fDSOpticsInputFile.close()
        f.close()

        #set as environmental variable, so that g4ds use that optics file instead.
        os.environ['DSOptics']= self._sDSOpticsFile # see DSIO.cc

