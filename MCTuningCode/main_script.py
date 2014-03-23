#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
sys.argv.append( '-b' ) #batch mode, http://root.cern.ch/phpBB3/viewtopic.php?t=3198%29 -> did not work for me
#or call as: python main_script.py -b
#from ROOT import gROOT

#ToDo:
#- submit jobs to Fermigrid
#- integrate into SAM


class MCTuning:
    """produce MC with varying parameters and analyse based on Paolo Agnes' code"""

    def __init__(self):
        #general:
        self._output_dir = "/scratch/darkside/reinhol1/"
        self._temp_dir = self._output_dir + "Temp/"
        self._code_dir = "/ds50/app/user/reinhol1/work/DS_Hawaii/MCTuningCode/"
        
        self._nevents = 1e4


        #g4ds related
        self._g4ds_dir = "%s/Linux-g++/" % os.environ['MY_G4DS']
        self._g4ds_output_prefix = "Optical" #.fil and .root are appended below
        self._macro_prefix = "optical" #optical.mac

        #output file for chi2 and figures produced in analysis code
        self._analysis_output_prefix = self._g4ds_output_prefix

        #parameters:
        self._par1_name="GridSteelRindScale"
        self._par1_min = 0.7
        self._par1_max = 1.3
        self._par1_step=0.1


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def _G4DS(self):
        self._macro_file()
        #self._optics_file()
        cwd = os.getcwd()
        os.system("cd %s; ./g4ds %s; cd %s" % (self._g4ds_dir, self._sMacroFile, cwd))

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def _macro_file(self):
        """here the macro file is modified. Mainly the output file name and the number of events."""
        #sJobLabel is set in loop()
        self._sMacroFile = "%s/%s_%s.mac" % (self._temp_dir, self._macro_prefix,  self._sJobLabel)
        print "sMacroFile: ", self._sMacroFile
        #copy macro and optics file to temp_dir and add proper name:
        #os.system("cp %s/%s.mac %s" %(self._code_dir, self._macro_prefix, self._sMacroFile))

        #modify the macro according to relevant variable changes

        fMacroInputFile = open("%s/%s.mac" % (self._code_dir, self._macro_prefix))
        fMacro = open(self._sMacroFile, 'w') #output macro, containing the varied parameters 
        #search and replace relevant lines
        for line in fMacroInputFile:
            if line.startswith("/run/beamOn"): #nevents
                line="/run/beamOn %d\n" % self._nevents
                #print "### ", line,
            elif line.startswith("/run/filename"):
                line="/run/filename %s%s_%s\n" % (self._output_dir, self._g4ds_output_prefix, self._sJobLabel) 
                #print "### ", line,
            print line,
            fMacro.write(line)

        fMacroInputFile.close()
        fMacro.close()

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def _DSOptics(self, par1_currentvalue):
        #os.system("cp %s/DSOptics.dat %s" %(code_dir, os.environ['sOptionsFile']))
        #os.environ['sOptionsFile']="%s/DSOptics_%s.dat" % (temp_dir, os.environ['sJobLabel'])
        #print "sOptionsFile: ", os.environ['sOptionsFile']

        """here the DSOptics.dat file is modified and stored in a different location. An environmental variable is set, so that g4ds finds this modified DSOptics.dat file."""
        #sJobLabel is set in loop()
        self._sDSOpticsFile = "%s/DSOptics_%s.dat" % (self._temp_dir, self._sJobLabel)
        print "sDSOpticsFile: ", self._sDSOpticsFile

        #modify the DSOptics.dat according to relevant variable changes
        fDSOpticsInputFile = open("%s/../data/detector/DSOptics.dat" % self._g4ds_dir)
        f = open(self._sDSOpticsFile, 'w') #output macro, containing the varied parameters 
        #search and replace relevant lines
        for line in fDSOpticsInputFile:
            if line.startswith(self._par1_name): 
                line="%s = %f\n" % (self._par1_name, par1_currentvalue)
                print "### modified line: ### ", line,
            elif line.startswith("WithNewGridModel"): 
                line="WithNewGridModel       = 0\n" #requirement for GridSteelRindScale
                print "### modified line: ### ", line,
            #print line,
            f.write(line)

        fDSOpticsInputFile.close()
        f.close()

        #set as environmental variable, so that g4ds use that optics file instead.
        os.environ['DSOptics']= self._sDSOpticsFile # see DSIO.cc


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def _G4ROOTER(self):
        os.system("%s/../tools/g4rooter %s/%s_%s.fil nevents=%d" % (self._g4ds_dir, self._output_dir, self._g4ds_output_prefix, self._sJobLabel, self._nevents))

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def _electronics_sim(self):
        print "eletronics sim not yet implemented."

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def _OneConfig(self):
        #gROOT.Reset()
        #gROOT.ProcessLine(".L %s/analyser.C" % self._code_dir)
        #gROOT.ProcessLine("analyser(\"%s/%s_%s.root\")" % (self._output_dir, self._g4ds_output_prefix, self._sJobLabel))
        os.system("%s/analyser.exe %s/%s_%s.root" % (self._code_dir, self._output_dir, self._g4ds_output_prefix, self._sJobLabel))

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def loop_1par(self):
        self._sJobLabel_Prefix= "GridSteelRindScale"
        fOut = open(self._sJobLabel_Prefix+".txt", 'w') #aggregate file: parameter, chi2
        for i in range(int(self._par1_min*100), int(self._par1_max*100)+1, int(self._par1_step*100)): #multiply by 100, since range expects integers, the +1 in the end value results in that value also being tested, rather than it being excluded
            #print i
            self._sJobLabel = "%s_%.2f" % (self._sJobLabel_Prefix, i*0.01)
            print "sJobLabel: ", self._sJobLabel

            #self._DSOptics(i*0.01)
            #self._G4DS()
            #self._G4ROOTER()
            #self._electronics_sim()
            self._OneConfig()

            #these files have been created in analyser.C
            f = open("%s/%s_%s.txt" % (self._output_dir, self._g4ds_output_prefix, self._sJobLabel))
            for line in f:
                line = "%.2f, %s" % (i*0.01, line)
                fOut.write(line)
            f.close()

        fOut.close()



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    x = MCTuning()
    x.loop_1par()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()
