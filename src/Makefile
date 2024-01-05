IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = hashmap.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hashmap.o hashmap_test.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -Wall -Wextra -Werror -g -o $@ $< $(CFLAGS)

hashmap: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ hashmap