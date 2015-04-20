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
    output_dir = "/pnfs/darkside/scratch/users/reinhol1/" #is potentially overwritten below
    jobindex = 0
    process = "0"

    print "before read environ_vars.txt"
    f=open("environ_vars.txt","r")
    lines=f.readlines()

    for line in lines:
        if line.find("="): print "=", line,
        else: print line,

    for line in lines:
        if line.startswith("#") or line.startswith("//"): continue #comment
        [var, value]=line.split("=")
        print var
        print value
        if var=="process_var": process=str(value)
        elif var=="output_dir": output_dir=str(value).strip() #here the 

    jobindex=int(process)
    
    f.close()

    print "jobindex: ", jobindex
    print "output_dir: ", output_dir

    print "before class invocation:"
    #time.sleep(60)
    #x = MCP.MCProdBase("scs_Andrew", 500, jobindex, output_dir, code_dir, g4ds_dir)
    #obsolete: #x = MCP.MCProdBase("Co57", 6e6, jobindex, output_dir, code_dir, g4ds_dir)
    #x = MCP.MCProdBase("Co57", 3e6, jobindex, output_dir, code_dir, g4ds_dir)
    x = MCP.MCProdBase("Ba133", 3e6, jobindex, output_dir, code_dir, g4ds_dir)
    #x = MCP.MCProdBase("Cs137", 3e6, jobindex, output_dir, code_dir, g4ds_dir)
    #x = MCP.MCProdBase("Th232", 3e6, jobindex, output_dir, code_dir, g4ds_dir)
    x.loop()

    print "end of main()"



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def outsourced():
    print "before variables"
#    if os.getenv("PROCESS"):
#        jobidx=os.getenv("PROCESS")
    if os.environ["PROCESS"]:
        jobidx=os.environ["PROCESS"]
        print "jobidx:", jobidx 
        jobindex=int(jobidx)
        print "jobindex (1): ", jobindex 
    else:
        print "PROCESS variable not available. Is jobsub called without -N option? Continue nevertheless."

    print "before CONDOR_DIR_DS_MCProd"
    #if os.getenv("CONDOR_DIR_DS_MCProd"):
    #    output_dir=os.getenv("CONDOR_DIR_DS_MCProd")
    if os.environ["CONDOR_DIR_DS_MCProd"]:
        output_dir=os.environ["CONDOR_DIR_DS_MCProd"]

