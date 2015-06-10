CC=g++
CPPFLAGS= -Wall --std=c++11 -fpic -I../libs/jsoncpp
LINKFLAGS=-shared -Wall --std=c++11 -Wl,-undefined -Wl,dynamic_lookup
LIBRARY=../lib/libengine.so
CPPFLAGS += -MD -MP
SRC=$(wildcard *.cpp)
LIBS =../libs/jsoncpp/jsoncpp.o

$(LIBRARY): $(SRC:%.cpp=%.o) $(LIBS)
	$(CC) $(LINKFLAGS) -o $@ $^

-include $(SRC:%.cpp=%.d)

clean:
	rm -f *.o *.d