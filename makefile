# ENSICAEN
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex
# 
# This file is owned by ENSICAEN students. No portion of this
# document may be reproduced, copied or revised without written
# permission of the authors.
# @author Antonin Huaut <antonin.huaut@ecole.ensicaen.fr>
# @version 1.0.0 - 2020-09-30
# 
# \file makefile
# \brief Generate project binary executable
# 
CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -std=c99
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