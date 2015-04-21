#!/bin/bash

export DS50app=/ds50/app
#export DS50data=/ds50/data
export MY_G4DS=/ds50/app/user/reinhol1/work/montecarlo/g4ds10/

echo "Begin `date`"
echo "PWD is $PWD"
export OLDPWD=$PWD
# Establish external products 
source ${DS50app}/products/setup

#%%%%%%%
#this is run on the worker node
#%%%%%%%
#source /ds50/app/ds50/setup_ds50 #causes trouble on the worker node, see below
#setup geant4 v4_9_6_p02 -q e4:debug #set in $MY_G4DS/configDarkSide.sh below
#setup root v5_34_12 -q e4:debug #set in $MY_G4DS/configDarkSide.sh below
#setup sam_web_client #-> disabled since in the output logfile it complained: ERROR: Product 'sam_web_client' (with qualifiers ''), has no current chain (or may not exist) 

#from submission_test.sh, from FIFE_Jobsub_tutorial.pptx
voms-proxy-info --all

source /cvmfs/fermilab.opensciencegrid.org/products/common/etc/setup
#source /cvmfs/fermilab.opensciencegrid.org/products/larsoft/setup - Ken says, I don't need this, Dec. 30 2014

setup ifdhc v1_6_2 -z /cvmfs/fermilab.opensciencegrid.org/products/common/db




cd $MY_G4DS
source configDarkSide.sh #has to be called in $MY_G4DS, otherwise libg4ds.so cannot be found. Paths in configDarkSide.sh are set using $PWD (maybe there would be a more elegant way of doing this.
cd $OLDPWD

#from submittion_test.sh
IFDH_OPTION=""

# set group based on the EXPERIMENT evnironment variable set by jobsub
GROUP=$EXPERIMENT

if [ -z $GROUP ]; then

# try to figure out what group the user is in
GROUP=`id -gn`
fi

echo "python version:"
python --version

SCRATCH_DIR="/pnfs/darkside/scratch/users"

#https://cdcvs.fnal.gov/redmine/projects/ifront/wiki/UsingJobSub#Environment-Variables-Known-To-Be-Important
    echo "HOST: $HOSTNAME"
    echo "CONDOR_DIR_INPUT: $CONDOR_DIR_INPUT"
    echo "CONDOR_DIR_DS_MCProd: $CONDOR_DIR_DS_MCProd" #(maybe) not necessary because of _CONDOR_SCRATCH_DIR - used anyway
    echo "_CONDOR_SCRATCH_DIR: $_CONDOR_SCRATCH_DIR"
    echo "TMP: $TMP"
    echo "OSG_WN_TMP: $OSG_WN_TMP"
    echo "CONDOR_TMP: $CONDOR_TMP"
    echo "CONDOR_EXEC: $CONDOR_EXEC"
    echo "PROCESS: $PROCESS" #https://cdcvs.fnal.gov/redmine/projects/ifront/wiki/Jobsub_command_reference
    #echo "LD_LIBRARY_PATH: $LD_LIBRARY_PATH"
    echo "GROUP: $GROUP"
    echo "SCRATCH_DIR: $SCRATCH_DIR"
    echo "------------------------------"
    echo "JOB_LABEL: $JOB_LABEL"
    echo "USER: $USER"
    echo "------------------------------"

#create a file environ_vars.txt, which is then read by main_script_prod.py
echo "#this is environ_vars.txt, which is used to transfer necessary enivronmental variables to main_script_prod.py. Python had an issue with os.getenv while testing in Dec. 2014" > environ_vars.txt
echo "process_var=$PROCESS" >> environ_vars.txt
echo "output_dir=$CONDOR_DIR_DS_MCProd" >> environ_vars.txt

#%%%%
#this is the main program, after everything is setup
#it produces an output file in $CONDOR_DIR_DS_MCProd (the g4ds macro is setup this way)
#python /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/HelloWorld.py

#make a local copy on the worker node... (following a tip by Ken, after we got the impression that one job would not be allowed to access HelloWorld_main_script_prod.py after one job started to use it.

ifdh cp -D /ds50/data/user/reinhol1/DS_CONDOR/CalibData/${JOB_LABEL}/*.py $PWD
ifdh cp -D /ds50/data/user/reinhol1/DS_CONDOR/CalibData/${JOB_LABEL}/*.mac $PWD 

#ifdh cp -D /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/main_script_prod.py $PWD
#ifdh cp -D /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/MCProdBase.py $PWD
#ifdh cp -D /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/Util.py $PWD
#ifdh cp -D /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/MCTuningBase.py $PWD
#ifdh cp -D /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/mac/*.mac $PWD 
#copy all the .mac files

chmod g+x *.py
chmod a+x *.py

#python /ds50/app/user/reinhol1/work/DS_Hawaii/DS_MCProd/main_script_prod.py
python main_script_prod.py

echo "------------------------------"
echo "print local directory content:"
echo "PWD: $PWD"
echo "------------------------------"
#ls
find . -iname "*.*" | sort -n
echo "------------------------------"
echo "------------------------------"

#python --version
echo "End `date`"
exit 0
