LIBDIR := /home/fangtooth/ElRifai/lib
HDRDIR := ./include
BINDIR := bin
TESTDIR := ./test
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
CFLAGS :=-Wall -Werror -g -fhosted -funsigned-char -fPIC -pie -Wl,-rpath=$(LIBDIR)
LFLAGS :=  -I$(HDRDIR) -L$(LIBDIR) -ltrajectoire

TARGET := ElRifai

$(TARGET): $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
	rm -f *.o


.PHONY: clean test

test: clean $(BINDIR)/$(TARGET)
	$(BINDIR)/$(TARGET) < std.in > std.out

clean:
	rm -f $(SRCPLOTDIR)/*
	rm -f $(BINDIR)/*
	rm -f $(DATADIR)/*
	rm -f $(SYSDIR)/*
	rm -f $(GRAPHDIR)/*
	rm -f $(SEARCHDIR)/*