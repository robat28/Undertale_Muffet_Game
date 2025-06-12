########################################################################
#  Project & build settings
########################################################################
TARGET := Muffet_Game
OUT := bin/$(TARGET)
BUILDDIR := bin/build
SFMLPATH ?=

# ----- toolchain & flags ----------------------------------------------
CXX := g++
CPPFLAGS ?= -I./include 
CXXFLAGS ?= -MMD -MP -Wall -pedantic -O2 -std=c++17 
LDFLAGS ?= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

ifneq ($(SFMLPATH),)
CPPFLAGS += -I$(SFMLPATH)/include
LDFLAGS := -L$(SFMLPATH)/lib $(LDFLAGS)
endif	

# ----- file lists ------------------------------------------------------
SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp,$(BUILDDIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

########################################################################
#  Build rules
########################################################################
all: $(OUT)

# ----- link ------------------------------------------------------------
$(OUT): $(OBJ) | bin
	$(CXX) $(OBJ) $(LDFLAGS) -o "$@"

# ----- compile ---------------------------------------------------------
$(BUILDDIR)/%.o: src/%.cpp | $(BUILDDIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c "$<" -o "$@"

# ----- on-demand directories -------------------------------------------
bin $(BUILDDIR):
	mkdir -p $@

########################################################################
#  House-keeping
########################################################################
clean: 
	rm -rf bin

.PHONY: all clean

# ----- include auto-generated header dependency files (ignore if missing)
-include $(DEP)
