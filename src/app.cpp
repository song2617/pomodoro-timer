#include "app.hpp"
#include "MainFrame.hpp"

namespace pomodoro{
bool App::OnInit(){
    MainFrame* frame = new MainFrame("PomodoroTimer");
    frame->SetClientSize(700,560);
    frame->Center();
    frame->Show();
    return true;
}
}

wxIMPLEMENT_APP(pomodoro::App);