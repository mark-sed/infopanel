#ifndef __LED_MATRIX_HPP__
#define __LED_MATRIX_HPP__

#include <stdint.h>
#include <cstddef>
#include <algorithm>

#include "libs/rpi_ws281x/ws2811.h"

namespace ConfLEDMatrix {
    const int STRIP_TYPE = WS2811_STRIP_GBR;
    const uint32_t TARGET_FREQUENCY = WS2811_TARGET_FREQ;
    const int DMA_NUMBER = 10;
    const int GPIO_PIN = 18;
    const int INVERT = 0;
    const size_t RENDER_CHANNEL = 0;
}

class LEDMatrix {
private:
    unsigned int width;
    unsigned int height;
    uint8_t brightness;
    ws2811_t ledstring;
    
public:
    LEDMatrix(unsigned int width, unsigned int height, uint8_t brightness);
    ~LEDMatrix();

    void render();

    void test();
    
    ws2811_led_t *pixels;
};

 #endif//__LED_MATRIX_HPP__
