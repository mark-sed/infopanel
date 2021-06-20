#include <iostream>
#include <ctime>
#include <unistd.h>
#include "info_panel.hpp"
#include "led_matrix.hpp"
#include "clock.hpp"
#include "font.hpp"
#include "config_loader.hpp"
#include "rest_api.hpp"
#include "scheduler.hpp"

LEDMatrix matrix(32, 8, 1);
ConfigLoader l;
APIStocks api_stocks(l);
APICrypto api_crypto(l);

bool is_market_open(){
    return api_stocks.is_active();
}

void wall_clock() {
    FontAscii ascii;
    auto sc = SimpleClock(std::move(ascii));
    int pos = -16+matrix.get_text_width()/2;
    while(true){
        sc.draw(matrix);
        matrix.render(pos);
        usleep(10*1000*1000);
    }
}

int main(int argc, char *argv[]){
    Scheduler scheduler;
    // Market open pipeline
    Pipeline p_market_open(is_market_open);
    p_market_open.push(wall_clock);
    
    // Market closed pipeline
    Pipeline p_market_closed([]() -> bool{return true;});
    p_market_closed.push(wall_clock);
    
    // Scheduler
    scheduler.push(p_market_open);
    scheduler.push(p_market_closed);
    scheduler.execute();

    return 0;
}
