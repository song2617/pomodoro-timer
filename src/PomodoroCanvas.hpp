#ifndef POMODOROCANVAS_HPP
#define POMODOROCANVAS_HPP

#include <wx/wx.h>
#include <wx/dcbuffer.h> //wxAutoBufferedPaintDC um Flimmern zu vermeiden
#include <cmath>         //sin() cos() M_PI
#include "Timer.hpp"

namespace pomodoro{

class PomodoroCanvas : public wxPanel{ //PomodoroCanvas ist auch ein kleiner panel innerhalb rightpanel
    public:                             // Warum nicht direkt wxPanel,sondern Vererbung? weil funktion OnPaint() muss umgeschrieben werden, FÜR Ring, time, pünkte....
        PomodoroCanvas(wxWindow* parent, Timer* timer); //es hat parent window, muss man parameter wxwindow setzen, aber nicht wie wxFrame mit wxString& title. xwFrame hat auch kein parent window, braucht es deshalb keinen parameter wxWindow 
    private:
        Timer* timer_;  //mit pointer verwenden hier und MainFrame denselben Timer, sonst hier ist eine Kopie 
        
        void OnPaint(wxPaintEvent& evt); //bei jedem Refresh() abgerufen, um alles zu aktualisieren 
        void DrawRing(wxAutoBufferedPaintDC& dc);  
        void DrawTime(wxAutoBufferedPaintDC& dc); //time und wörte
        void DrawDots(wxAutoBufferedPaintDC& dc); //4 tomate pünkte
        void DrawHint(wxAutoBufferedPaintDC& dc); //zB Long break after next

};

}

#endif