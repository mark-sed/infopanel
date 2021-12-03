#include "pybind11/pybind11.h"
#include <string>
#include "libs/json.hpp"
#include "info_panel.hpp"

using json = nlohmann::json;

/**
 * Wrapper for REST API and info panel communication 
 */ 
namespace wrapper {

    std::string hello(){
        return std::string("Pong");
    }

    void init() {
        info_panel::init_panel();
    }

    void run() {
        info_panel::run_panel();
    }

    namespace controller {
        
        bool set_brightness(int value){
            info_panel::matrix.set_brightness(value, true);
            return true;
        }

        bool show_stocks() {
            return true;
        }

        bool toggle_lamp() {
            return info_panel::matrix.toggle_lamp_mode();
        }

        bool toggle_display() {
            return info_panel::matrix.toggle();
        }

        bool show_clock(int time_sec) {
            return true;
        }

    } // namespace controller

    namespace settings {

        bool set_currency(std::string name) {
            return true;
        }

        bool set_finhub_key(std::string key) {
            return true;
        }

        bool set_polygon_key(std::string key) {
            return true;
        }

        bool set_scheduler(std::string jsonStr) {

            return true;
        }

    } // namespace settings

    namespace colors {

        bool set_symbol(std::string code) {
            return true;
        }

        bool set_price(std::string code) {
            return true;
        }

        bool set_gain(std::string code) {
            return true;
        }

        bool set_loss(std::string code) {
            return true;
        }

        bool set_neutral(std::string code) {
            return true;
        }

    } // namespace colors

    namespace get {

        std::string get_settings() {
            return "{}";
        }

        std::string get_brightness() {
            return std::string("{\"value\": ")+std::to_string(info_panel::matrix.get_brightness())+"}";
        }

        std::string get_scheduler() {
            return "{}";
        }

        bool get_lamp_status() {
            return info_panel::matrix.is_lamp_mode();
        }

        bool get_display_status() {
            return info_panel::matrix.is_on();
        }

    } // namespace get

} // namespace wrapper

// Creating python module
PYBIND11_MODULE(stockpanel, sp){
    sp.doc() = "Stock Panel API";
    
    sp.def("initPanel", &wrapper::init, "Inits panel");
    sp.def("runPanel", &wrapper::run, "Runs panel");
    
    sp.def("hello", &wrapper::hello, "Test method");

    sp.def("setBrightness", &wrapper::controller::set_brightness, "Brightness setter");
    sp.def("showStocks", &wrapper::controller::show_stocks, "Scrolls stocks");
    sp.def("toggleLamp", &wrapper::controller::toggle_lamp, "Toggles lamp mode");
    sp.def("toggleDisplay", &wrapper::controller::toggle_display, "Toggles display mode");
    sp.def("showClock", &wrapper::controller::show_clock, "Shows clock");
    
    sp.def("setCurrency", &wrapper::settings::set_currency, "Sets currency");
    sp.def("setFinhubKey", &wrapper::settings::set_finhub_key, "Sets finhub key");
    sp.def("setPolygonKey", &wrapper::settings::set_polygon_key, "Sets polygon key");
    sp.def("setScheduler", &wrapper::settings::set_scheduler, "Sets scheduler");

    sp.def("setColorSymbol", &wrapper::colors::set_symbol, "Sets color");
    sp.def("setColorPrice", &wrapper::colors::set_price, "Sets color");
    sp.def("setColorGain", &wrapper::colors::set_gain, "Sets color");
    sp.def("setColorLoss", &wrapper::colors::set_loss, "Sets color");
    sp.def("setColorNeutral", &wrapper::colors::set_neutral, "Sets color");

    sp.def("getSettings", &wrapper::get::get_settings, "Returns settings");
    sp.def("getBrightness", &wrapper::get::get_brightness, "Returns brightness");
    sp.def("getScheduler", &wrapper::get::get_scheduler, "Returns scheduler");
    sp.def("getLampStatus", &wrapper::get::get_lamp_status, "Returns lamp status");
    sp.def("getDisplayStatus", &wrapper::get::get_display_status, "Returns display status");
}
