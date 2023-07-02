SHELL=/bin/bash

GXX = g++
OXX = o
CXX = cc
HXX = h

ROOTFLGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --glibs)

FLGS = -I. $(ROOTFLGS) -I$(ONLINE_MAIN)/include -I$(OFFLINE_MAIN)/include
LIBS = -Wl,--no-as-needed  -L$(ONLINE_MAIN)/lib -L$(OFFLINE_MAIN)/lib -lpmonitor -lEvent -lNoRootEvent -lmessage      $(ROOTLIBS) -fPIC

TRGT = main.exe
OBJS = main.$(OXX) decoder.$(OXX)

$(TRGT) : $(OBJS)
	$(GXX) $(FLGS) -o $@ $^ $(LIBS)

%.$(OXX) : %.$(CXX)
	$(GXX) $(FLGS) -c $< -o $@ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(TRGT) $(OBJS) $(S_OBJS)
