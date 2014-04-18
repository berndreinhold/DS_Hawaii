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

  L= file_listing("GoodGuysBadGuys.exe","../") #pattern used in re.search(), dir="." (default)

  #search for the executable and possibly additional libraries

  fw_name="function_lists/GGBG_function_list.txt"
  #os.system("rm -f %s;" % fw_name) #remove, because then fw_name is opened for appending

  #f_name="../DCRPEPulse.cc"
  for f_name in L:
    print f_name
    #p=re.compile('(RecoBAMA|RecoBase|RecoI)') #only for RecoBAMA
    #p=re.compile('(\/GoodGuysBadGuys)') 
    #if p.search(f_name):
    #  print "-> ", f_name
      #filename_line_functions(f_name,fw_name)
    os.system("nm -Ca ../GoodGuysBadGuys.exe | grep \"GoodGuysBadGuys\" > %s_temp" % fw_name)

  f = open("%s_temp" % fw_name)

  unique_breakpoints =[]
  for line in f:
    buffer=line.split(' ') #['000000000040c894', 'T', 'GoodGuysBadGuys::RefillVars()\n']
    if buffer[1]=="T":
      #print buffer
      buffer2=buffer[2].split('(') #'GoodGuysBadGuys::RefillVars
      #print buffer2[0]
      if not len(buffer2[0].split('::'))==2:
        print "warning: unexpected: ", buffer2[0]
      if buffer2[0] not in unique_breakpoints:
        unique_breakpoints.append(buffer2[0])

  print unique_breakpoints

  fOut = open(fw_name, "w")

  for bp in unique_breakpoints:
    fOut.write("%s\n" % bp)

  fOut.close()

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
