/**
 * @file clock.hpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief Wall clock application
 * 
 * Contains all wall clocks that can be displayed on the info panel.
 */

#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_

#include <string>
#include <ctime>
#include "led_matrix.hpp"
#include "font.hpp"

/**
 * Base class for all clock styles
 */
class Clock {
protected:
    MatrixFont font;  ///< Font in which to render the clock text
    const std::string NAME = "Clock";  ///< Name of the clock

    /**
     * Constructor
     * @param font Font for the clock text
     */
    Clock(MatrixFont font, unsigned delay) : font(font), delay(delay) {};

    /**
     * Function for derived classes to get current time
     */
    const std::tm* get_time_now();
public:
    static const char *NAME_API;
    unsigned int delay; ///< Recommended delay for clock in ms

    /**
     * Draw method (draws clock to LEDMatrix)
     * @param matrix LED matrix to draw to
     */
    virtual void draw(LEDMatrix &matrix) = 0;
};


/**
 * Simples hours and minutes clock 
 * "HH:MM" clock format
 */
class SimpleClock : public Clock {
protected:
    const std::string NAME = "Simple clock";
public:
    SimpleClock(MatrixFont font) : Clock(font, 1'000) {};
    void draw(LEDMatrix &matrix) override;
};

#endif//_CLOCK_HPP_
