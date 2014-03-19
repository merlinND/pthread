COMPILER=@gcc
CPPFLAGS=-std=c99 -w -Wall
LINKER=@gcc
LINKERFLAGS=

INCPATH=
LIBPATH=
LIBS=-lm -lpthread

ECHO=@echo
TIMER=@time
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

all: before $(OUTPUTDIR)/$(EXE)

before:
	mkdir -p bin

# Ouput executable
$(OUTPUTDIR)/$(EXE): $(OBJ)
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
$(OUTPUTDIR)/generator: $(SRCDIR)/generator.c
	$(ECHO) Compiling $<...
	$(COMPILER) $(CPPFLAGS) $(INCPATH) -o $(OUTPUTDIR)/$@ $<

# Run
run: $(EXE) generator
	./$(OUTPUTDIR)/generator | ./$(OUTPUTDIR)/$(EXE);

# Run with timer
time: $(EXE) generator
	$(TIMER) ./$(OUTPUTDIR)/generator | ./$(OUTPUTDIR)/$(EXE);
