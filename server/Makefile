COMPILER=g++
FLAGS=-Wall -pedantic -std=c++17 -g
OUTPUT=stockpanel
SOURCES=
LIBS=

python:
	$(COMPILER) $(FLAGS) -shared -fPIC `python3 -m pybind11 --includes` $(SOURCES) wrapper.cpp -o $(OUTPUT)`python3-config --extension-suffix`

build:
	$(COMPILER) $(FLAGS) -o $(OUTPUT) $(SOURCES) main.cpp $(LIBS)
