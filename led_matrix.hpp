#ifndef __LED_MATRIX_HPP__
#define __LED_MATRIX_HPP__

#include <stdint.h>
#include <cstddef>
#include <algorithm>

#include "libs/rpi_ws281x/ws2811.h"

/** 
 * Configuration namespace, holds all needed values for HW configuration
 */
namespace ConfLEDMatrix {
    const int STRIP_TYPE = WS2811_STRIP_GBR;
    const uint32_t TARGET_FREQUENCY = WS2811_TARGET_FREQ;
    const int DMA_NUMBER = 10;
    const int GPIO_PIN = 18;
    const int INVERT = 0;
    const size_t RENDER_CHANNEL = 0;
}

/**
 * Enum class holding all basic colors
 */
enum class Colors : ws2811_led_t {
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF,
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
    /**
     * Constructor
     * @param width Amount of pixel horizontally in the LED matrix
     * @param height Amount of pixels vertically in the LED matrix
     * @param brightness Brightness of the panel (\in <0, 255>), by default this is 16
     */
    LEDMatrix(unsigned int width, unsigned int height, uint8_t brightness);
    ~LEDMatrix();

    /**
     * Renders drawn data to the LED matrix
     */
    void render();

    /**
     * Tests the LED matrix (in colors and effects)
     */
    void test();
    
    ws2811_led_t *pixels;  ///< Holds LED values to be rendered on the matrix
};

 #endif//__LED_MATRIX_HPP__
