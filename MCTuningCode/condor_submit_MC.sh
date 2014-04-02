#!/bin/bash

#stolen from Alden's ~aldenf/ds50analysis/darkart/analysis/condor_analysis.sh
#April 2014


exe=python


parameter="WLSEfficiency"
outdir="/scratch/darkside/reinhol1/$parameter/"

#mkdir -p $outdir

outfile=${outdir}/${parameter}_output.root
cmd_file=${outdir}/${parameter}.cmd
err_file=${outdir}/${parameter}.err
out_file=${outdir}/${parameter}.out
log_file=${outdir}/${parameter}.log

cat > $cmd_file <<EOF
 
universe = vanilla
executable = $exe
getenv = True
output = $out_file
error = $err_file
log = $log_file
arguments = main_script.py
notify_user = reinhol1@fnal.gov
notification = Always

queue
EOF

echo "Submitting $cmd_file ..."
#condor_submit $cmd_file
