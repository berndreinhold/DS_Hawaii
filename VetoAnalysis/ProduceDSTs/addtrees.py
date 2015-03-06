#!/usr/bin/python

import os

runlist = [11155, 11157, 10975, 10976]
for run in runlist:
    if run==11155 or run==11157:
        prefix="DSTAwayData/"
    else:
        prefix="DSTSlaveData/"
    for td in range(0,6):
        buffer= "hadd /scratch/darkside/reinhol1/Veto/%std%d0ODRun0%d.root /ds50/data/user/shawest/TestRuns/VetoOutput_Run0%d/td%dODRun0%d_0*.root" % (prefix, td, run, run, td, run)
        print buffer,
        os.system(buffer)
        
    for am in range(0,6):
        buffer="hadd /scratch/darkside/reinhol1/Veto/%sam%d0ODRun0%d.root /ds50/data/user/shawest/TestRuns/VetoOutput_Run0%d/am%dODRun0%d_0*.root" % (prefix,am, run, run, am, run)
        print buffer,
        os.system(buffer)
        

