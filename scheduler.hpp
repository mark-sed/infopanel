#ifndef _SCHEDULER_HPP_
#define _SCHEDULER_HPP_

#include <vector>

using Task = void(*)();
using IsActiveFunction = bool(*)();

class Pipeline {
private:
    std::vector<Task> tasks;
    IsActiveFunction is_active_fun;
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
