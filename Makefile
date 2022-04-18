SDIR=src
ODIR=build
CC=gcc
CFLAGS = 

_DEPS = utils.h histogram.h
DEPS = $(patsubst %,$(SDIR)/%,$(_DEPS))

_OBJ = bmp.o histogram.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/bmpParser: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f build/*.o bin/*