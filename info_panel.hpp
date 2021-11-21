/**
 * @file info_panel.hpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief Entry point.
 * 
 * Entry point to the application containing initializations and
 * control functions for info panel behavior.
 */

#ifndef _INFO_PANEL_HPP_
#define _INFO_PANEL_HPP_

#define INFO_PANEL_VERSION_MAJOR 1
#define INFO_PANEL_VERSION_MINOR 0
#define INFO_PANEL_VERSION_PATCH 0

#include "info_panel.hpp"
#include "led_matrix.hpp"
#include "clock.hpp"
#include "font.hpp"
#include "config_loader.hpp"
#include "rest_api.hpp"
#include "scheduler.hpp"

namespace info_panel {
    void init_panel();
    void run_panel();

    
    extern LEDMatrix matrix;
    extern ConfigLoader conf;
    extern APIStocks api_stocks;
    extern APICrypto api_crypto;
    extern FontAscii clock_ascii; // Will be std::moved, dont use
    extern FontAscii ascii;
    extern SimpleClock simpleClock;

}

#endif
