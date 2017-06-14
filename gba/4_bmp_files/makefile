# Config
OUTPUT   := bmp2h

# Directories
SRCDIR   := src
DSTDIR   := dst

# Compiler settings
CXX      := g++
CXXFLAGS :=
CXXSTD   := c++17

# End of config

SRCFILES := $(notdir $(wildcard $(SRCDIR)/*.cpp))
OBJFILES := $(SRCFILES:.cpp=.o)


.PHONY: default

default:
	mkdir -p dst
	make $(OUTPUT)

%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $(DSTDIR)/$@ $^ -std=$(CXXSTD) $(CXXFLAGS)

$(OUTPUT): $(OBJFILES)
	$(CXX) -o $@ $(foreach obj, $^, $(DSTDIR)/$(obj)) -std=$(CXXSTD) $(CXXFLAGS)

clean:
	rm -rf $(DSTDIR)
	rm $(OUTPUT)

run:
	./$(OUTPUT) res/link.h
