CC=g++
LFLAGS=-shared -o
LIBRARY=lib/libengine.so
OFILES=src/*.o
SRC=src

$(LIBRARY): $(OFILES)
	$(CC) $(LFLAGS) $(LIBRARY) $(OFILES)

src/%.o:
	make -C $(SRC) %.o

clean:
	rm $(SRC)/*.o