# Makefile for InfoPanel application
# This constains 2 targets:
#    build  Which builds the application to run without the REST API server
#    rest   Which builds the application to run with REST API server
#
# Use: make build
#      make rest
#
# Author: Marek Sedlacek
#

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

rest:
	$(CC) $(FLAGS) -shared -fPIC `python3 -m pybind11 --includes` wrapper.cpp $(FILES) $(SRC) $(LIBS) -o $(OUTPUT_WR)`python3-config --extension-suffix`
