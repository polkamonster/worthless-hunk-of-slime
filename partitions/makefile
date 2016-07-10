CC=g++
CXXFLAGS=-c -std=c++11 -O3 -I ~/boost_1_55_0 -Wall -Wno-unused-local-typedefs
LDFLAGS=
SOURCES=src/partitions.cpp src/partitions_main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
PROG=partition

all: $(SOURCES) $(PROG)

$(PROG): $(OBJECTS); $(CC) $(LDFLAGS) $(OBJECTS) -o $@
    
.cpp.o:; $(CC) $(CXXFLAGS) $< -o $@

clean:; rm -f $(PROG).exe src/*.o