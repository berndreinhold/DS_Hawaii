#!/usr/bin/python

import sys
import os
from socket import gethostname;

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def time_per_1k_ev(sim_type):
    if sim_type=="83Kr": 
        return 600. #seconds for 1000 events G4DS, S1+S2
    else:
        print "WARNING: sim_type %s was not recognized." % sim_type
        return 1000.
    
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def fermigrid():
    """queries the hostname and if it is not ds50.fnal.gov, ds50srv01.fnal.gov or ds50temp01.fnal.gov, then it assumes it is on fermigrid and returns true. """
    hostname = gethostname()
    if hostname.find("fnal.gov")==-1:
        print "you are not at fermilab: ", hostname
    else:
        if not hostname.startswith("ds50"):
            return 1

    return 0

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

