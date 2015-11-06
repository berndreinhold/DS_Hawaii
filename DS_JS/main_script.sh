#!/bin/bash

#Ken, Aug 11, 2015: I suspect that some of the nodes may not have seen the last CVMFS update. Add the following command to your main_script.sh file before doing any setups (so basically the first thing that the script does): 
/cvmfs/grid.cern.ch/util/cvmfs-uptodate /cvmfs/darkside.opensciencegrid.org

echo "Job starting on `hostname` at `date`."
echo "PWD is $PWD"
export OLDPWD=$PWD
#from submission_test.sh, from FIFE_Jobsub_tutorial.pptx
voms-proxy-info --all

# copied from /ds50/app/user/kherner/run_darkart_TEMPLATE_CVMFS.sh
if [ -e /cvmfs/darkside.opensciencegrid.org/ds50/app/products/setup ]; then
    echo "darkside CVMFS repository is mounted. Continuing on."
else
    echo "/cvmfs/darkside.opensciencegrid.org/ds50/app/products/setup does not exist."
    if [ -e /cvmfs/fermilab.opensciencegrid.org/fermilab/products/common/etc/setup ]; then
        echo "But the FNAL oasis setup file does."
    else
        echo "And neither does the FNAL setup file."
    fi
    echo "Exiting."
    exit 1
fi

source /cvmfs/darkside.opensciencegrid.org/ds50/app/products/setup
export PRODUCTS=/cvmfs/darkside.opensciencegrid.org/ds50/app/products:/cvmfs/fermilab.opensciencegrid.org/products/common/db

setup ifdhc -z /cvmfs/fermilab.opensciencegrid.org/products/common/db




cd $MY_G4DS
source configDarkSide.sh #has to be called in $MY_G4DS, otherwise libg4ds.so cannot be found. Paths in configDarkSide.sh are set using $PWD (maybe there would be a more elegant way of doing this.

ret_code=$?
if [ $ret_code != 0 ]; then
  printf "Error : [%d] when executing source configDarkSide.sh" $ret_code
fi

#helpful references:
#https://www.joedog.org/articles-cheat-sheet/
#http://stackoverflow.com/questions/6270440/simple-logical-operators-in-bash
#
if [ ${DEBUG:-0} -gt 0 ]; then
echo "DEBUG mode is on: $DEBUG"
cd $DEBUG_OPERATION_DIR
else 
echo "DEBUG mode is not on: $DEBUG"
cd $OLDPWD
fi

#from submission_test.sh
IFDH_OPTION=""

# set group based on the EXPERIMENT evnironment variable set by jobsub
GROUP=$EXPERIMENT

if [ -z $GROUP ]; then

# try to figure out what group the user is in
GROUP=`id -gn`
fi

echo "python version:"
python --version

#https://cdcvs.fnal.gov/redmine/projects/ifront/wiki/UsingJobSub#Environment-Variables-Known-To-Be-Important
    echo "HOST: $HOSTNAME"
    echo "CONDOR_DIR_INPUT: $CONDOR_DIR_INPUT"
 #   echo "CONDOR_DIR_DS_MCProd: $CONDOR_DIR_DS_MCProd" #(maybe) not necessary because of _CONDOR_SCRATCH_DIR - used anyway
    echo "_CONDOR_SCRATCH_DIR: $_CONDOR_SCRATCH_DIR"
    echo "TMP: $TMP"
    echo "OSG_WN_TMP: $OSG_WN_TMP"
    echo "CONDOR_TMP: $CONDOR_TMP"
    echo "CONDOR_EXEC: $CONDOR_EXEC"
    echo "PWD: $PWD"
    echo "------------------------------"
    echo "GROUP: $GROUP"
    echo "USER: $USER - when run on worker node" #on the worker node, ${USER} is not your username, but a generic username, therefore one cannot use $USER as part of a directory path
    echo "------------------------------"
    echo "DEBUG: $DEBUG" #possibly enabled in submit_jobsub.py
    echo "CATEGORY: $CATEGORY"
    echo "JOB_LABEL: $JOB_LABEL"
    echo "ISOTOPE: $ISOTOPE"
    echo "PROCESS: $PROCESS" #https://cdcvs.fnal.gov/redmine/projects/ifront/wiki/Jobsub_command_reference
    #echo "LD_LIBRARY_PATH: $LD_LIBRARY_PATH"
    echo "MY_G4DS: $MY_G4DS"
    echo "EXEC_BASE_DIR: $EXEC_BASE_DIR"
    echo "FINAL_OUTPUT_BASE_DIR: $FINAL_OUTPUT_BASE_DIR"
    echo "------------------------------"


#make a local copy on the worker node... (following a tip by Ken, after we got the impression that one job would not be allowed to access HelloWorld_main_script_prod.py after one job started to use it.

if [ ! ${DEBUG:-0} -gt 0 ]; then

ifdh cp -D ${EXEC_BASE_DIR}/${CATEGORY}/${JOB_LABEL}/${ISOTOPE}/*.py $PWD
ifdh cp -D ${EXEC_BASE_DIR}/${CATEGORY}/${JOB_LABEL}/${ISOTOPE}/${ISOTOPE}*.mac $PWD 

fi

chmod g+x *.py
chmod a+x *.py

#this is the main script running G4DS and g4rooter on the worker node.
python main_script_prod.py

##transfer files back from _CONDOR_SCRATCH_DIR to $final output dir on PNFS
if [ ${DEBUG:-0} -gt 0 ]; then
cp ${DEBUG_OPERATION_DIR}/*.* ${FINAL_OUTPUT_BASE_DIR}${CATEGORY}/${JOB_LABEL}/
#cp ${DEBUG_OPERATION_DIR}/${ISOTOPE}_${JOB_LABEL}*.* ${FINAL_OUTPUT_BASE_DIR}${CATEGORY}/${JOB_LABEL}/
#rm ${ISOTOPE}_${JOB_LABEL}*.*
#cp ${DEBUG_OPERATION_DIR}/*.* ${FINAL_OUTPUT_BASE_DIR}${CATEGORY}/${JOB_LABEL}/${ISOTOPE}
else
#ifdh cp -D ${_CONDOR_SCRATCH_DIR}/${ISOTOPE}_${JOB_LABEL}*.* ${FINAL_OUTPUT_BASE_DIR}${CATEGORY}/${JOB_LABEL}/
ifdh cp -D ${_CONDOR_SCRATCH_DIR}/*.* ${FINAL_OUTPUT_BASE_DIR}/${CATEGORY}/${JOB_LABEL}/
#rm ${ISOTOPE}_${JOB_LABEL}*.*
#now transfer all the rest
#ifdh cp -D ${_CONDOR_SCRATCH_DIR}/*.* /pnfs/darkside/scratch/users/reinhol1/${CATEGORY}/${JOB_LABEL}/${ISOTOPE}/
fi

echo "------------------------------"
echo "print local directory content:"
echo "PWD: $PWD"
echo "------------------------------"
#this is just for B.'s understanding/ debugging
#ls
find . -iname "*.*" | sort -n
echo "------------------------------"
echo "------------------------------"

echo "End `date`"
exit 0
