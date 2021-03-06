/**
 * @file led_matrix.cpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief LED matrix controls.
 * 
 * Interface and functions for working with LED matrix.
 */

#include <stdint.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <sstream>
#include <regex>
#include <locale>
#include <codecvt>
#include <string>
#include <algorithm>
#include <cctype>
#include "font.hpp"
#include "led_matrix.hpp"
#include "clock.hpp"

#include "config_loader.hpp"
#include "rest_api.hpp"
#include <iostream>
#include <unistd.h>

std::wstring to_wstring(std::string text){
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(text);
    return wide;
}

std::string to_upper(std::string text){
    std::string outs(text.length(), '\0');
    std::transform(text.begin(), text.end(), outs.begin(), ::toupper);
    return outs;
}

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

unsigned int LEDMatrix::parse_ctrl_seq(std::wstring wtext, ws2811_led_t &color){
    // TODO: Add escape sequence for {{
    // If the start of escape sequence is changed from '{' then this has to be 
    //     also done in the draw_text method (checking for begining)
    const std::string SEQ_PREFIX = "^\\{\\{";
    const std::string SEQ_POSTFIX = "\\}\\}";
    const std::string SEQ_COLOR = "(0[xX][0-9a-fA-F]{6})";
    const std::regex RE_CTRL_SEQ_COLOR(SEQ_PREFIX+SEQ_COLOR+SEQ_POSTFIX);

    std::string text = std::string(wtext.begin(), wtext.end());

    std::smatch match;
    if(!std::regex_search(text, match, RE_CTRL_SEQ_COLOR)){
        // Control sequence not matched, draw this text
        return 0;
    }
    if(match.size() < 2){
        return 0;
    }

    std::string new_color = match[1];
    // Parse hex string to int 
    // Ignoring errors because value is checked in regex
    int color_value = std::stoul(new_color, nullptr, 16);
    color = static_cast<ws2811_led_t>(color_value);
    return match[0].length();
}

void LEDMatrix::draw_text(std::wstring text, MatrixFont font, ws2811_led_t default_color){
    // TODO: Make this place in spacers if max_height != height?
    const unsigned int LETTER_SPACE = 1;
    size_t text_max_length = text.length()*font.get_max_width()*this->height + text.length()*this->height*LETTER_SPACE;
    this->pixels[LEDMatrix::ODD_I].resize(text_max_length);
    this->pixels[LEDMatrix::EVEN_I].resize(text_max_length);
    std::fill(this->pixels[LEDMatrix::ODD_I].begin(), this->pixels[LEDMatrix::ODD_I].end(), Color::BLACK);
    std::fill(this->pixels[LEDMatrix::EVEN_I].begin(), this->pixels[LEDMatrix::EVEN_I].end(), Color::BLACK);

    unsigned int odd_i = LEDMatrix::ODD_I;
    unsigned int even_i = LEDMatrix::EVEN_I;
    unsigned int render_pos = 0;
    ws2811_led_t color = default_color;
    for(unsigned int i = 0; i < text.length(); i++){
        // Parsing control sequences for colors
        if(text[i] == L'{'){
            i += this->parse_ctrl_seq(text.substr(i), color);
        }
        // Swap indexes if odd is rendered on even index and vice versa
        if((render_pos/height) % 2){
            odd_i = LEDMatrix::EVEN_I;
	        even_i = LEDMatrix::ODD_I;
        }
        else{
            odd_i = LEDMatrix::ODD_I;
	        even_i = LEDMatrix::EVEN_I;
	    }
        auto letter = font.unknown;
        if(font.letters.count(text[i]) > 0){
            letter = font.letters[text[i]];
        }
        int prev = font.get_max_height()-1;
        int r = prev;
        int stop = 0;
        for(size_t j = 0; j < letter.size(); j++){
            // Even columns
	        this->pixels[even_i][render_pos+j] = letter[j]*color;
            // Odd column
	        this->pixels[odd_i][render_pos+j] = letter[r]*color;
            r--;
            if(r < stop){
                stop += font.get_max_height();
                prev += font.get_max_height();
                r = prev;
            }
        }
        render_pos += letter.size();
        if(!std::iswspace(text[i]) && i+1 < text.length() && !std::iswspace(text[i+1])){ 
            // Add spacing in between numbers and letter
            // but not whitespaces and symbols nor letters after which is space
            render_pos += height*LETTER_SPACE;
        }
    }

    // Set height of the drawn text (1 line)
    this->text_height = font.get_max_height();
    // Set width of drawn text
    this->text_width = render_pos/font.get_max_height();
}

void LEDMatrix::draw_text(std::string text, MatrixFont font, ws2811_led_t default_color){
    draw_text(to_wstring(text), font, default_color);
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

void LEDMatrix::test(){
    /*const float GOLDEN_RATIO = 0.618033988749895;
    std::srand(std::time(nullptr));
    for(unsigned int i = 0; i < width*height; i++){
        // Generate random number in <0, 1>
        float h = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        // Add golden ratio for better value and set it back in the range
        h += GOLDEN_RATIO;
        h = std::fmod(h, 1.0);
        // Convert from hue (HSV) to RGB
        this->pixels[0][i] = hsv2rgb(h, 0.99, 0.99);
    }
    this->render(0);*/

    // Draw all characters
    /*
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
    }*/

    /*FontAscii ascii;
    draw_text(std::wstring(L"Hello {{0xFF00AA}} World { this is {{0x778800}} colored {{0xFFFFFF}} text."), ascii, Color::RED);
    long col = 0;
    while(true){
        this->render(col);
        col++;
        if(col >= this->text_width){
            col = 0;
        }
        usleep(90000);
    }*/

    /*FontAscii ascii;
    auto sc = SimpleClock(std::move(ascii));
    while(true){
        sc.draw(*this);
        this->render(-16+this->text_width/2);
        usleep(10*1000*1000);
    }*/

    ConfigLoader l;
    
    APIStocks s(l);
    APICrypto c(l);
    FontAscii ascii;
    long col = 0;
    std::wstring text = c.text() + s.text();
    this->draw_text(text, ascii);
    while(true){
        this->render(col);
        col++;
        if(col >= this->text_width){
            text = c.text() + s.text();
            this->draw_text(text, ascii);
            col = 0;
        }
        usleep(90000);
    }
}

void LEDMatrix::render(int offset){
    // TODO: Add negative offset for shifting text to right
    long i = offset % 2 ? LEDMatrix::ODD_I : LEDMatrix::EVEN_I; 
    
    std::fill(this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds, this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds+width*height, Color::BLACK);
    // Copy data from matrix to ledstring
    long last_i = width*height+offset*height;
    // Clear space before first character if offset is negative
    if(offset < 0){
	std::copy(&this->pixels[i].data()[0], &this->pixels[i].data()[width*height+offset*height], this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds+(-1*offset)*height);
    }
    else{
    	std::copy(&this->pixels[i].data()[offset*height], &this->pixels[i].data()[last_i], this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds);
    }
    // Clear space after last character
    if(this->pixels[i].size()-offset*height < width*height){
        std::fill(this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds+this->pixels[i].size()-offset*height, this->ledstring.channel[ConfLEDMatrix::RENDER_CHANNEL].leds+width*height, Color::BLACK);
    }
    // Call ws render to display new data
    ws2811_render(&this->ledstring);
}

unsigned int LEDMatrix::get_text_width(){
    return this->text_width;
}

unsigned int LEDMatrix::get_text_height(){
    return this->text_height;
}
