#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_

#include <string>
#include <ctime>
#include "led_matrix.hpp"
#include "font.hpp"

class Clock {
protected:
    MatrixFont font;
    const std::string NAME = "Clock";

    //Clock(MatrixFont &&font) : font(std::move(font)) {};
    Clock(MatrixFont font) : font(font) {};
    const std::tm* get_time_now();
public:
    virtual ~Clock() = 0;
    virtual void draw(LEDMatrix &matrix) = 0;
};

class SimpleClock : public Clock {
protected:
    const std::string NAME = "Simple clock";
public:
    //SimpleClock(MatrixFont &&font) : Clock(std::move(font)) {};
    SimpleClock(MatrixFont font) : Clock(font) {};
    void draw(LEDMatrix &matrix) override;
};

#endif//_CLOCK_HPP_
