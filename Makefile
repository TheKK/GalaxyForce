 #
 # Author: KK <thumbd03803@gmail.com>
 #
 # File: Makefile
 #

CXX := g++
CXXFLAG = -Wall -std=c++11 -g
#CXXFLAG = -Wall -std=c++11 -g -L/usr/lib32 -m32

SRC_DIR = $(PWD)/src
SRC = $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))

# Include flags
INCLUDE = -I $(PWD)/include
INCLUDE += $(shell pkg-config --cflags sdl2)
INCLUDE += $(shell pkg-config --cflags SDL2_image)
INCLUDE += $(shell pkg-config --cflags SDL2_ttf)
INCLUDE += $(shell pkg-config --cflags lua)
INCLUDE += $(shell pkg-config --cflags openal)
INCLUDE += $(shell pkg-config --cflags alure)

# Libs flags
LIB = $(shell pkg-config --libs sdl2)
LIB += $(shell pkg-config --libs SDL2_image)
LIB += $(shell pkg-config --libs SDL2_ttf)
LIB += $(shell pkg-config --libs lua)
LIB += $(shell pkg-config --libs openal)
LIB += $(shell pkg-config --libs alure)
LIB += -ljsoncpp

# Object files
OUT_DIR= $(PWD)/obj
OBJ := $(addprefix $(OUT_DIR)/, $(notdir $(SRC:.cpp=.o)))

OUT_EXE = ld31

all: $(OUT_EXE)
	@echo "===========[[Everything done!!]]============"

$(OUT_EXE): $(OBJ)
	@echo "    LD    " $(notdir $@)
	@$(CXX) $(addprefix $(OBJ_PATH)/, $(OBJ)) $(CXXFLAG) $(LIB) -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "    CC    " $(notdir $@)
	@$(CXX) -c $< $(CXXFLAG) $(INCLUDE) -o $@

.PHONY: clean
clean:
	@rm -frv $(OUT_DIR)/*.o $(OUT_EXE)
	@echo "===========[[Everything removed!!]]============"
