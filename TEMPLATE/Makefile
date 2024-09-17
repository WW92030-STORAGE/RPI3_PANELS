# Based on the Makefile from the original library.

CFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter -I .
CXXFLAGS=$(CFLAGS)
HFILES=header.h
CCFILES=main.cc header.cc
OBJECTS = main.o header.o
BINARIES=main
# Where our library resides. You mostly only need to change the
# RGB_LIB_DISTRIBUTION, this is where the library is checked out.
RGB_LIB_DISTRIBUTION=..
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

# To compile image-example
MAGICK_CXXFLAGS?=$(shell GraphicsMagick++-config --cppflags --cxxflags)
MAGICK_LDFLAGS?=$(shell GraphicsMagick++-config --ldflags --libs)

# This file also serves as a basic tutorial on makefiles
# The syntax for each "rule" is as follows:
# [target] : [prerequisites space separated]
# (\t)	[command]
# (\t)	[command etc.]

# When the makefile is run as "make" the first listed rule is attempted, and if the Make detects a prereq that isn't there it tries to search in other rules for ways to obtain the prereq.

# This first rule which is the default requires all binaries. 
# This means that the makefile will attempt to compile and link all the binaries together.
all : $(BINARIES)
	@echo ALL $(BINARIES)

# This attempts to compile the library for the RGB panels. The FORCE requirement essentially forces this to take place.
# $(MAKE) is a recursive subcall of make. 
$(RGB_LIBRARY): FORCE
	@echo FORCE $(RGB_LIBRARY)
	$(MAKE) -C $(RGB_LIBDIR)

# The only binary that exists right now is main. This binary requires all the .o files (main, header) to be compiled.
# Here we find two predefined variables: $@ is the target (in this case main) and $^ are all the prereqs (in this case $(OBJECTS)).
main : $(OBJECTS)
	@echo MAIN/RGB LIBRARY $^ $@
	$(CXX) $^ -o $@ $(LDFLAGS)

# All this does is compile a single X.cc file into an X.o file
%.o : %.cc
	@echo CC TO O $@ $<
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

# All this does is compile a single X.c file into an X.o file
%.o : %.c
	@echo C TO O $@ $<
	$(CC) -I$(RGB_INCDIR) $(CFLAGS) -c -o $@ $<

# All this does is remove any compiled .o and binaries
clean:
	rm -f $(OBJECTS) $(BINARIES)

FORCE:
.PHONY: FORCE
