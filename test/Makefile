LIBDIR := ../lib
HDRDIR := ../include
BINDIR := ../bin
TESTDIR := .
DATADIR := data
GRAPHDIR := graphes
SYSDIR := sysdyn
SRCPLOTDIR := sysdyn
TMPDIR := tmp
SEARCHDIR := search


SOURCES := $(wildcard $(TESTDIR)/*.c)

LIBRARY := $(wildcard $(LIBDIR)/.so)

INCLUDES := $(LIBRARY:$(LIBDIR)/%.so=$(HDRDIR)/%.h)

PLOTSRC := $(wildcard $(TESTDIR)/$(SRCPLOTDIR)/*.c)

$(PLOT) := $(PLOTSRC:$(TESTDIR)/$(SRCPLOTDIR)/%.c=$(TESTDIR)/$(SRCPLOTDIR)/%)

TARGET := projetOmar

CC := gcc

CFLAGS := -Wall -g -I$(HDRDIR)
LFLAGS := -L$(LIBDIR) -l$(LIBRARY)

$(TARGET): $(BINDIR)/$(TARGET)
	./$^
#link and compile the main C file that contains main
$(BINDIR)/$(TARGET): $(SOURCES) $(INCLUDES)
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#link and compile all the dynamic system C files, that normally are responsible for generating .dat files for plot
$(PLOT):$(TESTDIR)/$(SRCPLOTDIR)/%: $(TESTDIR)/$(SRCPLOTDIR)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

.PHONY: clean wipe

wipe:clean
	rm -rf $(TMPDIR)/*

clean:
	mv $(DATADIR)/* $(TMPDIR)
	mv $(SYSDIR)/* $(TMPDIR)
	mv $(GRAPHDIR)/* $(TMPDIR)
	mv $(BINDIR)/* $(TMPDIR)
	mv $(SEARCHDIR)/* $(TMPDIR)
