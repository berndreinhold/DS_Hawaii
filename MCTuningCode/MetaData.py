#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
import string
import shutil
import time


class MetaData:
    """this class is to retrieve file metadata, file location and other info while working at Fermilab. It uses SAM () and good old 'ls' to produce file catalogs.
    SAM data is used to retrieve a file list and run list matching certain criteria (e.g. Krypton runs without drift field). Then for this runlist metadata is queried. Meta data so far is only drift field, extraction field and number of events. This can be used in MC to produce corresponding datasets with 10 times the statistics.
    """

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def __init__(self):

        self._runlist = []
        self._raw_filelist = []
        self._recoed_filelist = []

        self._tempfile_dir = "/ds50/data/user/reinhol1/temp/"
        self._tempfile = "temp_%d.dat" % int(time.time()) #gives the unix timestamp in seconds

        self._tempfile = "%s%s" % (self._tempfile_dir,self._tempfile)

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def __del__(self):
        #print "don't delete for now"
        os.remove("%s" % self._tempfile)

        i=0
        for run in self._dict_run_file.keys():
            if i>2: continue
            #os.remove("%s_run%d" % self._tempfile, run) #from these files meta data is queried.
            i+=1
        
    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
    def setSAMQuery_SourceField(self, source_type, drift_field, extraction_field):
        query = "source.type %s and drift.field %d and extraction.field %d" % (source_type, drift_field, extraction_field)
        self.setSAMQuery_Base(query)

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
    def setSAMQuery_Source(self, source_type):
        query = "source.type %s" % source_type
        self.setSAMQuery_Base(query)

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
    def setSAMQuery_Base(self, query):
        """
        more flexible than the above query.
        fills the output of this query into a tempfile
        """

        #"drift.field 0 and extraction.field 0 and source.type 83Kr"

        if not query == "": query = " and " + query
        fullquery = "samweb -e darkside list-files file_type raw and detector.type TPC and trigger.mode TPC" + query

        self._SAMQuery = fullquery
        self._SAMQuery += " > %s" % self._tempfile
        print self._SAMQuery
        os.system(self._SAMQuery)

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def runlist(self):
        f = open(self._tempfile)
        #fill list of files from tempfile into raw_filelist:
        for line in f:
            self._raw_filelist.append(line.strip())
            
        #sort the list
        self._raw_filelist.sort()


        buf=""
        self._dict_run_file = {}
        for line in self._raw_filelist:
            buf = line.split('_')[1][1:] #ds50_r007337_sr028_20140214T203410.root -> r007337 -> strip the r
            #print int(buf)
            self._dict_run_file[int(buf)]=line #store exactly one filename per run to retrieve metadata in getMetaData

        #print my_dict.keys()
        self._runlist=list(self._dict_run_file.keys())
        print self._runlist

    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    def getMetaData(self):
        #requires dictionary of run to filename
        i=0
        self._dict_run_metadata = {}
        for run,v in self._dict_run_file.iteritems(): #https://docs.python.org/2/tutorial/datastructures.html
            if i>2: continue
            fullquery = "samweb -e darkside get-metadata %s > %s_run_%d" % (v, self._tempfile, run)
            #print run, fullquery
            os.system(fullquery)
            f=open("%s_run_%d" % (self._tempfile,run)) #contains the meta data
            for line in f:
                print line
                if not line.find("Last Event")==-1: print line #last event in the last file should give the proper number of events
                elif not line.find("Event Count")==-1: print line
                elif not line.find("Event Count")==-1: print line
                #elif :

            f.close()

            #os.system(fullquery)
            #print run, self._dict_run_file[run], fullquery
            i += 1

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    x = MetaData()
    #x.setSAMQuery_SourceField("83Kr", 0, 0);
    x.setSAMQuery_Source("83Kr");
    x.runlist()
    x.getMetaData()


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()
