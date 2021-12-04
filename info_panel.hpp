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

/**
 * InfoPanel namespace mainly to be used by external parts, like the REST API
 */ 
namespace info_panel {
    /** Initialized the panel */
    void init_panel();
    /** Intializes the panel using scheduler in the config */
    void init_panel_json();
    /** Runs one iteration of the panel behavior */
    void run_panel();

    extern LEDMatrix matrix;        ///< LED panel driver
    extern ConfigLoader conf;       ///< Configuration file loader
    extern APIStocks api_stocks;    ///< Instance of API Stocks
    extern APICrypto api_crypto;    ///< Instance of API Crypto
    extern FontAscii ascii;         ///< Font to be used by widgets
    extern SimpleClock simpleClock; ///< Simple clock for wall clock

    extern Scheduler scheduler;     ///< Main panel scheduler

    /** Scrolls crypto and stocks values. Used by controller interrupt */
    void crypto_stocks_data(Task *task);
    /** Shows wallclock. Used by controller interrupt */
    void wall_clock(Task *task);
}

#endif
