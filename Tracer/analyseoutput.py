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

  f = open('GGBG_output.txt')
  fOut = open('GGBG_output.txt_postprocessing','w')

  stacksize_map = dict() #C++ map, python dictionary
  stacksize=-1
  previous_line=""
  for line in f:
    if line.startswith('#0'):
      if stacksize>0:
        fOut.write("%d %s" %(stacksize+1, previous_line[4:]))
        if stacksize+1 in stacksize_map:
          stacksize_map[stacksize+1]+=1
        else:
          stacksize_map[stacksize+1]=1
      previous_line=line
      stacksize=0
    elif line.startswith('#'):
      stacksize+=1

  if stacksize>0: fOut.write("%d %s" %(stacksize+1, previous_line[4:]))

  print "(stacksize: occurrences)"
  print stacksize_map
  fOut.close()
    
#analyse further:
#awk '{print $1, $2}' GGBG_output.txt_postprocessing | sort | uniq -c | sort -n
#'problem': functions that are on the same level and inside a for-loop

#      1 2 GoodGuysBadGuys::GoodGuysBadGuys
#      1 2 GoodGuysBadGuys::~GoodGuysBadGuys
#      1 2 GoodGuysBadGuys::Loop
#      1 3 GoodGuysBadGuys::Init
#      2 4 GoodGuysBadGuys::Notify
#      4 3 GoodGuysBadGuys::FillPairs
#      8 3 GoodGuysBadGuys::PrintPossibleValues
#1000000 3 GoodGuysBadGuys::ClearVars
#1000000 3 GoodGuysBadGuys::LoadTree
#1000000 3 GoodGuysBadGuys::RefillVars


if __name__ == "__main__":
    main()
