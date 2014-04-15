#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
import shutil
import time


class MCTuning:
    """produce MC with varying parameters and analyse based on Paolo Agnes' code"""

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def __init__(self, out_prefix, out_dir, anacode_dir, g4ds_dir, ev=1e6):
        self._nevents = ev
        print "number of events: %.f" % self._nevents
        self._parameters()
        
        #general:
        #self._output_dir is used for the output of G4DS and other analysis stages, but also for the macro file and DSOptics.dat file.
        #self._output_dir = "/scratch/darkside/reinhol1/"
        #self._code_dir = "/ds50/app/user/reinhol1/work/DS_Hawaii/MCTuningCode/"
        self._output_dir = out_dir
        self._code_dir = anacode_dir
        
        #g4ds related
        #self._g4ds_dir = "%s/Linux-g++/" % os.environ['MY_G4DS']
        self._g4ds_dir = "%s/Linux-g++/" % g4ds_dir 
        #self._g4ds_output_prefix = "Optical" #.fil and .root are appended below
        #self._g4ds_output_prefix = "83mKr" #.fil and .root are appended below
        self._g4ds_output_prefix = out_prefix
        self._macro_prefix = self._g4ds_output_prefix

        #output file for chi2 and figures produced in analysis code
        self._analysis_output_prefix = self._g4ds_output_prefix


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% depends on the actual parameter
    def _parameters(self):
        #parameters:
        self._par1_name="GridSteelRindScale"
        self._par1_min = 0.7
        self._par1_max = 0.8 #1.3
        self._par1_step=0.1
        self._par1_linlog="lin" #linear or log scale, default is "lin", if "lin": step is applied additively, if "log": step is applied multiplicatively
        self._par1_format="%.1f" #used in loop_1par() below to add it to the output file
        self._fill_valuelist()

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def _fill_valuelist(self):
        i=self._par1_min
        self._valuelist=[]

        #add step:
        if self._par1_linlog=="lin":
            while i<self._par1_max:
                self._valuelist.append(i)
                i=i+self._par1_step

        #multiply by step:
        elif self._par1_linlog=="log":
            if self._par1_step<=1:
                print "self._par1_step has to be bigger than 1" % self._par1_step
                os.exit(-1)
            while i<self._par1_max:
                self._valuelist.append(i)
                i=i*self._par1_step

        else:
            print "something went wrong: _par1_linlog: %s, _par1_step: %f" % (self._par1_linlog, self._par1_step)

        print "value list:(%d elements)" % len(self._valuelist)
        print self._valuelist
        if len(self._valuelist)>10:
            print "warning, the valuelist contains more than 10 elements: ", len(self._valuelist)


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def _G4DS(self):
        self._macro_file()
        #self._optics_file()
        cwd = os.getcwd()
        cmd_list="cd %s; ./g4ds %s; cd %s" % (self._g4ds_dir, self._sMacroFile, cwd)
        print cmd_list
        os.system(cmd_list)

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all (not in all generality, but for now)
    def _macro_file(self):
        """here the macro file is modified. Mainly the output file name and the number of events."""
        #sJobLabel is set in loop()
        self._sMacroFile = "%s/%s_%s.mac" % (self._output_dir, self._macro_prefix,  self._sJobLabel)
        print "sMacroFile: ", self._sMacroFile
        #copy macro and optics file to output_dir and add proper name:
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

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% depends on the parameter
    def _DSOptics(self, par1_currentvalue):
        #os.system("cp %s/DSOptics.dat %s" %(code_dir, os.environ['sOptionsFile']))
        #os.environ['sOptionsFile']="%s/DSOptics_%s.dat" % (output_dir, os.environ['sJobLabel'])
        #print "sOptionsFile: ", os.environ['sOptionsFile']

        """here the DSOptics.dat file is modified and stored in a different location. An environmental variable is set, so that g4ds finds this modified DSOptics.dat file."""
        #sJobLabel is set in loop()
        self._sDSOpticsFile = "%s/DSOptics_%s.dat" % (self._output_dir, self._sJobLabel)
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
        os.environ['DSOptics']= self._sDSOpticsFile # see DSIO.cc, which I modified


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def _G4ROOTER(self):
        os.system("%s/../tools/g4rooter %s/%s_%s.fil nevents=%d" % (self._g4ds_dir, self._output_dir, self._g4ds_output_prefix, self._sJobLabel, self._nevents))

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def _electronics_sim(self):
        print "eletronics sim not yet implemented."

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def _OneConfig(self):
        #gROOT.Reset()
        #gROOT.ProcessLine(".L %s/analyser.C" % self._code_dir)
        #gROOT.ProcessLine("analyser(\"%s/%s_%s.root\")" % (self._output_dir, self._g4ds_output_prefix, self._sJobLabel))
        os.system("%s/analyser.exe %s/%s_%s.root" % (self._code_dir, self._output_dir, self._g4ds_output_prefix, self._sJobLabel))

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def loop_1par(self):
        #create dir
        self._output_dir += "/" + self._par1_name + "/"
        os.system("mkdir %s" % self._output_dir)

        self._sJobLabel_Prefix= self._par1_name
        self._MoveFiles() #has to come after the self._output_dir is updated
        
        fOut = open("%s/chi2_%s_%s.txt" % (self._output_dir, self._g4ds_output_prefix, self._sJobLabel_Prefix), 'w') #aggregate file: parameter, chi2, can only be filled, if _OneConfig() is run
        for i in self._valuelist:
            #print i
            format_string = "%s_"
            format_string += self._par1_format
            self._sJobLabel = format_string % (self._sJobLabel_Prefix, i)
            print "sJobLabel: ", self._sJobLabel

            if 1: #data production
                self._DSOptics(i)
                self._G4DS()
                self._G4ROOTER()
                self._electronics_sim()

            #analysis
            if 0:
                self._OneConfig()
                #these files have been created in analyser.C
                f = open("%s/%s_%s.txt" % (self._output_dir, self._g4ds_output_prefix, self._sJobLabel))
                for line in f:
                    line = (self._par1_format + " %s") % (i, line)
                    fOut.write(line)
                f.close()

        fOut.close()

        print "output dir: ", self._output_dir


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def _MoveFiles(self):
        _allfiles = os.listdir(self._output_dir)
        _files = []
        for _file in _allfiles:
            if _file.endswith(".fil"):
                _files.append(_file)
            if _file.endswith("_v1.fil"):
               print "WARNING: something went wrong. there is a file, that ends on '_v1.fil': ", _file
               print "this should not happen under normal circumstances. Please investigate."
               #sys.exit(0)
               
        if len(_files) == 0:
            return

        if len(self._valuelist) == 0:
            print "valuelist is empty. Something went wrong. Exit."
            sys.exit(0)
            
        _expected_filelist = []
        
        for i in self._valuelist:
            format_string = "%s_"
            format_string += self._par1_format
            self._sJobLabel = format_string % (self._sJobLabel_Prefix, i)
            _expected_filelist.append("%s_%s.fil" % (self._g4ds_output_prefix, self._sJobLabel))

        #print _expected_filelist

        if len(_files)< len(self._valuelist):
            print "Only a subset has been produced:"
            _fileset = set(_files).intersection(_expected_filelist)
            print _fileset
            print "Is production currently ongoing? Do nothing and wait."
            print "last modification times: "
            for _file in _files:
                print "%s: %s" % (_file, time.ctime(os.path.getmtime(self._output_dir+_file)))
            sys.exit(0)

        else:
            overlap = set(_files).intersection(_expected_filelist)
            if len(overlap)==len(_expected_filelist): #the file lists are identical
                #while 1: #create dir
                i=1
                while i:
                   if os.path.isdir(self._output_dir+"/v%d" % i):
                       i+=1
                   else:
                       os.mkdir(self._output_dir+"/v%d" % i)
                       break


                for _file in os.listdir(self._output_dir+"/*.*"):
                    os.move(_file, self._output_dir+"/v%d" % i)

                print "files have been moved to: %s" % (self._output_dir+"/v%d" % i)
