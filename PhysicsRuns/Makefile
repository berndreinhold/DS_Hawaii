TARGET = analysis_physicsruns
#DEP=$(TARGET:.out=.d)
SRCS = $(TARGET).C
#OBJS = $(addsuffix .o, $(notdir $(basename $(SRCS))))
OBJS = $(TARGET).o
DICTNAME = DarkArtDict
INCDIR =  /ds50/app/user/${USER}/work/darkart/analysis/

ROOTCFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS   = $(shell $(ROOTSYS)/bin/root-config --libs) -lProof -lHistPainter #-lMemStat
#ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)
CXXFLAGS   =  -I${INCDIR} $(ROOTCFLAGS) -Wall -fPIC -g #-pthread 
CXXLIBS    = $(ROOTLIBS)
CC = g++ 


all: $(TARGET) 

#%: %.o: leads to an error because of the second ':':  *** mixed implicit and static pattern rules.  Stop.
%: %.o $(INCDIR)$(DICTNAME).so
	echo $(OBJS)
	$(CC) $(CXXFLAGS) $(CXXLIBS) -L$(INCDIR) $(INCDIR)$(DICTNAME).so $(INCDIR)xylocator/xylocator.C $(INCDIR)xylocator/xy_pmtdata.C $< -o $@.exe

$(OBJS): $(SRCS)
	@echo "compile $(OBJS)"
	$(CC) $(CXXFLAGS) -c $^


$(INCDIR)$(DICTNAME).so: 
	cd $(INCDIR) && make 


clean:
	rm  -f $(OBJS)
	rm  -f $(TARGET)

