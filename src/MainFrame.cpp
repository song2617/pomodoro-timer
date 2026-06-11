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
        CheckNewDay();//beim nächsten tag clear die tasklist

        wx_timer_ = new wxTimer(this);
        Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
        wx_timer_->Start(1000);

        Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);//"X"drücken. es ist von system definiert, kein Button ist nötig.
    
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
     add_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnAddTask, this);
     task_list_->Bind(wxEVT_LISTBOX, &MainFrame::OnSelectTask, this);
     //task_list_->Bind(wxEVT_LISTBOX_DCLICK,&MainFrame::OnDoubleClickTask, this);
     task_list_->Bind(wxEVT_CHECKLISTBOX, &MainFrame::OnCompleteTask, this);
     delete_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnDeleteTask, this);

     left_panel_->SetSizer(sizer);
}

void MainFrame::BuildRightPanel(wxSplitterWindow* splitter){

    right_panel_ = new wxPanel(splitter, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //obere zeile
    wxBoxSizer* top_sizer = new wxBoxSizer(wxHORIZONTAL);
    state_label_ = new wxStaticText(right_panel_, wxID_ANY, "Work-25:00");
    wxStaticText* legend_work  = new wxStaticText(right_panel_, wxID_ANY, "● Work");   // Rote Legende für Arbeitszeit
    wxStaticText* legend_short = new wxStaticText(right_panel_, wxID_ANY, "● Short");  // Grüne Legende für kurze Pause
    wxStaticText* legend_long  = new wxStaticText(right_panel_, wxID_ANY, "● Long");   // Blaue Legende für lange Pause
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
    canvas_ = new PomodoroCanvas(right_panel_,&timer_);//hier ist point!
    //canvas_ = new wxPanel(right_panel_,wxID_ANY,wxDefaultPosition,wxSize(200,200));
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
    history_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnHistory, this);
    start_pause_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnStartPause, this);
    reset_btn_->Bind(wxEVT_BUTTON, &MainFrame::OnReset, this);

    right_panel_->SetSizer(sizer);

}

    //event-handle funktionen
    void MainFrame::OnAddTask(wxCommandEvent& evt){
        wxString name = task_input_->GetValue().Trim();
        if(name.IsEmpty()) return;//wx-spezifische leer-kontrolle von wxstring
        task_list_->Append(name);
        task_.push_back(Task(name.ToStdString()));
        task_input_->Clear();
    };

    void MainFrame::OnDeleteTask(wxCommandEvent& evt){
        int sel = task_list_->GetSelection();
        if(sel == wxNOT_FOUND) return; //od. -1
        task_list_->Delete(sel);
        task_.erase(task_.begin()+sel);
        selected_task_ = -1;
    };
    void MainFrame::OnSelectTask(wxCommandEvent& evt){
        selected_task_ = task_list_->GetSelection(); // ausgewähltes index bekommen
    };
 
    void MainFrame::OnCompleteTask(wxCommandEvent& evt){
        int sel = evt.GetInt();//index von checklistbox.evt bekommen mit Anhaken
        bool cheked = task_list_->IsChecked(sel);
        task_[sel].set_done(cheked);
        UpdateTaskDone();//statistik aktuallisieren

    };

    void MainFrame::UpdateTaskDone(){// taskdone label
        int done = 0;
        for(const auto& t: task_){
            if(t.is_done()==true) done++;
        }
        tasks_done_val_->SetLabel(wxString(std::to_string(done)+"/"+std::to_string(task_.size())));//wxString(arg) ist eine funktion, andere string-->wxString umwandeln
    }

    void MainFrame::OnStartPause(wxCommandEvent& evt){
        if(start_pause_btn_->GetLabel()== "Start"){
            start_pause_btn_->SetLabel("Pause");
            timer_.Start();
        }else if(start_pause_btn_->GetLabel()=="Pause"){
            start_pause_btn_->SetLabel("Resume");
            timer_.Pause();
        }else{
            start_pause_btn_->SetLabel("Pause");
            timer_.Resume();
        }
    }
    void MainFrame::OnReset(wxCommandEvent& evt){
        timer_.Reset();
        start_pause_btn_->SetLabel("Start");
    };

    void MainFrame::OnTimer(wxTimerEvent& evt){
        //1. tick lauft einmal
        //2.state_label_ aktual
        //3.canvas_ aktual
        //4.today_val_ aktual
        //5.blinkt beim phasenende
        bool phase_ended = timer_.Tick();

        if(timer_.state() == TimerState::Work){
            state_label_->SetLabel("Work-25:00");
        }else if(timer_.state() == TimerState::LongBreak){
            state_label_->SetLabel("Long-15:00");
        }else state_label_->SetLabel("Short-5:00");

        canvas_->Refresh();//!!!!!!!!!!!!!PomodoroCanvas::OnPaint() mit wxEVT_PAINT auslösen!!!!!!!!!!! manull auslösung!!!

        today_val_->SetLabel(wxString(std::to_string(timer_.pomodoros_done())));

        if(phase_ended){
            RequestUserAttention(wxUSER_ATTENTION_INFO);//icon blinkt
            for(int i=0;i<5;i++){
                SetBackgroundColour(wxColour(226,75,74));//red
                Refresh();                               //neu zeichnen
                Update();                                //sofort aktualisieren
                wxMilliSleep(200);                      //bleibt 0.2s
                SetBackgroundColour(wxNullColour);
                Refresh();
                Update();
                wxMilliSleep(200);
            }
            start_pause_btn_->SetLabel("Start");
        }
    };//

    void MainFrame::OnHistory(wxCommandEvent& evt){//history dialog
        std::vector<int> data = LoadHistory(); // 7 tage data

        // total avg best in 7 tagen
        int total = 0;
        int best = 0;
        for(int v : data){
            total+=v;
            if(v>best) best = v;
        }
        double avg = total/7.0;

        wxDialog* dlg = new wxDialog(this, wxID_ANY,"7-days History",wxDefaultPosition, wxSize(300,400));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        
        wxDateTime date = wxDateTime::Now();
        date-=wxDateSpan::Days(6);//6 tage nach vorn verschoben
        for(int i = 0; i <= 6; i++){
            wxString label = (i == 6) ? "Today": date.Format("%a"); //wochenstag
            wxString line = wxString::Format("%-6s: %d", label, data[i]);
            wxStaticText* text = new wxStaticText(dlg,wxID_ANY,line);
            sizer->Add(text,0,wxLEFT|wxTOP,14);
            date+=wxDateSpan::Day();//nächster tag
        }

        sizer->Add(new wxStaticLine(dlg,wxID_ANY),0,wxEXPAND|wxALL,14);

        wxString stats = wxString::Format("Total: %d   Avg: %.1f   Best: %d",total, avg, best);
        wxStaticText* stats_label = new wxStaticText(dlg, wxID_ANY, stats,wxDefaultPosition,wxDefaultSize,wxALIGN_CENTER);
       
        sizer->Add(stats_label,0,wxALIGN_CENTER|wxALL,14);
        
        dlg->SetSizer(sizer);
        dlg->ShowModal(); //dlg anzeigen, prozess blokieren
        dlg->Destroy();//dlg löschen
    };

    std::vector<int> MainFrame::LoadHistory(){//return 7 tage data
         wxDateTime date = wxDateTime::Now();
        std::vector<int> result(7,0);//7 elemente je 0
        for(int i = 6; i >= 0; i--){
            wxString filename = date.Format("%Y-%m-%d") + ".txt";
            std::ifstream file(filename.ToStdString());
            if(file.is_open()){
                file >> result[i];
                file.close();
            }
            date-=wxDateSpan::Day();
        }
        return result;
    };

    void MainFrame::OnClose(wxCloseEvent& evt){ //bei jedem schliessen wird neuest gespeichert mit gleichem namen.txt
        wxDateTime today = wxDateTime::Now(); //statische funktion von class wxDateTime gibt objct today
        wxString filename = today.Format("%Y-%m-%d") + ".txt";

        std::ofstream file(filename.ToStdString());
        if(file.is_open()){
            file<<timer_.pomodoros_done();
            file.close();
        }

        evt.Skip(); //fenster wirklich schlissen
    };

    void MainFrame::CheckNewDay(){
        std::string last_date; //lastdate vom lastopen bekommen
        std::ifstream read_file("last_open.txt");
        if(read_file.is_open()){
            read_file>>last_date;
            read_file.close();
        }

        wxDateTime today = wxDateTime::Now();
        wxString today_str = today.Format("%Y-%m-%d");

        if(last_date!=today_str.ToStdString()){
            task_list_->Clear();//UI clear
            task_.clear();      //vector clear
        }

        std::ofstream write_file("last_open.txt");
        write_file << today_str.ToStdString();
        write_file.close();
    };
}

