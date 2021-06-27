/**
 * @file ip_exceptions.hpp
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

#ifndef _IP_EXCEPTIONS_HPP_
#define _IP_EXCEPTIONS_HPP_

/**
 * Namespace containing error handling resources
 */
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

/**
 * Namespace containing warning handling resources
 */
namespace Warning {
    extern bool WARNING_MSGS_ON;  ///< If true, warning messages will be printed out

    /**
     * Prints our warning message to stdout
     * @param msg Message to be printed
     * @param extra Additional info like what() or returned data
     */
    void warning(const char *msg, const char *extra);
}

#endif//_IP_EXCEPTIONS_HPP_
