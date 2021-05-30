SRC=$(wildcard libs/rpi_ws281x/*.c)
FILES=$(wildcard *.cpp)
CC=g++
FLAGS=-Wall -fpermissive -std=c++17 -g
LIBS=-lm
EXT=.out
OUT_NAME=info_panel

build: $(SRC)
	$(CC) $(FLAGS) -o $(OUT_NAME)$(EXT) $(FILES) $^ $(LIBS)
