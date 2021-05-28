#include "led_matrix.hpp"
#include <stdint.h>

LEDMatrix::LEDMatrix(unsigned int width, unsigned int height, uint8_t brightness=16) : width(width), height(height), brightness(brightness){
    this->pixels = new ws2811_led_t[width*height];      
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
    ws2811_init(&this->ledstring);
};

LEDMatrix::~LEDMatrix(){
    delete [] this->pixels;
    ws2811_fini(&this->ledstring);
}

void LEDMatrix::test(){
    this->pixels[0] = 255;
    this->pixels[42] = 1000;
    this->pixels[255] = 255;
    this->render();
}

void LEDMatrix::render(){
   /*for(int i = 0; i < width*height; i++){
       this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds[i] = this->pixels[i];
   } */
   std::copy(this->pixels, &this->pixels[width*height], this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds);
   ws2811_render(&this->ledstring);
}
