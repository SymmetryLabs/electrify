CC=g++
LFLAGS=-shared -o
LIBRARY=lib/libengine.so
OFILES=src/*.o
SRC=src

all:
	make -C $(SRC) shared
	$(CC) $(LFLAGS) $(LIBRARY) $(OFILES)

clean:
	rm $(SRC)/*.o
    