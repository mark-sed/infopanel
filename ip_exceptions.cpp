#include <iostream>
#include <cstdlib>
#include "ip_exceptions.hpp" 

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