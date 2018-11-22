####################################################################################################################################
#                                           TRAJECTOIRE LIBRARY MakeFile                                                           #
#    TOP LEVEL Makefile to create the Shared Library "trajectoire"                                                                 #
#    and save it in ./lib directory. All source file code are stored in ./src directory                                            #
#    and all object file code are stored in ./obj directory all headers used for this library are                                  #
#    included into one header that is libtrajectoire.h. This library would be linked when compiling the main file in anothe        #
####################################################################################################################################



SRCDIR := src
HDRDIR := include
OBJDIR := tmp
LIBDIR := lib
TMPDIR := $(OBJDIR)


SOURCES :=$(wildcard $(SRCDIR)/*.c)

OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES := libtrajectoire.h

TARGET := $(INCLUDES:.h=.so)

CC := gcc

CFLAGS := -Wall -Werror -ggdb -funsigned-char

LFLAGS :=-I$(HDRDIR) -fPIC



all: $(LIBDIR)/$(TARGET)
	rm -f $(TMPDIR)/*


$(LIBDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) -pie $^ -o $@ -Wl,-E


$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDRDIR)/$(INCLUDES)
	$(CC) $(CFLAGS) $(LFLAGS) -c  $< -o $@ -DROOT=\"$$PWD\"


#link and compile all the TEMPORARY SRC FILES, that normally are responsible for generating .dat files for plot


PLOTSRC := $(wildcard $(TMPDIR)/*.c)



PLOT := $(PLOTSRC:$(TMPDIR)/%.c=$(TMPDIR)/%)

plot: $(PLOT)
	$^
	rm -f $(PLOT)
	rm -f $(TMPDIR)/*

$(PLOT):$(TMPDIR)/%: $(PLOTSRC)
	$(CC) $(CFLAGS) -I$(HDRDIR) -L$(LIBDIR) -ltrajectoire -Wl,-rpath=$(LIBDIR) $^ -o $@

.PHONY: clean

clean:
	rm -f $(LIBDIR)/$(TARGET)
	rm -f ./data/*.*