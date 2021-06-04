#ifndef _FONT_HPP_
#define _FONT_HPP_

#include <stdint.h>
#include <map>
#include <vector>
#include "libs/rpi_ws281x/ws2811.h"

/**
 * Base class for any font
 */
class MatrixFont {
protected:
    uint8_t max_height;  ///< The height of the biggest character in the font
    uint8_t max_width;   ///< The width of the biggest character in the font
    bool monospace;      ///< If the font is monospace or not
    const std::string NAME = "Base font";  ///< Name of the font

    /**
     * Constructor
     */
    MatrixFont(uint8_t max_height, uint8_t max_width, bool monospace)
              : max_height(max_height), max_width(max_width), monospace(monospace) {}
public:
    std::vector<ws2811_led_t> unknown;  ///< Character to be displayed if passed one is not found
    std::map<wchar_t, std::vector<ws2811_led_t> > letters;  ///< Map holding arrays of led configurations for all letters (1 for led on, 0 for led off)

    /**
     * Getter for max_width
     */
    uint8_t get_max_width() { return this->max_width; };
    
    /**
     * Getter for max_height
     */
    uint8_t get_max_height() { return this->max_height; };

    /**
     * Getter for monospace
     */
    bool is_monospace() { return this->monospace; };
};

/**
 * Simple ascii font
 * Contains only basic ASCII characters + CZ ascii ones
 */
class FontAscii : public MatrixFont {
protected:
    const std::string NAME = "Ascii";
public:
    /**
     * Constructor
     * Fills the database of characters
     */
    FontAscii();
};

#endif//_FONT_HPP_
