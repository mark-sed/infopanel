#include "led_matrix.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include "font.hpp"

#include <iostream>

LEDMatrix::LEDMatrix(unsigned int width, unsigned int height, uint8_t brightness) : 
                     width(width), height(height), brightness(brightness), 
                     pixels{std::vector<ws2811_led_t>(width*height), std::vector<ws2811_led_t>(width*height)}{ 
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
    ws2811_fini(&this->ledstring);
}

void LEDMatrix::set_brightness(uint8_t brightness, bool render){
    // No need to check if value is in range,
    // because brightness is of type uint8_t
    this->ledstring.channel[0].brightness = brightness;
    if(render){
        ws2811_render(&this->ledstring);
    }
}

void LEDMatrix::draw_text(std::string text, ws2811_led_t default_color){

}

void LEDMatrix::test(){
    FontAscii ascii;
    int p = 8;
    int prev = ascii.get_max_height()-1;
    int r = prev;
    int stop = 0;
    for(int i = 0; i < (ascii.get_max_width()-1)*ascii.get_max_height(); i++){
	    std::cout << r << std::endl;
        this->pixels[0][p++] = ascii.letters['B'][r];
        r--;
        if(r < stop){
            stop += ascii.get_max_height();
            prev += ascii.get_max_height();
            r = prev;
        }
    }
/*
    const float GOLDEN_RATIO = 0.618033988749895;
    std::srand(std::time(nullptr));
    for(int i = 0; i < width*height; i++){
	// Generate random number in <0, 1>
        float h = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        // Add golden ratio for better value and set it back in the range
	h += GOLDEN_RATIO;
	h = std::fmod(h, 1.0);
	// Convert from hue (HSV) to RGB
        this->pixels[i] = hsv2rgb(h, 0.99, 0.99);
    }*/
    this->render();
}

void LEDMatrix::render(unsigned int offset){
    size_t i = offset % 2 ? LEDMatrix::ODD_I : LEDMatrix::EVEN_I; 
    // Copy data from matrix to ledstring
    std::copy(&this->pixels[i].data()[offset*height], &this->pixels[i].data()[width*height+offset*height], this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds);
    // Call ws render to display new data
    ws2811_render(&this->ledstring);
}

static uint32_t hsv2rgb(float h, float s, float v){
    int h_i = static_cast<int>(h*6);
    float f = h*6 - h_i;
    float p = v * (1-s);
    float q = v * (1 - f*s);
    float t = v * (1 - (1 - f) * s);
    float r, g, b;
    switch(h_i){
        case 0:
            r = v;
            g = t;
            b = p;
        break;
        case 1:
            r = q;
            g = v;
            b = p;
        break;
        case 2:
            r = p;
            g = v;
            b = t;
        break;
        case 3:
            r = p;
            g = q;
            b = v;
        break;
        case 4:
            r = t;
            g = p;
            b = v;
        break;
        default:
            r = v;
            g = p;
            b = q;
        break;
    }

    uint32_t R = static_cast<uint32_t>(r*256);
    uint32_t G = static_cast<uint32_t>(g*256);
    uint32_t B = static_cast<uint32_t>(b*256);
    return ((R<<16) + (G<<8) + B);
}
