TARGET = xytree_generator

SRCS = $(TARGET).C
DICTNAME = DarkArtDict
DARKARTDIR = ../darkart/Products
DARKARTHEADERS = $(DARKARTDIR)/EventData.hh
OBJS = $(addsuffix .o, $(notdir $(basename $(SRCS))))
ROOTCFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS   = $(shell $(ROOTSYS)/bin/root-config --libs) -lProof -lHistPainter -lMinuit #-lMemStat
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)
ROOTCINT = $(ROOTSYS)/bin/rootcint
CXXFLAGS   = $(ROOTCFLAGS) -Wall -fPIC -g #-pthread 
CXXLIBS    = $(ROOTLIBS)
CC = g++ 


all: $(DICTNAME).so $(TARGET) 
#all: $(TARGET)

%: %.o
	$(CC) $(CXXFLAGS) $(CXXLIBS) $(DICTNAME).so $< -o $@
$(OBJS): $(SRCS)
	$(CC) $(CXXFLAGS) -c $^

XYReconstructor.o: XYReconstructor/XYReconstructor.cxx
	$(CC) $(CXXFLAGS) -c $^

XYRecHelper.o: XYReconstructor/XYRecHelper.cxx
	$(CC) $(CXXFLAGS) -c $^

$(DICTNAME).cxx: 
	$(ROOTCINT) -f $@ -c -p $(SRCS) XYReconstructor/XYReconstructor.h XYReconstructor/XYRecHelper.h $(DARKARTHEADERS) LinkDef.h

$(DICTNAME).so: $(DICTNAME).cxx XYReconstructor.o XYRecHelper.o
	$(CC) -shared -o $@ $(ROOTLDFLAGS) $(CXXFLAGS) $(CXXLIBS) -I$(ROOTSYS)/include $^

clean:
	rm  -r $(OBJS) $(DEP) $(SOBJS)  $(DICTNAME).so $(DICTNAME).cxx $(DICTNAME).h XYReconstructor.o XYRecHelper.o

