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

using TaskFun = void(*)(Task *task);  ///< Task behavior method
using IsActiveFunction = bool(*)();   ///< Pipeline activation function

/**
 * Main pipeline object which hold pointer to function with tasks behavior
 */ 
struct Task {
    TaskFun fun;                   ///< Function with tasks behavior
    unsigned int min_duration_ms;  ///< Minimal duration for the function to run in ms
    bool done;                     ///< Used for one_time tasks, true indicates that the task can be closed 
    bool one_time;                 ///< If the task is one time run or duration controlled
    const char *api_name;          ///< API name used for controller
    Task(TaskFun fun, const char *api_name, unsigned int min_duration_ms=0, bool one_time=false) {
        this->fun = fun;
        this->api_name = api_name;
        this->min_duration_ms = min_duration_ms;
        this->done = false;
        this->one_time = one_time;
    }; 
};

/**
 * Pipeline of tasks
 */ 
class Pipeline {
private:
    IsActiveFunction is_active_fun;       ///< Activation function
    size_t current_task_i;                ///< Index of currently running task
    std::chrono::milliseconds start_time; ///< Starting time of currently running task
public:
    std::vector<Task> tasks;                  ///< Queue of tasks
    Pipeline(IsActiveFunction is_active_fun);
    /** Getter for activation function */
    bool is_active();
    /** Pushes a new task into the pipeline of tasks */
    void push(Task t);
    /** Executes pipeline */
    void execute();
};

/**
 * Scheduler for LED panel
 */ 
class Scheduler {
private:
    std::vector<Pipeline> queue;          ///< Queue of pipelines
    Task *priority;                       ///< Priority task (interrupt task)
    std::chrono::milliseconds start_time; ///< Start time for priority task
public:
    Scheduler();
    /** Adds a new pipeline into the scheduler */
    void push(Pipeline p);
    /** Executes scheduler */
    void execute();
    
    /** 
     * Interrupts the scheduler to show stock prices 
     * @return False if there is no stocks widget in the scheduler (to read settings for it)
     */
    bool show_stocks();
    /** 
     * Interrupts the scheduler to show clock
     * @param time_sec For how many seconds to display the time
     * @return False if there is no clock widget in the scheduler (to read settings for it)
     */ 
    bool show_clock(int time_sec);
};

#endif//_SCHEDULER_HPP_
