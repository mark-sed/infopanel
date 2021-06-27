/**
 * @file clock.cpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief Wall clock application.
 * 
 * Contains all wall clocks that can be displayed on the info panel.
 */

#include "clock.hpp" 
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>


const std::tm *Clock::get_time_now(){
    std::time_t t = std::time(nullptr);
    return std::localtime(&t);
}

void SimpleClock::draw(LEDMatrix &matrix){
    static const wchar_t *FORMAT = L"%H:%M";
    std::wstringstream wss;
    wss << std::put_time(get_time_now(), FORMAT);
    // Render to display matrix
    matrix.draw_text(wss.str(), this->font, Color::RED);
}