# Makefile for Dictionary Operations Benchmark & Plotting

CC = gcc
CFLAGS = -O2 -Wall -Wextra -Isrc
SRC = src/main.c src/unsorted_array.c src/sorted_array.c src/singly_unsorted.c src/singly_sorted.c src/doubly_unsorted.c src/doubly_sorted.c
TARGET = benchmark

ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    RM = del /f /q
    RMDIR = rmdir /s /q
else
    RM = rm -f
    RMDIR = rm -rf
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

plot: run
	gnuplot scripts/plot_all.gp

clean:
	-$(RM) $(TARGET) *.o
	-$(RMDIR) data plots

.PHONY: all run plot clean
