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
    std::string get_vs_currency();
    std::string get_rest_font();

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
