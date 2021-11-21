/**
 * @file scheduler.cpp
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

#include "scheduler.hpp"
#include <chrono>

using namespace std::chrono;

Pipeline::Pipeline(IsActiveFunction is_active_fun) : current_task_i{0} {
    this->is_active_fun = is_active_fun;
    this->start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

bool Pipeline::is_active(){
    return this->is_active_fun();
}

void Pipeline::execute(){
    if(tasks.empty())
        return;

    if( (tasks[this->current_task_i].one_time && tasks[this->current_task_i].done)
        || (!tasks[this->current_task_i].one_time && duration_cast<milliseconds>(system_clock::now().time_since_epoch()) >= start_time + milliseconds(tasks[this->current_task_i].min_duration_ms))) {
        // Start another task
        this->current_task_i++;
        if(this->current_task_i >= this->tasks.size()){
            this->current_task_i = 0;
        }
        tasks[this->current_task_i].done = false;
        this->start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }
    
    tasks[this->current_task_i].fun(&(tasks[this->current_task_i]));
}

void Pipeline::push(Task t){
    this->tasks.push_back(t);
}

Scheduler::Scheduler() : queue{} {

}

void Scheduler::execute(){
    for(auto p: this->queue){
        // Find first active task in the queue
        // it is a priority queue so break after finding it
        if(p.is_active()){
            p.execute();
            break;
        }
    }
}

void Scheduler::push(Pipeline p){
    this->queue.push_back(p);
}
