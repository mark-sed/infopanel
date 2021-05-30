#include <iostream>
#include "info_panel.hpp"
#include "led_matrix.hpp"

#include "clock.hpp"
#include "font.hpp"

int main(int argc, char *argv[]){
    LEDMatrix matrix(32, 8, 1);
    matrix.test();
    return 0;
}
