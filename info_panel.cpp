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

#define SCROLL_DELAY 90000
// TODO: Read from config
#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8

LEDMatrix matrix(MATRIX_WIDTH, MATRIX_HEIGHT, 1);
ConfigLoader conf;
APIStocks api_stocks(conf);
APICrypto api_crypto(conf);
FontAscii clock_ascii; // Will be std::moved, dont use
FontAscii ascii;
auto sc = SimpleClock(std::move(clock_ascii));

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
    long col = -MATRIX_WIDTH;
    std::wstring text = api_crypto.text();
    matrix.draw_text(text, ascii);
    do{
        matrix.render(col);
        col++;
        usleep(SCROLL_DELAY);
    }while(col < static_cast<long>(matrix.get_text_width()));
}

void crypto_stocks_data(){
    // TODO: Add check for updating data instead of doing it all
    long col = -MATRIX_WIDTH;
    std::wstring text = api_crypto.text() + api_stocks.text();
    matrix.draw_text(text, ascii);
    do{
        matrix.render(col);
        col++;
        usleep(SCROLL_DELAY);
    }while(col < static_cast<long>(matrix.get_text_width()));
}

int main(int argc, char *argv[]){
    Scheduler scheduler;
    // Market open pipeline
    Pipeline p_market_open(is_market_open);
    p_market_open.push(wall_clock);
    // TODO: Add time for how long the task should run
    p_market_open.push(crypto_stocks_data);
    
    // Market closed pipeline
    Pipeline p_market_closed([]() -> bool{return true;});
    p_market_closed.push(wall_clock);
    //p_market_closed.push(crypto_data);
    
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
