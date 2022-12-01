EXECUTABLE_NAME = foxGame.out

CC = cc
RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS = -Wall -Werror

ALL_FLAGS = $(RAYLIB_FLAGS) $(CFLAGS)

all:
	$(CC) src/main.c -o build/$(EXECUTABLE_NAME) lib/*.c $(ALL_FLAGS) -I./include