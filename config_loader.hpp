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

    /**
     * Updates data from the loader into the config file
     */ 
    void write_to_config();

    // Getters and setters for config values
    std::string get_units_currency();
    bool set_units_currency(std::string name);

    bool get_units_time24h();

    std::string get_rest_font();
    std::string get_rest_color_symbol();
    bool set_rest_color_symbol(std::string code);
    std::string get_rest_color_price();
    bool set_rest_color_price(std::string code);
    std::string get_rest_color_gain();
    bool set_rest_color_gain(std::string code);
    std::string get_rest_color_loss();
    bool set_rest_color_loss(std::string code);
    std::string get_rest_color_neutral();
    bool set_rest_color_neutral(std::string code);

    std::string get_stocks_url_values();
    
    std::string get_stocks_url_values_key();
    bool set_stocks_url_values_key(std::string key);

    std::string get_stocks_url_market_open();
    std::string get_stocks_url_market_open_key();
    bool set_stocks_url_market_open_key(std::string key);

    std::vector<std::string> get_stocks_symbols();

    std::string get_crypto_url_values();
    std::vector<std::string> get_crypto_symbols();

    std::string get_clock_name();
    std::string get_clock_font();
};

#endif//_CONFIG_LOADER_HPP_
