TARGET = draw_graph

SRCS = $(TARGET).cpp
OBJS = $(TARGET).o

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CXXFLAGS   = $(ROOTCFLAGS) -Wall -fPIC
CXXLIBS    = $(ROOTLIBS)
CC = g++ 

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CXXLIBS) $(CXXFLAGS) -o $@

# suffix rule
.cc.o:
	$(CC) $(CXXFLAGS) -c $<

# clean
clean:
	rm -f $(TARGET) $(OBJS) 0514_cs.txt

execute: 0514_cs.txt $(TARGET)
	./$(TARGET)

0514_cs.txt:
	tar xJvf 0514_cs.tar.xz
