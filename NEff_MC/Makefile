ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
CXX = g++
CXXFLAGS = -g -Wall $(ROOTCFLAGS) -I.
LD = g++
LDFLAGS = $(ROOTLIBS) -I.

#CXXFLAGS += -I${DOGS_PATH}/DCUtil/ #for AfterMuFlagger
#LDFLAGS += -lDCDBInterface -lDCValidity -lDCRegistry -lDCUtil

.PHONY: all

all: GoodGuysBadGuys.exe

##############
%.exe: %.o 
	$(LD) -o $@ $< $(LDFLAGS)

##############

# default rule for making .o files from .cc or .C files
%.o: %.cc %.hh
	@echo '<< compiling' $< '>>'
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.C %.h
	@echo '<< compiling' $< '>>'
	$(CXX) $(CXXFLAGS) -c -o $@ $<


.PHONY: clean
clean: 
	rm -f ./*.o
	rm -f ./*.so
	rm -f ./*.exe a.out

fixmes:
	grep -HirnI -E 'fixme|warning|guess|fiction|later|for now|(/[/*].*[?!]{2,})' *.cc *.hh *.h *.C