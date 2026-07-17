TARGET = draw_graph makehist decayhist

CLASS = func.o
HEADER = makehist.hpp

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CXXFLAGS   = $(ROOTCFLAGS) -Wall -fPIC -O3
CXXLIBS    = $(ROOTLIBS)
CC = g++ 

.PHONY: all
all: $(TARGET)

define DEFF_TARGET_COMP
$(1): $(1).o $(CLASS)
	$$(CC) $$^ $$(CXXLIBS) $$(CXXFLAGS) -o $$@
endef

$(foreach t,$(TARGET),$(eval $(call DEFF_TARGET_COMP,$(t))))

# suffix rule
%.o:%.cpp $(HEADER)
	$(CC) $(CXXFLAGS) -c $<

# clean
.PHONY: clean
clean:
	$(RM) $(TARGET) $(TARGET2) $(TARGET3) *.o

DATAFILE = data/wave0.txt 
DATATAR = data/0702wave.tar.gz
TAR = tar xzvf 

.PHONY: execute
execute: $(TARGET) $(DATAFILE)
	$(foreach t,$(TARGET),./$(t);)

$(DATAFILE): $(DATATAR)
	$(TAR) $(DATATAR) -C $(@D)

# all clean
.PHONY: allclean
allclean: clean
	$(RM) $(dir $(DATAFILE))*.txt
