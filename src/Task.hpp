#ifndef TASK_HPP
#define TASK_HPP

#include <string>

namespace pomodoro{

class Task{ //für jede task-zeile 

public:
    Task(const std::string& name): name_{name}{};

    std::string name() const;
    void set_name(const std::string& name);
    bool is_done() const;
    void set_done(bool done);
private:
    std::string name_;
    bool is_done_ = false;
};   

}


#endif