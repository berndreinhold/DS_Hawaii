#!/usr/bin/python


import sys
#import time
import os
import MCProdBase as MCP

sys.argv.append( '-b' ) #batch mode, or call as: python main_script_prod.py -b
sys.argv.append( '-u' ) #stackoverflow.com/questions/107705/disable-output-buffering

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    print "begin of main(): Hello World. This is to understand a strange bug in the other main_script_prod.py"

    code_dir = "/ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/"
    g4ds_dir = "/ds50/app/user/reinhol1/work/montecarlo/g4ds10/"
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

    #print "CONDOR_DIR_DS_MCProd: %s" % os.environ["CONDOR_DIR_DS_MCProd"]


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

    if int(os.environ["DEBUG"])>0:
        if isotope=="Co57": events=10000
        else:
            events=1000
    else:
        if isotope=="Co57": events=3e6 #for Co57, several hours
        elif isotope=="Ba133": events=2e5 #for Ba133, ???
        elif isotope=="Cs137": events=2e5 #for Cs137
        elif isotope=="Th232": events=1e5 #for Th232, 45 min/1e5
        elif isotope=="Ar39": events=2e5 #
        elif isotope=="Kr83m": events=2e5 #
        else:
            print "isotope (%s) was not identified, process 1e5 events per default" % isotope
            events=1e5
    x = MCP.MCProdBase(isotope, events, jobindex, output_dir, code_dir, g4ds_dir) #isotope is identical to the macro name, adjust this, if the g4ds macros' names change.
    #isotope can be: Ba133, Co57, Cs137, Th232, Kr83m, Ar39
    x.loop()

    print "end of main()"



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()

