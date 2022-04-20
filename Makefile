SDIR=src
ODIR=build
CC=gcc
CFLAGS = -lm

_DEPS = utils.h histogram.h grayscale.h steganography.h
DEPS = $(patsubst %,$(SDIR)/%,$(_DEPS))

_OBJ = bmp.o histogram.o grayscale.o steganography.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/bmpParser: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f build/*.o bin/*