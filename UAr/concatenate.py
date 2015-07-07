#!/usr/bin/python


import sys
#import time
import os
import ROOT
from sets import Set #https://docs.python.org/2/library/sets.html
#import TDirectory

sys.argv.append( '-b' ) #batch mode, or call as: python main_script_prod.py -b
sys.argv.append( '-u' ) #stackoverflow.com/questions/107705/disable-output-buffering

out_dir = "/scratch/darkside/reinhol1/UAr/"
#out_dir = "/scratch/darkside/reinhol1/Calib_XY/"
in_dir = "/scratch/darkside/slad/20150308/" #for SLAD files 
#in_dir = "~masayuki/workspace/darkart/UAr_analysis/" #for veto coincidence DSTs

list_of_trees = []

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    print "concatenate either SLAD files or Masa's DSTs into one output file using hadd."

    #https://docs.google.com/spreadsheets/d/1qa19StvmE2dO2A18HICLftLFlg8bbBmY8CYTra5y3hk/edit?pli=1#gid=2028213772
    #Co57: 200 V/cm
    #run_list = [10093, 10094, 10095, 10096, 10097, 10098, 10100, 10101, 10102] #10099 is a junk run
    #Co57, 100 V/cm
    #run_list = [10242, 10243, 10244, 10245]

    #Ba133, 150 V/cm
    #run_list = [10344, 10346, 10347, 10348, 10349, 10350] #10345 is junk

    #Ba133, 100 V/cm
    #run_list = [10333, 10334, 10335, 10336]

    #run_list = [11530, 11532,11534, 11536] #atmospheric argon

    #underground argon
    run_list = [11869, 11868, 11867, 11865, 11864, 11863, 11862, 11860, 11859, 11858, 11856]
    run_list.extend([11900, 11898, 11897, 11896, 11894, 11893, 11891, 11890, 11889, 11876, 11875, 11874, 11873, 11872]) #during the extension

    run_list.sort()
    #SLAD:
    out_name_prefix="UAr_200Vcm_run%d-%d_MasaDocDB1193" % (run_list[0], run_list[-1])
    #out_name_prefix="AAr_200Vcm_run%d-%d_MasaDocDB1193" % (run_list[0], run_list[-1])
    #Masa's veto DSTs, DocDB 1187 (even though this DocDB 1187 is on null field runs, I use them for 200 V/cm here)
    #out_name_prefix="Calib_Co57_100Vcm_run%d-%d" % (run_list[0], run_list[-1])
    #out_name_prefix="Calib_Ba133_100Vcm_run%d-%d" % (run_list[0], run_list[-1])
    #out_name_prefix="UAr_200Vcm_vetoDSTs_run%d-%d_MasaDocDB1193" % (run_list[0], run_list[-1])
    #out_name_prefix="AAr_200Vcm_vetoDSTs_run%d-%d_MasaDocDB1193" % (run_list[0], run_list[-1])

    SLAD(run_list, out_name_prefix)
    #MasaVetoDSTs(run_list, out_name_prefix)

def MasaVetoDSTs(run_list, out_name_prefix):
    print "concatenate Masa's veto DSTs into one output file using hadd. File references and code, etc. are in DocDB 1187. Nice."
    
    rl = ["%sDST_Run%06d.root" % (in_dir, x) for x in run_list]
    hadd(rl, out_name_prefix + ".root")

def SLAD(run_list, out_name_prefix):
    print "concatenate SLAD files into one output file using hadd, including the one for masas_xy (, s2, all_pulses - optional)."

    rl = ["%sRun%06d.root" % (in_dir, x) for x in run_list]
    rl_XY = ["%sRun%06d_masas_xy.root" % (in_dir, x) for x in run_list]
    rl_XY_Jason = ["%sRun%06d_xylocator_xy.root" % (in_dir, x) for x in run_list]
    #rl_s2 = ["%sRun%06d_s2.root" % (in_dir, x) for x in run_list]
    #rl_allpulses = ["%sRun%06d_allpulses.root" % (in_dir, x) for x in run_list]
    
    hadd(rl, out_name_prefix + ".root")
    hadd(rl_XY, out_name_prefix + "_masas_xy.root")
    hadd(rl_XY_Jason, out_name_prefix + "_xylocator_xy.root")
    #hadd(rl_s2, out_name_prefix + "_s2.root")
    #hadd(rl_allpulses, out_name_prefix + "_allpulses.root")

    #list the trees and their entries:
    for l in list_of_trees: #a global variable
        print "%s %s %d" % (l[0], l[1], l[2])

    #below are cross checks
    s = Set()
    for l in list_of_trees:
        if l[0]=="logbook":
            if not len(rl)== l[2]:
                print "something went wrong: logbook should have 1 entry per run: %d %d" % (len(rl), l[2])
        else:
            s.add(l[2])

    if not len(s)==1:
        print "something went wrong:"
        print s



def hadd(run_list, out_name):
    #print run_list
    
    buffer = "hadd -f %s%s %s" % ( out_dir, out_name," ".join(run_list))

    print buffer
    os.system(buffer)

    checkAllTrees("%s%s" % (out_dir, out_name))

#https://root.cern.ch/root/roottalk/roottalk04/2075.html
def checkAllTrees(out_file):
    f = ROOT.TFile(out_file)
    dirlist = f.GetListOfKeys()
    #dirlist.ls()

    iter = dirlist.MakeIterator()
    key = iter.Next()

    while key:
        if key.GetClassName() == 'TTree' or key.GetClassName() == 'TChain':
            t = key.ReadObj()
            a = key.GetName(), key.GetTitle(), t.GetEntries()
            #print a
            list_of_trees.append(a)
        key = iter.Next()



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()

