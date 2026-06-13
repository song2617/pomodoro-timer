#define DEBUG_MODE
#include "Timer.hpp"

namespace pomodoro{

#ifdef DEBUG_MODE
    static constexpr int WORK_SECONDS = 25;
    static constexpr int SHORT_BREAK_SECONDS = 5;
    static constexpr int LONG_BREAK_SECONDS = 15;
#else
    static constexpr int WORK_SECONDS = 25 * 60;
    static constexpr int SHORT_BREAK_SECONDS = 5 * 60;
    static constexpr int LONG_BREAK_SECONDS = 15 * 60;
#endif

Timer::Timer(): seconds_left_{WORK_SECONDS}{}

void Timer::Start(){is_running_ = true;}

void Timer::Pause(){is_paused_ = true; is_running_ = false;}

void Timer::Resume(){is_running_ = true; is_paused_ =false;}

void Timer::Reset(){is_paused_ = false; is_running_ = false; 
    seconds_left_ = WORK_SECONDS; state_ = TimerState::Work; pomodoros_in_round_ = 0;}

bool Timer::Tick(){//jede 1. Sekunde aufgerufen.True zurückgegeben beim Änderung des status, sonst immer je 1. sek. False zurückgegeben
    if(!is_running_||is_paused_) return false;
    seconds_left_--;
    if(seconds_left_>0) return false;

    is_running_ = false;

    if(state_ == TimerState::Work){
        pomodoros_done_++;
        pomodoros_in_round_++;
        if(pomodoros_in_round_ == 4){
            state_ = TimerState::LongBreak;
            seconds_left_ = LONG_BREAK_SECONDS;
            pomodoros_in_round_ = 0;
        }else{
            state_ = TimerState::ShortBreak;
            seconds_left_ = SHORT_BREAK_SECONDS;
        }
    } else{
        state_ = TimerState::Work;
        seconds_left_ = WORK_SECONDS;
    }

    return true;

}

int Timer::seconds_left() const{return seconds_left_;}
TimerState Timer::state() const{return state_;}
bool Timer::is_running() const{return is_running_;}
bool Timer::is_paused() const{return is_paused_;}
int Timer::pomodoros_done() const{return pomodoros_done_;}
int Timer::pomodoros_in_round() const{return pomodoros_in_round_;}

int Timer::total_seconds() const {
    if(state_ == TimerState::Work) return WORK_SECONDS;
    else if(state_ == TimerState::LongBreak) return LONG_BREAK_SECONDS;
    else return SHORT_BREAK_SECONDS;
}

}