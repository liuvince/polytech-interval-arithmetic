CC = gcc
SRC = conversion.c operation.c newton.c matrice.c function.c
OBJ = $(SRC:.c=.o)
LDLIBS = -lm

all: libfpinter.a

libfpinter.a: $(OBJ)
	ar cru $@ $(OBJ)
	ranlib $@

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	-rm -f $(OBJ) libfpinter.a

.PHONY: all clean
