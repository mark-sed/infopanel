#include "pybind11/pybind11.h"
#include <string>

namespace wrapper {

    std::string hello(){
        return std::string("Hello, World!");
    }

}

// Creating python module
PYBIND11_MODULE(stockpanel, sp){
    sp.doc() = "Stock Panel API";
    sp.def("hello", &wrapper::hello, "Test method");
}