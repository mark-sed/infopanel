/**
 * @file scheduler.hpp
 * @author Marek Sedlacek
 * @date June 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * @license This project is released under the GNU Public License.
 *          See LICENSE file in main directory.
 * 
 * @brief Scheduling for InfoPanel applications.
 * 
 * Scheduling for application displaying onto the InfoPanel.
 */

#ifndef _SCHEDULER_HPP_
#define _SCHEDULER_HPP_

#include <vector>
#include <chrono>

struct Task;

using TaskFun = void(*)(Task *task);
using IsActiveFunction = bool(*)();

// TODO: Add delays

struct Task {
    TaskFun fun;
    unsigned int min_duration_ms;  ///< Minimal duration for the function to run in ms
    bool done;
    bool one_time;
    const char *api_name;
    Task(TaskFun fun, const char *api_name, unsigned int min_duration_ms=0, bool one_time=false) {
        this->fun = fun;
        this->api_name = api_name;
        this->min_duration_ms = min_duration_ms;
        this->done = false;
        this->one_time = one_time;
    }; 
};

class Pipeline {
private:
    IsActiveFunction is_active_fun;
    size_t current_task_i;
    std::chrono::milliseconds start_time;
public:
    std::vector<Task> tasks;
    Pipeline(IsActiveFunction is_active_fun);
    bool is_active();
    void push(Task t);
    void execute();
};

class Scheduler {
private:
    std::vector<Pipeline> queue;
    Task *priority;
    std::chrono::milliseconds start_time;
public:
    Scheduler();
    void push(Pipeline p);
    void execute();
    
    bool show_stocks();
    bool show_clock(int time_sec);
};

#endif//_SCHEDULER_HPP_
