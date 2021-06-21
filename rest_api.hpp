#ifndef _REST_API_HPP_
#define _REST_API_HPP_

#include <future>
#include <unistd.h>
#include "led_matrix.hpp"
#include "config_loader.hpp"
#include "font.hpp"
#include "rest_api.hpp"

/**
 * Base class for REST APIs
 */
class RestAPI {
protected:
    ConfigLoader conf;

    RestAPI(ConfigLoader conf) : conf(conf) {};

    /**
     * Async GET call to passed in url
     * @param url URL to which send the request
     * @return async response from the server
     */
    std::future<std::string> GET(std::string const& url);

    /**
     * Async POST call to passed in url with passed in body
     * @param url URL to which send the request
     * @param body JSON body of the POST request
     * @return async response from the server
     */
    std::future<std::string> POST(std::string const& url, std::string const& body);
public:
    /**
     * Method for all the REST APIs to draw text to led matrix
     * @return formatted text for drawing on a matrix
     */
    virtual std::wstring text() = 0;

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
    APIStocks(ConfigLoader conf) : RestAPI(conf) {};
    std::wstring text() override;
    bool is_active() override;
};

/**
 * Rest API for getting crypto market values
 */
class APICrypto : public RestAPI {
public:
    APICrypto(ConfigLoader conf) : RestAPI(conf) {};
    std::wstring text() override;
};


void scroll_crypto_stocks(LEDMatrix matrix, ConfigLoader conf, APICrypto crypto, APIStocks stocks, MatrixFont font);

#endif//_REST_API_HPP_
