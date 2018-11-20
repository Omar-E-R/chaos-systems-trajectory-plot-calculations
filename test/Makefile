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


#link and compile the main C file that contains main

CC := gcc
CFLAGS := -Wall -g -fPIC -I$(HDRDIR)
LFLAGS := -L$(LIBDIR) -ltrajectoire

TARGET := ElRifai

$(TARGET): $(BINDIR)/$(TARGET)
	./scripts/start.sh
	rm -f *.o
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
$(OBJECTS): %.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@


#link and compile all the TEMPORARY SRC FILES, that normally are responsible for generating .dat files for plot


PLOTSRC := $(wildcard $(TESTDIR)/$(SRCPLOTDIR)/*.c)
PLOTOBJ := $(PLOTSRC:%.c=%.o)
PLOT := $(PLOTSRC:$(TESTDIR)/$(SRCPLOTDIR)/%.c=$(TESTDIR)/$(BINDIR)/%)

plot: $(PLOT)
	$(PLOT)
	rm -f $(PLOT)
	rm -f $(SRCPLOTDIR)/*
$(PLOT):$(TESTDIR)/$(BINDIR)/%: $(PLOTOBJ)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@
$(PLOTOBJ): %.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean test
test:
	$(BINDIR)/$(TARGET) < std.in > std.out

clean:
	rm -f $(PLOT)
	rm -f $(SRCPLOTDIR)/*
	rm -f $(BINDIR)/*
	rm -f $(DATADIR)/*
	rm -f $(SYSDIR)/*
	rm -f $(GRAPHDIR)/*
	rm -f $(SEARCHDIR)/*