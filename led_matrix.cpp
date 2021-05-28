#include "led_matrix.hpp"
#include <stdint.h>

LEDMatrix::LEDMatrix(unsigned int width, unsigned int height, uint8_t brightness=16) : width(width), height(height), brightness(brightness){
    this->pixels = new ws2811_led_t[width*height]; 
    // Setup ledstring     
    ws2811_t temp_ledstring = {
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
    this->ledstring = temp_ledstring;
    // Init ws with config ledstring
    ws2811_init(&this->ledstring);
};

LEDMatrix::~LEDMatrix(){
    delete [] this->pixels;
    ws2811_fini(&this->ledstring);
}

void LEDMatrix::test(){
    this->pixels[0] = Color::RED;
    this->pixels[42] = 0x00'008000;//Color::BLUE;
    this->pixels[255] = 0x00'BC8F8F;
    this->render();
}

void LEDMatrix::render(){
    // Copy data from matrix to ledstring
    std::copy(this->pixels, &this->pixels[width*height], this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds);
    // Call ws render to display new data
    ws2811_render(&this->ledstring);
}
