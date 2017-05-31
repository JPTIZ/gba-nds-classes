OUTPUT := waterfall

ARCH   := -mthumb -mthumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi -fno-exceptions

PREFIX := $(DEVKITARM)/bin/
CXX    := $(PREFIX)arm-none-eabi-g++
OBJCPY := $(PREFIX)arm-none-eabi-objcopy
OBJDIR := build

SOURCEFILES := $(notdir $(wildcard src/*.cpp))
OBJFILES    := $(patsubst %, $(OBJDIR)/%,$(SOURCEFILES:.cpp=.o))


.PHONY:
	make default

default:
	mkdir -p build
	make $(OUTPUT).gba

$(OBJDIR)/%.o: src/%.cpp
	$(CXX) -c $^ -o $@ $(ARCH) -std=c++17 -O2

$(OUTPUT).elf: $(OBJFILES)
	$(CXX) -o $(OUTPUT).elf $(OBJFILES) $(ARCH) -specs=gba.specs

$(OUTPUT).gba: $(OUTPUT).elf
	$(OBJCPY) -O binary $(OUTPUT).elf $(OUTPUT).gba
	gbafix $(OUTPUT).gba

clean:
	rm -f $(OUTPUT).elf $(OUTPUT).gba
	rm -r $(OBJDIR)
