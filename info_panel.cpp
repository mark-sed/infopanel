#include <iostream>
#include "info_panel.hpp"
#include "led_matrix.hpp"

#include "clock.hpp"
#include "font.hpp"
#include "config_loader.hpp"
#include "rest_api.hpp"

int main(int argc, char *argv[]){
    LEDMatrix matrix(32, 8, 1);
    ConfigLoader l;
    
    APIStocks s(l);
    s.draw(matrix);
    matrix.render(0);
    
    return 0;
}
