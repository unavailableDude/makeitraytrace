SRC_DIR = src
BUILD_DIR = bin/debug
INCLUDE_DIR = include
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
BIN_NAME = raytracer
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib#-Llib/SDL2_ttf
LIBRARY_PATHS_LX = -Llib/SDL2
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g #-Werror
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2#-lSDL2_ttf
LINKER_FLAGS_LX = -lsdl2

OBJECT_DIR = obj
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJECT_DIR)/%.o,$(SRC_FILES))

all: $(BIN_NAME)

$(BIN_NAME): $(OBJECTS)
	$(CC) $(COMPILER_FLAGS) $^ $(LIBRARY_PATHS) $(LINKER_FLAGS) $(INCLUDE_PATHS) -o $(BUILD_DIR)/$(BIN_NAME).exe

# main.o: $(SRC_DIR)/main.cpp
# 	$(CC) $(COMPILER_FLAGS) $^ -c $(LIBRARY_PATHS) $(LINKER_FLAGS) $(INCLUDE_PATHS) -o $(OBJECT_DIR)/$@

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CC) $(COMPILER_FLAGS) $(filter %.cpp,$^) -c $(LIBRARY_PATHS) $(LINKER_FLAGS) $(INCLUDE_PATHS) -o $@

clean:
	rm -f $(BUILD_DIR)/$(BIN_NAME).exe
	rm -f $(OBJECT_DIR)/*.o
	rm -f $(OBJECT_DIR)/*.exe
	rm -f $(OBJECT_DIR)/*.a

run:
	./$(BUILD_DIR)/$(BIN_NAME).exe

print_objects:
	@echo $(OBJECTS)