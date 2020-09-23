CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic
EXEC=main
HEADER_DIR=header/
OBJS_DIR=objs/
SRC_DIR=src/
BIN_DIR=bin/

SRC_FILES:= $(shell find src/ -type f -name "*.c")
OBJS_LIST_FILES:= $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC_FILES))

$(BIN_DIR)$(EXEC): $(OBJS_LIST_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)%.o: $(SRC_DIR)%.c $(HEADER_DIR)/%.h
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	make -s
	cd $(BIN_DIR) && ./$(EXEC)

clean:
	rm -r $(OBJS_DIR)
	rm -r $(BIN_DIR)