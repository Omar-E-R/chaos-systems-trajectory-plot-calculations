####################################################################################################################################
#                                           TRAJECTOIRE LIBRARY MakeFile                                                           #
#    TOP LEVEL Makefile to create the Shared Library "trajectoire"                                                                 #
#    and save it in ./lib directory. All source file code are stored in ./src directory                                            #
#    and all object file code are stored in ./obj directory all headers used for this library are                                  #
#    included into one header that is libtrajectoire.h. This library would be linked when compiling the main file in anothe        #
####################################################################################################################################


SRCDIR := src
HDRDIR := include
OBJDIR := obj
LIBDIR := lib
TMPDIR := tmp


SOURCES :=$(wildcard $(SRCDIR)/*.c)

OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES := libtrajectoire.h

TARGET := $(INCLUDES:.h=.so)

CC := gcc

CFLAGS := -Wall -g

#-pie on some systems -fpic or -fPIC
LFLAGS := -pie -I$(HDRDIR)


$(LIBDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDRDIR)/$(INCLUDES)
	$(CC) $(CFLAGS) $(LFLAGS) -c  $< -o $@

.PHONY: clean wipe

wipe:
	rm -rf $(TMPDIR)/*
clean:
	mv -f $(OBJECTS) $(TMPDIR)
	mv -f $(LIBDIR)/$(TARGET) $(TMPDIR)