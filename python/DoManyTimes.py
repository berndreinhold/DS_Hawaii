#!/usr/bin/python

import os

#loop through a file catalog and do the same thing on each file in the catalog
#call as 'python DoManyTimes.py'
#dec. 2013

cat_dir = "/home/reinhold/Documents/DS/Studies/FileCatalogs/"
file_cat = "allROOTfiles.cat"
program_dir = "/home/reinhold/Documents/DS/Studies/Erin_S4Det/"

f = open('%s/%s' % (cat_dir, file_cat))
print 'file catalog: %s/%s' % (cat_dir, file_cat)

for line in f:
    print line,
    #os.system("[your program's name] %s" % line)
    os.system("%s/GoodGuysBadGuys.exe %s" % (program_dir,line))
