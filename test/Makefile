LIBDIR := ../lib
HDRDIR := ../include
BINDIR := bin
OBJDIR := obj
TESTDIR := .
DATADIR := data
GRAPHDIR := graphes
SYSDIR := sysdyn
SRCPLOTDIR := tmp
SEARCHDIR := search


SOURCES := $(wildcard $(TESTDIR)/*.c)

OBJECTS := $(SOURCES:%.c=%.o)

LIBRARY := $(wildcard $(LIBDIR)/*.so)

INCLUDES := $(LIBRARY:$(LIBDIR)/%.so=$(HDRDIR)/%.h)



CC := gcc
CFLAGS := -Wall -g -I$(HDRDIR)
LFLAGS := -L$(LIBDIR) -ltrajectoire

TARGET := projetOmar

$(TARGET): $(BINDIR)/$(TARGET)
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../lib
	export LD_LIBRARY_PATH
	$^
#link and compile the main C file that contains main
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
$(OBJECTS):%.o:%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@




PLOTSRC := $(wildcard $(TESTDIR)/$(SRCPLOTDIR)/*.c)
PLOTOBJ:= $(PLOTSRC:%.c=%.o)
PLOT := $(PLOTSRC:$(TESTDIR)/$(SRCPLOTDIR)/%.c=$(TESTDIR)/$(SRCPLOTDIR)/%)

#link and compile all the dynamic system C files, that normally are responsible for generating .dat files for plot
#$(PLOT):$(TESTDIR)/$(SRCPLOTDIR)/%: $(TESTDIR)/$(SRCPLOTDIR)/%.c $(INCLUDES)
#	$(CC) $(CFLAGS) $< $(LFLAGS) -o $@

.PHONY: clean wipe

wipe:
	rm -rf $(TMPDIR)/*

clean:
	rm -rf $(BINDIR)/*
	rm -rf $(DATADIR)/*
	rm -rf $(SYSDIR)/*
	rm -rf $(GRAPHDIR)/*
	rm -rf $(SEARCHDIR)/*
