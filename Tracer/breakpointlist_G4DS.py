#!/usr/bin/python
# -*- coding: utf-8 -*-

#@author: Bernd
#@date: Dec 2013
#@abstract: make a list of functions of an executable (and libraries) to set breakpoints afterwards
#inspired by previous python-scripts
#
import re
import os

#see http://www.linuxquestions.org/questions/linux-general-1/list-library-function-of-a-shared-library-so-438693/


def main(dirpath=None):
  old_pwd=os.getcwd()
  os.chdir("/home/reinhold/Software/DS/montecarlo/g4ds/Linux-g++/")
  print os.getcwd()
  L= file_listing("g4ds") #pattern used in re.search(), dir="." (default)

  #search for the executable and possibly additional libraries

  fw_name="/home/reinhold/Software/DS/DS_Hawaii/Tracer/function_lists/G4DS_function_list.txt"
  #os.system("rm -f %s;" % fw_name) #remove, because then fw_name is opened for appending

  #f_name="../DCRPEPulse.cc"
  for f_name in L:
    print f_name
    #p=re.compile('(RecoBAMA|RecoBase|RecoI)') #only for RecoBAMA
    #p=re.compile('(\/GoodGuysBadGuys)') 
    #if p.search(f_name):
    #  print "-> ", f_name
      #filename_line_functions(f_name,fw_name)
    os.system("nm -Ca g4ds> %s_temp" % fw_name)

  f = open("%s_temp" % fw_name)

  unique_breakpoints =[]
  for line in f:
    if line.startswith("0000"):
      nm_output_case1(line, unique_breakpoints)
    elif line.startswith("    "):
      nm_output_case2(line, unique_breakpoints)




  fOut = open(fw_name, "w")
  fOut2 = open(fw_name+"_notwritten", "w")

  for bp in unique_breakpoints:
    if bp.startswith("DS") or bp.startswith("G4") or bp.startswith("CLHEP") or bp.startswith("main") or bp.startswith("run") or bp.startswith("the"):
      print bp
      fOut.write("%s\n" % bp)
    else:
      fOut2.write("%s\n" % bp)

  fOut.close()
  fOut2.close()
  os.chdir(old_pwd)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def nm_output_case1(line, unique_breakp):
    #case1 starts with '0000': ['000000000040c894', 'T', 'GoodGuysBadGuys::RefillVars()\n']
    if not line.startswith("0000"):
      print "this is not case1, which starts with 0000: ", line
      os._exit(-1)

    line=line.strip('\n')
    buffer=line.split(' ') 
  
    #this worked before, but not here: if buffer[1]=="T":

    buffer2=buffer[2].split('(') #'GoodGuysBadGuys::RefillVars
    #print buffer2[0]
    if not len(buffer2[0].split('::'))==2:
      print "warning: unexpected: ", buffer2[0]
      if buffer2[0] not in unique_breakp:
        unique_breakp.append(buffer2[0])

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def nm_output_case2(line, unique_breakp):
    #case2 starts with '    ': ['              ', 'U', 'DSLogger::toEnum(std::string const&)\n']
    if not line.startswith("    "):
      print "this is not case 2, which starts with '    ': ", line
      os._exit(-1)
  
    line=line.strip() #remove all the white space
    buffer=line.split(' ')
  
    if buffer[0]=="U":
      buffer2=buffer[1].split('(') #'GoodGuysBadGuys::RefillVars
      #print buffer2[0]
      if not len(buffer2[0].split('::'))==2:
        print "warning: unexpected: ", buffer2[0]
      if buffer2[0] not in unique_breakp:
        unique_breakp.append(buffer2[0])  

    else:
      print "WARNING: unexpected flag: ", line


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#see http://stackoverflow.com/questions/120656/directory-listing-in-python
#default is to use the current dir
def file_listing(pattern="(\.cc|\.C|\.h)$", dirpath='.'):
  L = list()
  Nonselected_L = list()
  
  for dirname, dirnames, filenames in os.walk(dirpath):
    #for subdirname in dirnames:
    #  print os.path.join(dirname, subdirname)
    for filename in filenames:
      if re.search(pattern, filename) and not \
         re.search("Cint.cc$", filename): L.append(os.path.join(dirname, filename))
      else: Nonselected_L.append(os.path.join(dirname, filename))

  #print "matched pattern (",pattern,"):" , L
  #print "did not match pattern (",pattern,"):", Nonselected_L
  return L

#f is the file to be read, fw is the file to be written to
def filename_line_functions(f_name, fw_name): 
  open_bracket=0
  line_counter=0
  f = open(f_name,"r") #read this file
  fw= open(fw_name, "a") #write-only
  line_list = f.readlines()

  #only store the first line
  one_line_only=1
  #the number of namespaces increase the level of the open brackets
  #might not work properly, if there are more than one namespace
  namespace=0
  #does a line-wise comparison
  for line in line_list:
    line_counter+=1

    if re.search("namespace", line) and \
           re.search("{", line) and not re.search("using", line) :
      namespace+=1

    if re.search("{", line):
      open_bracket+=1
      if open_bracket==1+namespace: one_line_only=0
    if re.search("}", line):  
      open_bracket-=1


    if open_bracket==1+namespace and one_line_only==0:
      one_line_only=1
      fw.write(f_name)
      fw.write(":")
      fw.write(str(line_counter))
      fw.write(" ")
      fw.write(line)
    
    #fw.write(line)
    #    else: 
    #      fw.write(line)
    #      print ".", #progress bar
    #print re.search('.*::.*\(.*\).*{', line), re.search('.*::.*\(.*\)(?!.*[\(\)].*{].*{', line)


    
    


if __name__ == "__main__":
    main()


  #f_name="DCRTriggerGroup_test.txt"
  #  f_name="test_sample.txt"
  #  insert_into_file(f_name, f_name + "_mod"); #x.cc_orig -> x.cc_mod (at the same time create .cc_mod new)
  
 
    #os.rename(f_name, f_name + "_one_try"); #x.cc -> x.cc_orig
    
    #insert_into_file(f_name, f_name[:-8]); #x.cc_orig -> x.cc_mod (at the same time create .cc_mod new)
    #  os.rename(f_name + "_mod", f_name)
