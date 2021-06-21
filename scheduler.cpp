#include <chrono>
#include "scheduler.hpp"

Pipeline::Pipeline(IsActiveFunction is_active_fun) {
    this->is_active_fun = is_active_fun;
}

bool Pipeline::is_active(){
    return this->is_active_fun();
}

void Pipeline::execute(){
    using namespace std::chrono;
    for(auto task: this->tasks){
        // Make sure the tasks run for the least specified amount of time
        auto start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        do{
            task.fun();
        }while(duration_cast<milliseconds>(system_clock::now().time_since_epoch()) < start_time + milliseconds(task.min_duration_ms));
    }
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
