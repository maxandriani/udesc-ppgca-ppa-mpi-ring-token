
CC=mpicc
CFLAGS= -Wall
LDFLAGS= 
SRCDIR=./src
BINDIR=./bin
TARGETS=ring

# Find all C sources
SOURCES := $(wildcard $(SRCDIR)/*.c)
# Generate temporary files on bin
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(filter-out $(SRCDIR)/$(TARGETS).c, $(SOURCES)))

# Main target
build: $(BINDIR) | $(OBJECTS) $(BINDIR)/$(TARGETS)
clean:
	rm -rf ./bin*
run: 
	mpirun --machinefile hosts --mca btl_tcp_if_include 10.20.221.0/24 ./bin/$(TARGETS)

# Geenrate bin dir
$(BINDIR):
	mkdir $(BINDIR)

# Compile each .c source file into object folder bindir/.o
$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGETS): $(SRCDIR)/$(TARGETS).c $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Dependencias
$(SRCDIR)/ring.c: $(BINDIR)/utils.o
$(BINDIR)/utils.o: $(SRCDIR)/utils.c $(SRCDIR)/utils.h