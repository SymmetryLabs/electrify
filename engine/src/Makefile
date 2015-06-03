CC=g++
CFLAGS=-c -Wall --std=c++11 -fpic

all: *.o

%.o: %.cpp ../include/%.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@