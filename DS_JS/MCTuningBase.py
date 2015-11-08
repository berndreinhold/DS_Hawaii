#!/usr/bin/python

import sys
import os
import string
import shutil
import time
import math
import Util

class MCTuning:
    """produce MC with varying parameters and analyse based on Paolo Agnes' code"""

    #ev is 'events per job' 
    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def __init__(self, out_prefix, ev, job_index=-1, randomseed_offset=0, out_dir="", anacode_dir="", g4ds_dir=""):
        #check all directories, that they end on '/'
        if not out_dir.endswith("/"): out_dir+="/"
        if not anacode_dir.endswith("/"): anacode_dir+="/"
        if not g4ds_dir.endswith("/"): g4ds_dir+="/"

        self._simulation_type=out_prefix #Optical or 83mKr 

        self._randomseed_offset=randomseed_offset
        self._nevents = ev #nevents is written into the G4DS macro
        print "number of events (per job): %.f" % self._nevents
        self._job_index=job_index
        self._heprandomseed=randomseed_offset #not used, e.g. set in MCProdBase.py to self._job_index
        self._parameters()

 
        #this is the configuration mode in which nothing more is needed
        if job_index<0:
            print "job_index is <0: %d" % job_index
            return
        self._fill_valuelist(job_index)
        
        #general:
        #self._output_dir is used for the output of G4DS and other analysis stages, but also for the macro file and DSOptics.dat file.
        #self._output_dir = "/scratch/darkside/reinhol1/"
        #self._code_dir = "/ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/"
        self._output_dir = out_dir
        self._code_dir = anacode_dir
        
        #g4ds related
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

        #this is for the whole parameter scan
        self._par1_min = 0.7
        self._par1_max = 1.3
        self._par1_step=0.1
        self._par1_linlog="lin" #linear or log scale, default is "lin", if "lin": step is applied additively, if "log": step is applied multiplicatively
        self._par1_format="%.1f" #used in loop_1par() below to add it to the output file

        self._fill_valuelist_all()

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
    def NJobs(self):
        """ requires self._valuelist_all to be filled"""
        time_per_1k_ev = Util.time_per_1k_ev(self._simulation_type)
        total_nevents=len(self._valuelist_all)*self._nevents
        total_time = 1.*time_per_1k_ev*total_nevents/1000 #in seconds
        time_per_job=4*3600; #sec

        if time_per_1k_ev*self._nevents/1000/time_per_job>1:
            print "WARNING: this job will take about %.1f h. But a typical run should not take longer than 4h. resize the number of events per job" % (time_per_1k_ev*self._nevents/1000/3600)
        

        return int(math.ceil(total_time/time_per_job))

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% valuelist for the whole parameter scan (if there are more than one job submission)
    def _fill_valuelist_all(self):
        i=self._par1_min
        self._valuelist_all=[]

        #add step:
        if self._par1_linlog=="lin":
            while i<self._par1_max:
                self._valuelist_all.append(i)
                i=i+self._par1_step

        #multiply by step:
        elif self._par1_linlog=="log":
            if self._par1_step<=1:
                print "self._par1_step has to be bigger than 1" % self._par1_step
                os.exit(-1)
            while i<self._par1_max:
                self._valuelist_all.append(i)
                i=i*self._par1_step

        else:
            print "something went wrong: _par1_linlog: %s, _par1_step: %f" % (self._par1_linlog, self._par1_step)

        print "value list:(%d elements)" % len(self._valuelist_all)
        print self._valuelist_all
        if len(self._valuelist_all)>10:
            print "warning, the valuelist_all contains more than 10 elements: ", len(self._valuelist_all)


    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% valuelist for one Fermigrid job
    def _fill_valuelist(self, index):
        """
        fill _valuelist from _valuelist_all, based on number of jobs to split this parameter scan into.
        index is provided by the jobsub -N variable

        consider self._valuelist_all = [0,1,2,3,4,5,6], njobs=4 and index=1
        in this case math.ceil(len(self._valuelist_all)/njobs) becomes 2
        and self._valuelist should be [2,3]

        for njobs=3, self._valuelist is [6] -> therefore the math.ceil-function.
        works also, if njobs is 1.

        There is also the case where there is no valuelist needed (the valuelist is 1)
        """
        self._valuelist = []
        
        njobs=self.NJobs()
        if index>=njobs:
            print "index >= self.Njobs(). This should not happen under normal circumstances. Please investigate. index: %d, self.Njobs(): %d" % (index, njobs)
            #os._exit(-1)

        i=0
        step = int(math.ceil(len(self._valuelist_all)/njobs)) #python seems to do funny things with precision of numbers. Sometimes 1 is 0.9999999999999999 and then a int(1) and float(1.) comparison can be problematic. that's why the cast to int above.
        for value in self._valuelist_all:
            if i>=index*step and i< (index+1)*step:
                self._valuelist.append(value)
            i+=1

        print self._valuelist

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

        #fMacroInputFile = open("%s/%s.mac" % (self._code_dir, self._macro_prefix))
        fMacroInputFile = open("%s.mac" % self._macro_prefix) #call locally on the worker node.
        fMacro = open(self._sMacroFile, 'w') #output macro, containing the varied parameters 
        #search and replace relevant lines
        for line in fMacroInputFile:
            line.strip() #get rid of whitespace at the beginning and the end of the string
            if line.startswith("/run/beamOn"): #nevents
                line="/run/beamOn %d\n" % self._nevents
                #print "### ", line,
            elif line.startswith("/run/filename"):
                line="/run/filename %s%s_%s\n" % (self._output_dir, self._g4ds_output_prefix, self._sJobLabel) 
                #print "### ", line,
            elif line.startswith("/ds/manager/eventcounter"):
                line="/ds/manager/eventcounter %d\n" % int(self._nevents*1.0/10)
            elif line.startswith("/run/heprandomseed"):
                if self._heprandomseed>0:
                    line="/run/heprandomseed %d\n" % self._heprandomseed
                
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
        os.system("%s/../tools/g4rooter_full %s/%s_%s.fil nevents=%d" % (self._g4ds_dir, self._output_dir, self._g4ds_output_prefix, self._sJobLabel, self._nevents))

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def _electronics_sim(self):
        print "eletronics sim not yet included."

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def _OneConfig(self):
        #gROOT.Reset()
        #gROOT.ProcessLine(".L %s/analyser.C" % self._code_dir)
        #gROOT.ProcessLine("analyser(\"%s/%s_%s.root\")" % (self._output_dir, self._g4ds_output_prefix, self._sJobLabel))
        os.system("%s/analyser.exe %s/%s_%s.root" % (self._code_dir, self._output_dir, self._g4ds_output_prefix, self._sJobLabel))

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% common to all
    def loop_1par(self):
        #create dir
        #self._output_dir += "/" + self._par1_name + "/"
        #os.system("mkdir %s" % self._output_dir)
        #jobsub complained when creating a subdirectoyr on the worker node and try to transfer it at the end. therefore eliminated it here and adapted output paths in submit_jobsub.py

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
    #not clear, what the role of this is. It is called in loop_1par() at the beginning ... (Bernd, Dec. 27, 2014
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
