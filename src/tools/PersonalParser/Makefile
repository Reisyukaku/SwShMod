TARGET   := PersonalParse

BUILD    := build
SOURCE	 := src

CXX      := g++
CXXFLAGS := -w -O2 -std=gnu++17 -static-libgcc -static-libstdc++
LDFLAGS  := 

rwildcard = $(foreach d, $(wildcard $1*), $(filter $(subst *, %, $2), $d) $(call rwildcard, $d/, $2))
OBJECTS := $(patsubst $(SOURCE)/%.cpp, $(BUILD)/%.o, $(call rwildcard, $(SOURCE), *.cpp))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BUILD)/%.o: $(SOURCE)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $< $(CXXFLAGS) -o $@

clean:
	@echo cleaning...
	@rm -rf $(BUILD)
