CC=g++
CPPFLAGS= -Wall --std=c++11 -fpic
LINKFLAGS=-shared -Wall --std=c++11 -Wl,-undefined -Wl,dynamic_lookup
LIBRARY=../lib/libengine.so
CPPFLAGS += -MD -MP
SRC=$(wildcard *.cpp)

$(LIBRARY): $(SRC:%.cpp=%.o)
	$(CC) $(LINKFLAGS) -o $@ $^

-include $(SRC:%.cpp=%.d)

clean:
	rm -f *.o *.d