####### ignore what follows for now (July 6, 2015, Bernd, bernd@hawaii.edu)

#create 
###/ds50/data/user/${USER}/DS_CONDOR
###/ds50/data/user/${USER}/DS_CONDOR/DB
#/scratch/darkside/reinhol1/DS_CONDOR/
#/scratch/darkside/reinhol1/DS_CONDOR/DB/

#check that these directories exist in submit_jobsub.py, otherwise exit with the comment to run initial_setup.sh
#-d DS_JS /pnfs/darkside/scratch/users/reinhol1/CalibData needs to be set in submit_jobsub.py - if it does not exist, exit job

#in main_script_prod.py:
#    code_dir = "/ds50/app/user/reinhol1/work/DS_Hawaii/DS_JS/"
#    g4ds_dir = "/ds50/app/user/reinhol1/work/montecarlo/g4ds10/"


#MY_PNFS is used in main_script.sh to transfer files.