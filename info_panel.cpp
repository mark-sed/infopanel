/**
 * @file info_panel.cpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief Entry point.
 * 
 * Entry point to the application containing initializations and
 * control functions for info panel behavior.
 */

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include "info_panel.hpp"
#include "led_matrix.hpp"
#include "clock.hpp"
#include "font.hpp"
#include "config_loader.hpp"
#include "rest_api.hpp"
#include "scheduler.hpp"

// TODO: Read from config
#define SCROLL_DELAY 90000
#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8
#define MARKET_UPDATE_TIME_MS milliseconds(10*60*1000)
#define MARKET_OPEN_UPDATE_TIME_MS milliseconds(30*60*1000)

using namespace info_panel;

LEDMatrix matrix(MATRIX_WIDTH, MATRIX_HEIGHT, 1);
ConfigLoader conf;
APIStocks api_stocks(conf);
APICrypto api_crypto(conf);
FontAscii clock_ascii; // Will be std::moved, dont use
FontAscii ascii;
auto sc = SimpleClock(std::move(clock_ascii));

bool is_market_open(){
    using namespace std::chrono;
    static bool activity = api_stocks.is_active();
    static milliseconds last_time = milliseconds(0);

    time_t tt;
    time(&tt);
    tm curr_time = *localtime(&tt);

    // Check every new hour and every set amount of minutes (to be sure)
    // TODO: Adjust time check windows to match with activity check in scheduler when added
    if((curr_time.tm_min == 0) || duration_cast<milliseconds>(system_clock::now().time_since_epoch()) >= last_time + MARKET_OPEN_UPDATE_TIME_MS){
        activity = api_stocks.is_active();
        last_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }
    return activity;
}

void wall_clock() {
    sc.draw(matrix);
    int pos = -16+matrix.get_text_width()/2;
    matrix.render(pos);
    usleep(sc.delay);
}

void crypto_data(){
    long col = -MATRIX_WIDTH;
    // Because this is run 1 time every 10 minutes it's ok to request data everytime
    std::wstring text = api_crypto.text();
    matrix.draw_text(text, ascii);
    do{
        matrix.render(col);
        col++;
        usleep(SCROLL_DELAY);
    }while(col < static_cast<long>(matrix.get_text_width()));
}

void crypto_stocks_data(){
    using namespace std::chrono;
    static milliseconds last_time = milliseconds(0);
    static std::wstring text;

    long col = -MATRIX_WIDTH;
    if(duration_cast<milliseconds>(system_clock::now().time_since_epoch()) >= last_time + MARKET_UPDATE_TIME_MS){
        text = api_crypto.text() + api_stocks.text();
        last_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }
    matrix.draw_text(text, ascii);
    do{
        matrix.render(col);
        col++;
        usleep(SCROLL_DELAY);
    }while(col < static_cast<long>(matrix.get_text_width()));
}

Scheduler scheduler;

void info_panel::init_panel() {
    std::cout << "Starting panel\n";
    // Market open pipeline
    Task wc_open_task(wall_clock, 10'000);
    Task crst_task(crypto_stocks_data, 0);
    Pipeline p_market_open(is_market_open);
    p_market_open.push(wc_open_task);
    p_market_open.push(crst_task);
    
    // Market closed pipeline
    Task wc_closed_task(wall_clock, 1'000*60*10); // 10 mins of clock
    Task crypto_task(crypto_data, 0);
    Pipeline p_market_closed([]() -> bool{return true;});
    p_market_closed.push(wc_closed_task);
    p_market_closed.push(crypto_task);
    
    // Scheduler
    scheduler.push(p_market_open);
    scheduler.push(p_market_closed);
}

void info_panel::run_panel() {
    // Main loop
    // Just execute scheduler
    //while(true){
    scheduler.execute();
    //}
}

int main(int argc, char *argv[]){
    info_panel::init_panel();
    while(true){
        info_panel::run_panel();
    }
    return 0;
}
