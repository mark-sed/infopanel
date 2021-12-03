/**
 * @file rest_api.hpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief RestAPIs for display applications.
 * 
 * Restful API handling for display applications that need it.
 */

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

    /**
     * Getter for API name
     */ 
    virtual const char *get_name() { return "Unknown"; }
};

/**
 * Rest API for getting stock market values
 */
class APIStocks : public RestAPI {
public:
    static const char *NAME;
    APIStocks(ConfigLoader conf) : RestAPI(conf) {};
    std::wstring text() override;
    bool is_active() override;
    const char *get_name() override { return this->NAME; }
};

/**
 * Rest API for getting crypto market values
 */
class APICrypto : public RestAPI {
public:
    static const char *NAME;
    APICrypto(ConfigLoader conf) : RestAPI(conf) {};
    std::wstring text() override;
    const char *get_name() override { return this->NAME; }
};


//void scroll_crypto_stocks(LEDMatrix matrix, ConfigLoader conf, APICrypto crypto, APIStocks stocks, MatrixFont font);

#endif//_REST_API_HPP_
