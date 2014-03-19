# Libs
LIB_SYS = -lm -lpthread

# Compilation Binaries
CC = gcc
CFLAGS = -DDEBUG -g -Wall
LNFLAGS = $(LIB_SYS)

# Tools
TIMER = time
ECHO = @echo

# Exe Name
EXE = PrimeNumbers

# Sources
SRC = main.c primes.c worker.c sequential.c

# Objets
OBJECTS = $(SRC:%.c=bin/%.o)

# Phony targets
.PHONY: clean run time

# Rules
all: bin/$(EXE)

clean:
	rm -rf bin/

bin/$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(LNFLAGS)

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
	$(TIMER) ./bin/$(EXE) -w < ./tmp/numbers.txt;

# Patterns
bin/%.o: src/%.c
	mkdir -p `dirname $@`
	$(CC) -c $(CFLAGS) -o $@ $<
