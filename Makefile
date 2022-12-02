EXECUTABLE_NAME = foxGame.out
SOURCE_FILE = src/main.c
LIB_FILES = $(wildcard lib/*.c)

CC = cc
RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS = -Wall -Werror

ALL_FLAGS = $(RAYLIB_FLAGS) $(CFLAGS)

all:
	$(CC) $(SOURCE_FILE) -o build/$(EXECUTABLE_NAME) $(LIB_FILES) $(ALL_FLAGS) -I./include