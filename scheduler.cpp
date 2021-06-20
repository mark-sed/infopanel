#include "scheduler.hpp"

Pipeline::Pipeline(IsActiveFunction is_active_fun) {
    this->is_active_fun = is_active_fun;
}

bool Pipeline::is_active(){
    return this->is_active_fun();
}

void Pipeline::execute(){
    for(auto task: this->tasks){
        task();
    }
}

void Pipeline::push(Task t){
    this->tasks.push_back(t);
}

Scheduler::Scheduler() : queue{} {

}

void Scheduler::execute(){
    for(auto p: this->queue){
        if(p.is_active()){
            p.execute();
        }
    }
}

void Scheduler::push(Pipeline p){
    this->queue.push_back(p);
}
