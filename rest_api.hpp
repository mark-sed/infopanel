#ifndef _REST_API_HPP_
#define _REST_API_HPP_

#include "led_matrix.hpp"

/**
 * Base class for REST APIs
 */
class RestAPI {
protected:
    RestAPI(){};
public:
    /**
     * Method for all the REST APIs to draw text to led matrix
     */
    virtual void draw(LEDMatrix &matrix) = 0;

    /**
     * Returns true if the API is active
     * Mainly meant to be used by APIs for stock market and such -
     * to check if it's open (if there is an event...)
     */
    virtual bool is_active() { return true; };
};

/**
 * Rest API for getting stock market values
 */
class APIStocks : public RestAPI {
public:
    void draw(LEDMatrix &matrix) override;
    bool is_active() override;
};

/**
 * Rest API for getting crypto market values
 */
class APICrypto : public RestAPI {
public:
    void draw(LEDMatrix &matrix) override;
};

#endif//_REST_API_HPP_
