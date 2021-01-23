CC = gcc
SRC = main.c
OBJ = $(SRC:.c=.o)
LDFLAGS = -L../lib
LDLIBS = -lfpinter -lm
INCDIR= ../lib/

all: calc

calc: $(OBJ) 
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

%.o: %.c
	$(CC) -I$(INCDIR) -c -o $@ $<

clean:
	-rm -f $(OBJ) calc

install: calc
	mkdir -p $(BINDIR)
	cp calc $(BINDIR)

.PHONY: all clean install
