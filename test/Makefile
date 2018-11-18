LIBDIR := ../lib
HDRDIR := ../include
BINDIR := bin
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
	#clear
#link and compile the main C file that contains main
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
$(OBJECTS): %.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@




PLOTSRC := $(wildcard $(TESTDIR)/$(SRCPLOTDIR)/*.c)
PLOTOBJ := $(PLOTSRC:%.c=%.o)
PLOT := $(PLOTSRC:$(TESTDIR)/$(SRCPLOTDIR)/%.c=$(TESTDIR)/$(BINDIR)/%)

#link and compile all the dynamic system C files, that normally are responsible for generating .dat files for plot
plot: $(PLOT)
$(PLOT):$(TESTDIR)/$(BINDIR)/%: $(PLOTOBJ)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@
	$@
$(PLOTOBJ): %.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

.PHONY: clean

clean:
	rm -f $(BINDIR)/*
	rm -f *.o
	rm -f $(DATADIR)/*
	rm -f $(SYSDIR)/*
	rm -f $(GRAPHDIR)/*
	rm -f $(SEARCHDIR)/*
	rm -f $(SRCPLOTDIR)/*
