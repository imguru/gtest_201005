#!/bin/sh
g++ $1 -I. -lgtest -L. -pthread -DGTEST_LEAK_TEST
