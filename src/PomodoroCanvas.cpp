#include "PomodoroCanvas.hpp"

namespace pomodoro{

PomodoroCanvas::PomodoroCanvas(wxWindow* parent, Timer* timer) 
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(220,280))
    ,timer_(timer)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT); // automatisches Ausmalen von system verhindern , alles von OnPaint() gezeichnet. um Flimmern zu vermeiden
    Bind(wxEVT_PAINT, &PomodoroCanvas::OnPaint, this);//wxEVT_PAINT ist ein signal von system: "ich weiss nicht was anzuzeigen, bitte OnPaint()!" zB. window init, nach überdeckung neu auftretung, wider erscheinen nach minimum...
}

void PomodoroCanvas::OnPaint(wxPaintEvent& evt){
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(GetBackgroundColour()));
    dc.Clear();
    DrawRing(dc);  
    DrawTime(dc); 
    DrawDots(dc); 
    DrawHint(dc);
}

void PomodoroCanvas::DrawRing(wxAutoBufferedPaintDC& dc){

    int cx = 110, cy = 110, r = 80;
    //Kreis-hintergrund
    dc.SetPen(wxPen(wxColor(220,220,220),12));// linie zeichnen. parameter wxPen ist fixiert.
    dc.SetBrush(*wxTRANSPARENT_BRUSH);//keine füllungsfarbe.
    dc.DrawCircle(cx,cy,r);

    //kurve-vordegrund berechnen
    // 1. aktuelle color von 3-color setzen
    wxColor color;
    if(timer_->state()==TimerState::Work) color = wxColor(226,75,74);
    else if(timer_->state()==TimerState::LongBreak) color = wxColor(55,138,221);
    else color = wxColor(99,153,34);
    // 2. totalle sekunden in aktueller phase
    int total = timer_->total_seconds();
    // 3. winkel von verbleibenden sekunden berechnen
    double ratio = (double)timer_->seconds_left()/total;
    double angle = 360.0 * ratio;
    // 4. zeichnen
    dc.SetPen(wxPen(color,12));
    dc.DrawArc( // start, end, herz- punkte
        cx, cy-r,
        cx + (int)(r*sin(angle*M_PI/180)), cy - (int)(r*cos(angle*M_PI/180)), //hier muss int schreiben weil bei int und double ist das ergbniss automatisch double 
        cx, cy
    );

}

void PomodoroCanvas::DrawTime(wxAutoBufferedPaintDC& dc){

    //Time zeichnen
    int s = timer_->seconds_left();
    int min = s / 60;
    int sec = s % 60;
    wxString time_str = wxString::Format("%02d:%02d", min, sec); 

    dc.SetFont(wxFont(28, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));// font setzen
    dc.SetTextForeground(wxColor(50,50,50));
    wxSize ts = dc.GetTextExtent(time_str);//wie viele pixes besitzt dieses time_str 
    dc.DrawText(time_str, 110 - ts.GetWidth()/2, 70);

    //wörte zeichnen
    wxString sub;
    if(!timer_->is_running()&&!timer_->is_paused()) sub = "Ready"; 
    else if(timer_->state() == TimerState::Work) sub = "Remain";
    else if(timer_->state() == TimerState::LongBreak) sub = "Long Break";
    else sub = "Short Break";

    dc.SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dc.SetTextForeground(wxColor(150,150,150));
    wxSize ss = dc.GetTextExtent(sub);
    dc.DrawText(sub, 110 - ss.GetWidth()/2,120);
}

void PomodoroCanvas::DrawDots(wxAutoBufferedPaintDC& dc){
    int done = timer_->pomodoros_in_round();
    int cy = 220; //circle boden ist 110+80

    for(int i = 0; i<4; i++){
        if(i < done){
            dc.SetPen(wxPen(wxColor(226,75,74),1));
            dc.SetBrush(wxBrush(wxColor(226,75,74)));
        }else{
            dc.SetPen(wxPen(wxColor(200,200,200),1));
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
        }

        dc.DrawCircle(80 + i*20, cy, 6);
    }
}

void PomodoroCanvas::DrawHint(wxAutoBufferedPaintDC& dc){
    int done = timer_->pomodoros_in_round();
    if(done == 3){
        dc.SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        dc.SetTextForeground(wxColor(150,150,150));
        dc.DrawText("Long Break After Next...", 30, 230);
    }
}

}