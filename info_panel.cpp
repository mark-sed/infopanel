#include <iostream>
#include "led_matrix.hpp"

int main(int argc, char *argv[]){
    LEDMatrix matrix(32, 8, 16);
    matrix.test();
    return 0;
}
