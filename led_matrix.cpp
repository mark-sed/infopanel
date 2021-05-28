#include "led_matrix.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>

#include <iostream>

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

static uint32_t hsv2rgb(float H, float S, float V){
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    uint32_t R = (r+m)*255;
    uint32_t G = (g+m)*255;
    uint32_t B = (b+m)*255;
    return ((R<<16) + (G<<8) + B);
}

void LEDMatrix::test(){
    const float GOLDEN_RATION = 0.618033988749895;
    std::srand(std::time(nullptr));
    for(int i = 1; i < width*height-1; i++){
        float h = std::rand() + GOLDEN_RATION;
        h = std::fmod(h, 1);
        this->pixels[i-1] = hsv2rgb(h, 0.99, 0.99);
    }

    this->render();
}

void LEDMatrix::render(){
    // Copy data from matrix to ledstring
    std::copy(this->pixels, &this->pixels[width*height], this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds);
    // Call ws render to display new data
    ws2811_render(&this->ledstring);
}
