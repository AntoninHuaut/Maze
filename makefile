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
CFLAGS=-Wall -Wextra -Werror
CPPFLAGS=-I$(HEADER_DIR)
EXEC=main
EXEC_TEST=$(EXEC)_test
HEADER_DIR=header/
LDFLAGS=-lm
OBJS_DIR=objs/
SRC_DIR=src/
MAIN_DIR=main/
BIN_DIR=bin/

SRC_FILES:= $(shell find src/ -type f -name "*.c")
OBJS_LIST_FILES:= $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC_FILES))

.PHONY: run doc test clean

$(BIN_DIR)$(EXEC): $(OBJS_DIR)main.o $(OBJS_LIST_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)$(EXEC_TEST): $(OBJS_DIR)main_test.o $(OBJS_LIST_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

#

$(OBJS_DIR)main.o: $(MAIN_DIR)main.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

$(OBJS_DIR)main_test.o: $(MAIN_DIR)main_test.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

run:
	make -s $(BIN_DIR)$(EXEC)
	cd $(BIN_DIR) && ./$(EXEC)

doc:
	doxygen doxyfile_conf || echo "Doxygen is not installed, please install it"

test:
	make -s $(BIN_DIR)$(EXEC_TEST)
	cd $(BIN_DIR) && ./$(EXEC_TEST)

clean:
	rm -rf $(OBJS_DIR) $(BIN_DIR)