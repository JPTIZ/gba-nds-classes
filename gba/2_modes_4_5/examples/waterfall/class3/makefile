OUTPUT := example

ARCH   := -mthumb -mthumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi -fno-exceptions

CXX    := arm-none-eabi-g++
OBJCPY := arm-none-eabi-objcopy

SOURCEFILES := $(notdir $(wildcard *.cpp))
OBJFILES    := $(SOURCEFILES:.cpp=.o)

.PHONY: $(OUTPUT).gba
default: $(OUTPUT).gba

%.o: %.cpp
	$(CXX) -c $^ -o $@ $(ARCH) -std=c++17 -O2

$(OUTPUT).elf: $(OBJFILES)
	$(CXX) -o $(OUTPUT).elf $(OBJFILES) $(ARCH) -specs=gba.specs

$(OUTPUT).gba: $(OUTPUT).elf
	$(OBJCPY) -O binary $(OUTPUT).elf $(OUTPUT).gba
	gbafix $(OUTPUT).gba

clean:
	rm *.o $(OUTPUT).elf $(OUTPUT).gba
