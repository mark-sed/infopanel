/**
 * @file config_loader.hpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief Resources for loading configuration data.
 * 
 * Functions for loading configuration data. Mainly from the
 * config.json file.
 */

#ifndef _CONFIG_LOADER_HPP_
#define _CONFIG_LOADER_HPP_

#include <string>
#include <vector>
#include "libs/json.hpp"

using json = nlohmann::json;

/**
 * Class for loading and accessing values from config file
 */
class ConfigLoader {
private:
    static const std::string PATH;
    json json_data;
public:
    /**
     * Constructor
     * Calls reload function
     */
    ConfigLoader();
    
    /**
     * Reads data from json file specified by PATH constant
     */
    void reload();

    // Getters for config values
    std::string get_units_currency();
    bool get_units_time24h();

    std::string get_rest_font();
    std::string get_rest_color_symbol();
    std::string get_rest_color_price();
    std::string get_rest_color_gain();
    std::string get_rest_color_loss();
    std::string get_rest_color_neutral();

    std::string get_stocks_url_values();
    std::string get_stocks_url_values_key();
    std::string get_stocks_url_market_open();
    std::string get_stocks_url_market_open_key();
    std::vector<std::string> get_stocks_symbols();

    std::string get_crypto_url_values();
    std::vector<std::string> get_crypto_symbols();

    std::string get_clock_name();
    std::string get_clock_font();
};

#endif//_CONFIG_LOADER_HPP_
