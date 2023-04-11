APP_NAME = main
CC = gcc

CFLAGS = -g -O0

SRC_DIR = src
APP_SOURCES = $(shell find $(SRC_DIR) -name '*.c')

.PHONY: all
all: $(APP_NAME)

$(APP_NAME): $(APP_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(APP_SOURCES)

.PHONY: clean
clean:
	$(RM) $(APP_NAME)
