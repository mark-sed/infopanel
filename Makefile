SRC=$(wildcard libs/rpi_ws281x/*.c)
FILES=clock.cpp config_loader.cpp font.cpp info_panel.cpp ip_exceptions.cpp led_matrix.cpp rest_api.cpp scheduler.cpp 
CC=g++
FLAGS=-Wall -fpermissive -std=c++17 -g
LIBS=-lpthread -lcurl -lcurlpp
EXT=.out
OUT_NAME=infopanel
OUTPUT_WR=stockpanel
PATHS=libs/curlpp/include

build:
	$(CC) $(FLAGS) -I $(PATHS) -o $(OUT_NAME)$(EXT) $(FILES) $(SRC) $(LIBS)

python:
	$(CC) $(FLAGS) -shared -fPIC `python3 -m pybind11 --includes` wrapper.cpp $(FILES) $(SRC) $(LIBS) -o $(OUTPUT_WR)`python3-config --extension-suffix`
