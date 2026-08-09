# Compiler and flags
CC = gcc
CFLAGS = -O3 -Wall
GNUPLOT = gnuplot

# Directories
SRC_DIR = src
DATA_DIR = data
PLOTS_DIR = plots
SCRIPTS_DIR = scripts

# Targets
TARGET = merge_k_arrays.exe
PLOT_OUT = $(PLOTS_DIR)/merge_k_arrays_plots.png

all: dirs build run plot

dirs:
	@mkdir -p $(DATA_DIR) $(PLOTS_DIR)

build: $(TARGET)

$(TARGET): $(SRC_DIR)/merge_k_arrays.c
	$(CC) $(CFLAGS) $< -o $@

run: $(TARGET) dirs
	./$(TARGET)

plot: $(PLOT_OUT)

$(PLOT_OUT): $(SCRIPTS_DIR)/plot_results.gp $(DATA_DIR)/benchmark_k.dat
	$(GNUPLOT) $(SCRIPTS_DIR)/plot_results.gp

clean:
	rm -f $(TARGET)
	rm -rf $(DATA_DIR)/*.dat $(PLOTS_DIR)/*.png

.PHONY: all dirs build run plot clean
