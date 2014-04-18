#!/bin/bash
#see http://stackoverflow.com/questions/311840/tool-to-trace-local-function-calls-in-linux
#6.12.2009
#updated in dec. 2013

#see Makefile

software_package="GGBG"
in="function_lists/"$software_package"_function_list.txt"
out="function_lists/"$software_package"_gdb.txt"
gawk ' { print "b " $1; 
    print "commands"; 
    print "silent"; 
    print "bt"; 
    print "c"; 
    print "end"; 
    print ""; 
} ' $in > $out;

#add 'run' at the end
echo 'run' >> $out;


echo "file '" $out "' has been produced. use as gdb --command=[file] [executable]"
echo " gdb --command="$out" [executable]"



