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
LIBS=-lm
OBJS_DIR=objs/
SRC_DIR=src/
BIN_DIR=bin/

TMP_TEST=".tmp_test"
TMP_RUN=".tmp_run"
PARAM=

SRC_FILES:= $(shell find src/ -type f -name "*.c")
OBJS_LIST_FILES:= $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC_FILES))

$(BIN_DIR)$(EXEC): $(OBJS_LIST_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(PARAM)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c $(HEADER_DIR)/%.h
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(PARAM)

run:
	./clean.sh 0 $(TMP_TEST) $(TMP_RUN)
	make -s
	cd $(BIN_DIR) && ./$(EXEC)

doc:
	doxygen doxyfile_conf || echo "Doxygen is not installed, please install it"

test:
	./clean.sh 1 $(TMP_TEST) $(TMP_RUN)
	make -s PARAM="-D UNIT_TESTS"
	cd $(BIN_DIR) && ./$(EXEC)

clean:
	rm -r $(TMP_TEST) $(TMP_RUN) $(OBJS_DIR) $(BIN_DIR) 2> /dev/null