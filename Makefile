COMPILER=gcc
CPPFLAGS=-std=c99 -w -Wall
LINKER=gcc
LINKERFLAGS=

INCPATH=
LIBPATH=
LIBS=-lm

ECHO=@echo
CLEAN=clean

SRCDIR=src
OUTPUTDIR=bin
EXE=PrimeNumbers

FILES=

HEADERS=$(addprefix $(SRCDIR)/,$(FILES))
IMPL=$(HEADERS:.h=.c)

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
$(OUTPUTDIR)/%.o: $(SRCDIR)/%.c
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

# Run
run: $(EXE) generator
	./$(OUTPUTDIR)/generator | ./$(OUTPUTDIR)/$(EXE);
