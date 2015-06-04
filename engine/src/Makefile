CC=g++
CPPFLAGS= -Wall --std=c++11 -fpic
LFLAGS=-shared -Wall --std=c++11
LIBRARY=../lib/libengine.so
CPPFLAGS += -MD -MP
SRC=$(wildcard *.cpp)

$(LIBRARY): $(SRC:%.cpp=%.o)
	$(CC) $(LFLAGS) -o $@ $^

-include $(SRC:%.cpp=%.d)

clean:
	rm -f *.o *.d