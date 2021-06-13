SRC=$(wildcard libs/rpi_ws281x/*.c)
FILES=$(wildcard *.cpp)
CC=g++
FLAGS=-Wall -fpermissive -std=c++17 -g
LIBS=-lpthread -lcurl -lcurlpp
EXT=.out
OUT_NAME=info_panel
PATHS=libs/curlpp/include

build: $(SRC)
	$(CC) $(FLAGS) -I $(PATHS) -o $(OUT_NAME)$(EXT) $(FILES) $^ $(LIBS)
