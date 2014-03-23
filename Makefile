# Libs
LIB_SYS = -lm -lpthread
LIB_USR = -Ilib

# Compilation Binaries
CC = gcc
CFLAGS = -DDEBUG -g -Wall -O3
LNFLAGS = $(LIB_SYS) $(LIB_USR)

# Tools
TIMER = time
ECHO = @echo

# Exe Name
EXE = PrimeNumbers

# Sources
SRC = main.c primes.c worker.c sequential.c memoized.c cache.c

# Objets
OBJECTS = $(SRC:%.c=bin/%.o) bin/hashmap.o

# Phony targets
.PHONY: clean run time

# Rules
all: bin/generator bin/$(EXE) bin/hashmap.o

clean:
	rm -rf bin/

bin/$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(LNFLAGS)

# Libraries to compile
bin/hashmap.o: lib/hashmap.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Generator
bin/generator: src/generator.c
	$(ECHO) Compiling $<...
	$(CC) $(CFLAGS) $(LIB_SYS) -o $@ $<

# Run
run: bin/$(EXE) bin/generator
	./bin/generator | ./bin/$(EXE);

# Run with timer
time: bin/$(EXE) bin/generator
	mkdir -p tmp
	./bin/generator > ./tmp/numbers.txt
	$(ECHO)
	$(ECHO) "------> Sequencial Run"
	$(TIMER) ./bin/$(EXE) -s < ./tmp/numbers.txt;
	$(ECHO)
	$(ECHO) "------> Lazy Run"
	$(TIMER) ./bin/$(EXE) -l < ./tmp/numbers.txt;
	$(ECHO)
	$(ECHO) "------> Worker Run"
	$(TIMER) ./bin/$(EXE) -w 4 < ./tmp/numbers.txt;
	$(ECHO)
	$(ECHO) "------> Memoized Run"
	$(TIMER) ./bin/$(EXE) -m < ./tmp/numbers.txt;

# Patterns
bin/%.o: src/%.c
	mkdir -p `dirname $@`
	$(CC) -c $(CFLAGS) $(LIB_USR) -o $@ $<
