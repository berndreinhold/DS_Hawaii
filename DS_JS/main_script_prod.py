#!/usr/bin/python


import sys
#import time
import os
import MCProdBase as MCP

sys.argv.append( '-b' ) #batch mode, or call as: python main_script_prod.py -b
sys.argv.append( '-u' ) #stackoverflow.com/questions/107705/disable-output-buffering

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():

    code_dir = os.environ["DS_JS"]
    g4ds_dir = os.environ["MY_G4DS"] #set in main_script.sh
    output_dir = "" #is overwritten below, when on the worker node
    jobindex = 0
    #process = "0"

    print "JOB_LABEL: %s" % os.environ["JOB_LABEL"]
    print "PROCESS: %s" % os.environ["PROCESS"]
    print "ISOTOPE: %s" % os.environ["ISOTOPE"]
    if int(os.environ["DEBUG"])>0: #debug variable is always set
        output_dir=str(os.environ["DEBUG_OPERATION_DIR"])
    else:
        output_dir=str(os.environ["_CONDOR_SCRATCH_DIR"])
        
    #print "CONDOR_DIR_DS_JS: %s" % os.environ["CONDOR_DIR_DS_JS"]
    

    jobindex=int(os.environ["PROCESS"])
    isotope=str(os.environ["ISOTOPE"])
    #os.environ["CATEGORY"] - is not used here, only in main_script.sh
     
    print "jobindex: ", jobindex
    print "output_dir: ", output_dir


    #x = MCP.MCProdBase("Ar39", 500, jobindex, output_dir, code_dir, g4ds_dir)
    #
    #x = MCP.MCProdBase("Co57", 3e6, jobindex, output_dir, code_dir, g4ds_dir)
    #x = MCP.MCProdBase("Ba133", 5e5, jobindex, output_dir, code_dir, g4ds_dir)
    #x = MCP.MCProdBase("Cs137", 3e6, jobindex, output_dir, code_dir, g4ds_dir)

    #events per job
    if int(os.environ["DEBUG"])>0:
        if isotope.startswith("Co57"): events=10000
        else:
            events=1000
    else:
        opticsOn=1 #depends on the G4DS macro configuration!
        if opticsOn:

            if isotope.startswith("Co57"): events=1e5 #3e6 #for Co57, several hours
            elif isotope.startswith("Ba133"): events=2e5 #2e5 #for Ba133, ???
            elif isotope.startswith("Na22"): events=4e4 #2e5 #for Na22
            elif isotope.startswith("Ge68"): events=1e5 #2e5 #for Na22 #5e4 in about 2 hours
            elif isotope.startswith("Cs137"): events=2e5 #for Cs137
            elif isotope.startswith("Th232"): events=1e5 #for Th232, 45 min/1e5
            elif isotope.startswith("Ar39"): events=2e4 #8h for 20000 events
            elif isotope.startswith("Kr83m"): events=2e4 #5e4 for a 41.5 keV gamma, with the RDM generator it takes 3 times as long: 2e4 events
            elif isotope.startswith("AmC"): events=2e4 
            else:
                print "isotope (%s) was not identified, process 1e5 events per default" % isotope
                events=1e5
        else:
            if isotope.startswith("Co57"): events=3e6 #took 1h
            elif isotope.startswith("Cs137"): events=2.5e6
            elif isotope.startswith("Na22"): events=2e6
            elif isotope.startswith("Gamma"): events=2e6
            elif isotope.startswith("E"): events=5e6 
            else:
                print "isotope (%s) was not identified, process 1e6 events per default" % isotope
                events=1e6
                
    randomseed_offset=1002; #that's also a parameter, which can be varied per job submissions
    x = MCP.MCProdBase(isotope, events, jobindex, randomseed_offset, output_dir, code_dir, g4ds_dir) #isotope is identical to the macro name, adjust this, if the g4ds macros' names change.
    #isotope can be: Ba133, Co57, Cs137, Th232, Kr83m, Ar39
    x.loop()

    print "end of main()"



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()

