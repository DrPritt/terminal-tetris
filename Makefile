# Directories
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

# Compiler settings
CC := g++
CFLAGS := -std=c++20 -g -Wpedantic # -Wall -Werror
CPPFLAGS := -I $(INC_DIR)  
LDLIBS := -lm  -lncurses
VALGRIND_FLAGS := -s --leak-check=full --show-leak-kinds=all --track-origins=yes

TARGET := main

OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))

all: $(TARGET)
	@ echo "Compiling complete!"
	@ echo
	@ ./$(TARGET)

valrun:
	@ echo "Running program with valgrind!"
	@ echo
	@ valgrind $(VALGRIND_FLAGS) ./$(TARGET)

run:
	@ echo "Running program!"
	@ echo
	@ ./$(TARGET)

clean:
	@ echo "Cleaning up..."
	@ rm -f $(OBJ_DIR)/* ./$(TARGET)

$(TARGET): $(OBJS)
	@ echo
	@ echo "Compiling object files..."
	@ $(CC) $(OBJS) -o $@ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@ echo "Compiling $< -> $@"
	@ $(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
