#include "led_matrix.hpp"
#include <stdint.h>

LEDMatrix::LEDMatrix(unsigned int width, unsigned int height, uint8_t brightness=16) : width(width), height(height), brightness(brightness){
    this->pixels = new ws2811_led_t[width*height];      
    this->ledstring = {
        .freq = ConfLEDMatrix::TARGET_FREQUENCY,
        .dmanum = ConfLEDMatrix::DMA_NUMBER,
        .channel = {
            [0] = {
                .gpionum = ConfLEDMatrix::GPIO_PIN,
                .invert = ConfLEDMatrix::INVERT,
                .count = static_cast<int>(width*height),
                .strip_type = ConfLEDMatrix::STRIP_TYPE,
                .brightness = brightness,
            },
            [1] = {
                .gpionum = 0,
                .invert = 0,
                .count = 0,
                .brightness = 0,
            },
        },
    };
};

LEDMatrix::~LEDMatrix(){
    delete [] this->pixels;
}

void LEDMatrix::test(){
    this->pixels[0] = 255;
    this->pixels[42] = 1000;
    this->pixels[255] = 255;
    this->render();
}

void LEDMatrix::render(){
    std::copy(this->pixels, this->pixels+this->width*this->height, this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds);
}
