TARGET = draw_graph
TARGET2 = makehist
TARGET3 = decayhist

SRCS = $(TARGET:%=%.cpp)
OBJS = $(TARGET:%=%.o) func.o
OBJS2 = $(TARGET2:%=%.o) func.o
OBJS3 = $(TARGET3:%=%.o) func.o

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CXXFLAGS   = $(ROOTCFLAGS) -Wall -fPIC
CXXLIBS    = $(ROOTLIBS)
CC = g++ 

all: $(TARGET) $(TARGET2) $(TARGET3)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CXXLIBS) $(CXXFLAGS) -o $@

$(TARGET2): $(OBJS2)
	$(CC) $(OBJS2) $(CXXLIBS) $(CXXFLAGS) -o $@

$(TARGET3): $(OBJS3)
	$(CC) $(OBJS3) $(CXXLIBS) $(CXXFLAGS) -o $@

# suffix rule
.cc.o:
	$(CC) $(CXXFLAGS) -c $<

# clean
clean:
	rm -f $(TARGET) $(OBJS) $(TARGET2) $(OBJS2)

execute: data/muondacay0.txt $(TARGET)
	./$(TARGET)

data/muondacay0.txt:
	tar xzvf muondecay.tar.gz
