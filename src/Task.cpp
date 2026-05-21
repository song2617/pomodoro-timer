#include "Task.hpp"

namespace pomodoro{
    std::string Task::name() const {return name_;}
    void Task::set_name(const std::string& name){name_ = name;}
    bool Task::is_done() const {return is_done_;}
    void Task::set_done(bool done){is_done_ = done;}
}