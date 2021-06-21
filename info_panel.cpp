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
ConfigLoader conf;
APIStocks api_stocks(conf);
APICrypto api_crypto(conf);
FontAscii ascii;
auto sc = SimpleClock(std::move(ascii));

bool is_market_open(){
    return api_stocks.is_active();
}

void wall_clock() {
    sc.draw(matrix);
    int pos = -16+matrix.get_text_width()/2;
    matrix.render(pos);
    usleep(sc.delay);
}

void crypto_data(){

}

void crypto_market_data(){
    // TODO: Add check for updating data instead of doing it all
    // FIXME: Does not render (no leds are on)
    APIStocks stocks(conf);
    APICrypto crypto(conf);
    long col = 0;
    std::wstring text = crypto.text() + stocks.text();
    matrix.draw_text(text, font);
    do{
        matrix.render(col);
        col++;
        usleep(90000);
    }while(col < static_cast<long>(matrix.get_text_width()));
}

int main(int argc, char *argv[]){
    Scheduler scheduler;
    // Market open pipeline
    Pipeline p_market_open(is_market_open);
    p_market_open.push(wall_clock);
    p_market_open.push(crypto_market_data);
    
    // Market closed pipeline
    Pipeline p_market_closed([]() -> bool{return true;});
    p_market_closed.push(wall_clock);
    
    // Scheduler
    scheduler.push(p_market_open);
    scheduler.push(p_market_closed);

    // Main loop
    // Just execute scheduler
    while(true){
        scheduler.execute();
    }

    return 0;
}
