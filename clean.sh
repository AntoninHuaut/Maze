#!/bin/bash

CLEAN_CMD="make clean"

if [ ! $# -eq 3 ]; then
    exit 0
fi

TMP_TEST=$2
TMP_RUN=$3

# 0 = run
if [ $1 -eq 0 ]; then
    if [ -f $TMP_TEST ]; then
        rm $TMP_TEST 2> /dev/null
        $CLEAN_CMD
    fi
    if [ ! -f $TMP_RUN ]; then
        $CLEAN_CMD
        touch $TMP_RUN
    fi
else # other = test
    if [ -f $TMP_RUN ]; then
        rm $TMP_RUN 2> /dev/null
        $CLEAN_CMD
    fi
    if [ ! -f $TMP_TEST ]; then
        $CLEAN_CMD
        touch $TMP_TEST
    fi
fi