#include <iostream>
#include "info_panel.hpp"
#include "led_matrix.hpp"

#include "clock.hpp"
#include "font.hpp"
#include "config_loader.hpp"

int main(int argc, char *argv[]){
    LEDMatrix matrix(32, 8, 1);
    matrix.test();
    //ConfigLoader l;
    return 0;
}
