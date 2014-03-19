# Libs
LIB_SYS = -lm -lpthread

# Compilation Binaries
CC = gcc
CFLAGS = -DDEBUG -g -Wall
LNFLAGS = $(LIB_SYS)

# Exe Name
EXE = PrimeNumbers

# Sources
SRC = main.c primes.c worker.c

# Objets
OBJECTS = $(SRC:%.c=build/%.o)

# Phony targets
.PHONY: clean run

# Rules
all: bin/$(EXE)

clean:
	rm -rf build/

bin/$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(LNFLAGS)

# Generator
bin/generator: src/generator.c
	echo Compiling $<...
	$(CC) $(CFLAGS) $(LIB_SYS) -o $@ $<

# Run
run: bin/$(EXE) bin/generator
	./bin/generator | ./bin/$(EXE);

# Run with timer
time: bin/$(EXE) bin/generator
	$(TIMER) ./bin/generator | ./bin/$(EXE);

# Patterns
build/%.o: src/%.c
	mkdir -p `dirname $@`
	$(CC) -c $(CFLAGS) -o $@ $<
