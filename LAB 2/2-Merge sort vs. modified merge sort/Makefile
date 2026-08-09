# Makefile for Merge Sort vs Modified 3-Way Merge Sort

CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11
TARGET = merge_compare
SRC = main.c

ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    EXT = .exe
else
    RM = rm -f
    EXT =
endif

all: $(TARGET)$(EXT)

$(TARGET)$(EXT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)$(EXT)

run: $(TARGET)$(EXT)
	./$(TARGET)$(EXT)

plot:
	gnuplot -p plot.gp

clean:
	$(RM) $(TARGET)$(EXT) benchmark_results.dat runtime_comparison.png

.PHONY: all run plot clean
