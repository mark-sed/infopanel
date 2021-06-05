#include <string>
#include <fstream>
#include <vector>
#include <streambuf>
#include "libs/json.hpp"
#include "config_loader.hpp"

#include <iostream>
#include <sstream>

using json = nlohmann::json;

const std::string ConfigLoader::PATH = "config.json";

ConfigLoader::ConfigLoader(){
    this->reload();
}

void ConfigLoader::reload(){
    std::ifstream f(ConfigLoader::PATH);
    std::string conf((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    this->json_data = json::parse(conf);
}

std::string ConfigLoader::get_vs_currency(){
    return this->json_data["rest_api"]["vs_currency"].get<std::string>();
}

std::string ConfigLoader::get_stocks_url_values(){
    return this->json_data["rest_api"]["stocks"]["url_values"].get<std::string>();
}

std::string ConfigLoader::get_stocks_url_values_key(){
    return this->json_data["rest_api"]["stocks"]["url_values_keys"].get<std::string>();
}

std::string ConfigLoader::get_stocks_url_market_open(){
    return this->json_data["rest_api"]["stocks"]["url_market_open"].get<std::string>();
}

std::string ConfigLoader::get_stocks_url_market_open_key(){
    return this->json_data["rest_api"]["stocks"]["url_market_open_key"].get<std::string>();
}

std::vector<std::string> ConfigLoader::get_stocks_symbols(){
    return this->json_data["rest_api"]["stocks"]["symbols"].get<std::vector<std::string> >();
}

std::string ConfigLoader::get_crypto_url_values(){
    return this->json_data["rest_api"]["crypto"]["url_values"].get<std::string>();
}

std::vector<std::string> ConfigLoader::get_crypto_symbols(){
    return this->json_data["rest_api"]["crypto"]["symbols"].get<std::vector<std::string> >();
}

std::string ConfigLoader::get_clock_name(){
    return this->json_data["clock"]["name"].get<std::string>();
}