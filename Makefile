CXX ?= g++
CFLAGS = -O3 -std=c++14 -Wall -Wfatal-errors
RM ?= rm -f

PROGS = jul

all: $(PROGS)

$(PROGS): % : %.cpp lodepng.o
	$(CXX) $(CFLAGS) -o $@ $< lodepng.o

lodepng.o: lodepng.cpp lodepng.h
	$(CXX) $(CFLAGS) -c -o lodepng.o lodepng.cpp

clean:
	$(RM) $(PROGS) lodepng.o
