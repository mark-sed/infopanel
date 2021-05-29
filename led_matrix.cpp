#include "led_matrix.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include "font.hpp"
#include <sstream>

#include <iostream>
#include <unistd.h>

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

void LEDMatrix::draw_text(std::wstring text, MatrixFont font, ws2811_led_t default_color){
    // TODO: Make this place in spacers if max_height != height?
    const unsigned int LETTER_SPACE = 1;
    size_t text_max_length = text.length()*font.get_max_width()*this->height + text.length()*this->height*LETTER_SPACE;
    this->pixels[LEDMatrix::ODD_I].resize(text_max_length+0/*height*width*/);
    this->pixels[LEDMatrix::EVEN_I].resize(text_max_length+0/*height*width*/);
    std::fill(this->pixels[LEDMatrix::ODD_I].begin(), this->pixels[LEDMatrix::ODD_I].end(), Color::BLACK);
    std::fill(this->pixels[LEDMatrix::EVEN_I].begin(), this->pixels[LEDMatrix::EVEN_I].end(), Color::BLACK);
    
    unsigned int odd_i = LEDMatrix::ODD_I;
    unsigned int even_i = LEDMatrix::EVEN_I;
    unsigned int render_pos = 0;
    ws2811_led_t color = default_color;
    for(unsigned int i = 0; i < text.length(); i++){
        if((render_pos/height) % 2){
            // Swap indexes if odd is rendered on even index and vice versa
            odd_i = LEDMatrix::EVEN_I;
	    even_i = LEDMatrix::ODD_I;
	}
	else{
            odd_i = LEDMatrix::ODD_I;
	    even_i = LEDMatrix::EVEN_I;
	}
        int prev = font.get_max_height()-1;
        int r = prev;
        int stop = 0;
        for(long j = 0; j < font.letters[text[i]].size(); j++){
            // Even columns
	    this->pixels[even_i][render_pos+j] = font.letters[text[i]][j]*color;
            // Odd column
	    this->pixels[odd_i][render_pos+j] = font.letters[text[i]][r]*color;
            r--;
            if(r < stop){
                stop += font.get_max_height();
                prev += font.get_max_height();
                r = prev;
            }
        }
        render_pos += font.letters[text[i]].size() + height*LETTER_SPACE;
    }
}

void LEDMatrix::test(){
    /*const float GOLDEN_RATIO = 0.618033988749895;
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

    // Draw all characters
    FontAscii ascii;
    std::wstringstream ss;
    for(const auto &pair: ascii.letters){
	ss << pair.first;
    }
    draw_text(ss.str(), ascii, Color::RED);
    long col = 0;
    while(true){
        this->render(col);
        col++;
        if(col >= this->pixels[LEDMatrix::EVEN_I].size()/height){
            col = 0;
        }
        usleep(90000);
    }
}

void LEDMatrix::render(unsigned int offset){
    // TODO: Add negative offset for shifting text to right
    
    size_t i = offset % 2 ? LEDMatrix::ODD_I : LEDMatrix::EVEN_I; 
    
    std::fill(this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds, this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds+width*height, Color::BLACK);
    // Copy data from matrix to ledstring
    size_t last_i = width*height+offset*height;
    std::copy(&this->pixels[i].data()[offset*height], &this->pixels[i].data()[last_i], this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds);
    // Clear space after last character
    if(this->pixels[i].size()-offset*height < width*height){
        std::fill(this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds+this->pixels[i].size()-offset*height, this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds+width*height, Color::BLACK);
    }
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
