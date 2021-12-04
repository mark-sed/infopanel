/**
 * @file led_matrix.hpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief LED matrix controls.
 * 
 * Interface and functions for working with LED matrix.
 */

#ifndef _LED_MATRIX_HPP_
#define _LED_MATRIX_HPP_

#include <stdint.h>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <string>

#include "libs/rpi_ws281x/ws2811.h"
#include "font.hpp"

/** Coverts string to wstring */
std::wstring to_wstring(std::string text);
/** Converts string to upper case */
std::string to_upper(std::string text);

/** 
 * Configuration namespace, holds all needed values for HW configuration
 */
namespace ConfLEDMatrix {
    const int STRIP_TYPE = WS2811_STRIP_GRB;
    const uint32_t TARGET_FREQUENCY = WS2811_TARGET_FREQ;
    const int DMA_NUMBER = 10;
    const int GPIO_PIN = 18;
    const int INVERT = 0;
    const size_t RENDER_CHANNEL = 0;
}

/**
 * Enum class holding all basic colors
 */
enum Color : ws2811_led_t {
    BLACK = 0x00'00'00'00,
    WHITE = 0x00'FF'FF'FF,
    RED = 0x00'FF'00'00,
    LIME = 0x00'00'FF'00,
    BLUE = 0x00'00'00'FF,
    YELLOW = 0x00'FF'FF'00,
    CYAN = 0x00'00'FF'FF,
    MAGENTA = 0x00'FF'00'FF,
    SILVER = 0x00'C0'C0'C0,
    GRAY = 0x00'80'80'80,
    MAROON = 0x00'80'00'00,
    OLIVE = 0x00'80'80'00,
    GREEN = 0x00'00'80'00,
    PURPLE = 0x00'80'00'80,
    TEAL = 0x00'00'80'80,
    NAVY = 0x00'00'00'80,
    PINK = 0x00'FF'69'B4,
    INDIGO = 0x00'4B'00'82,
    VIOLET = 0x00'94'00'D3,
    ORANGE = 0x00'FF'A5'00,
};

/**
 * Led matrix 
 * ws2811 led strip in matrix configuration
 */
class LEDMatrix {
private:
    unsigned int width;       ///< Amount of pixels horizontally
    unsigned int height;      ///< Amount of pixels vertically
    uint8_t brightness;       ///< Brightness of the LEDs \in <0, 255>
    unsigned int text_width;  ///< Width of drawn content (in panel pixels)
    unsigned int text_height; ///< Height of drawn content (in panel pixels)
    ws2811_t ledstring;       ///< Configuration struct
    bool on;                  ///< If the the panel displays data, otherwise it does not
    bool lamp_mode;           ///< Lamp mode with the whole display shining
    
    /**
     * Parses control sequence
     * @param wtext Text to be parsed for control sequence, 
     *              it has to start with the first character of the sequence (substr)
     * @param color Current drawing color, might be changed if color sequence is matched
     * @return Offset for text parsing (length of matched sequence)
     */
    unsigned int parse_ctrl_seq(std::wstring wtext, ws2811_led_t &color);
public:
    static const size_t EVEN_I = 0;
    static const size_t ODD_I = 1;
    std::vector<ws2811_led_t> pixels[2];  ///< Holds LED values to be rendered on the matrix for odd and even offset
    /**
     * Constructor
     * @param width Amount of pixel horizontally in the LED matrix
     * @param height Amount of pixels vertically in the LED matrix
     * @param brightness Brightness of the panel (\in <0, 255>), by default this is 16
     */
    LEDMatrix(unsigned int width, unsigned int height, uint8_t brightness=16);
    ~LEDMatrix();

    /**
     * Sets brightness for panel
     * @param brightness New brightness value
     * @param render If this is true, then ws2811_render will be called. This is false by default.
     */
    void set_brightness(uint8_t brightness, bool render=false);

    /**
     * @return Brightness of the panel
     */ 
    uint8_t get_brightness() { return brightness; };

    /**
     * Toggles the panel on/off
     * @return Current (after toggle) status of the panel (true = on; false = off)
     */ 
    bool toggle();

    /**
     * @return If the panel is on (true) or off (false)
     */ 
    bool is_on() { return on; }

    /**
     * Toggles lamp mode on/off
     * @return Current (after toggle) status of the lamp mode (true = on; false = off)
     */ 
    bool toggle_lamp_mode();

    /**
     * @return If the panel is in lamp mode
     */ 
    bool is_lamp_mode() { return lamp_mode; }

    /**
     * Draws text to canvas (for rendering on the panel)
     * @note Previous canvas will be cleared
     * @param text Text to be drawn
     * @param font Font for the whole text
     * @param default_color Color to use in case no escape sequence is in the text
     */
    void draw_text(std::wstring text, MatrixFont font, ws2811_led_t default_color=Color::WHITE);
    
    void draw_text(std::string text, MatrixFont font, ws2811_led_t default_color=Color::WHITE);

    /**
     * Renders drawn data to the LED matrix
     * @offset At what column should the first rendered pixels pixel be.
     *         So for offset 2 - the 3rd column will be at the start of the panel
     */
    void render(int offset=0);

    /**
     * Tests the LED matrix (effects showcase)
     */
    void test();
    
    // Getters
    unsigned int get_text_width();
    unsigned int get_text_height();
};

 #endif//_LED_MATRIX_HPP_
