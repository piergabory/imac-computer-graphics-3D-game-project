# PROJECT PASTEQUE MAKEFILE
# C++ and Computer Graphics Project for IMAC engineering school https://www.ingenieur-imac.fr
# -------------
# by: Pierre Gabory

# Handles compiling the following project and ensure some OS compatibility.


######### PARAMETERS #########

# executable name
APP_BIN = product

# compile flags
CPPFLAGS = -Wall -g -Os
LDFLAGS =

# paths
# Source files
SRC_PATH = src

# Header files
INC_PATH = -I includes

# .o files
OBJ_PATH = obj

# executable path
BIN_PATH = bin

# librairies path
LIB_PATH = lib



######### INIT #########

# get source files
SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.cpp')

# get object files
OBJ_FILES = $(subst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o, $(SRC_FILES))





######### OPERATING SYSTEM CHECK #########

# WINDOWS
ifeq ($(OS),Windows_NT)
	CC = g++
	CPPFLAGS += -D Windows

# UNIX
else
	UNAME_S := $(shell uname -s)

	# LINUX
	ifeq ($(UNAME_S),Linux)
		CC = g++
		CPPFLAGS += -D Linux
	endif

	# MACINTOSH
	ifeq ($(UNAME_S),Darwin)
		CC = g++
		CPPFLAGS += -D MacOS
	endif
endif



######### TASKS #########

# main task
all: $(APP_BIN)


# Linking
$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(LDFLAGS)


# Compiling
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p "$(@D)"
	$(CC) -g -c -pthread $< -o $@ $(CPPFLAGS) $(INC_PATH)


# cleaning
clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)

