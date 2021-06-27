/**
 * @file ip_exceptions.cpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief InfoPanel exceptions.
 * 
 * Handlers and interface for InfoPanel exceptions and error handeling.
 */

#include <iostream>
#include <cstdlib>
#include "ip_exceptions.hpp" 

bool Warning::WARNING_MSGS_ON = true;

const char *Error::get_code_name(Error::ErrorCode c){
    const char *NAMES[] = {
        "none",
        "configuration"
    };
    constexpr int names_size = sizeof(NAMES)/sizeof(char *);
    if(c < names_size){
        return NAMES[c];
    }
    return "unknown";
}

[[ noreturn ]] void Error::fatal_error(Error::ErrorCode return_code, const char *msg, const char *what="", const char *tip=""){
    std::cerr << "ERROR (" << Error::get_code_name(return_code) << "): " << msg << "!";
    if(what[0] != '\0'){
        std::cerr << " (" << what << ")";
    }
    std::cerr << std::endl;
    if(tip[0] != '\0'){
        std::cerr << "NOTE: " << tip << "." << std::endl;
    }
    std::exit(return_code);
}

void Warning::warning(const char *msg, const char *extra){
    if(Warning::WARNING_MSGS_ON){
        std::cout << "WARNING: " << msg << ".";
        if(extra[0] != '\0'){
            std::cout << " (" << extra << ")";
        }
        std::cout << std::endl;
    }
}