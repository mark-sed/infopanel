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
};

/**
 * Rest API for getting stock market values
 */
class APIStocks : public RestAPI {
public:
    void draw(LEDMatrix &matrix) override;
};

/**
 * Rest API for getting crypto market values
 */
class APICrypto : public RestAPI {
public:
    void draw(LEDMatrix &matrix) override;
};

#endif//_REST_API_HPP_
