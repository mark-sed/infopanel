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

using TaskFun = void(*)();
using IsActiveFunction = bool(*)();

// TODO: Add delays

struct Task {
    TaskFun fun;
    unsigned int min_duration_ms;  ///< Minimal duration for the function to run in ms
    Task(TaskFun fun, unsigned int min_duration_ms=0) {
        this->fun = fun;
        this->min_duration_ms = min_duration_ms;
    }; 
};

class Pipeline {
private:
    std::vector<Task> tasks;
    IsActiveFunction is_active_fun;
    size_t current_task_i;
    std::chrono::milliseconds start_time;
public:
    Pipeline(IsActiveFunction is_active_fun);
    bool is_active();
    void push(Task t);
    void execute();
};

class Scheduler {
private:
    std::vector<Pipeline> queue;
public:
    Scheduler();
    void push(Pipeline p);
    void execute();
};

#endif//_SCHEDULER_HPP_
