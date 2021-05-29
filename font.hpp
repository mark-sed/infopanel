#ifndef _FONT_HPP_
#define _FONT_HPP_

#include <stdint.h>
#include <map>
#include <vector>

#define FONT_ENTRY(k, ...) {(k), std::vector<ws2811_led_t>{__VA_ARGS__}}

using LetterT = wchar_t;

class MatrixFont {
protected:
    uint8_t max_height;
    uint8_t max_width;
    bool monospace;
    std::vector<ws2811_led_t> unknown;
public:
    std::map<LetterT, std::vector<ws2811_led_t> > letters;

    MatrixFont(uint8_t max_height, uint8_t max_width, bool monospace)
              : max_height(max_height), max_width(max_width), monospace(monospace) {}

    uint8_t get_max_width() { return this->max_width; };
    uint8_t get_max_height() { return this->max_height; };
    bool is_monospace() { return this->monospace; };
};

class FontAscii : public virtual MatrixFont {
private:
public:
    FontAscii() : MatrixFont(8, 5, false){
        this->letters = {
            FONT_ENTRY(L'b',
		        0, 1, 1, 1, 1, 1, 1, 0, 
                0, 1, 0, 0, 1, 0, 1, 0,
                0, 0, 1, 1, 0, 0, 1, 0,
                0, 0, 1, 1, 0, 0, 0, 0
            ),
            FONT_ENTRY(L'B',
		        0, 1, 1, 1, 1, 1, 1, 0,
		        0, 1, 0, 0, 1, 0, 1, 0,
		        0, 1, 0, 1, 0, 0, 1, 0,
		        0, 0, 1, 1, 0, 1, 0, 0,
            ),

            FONT_ENTRY(L'\0',
		        0, 0, 0, 0, 0, 0, 0, 0,
		        0, 0, 0, 0, 0, 0, 0, 0,
		        0, 0, 0, 0, 0, 0, 0, 0,
		        0, 0, 0, 0, 0, 0, 0, 0,
            ),
        };
    };
};

#endif//_FONT_HPP_
