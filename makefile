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
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99
EXEC=main
EXEC_TEST=$(EXEC)_test
HEADER_DIR=header/
LIBS=-lm
OBJS_DIR=objs/
SRC_DIR=src/
BIN_DIR=bin/

SRC_FILES:= $(shell find src/ -type f -name "*.c")
OBJS_LIST_FILES:= $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC_FILES))

.PHONY: run doc test clean

$(BIN_DIR)$(EXEC): $(OBJS_LIST_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(PARAM)

$(BIN_DIR)$(EXEC_TEST): $(OBJS_LIST_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(PARAM)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c $(HEADER_DIR)/%.h
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(PARAM)

run:
	make clean_main
	make -s $(BIN_DIR)$(EXEC)
	cd $(BIN_DIR) && ./$(EXEC)

doc:
	doxygen doxyfile_conf || echo "Doxygen is not installed, please install it"

test:
	make clean_main
	make -s $(BIN_DIR)$(EXEC_TEST) PARAM="-D UNIT_TESTS"
	cd $(BIN_DIR) && ./$(EXEC_TEST)

clean_main:
	rm -r $(OBJS_DIR)main.o 2> /dev/null

clean:
	rm -r $(OBJS_DIR) $(BIN_DIR) 2> /dev/null