# PROJECT PASTEQUE MAKEFILE
# C++ and Computer Graphics Project for IMAC engineering school https://www.ingenieur-imac.fr
# -------------
# by: Pierre Gabory

# Handles compiling the following project and ensure some OS compatibility.






######### PARAMETERS #########

# executable name
APP_BIN = product

# compile
CC = g++
CPPFLAGS = -std=c++11 -Wall -g -Os

# paths
# Source files
SRC_PATH = src

# Header files
INC_PATH := $(addprefix -I,$(shell find ./includes -type d -print))

# .o files
OBJ_PATH = obj

# executable path
BIN_PATH = bin

# local librairies 
LDFLAGS = -I./lib





######### INIT #########

# get source files
SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.cpp')

# get object files
OBJ_FILES = $(subst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o, $(SRC_FILES))






######### OPERATING SYSTEM CHECK #########

# WINDOWS
ifeq ($(OS),Windows_NT)
	CPPFLAGS += -D __MICROSOFT__

# UNIX
else
	UNAME_S := $(shell uname -s)

	# LINUX
	ifeq ($(UNAME_S),Linux)
		CPPFLAGS += -D __LINUX__
		LDFLAGS += -lGL -lGLU -lGLEW -lSDL2 -lm
	endif

	# MACINTOSH
	ifeq ($(UNAME_S),Darwin)
		CPPFLAGS += -D __APPLE__

		# Apple included frameworks
		LDFLAGS +=  -framework OpenGL -framework GLUT -framework Cocoa

		# Imported frameworks and librairies
		LDFLAGS +=  -F/Library/Frameworks -framework SDL2

	endif
endif






######### TASKS #########

# main task
all: $(APP_BIN)


# Linking
$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(INC_PATH) $(CPPFLAGS) $(LDFLAGS)


# Compiling
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p "$(@D)"
	$(CC) -g -c -pthread $< -o $@ $(CPPFLAGS) $(INC_PATH)

# running the app
run:
	$(BIN_PATH)/$(APP_BIN)

# cleaning
clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)

