# Executable names:
EXE = shortestpathflight
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o assembler.o helper.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk
