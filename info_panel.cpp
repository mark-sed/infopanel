#include <iostream>
#include "info_panel.hpp"
#include "led_matrix.hpp"


#include "font.hpp"

int main(int argc, char *argv[]){
    LEDMatrix matrix(32, 8, 4);
    matrix.test();
    return 0;
}
