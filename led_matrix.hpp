#ifndef _LED_MATRIX_HPP_
#define _LED_MATRIX_HPP_

#include <stdint.h>
#include <cstddef>
#include <algorithm>

#include "libs/rpi_ws281x/ws2811.h"

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
    unsigned int width;  ///< Amount of pixels horizontally
    unsigned int height; ///< Amount of pixels vertically
    uint8_t brightness;  ///< Brightness of the LEDs \in <0, 255>
    ws2811_t ledstring;  ///< Configuration struct
    
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

    void draw_text(std::string text, ws2811_led_t default_color=Color::WHITE);

    /**
     * Renders drawn data to the LED matrix
     * @offset At what column should the first rendered pixels pixel be.
     *         So for offset 2 - the 3rd column will be at the start of the panel
     */
    void render(unsigned int offset=0);

    /**
     * Tests the LED matrix (in colors and effects)
     */
    void test();
    
};

 #endif//_LED_MATRIX_HPP_
