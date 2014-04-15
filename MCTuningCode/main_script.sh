#!/bin/bash

export DS50app=/ds50/app
export DS50data=/ds50/data
export MY_G4DS=/ds50/app/user/reinhol1/work/montecarlo/g4ds/

echo "PWD is $PWD"
export OLDPWD=$PWD
# Establish external products 
source ${DS50app}/products/setup

#source /ds50/app/ds50/setup_ds50 #causes trouble on the worker node, see below
#setup geant4 v4_9_6_p02 -q e4:debug #set in $MY_G4DS/configDarkSide.sh below
#setup root v5_34_12 -q e4:debug #set in $MY_G4DS/configDarkSide.sh below
setup sam_web_client

cd $MY_G4DS
source configDarkSide.sh #has to be called in $MY_G4DS, otherwise libg4ds.so cannot be found. Paths in configDarkSide.sh are set using $PWD (maybe there would be a more elegant way of doing this.
cd $OLDPWD

#https://cdcvs.fnal.gov/redmine/projects/ifront/wiki/UsingJobSub#Environment-Variables-Known-To-Be-Important
    echo "HOST: $HOSTNAME"
    echo "CONDOR_DIR_INPUT: $CONDOR_DIR_INPUT"
    echo "CONDOR_DIR_whatever: $CONDOR_DIR_whatever"
    echo "_CONDOR_SCRATCH_DIR: $_CONDOR_SCRATCH_DIR"
    echo "TMP: $TMP"
    echo "OSG_WN_TMP: $OSG_WN_TMP"
    echo "CONDOR_TMP: $CONDOR_TMP"
    echo "CONDOR_EXEC: $CONDOR_EXEC"
    echo "LD_LIBRARY_PATH: $LD_LIBRARY_PATH"

python /ds50/app/user/reinhol1/work/DS_Hawaii/MCTuningCode/main_script.py