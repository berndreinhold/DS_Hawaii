#!/usr/bin/python

import os

#produce a file catalog
#call as 'python filecatalog.py'
#dec. 2013

indir = "/home/reinhold/Documents/DS/Studies/Erin_S4Det/data/"
outdir = "/home/reinhold/Documents/DS/Studies/FileCatalogs/"
file_cat = "allROOTfiles.cat"
f = open(outdir + file_cat, "w")

i=0 #counter

files=os.listdir(indir)
files.sort() #this way there is always a well defined order

for _file in files:
	#if _file.endswith(".root") and _file.startswith("Cosmics_AA_Stab_Presel"):
	if _file.endswith(".root"):
	        print _file
	        f.write(indir+_file + '\n')
	        i=i+1

print "wrote %d files into catalog: %s (from input dir: %s)" % (i, outdir + file_cat, indir)
f.close()

