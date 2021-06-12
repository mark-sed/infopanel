#ifndef _IP_EXCEPTIONS_HPP_
#define _IP_EXCEPTIONS_HPP_

namespace Error {

    /**
     * Holds error codes for exiting application
     */
    enum ErrorCode {
        NONE = 0,
        CONFIGURATION
    };

    /**
     * Returns code name of passed in ErrorCode
     * Also checks if the value is valid (otherwise returns "unknown")
     * @param c Error code value
     */
    const char *get_code_name(ErrorCode c);

    /**
     * This function should be called in case a fatal error occures
     * @note This function will end the program
     * @param return_code Code to return after exiting
     * @param msg A short description of the error
     * @param what Exception message or longer error description. By default this is empty
     * @param tip A message of what could have caused this error. By default this is empty
     */
    [[ noreturn ]] void fatal_error(ErrorCode return_code, const char *msg, const char *what, const char *tip);
}

#endif//_IP_EXCEPTIONS_HPP_
