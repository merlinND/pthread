COMPILER=gcc
CPPFLAGS=-w -Wall
LINKER=gcc
LINKERFLAGS=

INCPATH=
LIBPATH=
LIBS=

ECHO=@echo
CLEAN=clean

SRCDIR=src
OUTPUTDIR=bin
EXE=PrimeNumbers

FILES=

HEADERS=$(addprefix $(SRCDIR)/,$(FILES))
IMPL=$(HEADERS:.h=.cpp)

OBJ=$(addprefix $(OUTPUTDIR)/,$(FILES:.h=.o))
OBJ+=$(OUTPUTDIR)/main.o

.PHONY: all before $(CLEAN)

all: before $(EXE)

before:
	mkdir -p bin

# Ouput executable
$(EXE): $(OBJ)
	$(ECHO) Linking $(EXE)...
	$(LINKER) $(LINKERFLAGS) $(INCPATH) $(LIBPATH) -o $(OUTPUTDIR)/$(EXE) $(OBJ) $(LIBS)

# Generic rule
$(OUTPUTDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/common.h
	$(ECHO) Compiling $<...
	$(COMPILER) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

# Explicit dependancies


$(CLEAN):
	$(ECHO) Cleaning project.
	rm -f $(OBJ) $(OUTPUTDIR)/$(EXE) core

# Generator
generator: $(SRCDIR)/generator.c
	$(ECHO) Compiling $<...
	$(COMPILER) $(CPPFLAGS) $(INCPATH) -o $(OUTPUTDIR)/$@ $<
