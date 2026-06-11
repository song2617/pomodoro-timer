#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/splitter.h>
#include <vector>
#include <wx/statline.h>
#include <fstream> //für history einschreiben

#include "PomodoroCanvas.hpp"
#include "Task.hpp"
#include "Timer.hpp"

namespace pomodoro{

class MainFrame : public wxFrame{
public:
    MainFrame(const wxString& title);
private:
    wxPanel* left_panel_;
    wxTextCtrl* task_input_;
    wxButton* add_btn_;
    wxButton* delete_btn_;
    wxCheckListBox* task_list_;
    //wxStaticText* yesterday_val_;

    wxPanel* right_panel_;

    PomodoroCanvas* canvas_; //Bereich::kreis mit untere pünkte
    
    wxStaticText* state_label_;
    wxButton* start_pause_btn_;
    wxButton* reset_btn_;
    wxButton* history_btn_;
    wxStaticText* today_val_;
    wxStaticText* tasks_done_val_;

    wxTimer* wx_timer_;
    Timer timer_;
    std::vector<Task> task_;
    int selected_task_ = -1;//0,1,2,3...

    void BuildLeftPanel(wxSplitterWindow* splitter);
    void BuildRightPanel(wxSplitterWindow* splitter);

    void CheckNewDay();//nächsten tag leert sich die tasklist

    void OnAddTask(wxCommandEvent& evt);
    void OnDeleteTask(wxCommandEvent& evt);
    void OnSelectTask(wxCommandEvent& evt);
    //void OnDoubleClickTask(wxCommandEvent& evt);
    void OnCompleteTask(wxCommandEvent& evt);       void UpdateTaskDone();
    void OnStartPause(wxCommandEvent& evt);
    void OnReset(wxCommandEvent& evt);
    void OnTimer(wxTimerEvent& evt);//
    void OnHistory(wxCommandEvent& evt);   std::vector<int> LoadHistory();//Poromodo von 7 tagen
    void OnClose(wxCloseEvent& evt);//history vorbeispeichern beim zumachen

};

}

#endif