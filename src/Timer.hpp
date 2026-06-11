#ifndef TIMER_HPP
#define TIMER_HPP

#include <string>

namespace pomodoro{

enum class TimerState{
    Work,
    ShortBreak,
    LongBreak
};

/*
1.benutzer bedienung

2.status ablesen 
    2.1 verbleibende sekunden, momentaner status
    2.2 is_running, is_pause
    2.3 tomaten in rund, tomaten today   

3.private funktionen für DEGUG
*/
class Timer{

public:
    Timer();

    void Start();
    void Pause();
    void Resume();
    void Reset();
    bool Tick();//

    int seconds_left() const;
    TimerState state() const;
    bool is_running() const;
    bool is_paused() const;
    int pomodoros_done() const;
    int pomodoros_in_round() const;

    int total_seconds() const; // 当前阶段的总秒数
    void set_pomodoros_done(int n){pomodoros_done_ = n;}

private:
    TimerState state_ = TimerState::Work;
    int seconds_left_ = 0;
    bool is_running_ = false;
    bool is_paused_ = false;
    int pomodoros_done_ = 0;
    int pomodoros_in_round_ = 0;
};   

}


#endif