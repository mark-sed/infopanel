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
#include "rest_api.hpp"
#include "info_panel.hpp"
#include "clock.hpp"
#include <chrono>
#include <string>

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
        if(priority != nullptr) {
            if((priority->one_time && priority->done)
                || (!priority->one_time && duration_cast<milliseconds>(system_clock::now().time_since_epoch()) >= start_time + milliseconds(priority->min_duration_ms))) {
                delete this->priority;
                this->priority = nullptr;
            }
            else {
                this->priority->fun(priority); 
            }   
        }
        else {
            // Find first active task in the queue
            // it is a priority queue so break after finding it
            if(p.is_active()){
                p.execute();
                break;
            }
        }
    }
}

void Scheduler::push(Pipeline p){
    this->queue.push_back(p);
}

bool Scheduler::show_stocks() {
    for(auto p: this->queue) {
        for(auto task: p.tasks) {
            if(std::string(task.api_name) == std::string(APIStocks::NAME) 
                || std::string(task.api_name) == std::string(APICrypto::NAME)) {
                if(this->priority != nullptr) {
                    delete this->priority;
		    this->priority = nullptr;
                }
                auto show_task = new Task(info_panel::crypto_stocks_data, APIStocks::NAME, 0, true);
                this->priority = show_task;
                this->start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
                return true;
            }
        }
    }
    return false;
}

bool Scheduler::show_clock(int time_sec) {
    if(time_sec <= 0) {
        return true;
    }
    for(auto p: this->queue) {
        for(auto task: p.tasks) {
            if(std::string(task.api_name) == std::string(Clock::NAME_API)) {
                if(this->priority != nullptr) {
                    delete this->priority;
		    this->priority = nullptr;
                }
                auto show_task = new Task(info_panel::wall_clock, Clock::NAME_API, time_sec*1000, false);
                this->priority = show_task;
                this->start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
                return true;
            }
        }
    }
    return false;
}
