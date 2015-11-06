#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
#sys.argv.append( '-b' ) #batch mode, or call as: python main_script.py -b
#sys.argv.append( '-u' ) #stackoverflow.com/questions/107705/disable-output-buffering
#import MCTuningBase as MCT

#adapt these to your needs:
debug_exec_workernode_dir="/scratch/darkside/reinhol1/Temp/DS_JS_Test/" #this directory is only relevant in debug mode. It is the equivalent of the local directory on the workernode where all the python scripts and macros are copied to and executed #need to change directory, since /ds50/data/user/reinhol1/DS_CONDOR/ gives a permission denied error, despite doing chmod 755 on main_script.sh

exec_base_dir="/ds50/data/user/reinhol1/DS_CONDOR/" #this directory is on ds50srv01 (or equivalent machine), where all the python scripts and G4DS macros are copied to and adjusted before them being copied to the worker node (within main_script.sh)
#DS_JS="/scratch/darkside/reinhol1/Test_GIT/DS_Hawaii/DS_JS/" #checkout directory of this code
DS_JS=os.getcwd()
final_output_base_dir="/pnfs/darkside/scratch/users/%s/" % (os.environ["USER"])
#final_output_base_dir="/scratch/darkside/reinhol1/Test_GIT/output/"
MY_G4DS="/ds50/app/user/reinhol1/work/montecarlo/g4ds10/" #this path is called on the worker node



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#example: category: CalibData, joblabel: CopperRings_SourceHolder_opticsOn_center+26mm
#category is for output
def config_setup(category, isotope, joblabel, debug=0):

    os.environ["EXEC_BASE_DIR"]=exec_base_dir
    os.environ["MY_G4DS"]=MY_G4DS
    os.environ["FINAL_OUTPUT_BASE_DIR"]=final_output_base_dir
    os.environ["DS_JS"]=DS_JS
    
    #mkdir output directory, this has to match the ${FINAL_OUTPUT_BASE_DIR} in main_script.sh
    try:
        directory ="%s/%s/%s/" % (final_output_base_dir, category, joblabel)
        if not os.path.exists(directory):
            os.makedirs(directory)
            os.system("chmod g+w %s" % (directory))
        print directory
        directory = "%s/%s/" % (directory,isotope)
        if not os.path.exists(directory):
            os.makedirs(directory)
            os.system("chmod g+w %s" % (directory))
        print directory
        
        #make directory for job files
        directory = "%s/%s/" % (exec_base_dir,category)
        if not os.path.exists(directory):
            os.makedirs(directory)
            os.system("chmod g+w %s" % (directory))
        print directory

        directory = "%s/%s/%s/" % (exec_base_dir,category, joblabel)
        if not os.path.exists(directory):
            os.makedirs(directory)
            os.system("chmod g+w %s" % (directory))
        print directory

        directory = "%s/%s/%s/%s/" % (exec_base_dir, category, joblabel, isotope)
        if not os.path.exists(directory):
            os.makedirs(directory)
            os.system("chmod g+w %s" % (directory))
        print directory
        
        #transfer job files to this directory, then these are copied to the worker node in main_script.sh, and run on the worker node
        os.system("cp %s/main_script_prod.py %s/" % (DS_JS, directory))
        os.system("cp %s/MCProdBase.py %s/" % (DS_JS, directory))
        os.system("cp %s/MCTuningBase.py %s/" % (DS_JS, directory))
        os.system("cp %s/Util.py %s/" % (DS_JS, directory))
        os.system("cp %s/mac/%s*.mac %s" % (DS_JS, isotope, directory))
        os.system("cp %s/main_script.sh /%s/%s_%s_main_script.sh" % (DS_JS, directory, isotope, joblabel)) #rename it, because this is then more descriptive in the 'query jobsub_q -G darkside --user=reinhol1', where the sh-script is printed to screen ,otherwise it is the same across all isotopes.
        os.system("chmod g+x /%s/%s_%s_main_script.sh" % (directory, isotope, joblabel))
        os.system("chmod a+x /%s/%s_%s_main_script.sh" % (directory, isotope, joblabel))
###
	#os.system("cp /ds50/app/user/reinhol1/work/DS_Hawaii/DS_JS/main_script.sh /%s/main_script.sh" % directory) 
        #os.system("chmod g+x /%s/main_script.sh" % directory)
        #os.system("chmod a+x /%s/main_script.sh" % directory)
    except OSError:
        e = sys.exc_info()[0]
        print "Error: %s" % e 
        raise

    return directory


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    debug=0
    os.environ['DEBUG']="%d" % debug #to switch the debug mode off, set to a value below 1

    #configure correctly: just get the number of jobs and the parameter
    #x = MCT.MCTuning("83Kr",1e4)
    #(nJobs, JobsPerEvent) = x.NJobs()

    nJobs = 1
    #nJobs = 10 #is ignored in DEBUG mode
    #os.environ['CATEGORY']="CalibData"; #radioactive sources are there, 39Ar and 83mKr are in a different category. This category is used in output directories on PNFS and /ds50/data/ see above 
    #os.environ['JOB_LABEL']="CopperRings_NullField_center_plus26mm";
    #os.environ['JOB_LABEL']="CopperRings_200V_ExtLarScint0_center_plus26mm";
    #os.environ['ISOTOPE']="Co57";

    os.environ['CATEGORY']="CalibData"; #radioactive sources are there, 39Ar and 83mKr are in a different category. This category is used in output directories on PNFS and /ds50/data/ see above 
    #os.environ['JOB_LABEL']="initial_test";
    os.environ['JOB_LABEL']="TPC_cathode_speckles";

    #ISOTOPE is also used as name of the macro
    #os.environ['ISOTOPE']="Na22";
    #os.environ['ISOTOPE']="Ge68";
    #os.environ['ISOTOPE']="Co57_DS20k";
    #os.environ['ISOTOPE']="Cs137_DS20k";
    #os.environ['ISOTOPE']="Gamma2MeV_DS20k";
    #os.environ['ISOTOPE']="Gamma4MeV_DS20k";
    #os.environ['ISOTOPE']="Gamma6MeV_DS20k";
    #os.environ['ISOTOPE']="Gamma8MeV_DS20k";
    #os.environ['ISOTOPE']="Gamma10MeV_DS20k";
    os.environ['ISOTOPE']="E500keV_DS20k";
    
    #os.environ['ISOTOPE']="Na22_DS20k";
    #os.environ['ISOTOPE']="Ba133";

    #os.environ['CATEGORY']="Internal"; 
    #os.environ['JOB_LABEL']="FastSim";
    #os.environ['ISOTOPE']="Ar39";
    
    #os.environ['CATEGORY']="Internal"; 
    #os.environ['JOB_LABEL']="NullField_Uniform";
    #os.environ['ISOTOPE']="Kr83m";
    
    exec_dir=config_setup(os.environ['CATEGORY'],  os.environ['ISOTOPE'], os.environ['JOB_LABEL'], debug)

    if(debug>0):
        #for debugging:
        #os.system("/ds50/data/user/reinhol1/DS_CONDOR/%s/%s/%s/%s_%s_main_script.sh" % (os.environ['CATEGORY'], os.environ['JOB_LABEL'], os.environ['ISOTOPE'], os.environ['ISOTOPE'], os.environ['JOB_LABEL'])) #the macro run in this /ds50/data/ subdirectory gives permission denied errors, therefore use scratch for debugging mode
        os.system("cp %s/*.* %s/" % (exec_dir, debug_exec_workernode_dir)) #the .mac, the .py and the .sh script
        os.environ['DEBUG_OPERATION_DIR']=debug_exec_workernode_dir
        os.environ['PROCESS']="%d" % 0 #in non-debug mode this variable is available on the worker node through the -N option.
        os.chdir("%s/" % debug_exec_workernode_dir)
        os.system("./%s_%s_main_script.sh" % (os.environ['ISOTOPE'], os.environ['JOB_LABEL']))

    else:
        submission_string = "jobsub_submit -G darkside -M --OS=SL6 -N %d -e JOB_LABEL -e ISOTOPE -e CATEGORY -e DEBUG -e FINAL_OUTPUT_BASE_DIR -e DS_JS -e MY_G4DS -e EXEC_BASE_DIR --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file://%s/%s_%s_main_script.sh" % (nJobs, exec_dir, os.environ['ISOTOPE'], os.environ['JOB_LABEL'])
        #remove the -L option! Or provide absolute output path (e.g. on /pnfs/...)
        #main_script.sh is renamed just because of the more descriptive 'query jobsub_q -G darkside --user=reinhol1' (see comment above)
	#submission_string = "jobsub_submit -G darkside -M --OS=SL6 -N %d -e JOB_LABEL -e ISOTOPE -e CATEGORY -e DEBUG --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file://%s/main_script.sh" % (nJobs, "/ds50/app/user/reinhol1/work/DS_Hawaii/DS_JS/")

        print submission_string
        os.system(submission_string)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()

#submission_string = "jobsub -g -M --OS=SL6 --opportunistic -f /scratch/darkside/reinhol1/test_condor/Optical_FusedSilicaUVAbs_1.6e-04.root -d whatever /scratch/darkside/reinhol1/test_condor/ IO_test.py"
    #--append_condor_requirements '(Disk >= N)

    #parameters = "-e P1_NAME"
    #parameters = ""
    #submission_string = "jobsub -g -M --OS=SL6 -N %d --opportunistic -d whatever %s /ds50/data/user/reinhol1/work/test_MCTuning/%s/ /ds50/app/user/reinhol1/work/DS_Hawaii/MCTuningCode/main_script.sh" % (nJobs, parameters,x._par1_name)
    #submission_string = "jobsub_submit -G darkside -M --OS=SL5,SL6 -N 2 -d DS_JS /pnfs/darkside/scratch/users/reinhol1/Ar39/ --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file:///ds50/app/user/reinhol1/work/DS_Hawaii/DS_JS/main_script.sh"
    #submission_string = "jobsub_submit -G darkside -M --OS=SL6 -N 10 -d DS_JS /pnfs/darkside/scratch/users/reinhol1/CalibData/ --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file:///ds50/app/user/reinhol1/work/DS_Hawaii/DS_JS/main_script.sh"
    #submission_string = "jobsub_submit -G darkside -M --OS=SL6 -N 1 -e JOB_LABEL -d DS_JS /pnfs/darkside/scratch/users/reinhol1/CalibData/%s --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --role=Analysis file:///ds50/app/user/reinhol1/work/DS_Hawaii/DS_JS/main_script.sh" % os.environ['JOB_LABEL']
