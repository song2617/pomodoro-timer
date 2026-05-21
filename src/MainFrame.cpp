#include "MainFrame.hpp"


namespace pomodoro{
MainFrame::MainFrame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY,title, wxDefaultPosition, wxDefaultSize,
    (wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER))){
    
        wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY);//this ist MainFrame, die size ist automatisch wie MaaiFrame
        BuildLeftPanel(splitter);
        BuildRightPanel(splitter);
        splitter->SplitVertically(left_panel_, right_panel_, 265);
        splitter->SetMinimumPaneSize(265);

        //Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);//"X"drücken. es ist von system definiert, kein Button ist nötig.
    
}

void MainFrame::BuildLeftPanel(wxSplitterWindow* splitter){
    left_panel_ = new wxPanel(splitter,wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);//verticaler layout-manager für links

    //task label
    wxStaticText* task_label = new wxStaticText(left_panel_, wxID_ANY, "Task");
    sizer->Add(task_label, 0, wxLEFT | wxTOP, 14);// Zum Sizer hinzufügen: feste Größe, 14px Abstand links und oben

    //eingabefeld+button
    wxBoxSizer* input_sizer = new wxBoxSizer(wxHORIZONTAL);
    task_input_ = new wxTextCtrl(left_panel_, wxID_ANY,"", wxDefaultPosition, wxDefaultSize);
    add_btn_ = new wxButton(left_panel_, wxID_ANY, "+", wxDefaultPosition, wxSize(28,28));
    input_sizer->Add(task_input_, 1, wxEXPAND);// Eingabefeld zum horizontalen Sizer hinzufügen: Breite füllt den gesamten verbleibenden Raum (proportion=1), Höhe passt sich der Sizer-Höhe an (wxEXPAND)
    input_sizer->Add(add_btn_, 0, wxLEFT, 6);
    sizer->Add(input_sizer, 0, wxLEFT | wxTOP, 14);

    //task-liste
    task_list_ = new wxCheckListBox(left_panel_, wxID_ANY);
    sizer->Add(task_list_, 1, wxEXPAND | wxLEFT | wxRIGHT, 14);
    //delete-button
    delete_btn_ = new wxButton(left_panel_, wxID_ANY, "X delete selected task", wxDefaultPosition, wxDefaultSize);
    sizer->Add(delete_btn_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 14);

    sizer->AddStretchSpacer(1);

    //linke trennlinie
    wxStaticLine* line_1 = new wxStaticLine(left_panel_, wxID_ANY);
    sizer->Add(line_1, 0, wxEXPAND|wxTOP, 14);

    //yesterday
    yesterday_val_ = new wxStaticText(left_panel_, wxID_ANY, "0");
    wxStaticText* yesterday_lbl_ = new wxStaticText(left_panel_,wxID_ANY, "Yesterday");
    wxBoxSizer* yesterday_sizer = new wxBoxSizer(wxVERTICAL);
    yesterday_sizer->Add(yesterday_val_, 0);
    yesterday_sizer->Add(yesterday_lbl_, 0);

    sizer->Add(yesterday_sizer, 0, wxALL, 14);

    //binden
     //add_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnAddTask, this);
     //task_list_->Bind(wxEVT_LISTBOX, &MainFrame::OnSelectTask, this);
     //task_list_->Bind(wxEVT_LISTBOX_DCLICK,&MainFrame::OnDoubleClickTask, this);
     //task_list_->Bind(wxEVT_CHECKLISTBOX, &MainFrame::OnCompleteTask, this);
     //delete_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnDeleteTask, this);

     left_panel_->SetSizer(sizer);
}

void MainFrame::BuildRightPanel(wxSplitterWindow* splitter){

    right_panel_ = new wxPanel(splitter, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //obere zeile
    wxBoxSizer* top_sizer = new wxBoxSizer(wxHORIZONTAL);
    state_label_ = new wxStaticText(right_panel_, wxID_ANY, "work-25:00");
    wxStaticText* legend_work  = new wxStaticText(right_panel_, wxID_ANY, "● work");   // Rote Legende für Arbeitszeit
    wxStaticText* legend_short = new wxStaticText(right_panel_, wxID_ANY, "● short");  // Grüne Legende für kurze Pause
    wxStaticText* legend_long  = new wxStaticText(right_panel_, wxID_ANY, "● long");   // Blaue Legende für lange Pause
    legend_work->SetForegroundColour(wxColour(226, 75, 74));                            // Rote Farbe für Arbeitszeit
    legend_short->SetForegroundColour(wxColour(99, 153, 34));                           // Grüne Farbe für kurze Pause
    legend_long->SetForegroundColour(wxColour(55, 138, 221));                           // Blaue Farbe für lange Pause
           
    history_btn_ = new wxButton(right_panel_, wxID_ANY, "...", wxDefaultPosition, wxDefaultSize);
    top_sizer->Add(state_label_, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 14);
    top_sizer->Add(legend_work,  0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);             // Rote Legende, 10px Abstand links
    top_sizer->Add(legend_short, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 6);              // Grüne Legende, 6px Abstand links
    top_sizer->Add(legend_long,  0, wxALIGN_CENTER_VERTICAL | wxLEFT, 6); 
    top_sizer->AddStretchSpacer(1);                                                     //  stretchspace schiebt die beiden teile an die seite  
    top_sizer->Add(history_btn_, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 28);
    sizer->Add(top_sizer, 0, wxEXPAND | wxTOP, 14);             // Blaue Legende, 6px Abstand links

    // Canvas-Platzhalter
    //canvas_ = new PomodoroCanvas(right_panel_);
    canvas_ = new wxPanel(right_panel_,wxID_ANY,wxDefaultPosition,wxSize(200,200));
    sizer->Add(canvas_, 0, wxALIGN_CENTER | wxTOP, 14);

    //tomaten-punkte hinweis in PomodoroCanvas

    //schalter
    wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    start_pause_btn_ = new wxButton(right_panel_, wxID_ANY, "Start");
    reset_btn_ = new wxButton(right_panel_, wxID_ANY, "Reset");
    btn_sizer->Add(start_pause_btn_, 0, wxRIGHT, 8);
    btn_sizer->Add(reset_btn_, 0);
    sizer->Add(btn_sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 14);

    sizer->AddStretchSpacer(1);

     //rechte trennlinie
    wxStaticLine* line_2 = new wxStaticLine(right_panel_, wxID_ANY);
    sizer->Add(line_2, 0, wxEXPAND|wxTOP, 14);

    //untere statistik
    wxBoxSizer* stats_sizer = new wxBoxSizer(wxHORIZONTAL);
    
    today_val_ = new wxStaticText(right_panel_, wxID_ANY, "0");
    wxStaticText* today_lbl = new wxStaticText(right_panel_, wxID_ANY, "today");
    wxBoxSizer* today_sizer = new wxBoxSizer(wxVERTICAL);
    today_sizer->Add(today_val_, 0, wxALIGN_CENTER);
    today_sizer->Add(today_lbl, 0, wxALIGN_CENTER);

    tasks_done_val_ = new wxStaticText(right_panel_, wxID_ANY, "0/0");
    wxStaticText* tasks_done_lbl = new wxStaticText(right_panel_, wxID_ANY, "tasks done");
    wxBoxSizer* tasks_done_sizer = new wxBoxSizer(wxVERTICAL);
    tasks_done_sizer->Add(tasks_done_val_, 0, wxALIGN_CENTER);
    tasks_done_sizer->Add(tasks_done_lbl, 0, wxALIGN_CENTER);

    stats_sizer->Add(today_sizer, 1, wxALIGN_CENTER);
    stats_sizer->Add(tasks_done_sizer, 1, wxALIGN_CENTER);

    sizer->Add(stats_sizer, 0, wxEXPAND | wxALL, 14);

    //binden
    //history_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnHistory, this);
    //start_pause_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnStartPause, this);
    //reset_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnReset, this);

    right_panel_->SetSizer(sizer);

}
}

