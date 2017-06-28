# Config
OUTPUT   := bmp2h

# Directories
SRCDIR   := src
DSTDIR   := dst

# Compiler settings
CXX      := g++
CXXFLAGS := -lstdc++fs
CXXSTD   := c++17

# End of config

SRCFILES := $(notdir $(wildcard $(SRCDIR)/*.cpp))
OBJFILES := $(SRCFILES:.cpp=.o)


.PHONY: default

default:
	@echo
	@echo Compiling...
	@echo
	mkdir -p dst
	make $(OUTPUT)

%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $(DSTDIR)/$@ $^ -std=$(CXXSTD) $(CXXFLAGS)

$(OUTPUT): $(OBJFILES)
	@echo
	@echo Linking...
	@echo
	$(CXX) -o $@ $(foreach obj, $^, $(DSTDIR)/$(obj)) -std=$(CXXSTD) $(CXXFLAGS)

clean:
	rm -rf $(DSTDIR)
	rm $(OUTPUT)

run: default
	@echo
	@echo Running...
	@echo
	./$(OUTPUT) res/link.bmp
