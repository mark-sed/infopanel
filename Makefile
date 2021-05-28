SRC=$(wildcard libs/rpi_ws281x/*.c)
FILES=info_panel.cpp led_matrix.cpp
CC=g++
FLAGS=-Wall -fpermissive -std=c++17 -g
LIBS=-lm

build: $(SRC)
	$(CC) $(FLAGS) -o info_panel $(FILES) $^ $(LIBS)
