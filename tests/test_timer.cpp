#include "../src/Timer.hpp"
#include <cassert>
#include <iostream>

using namespace pomodoro;

int main(){
    // Test 1: Anfangszustand ist Work
    Timer t;
    assert(t.state() == TimerState::Work);

    // Test 2: am Anfang nicht laufend, nicht pausiert
    assert(t.is_running() == false);
    assert(t.is_paused() == false);

    // Test 3: am Anfang Pomodoro-Zähler auf 0
    assert(t.pomodoros_done() == 0);
    assert(t.pomodoros_in_round() == 0);

    // Test 4: verbleibende Zeit gleich Gesamtarbeitszeit
    assert(t.seconds_left() == t.total_seconds());

    // Test 5: nach Start ist is_running true
    t.Start();
    assert(t.is_running() == true);

    // Test 6: nach einem Tick verringert sich die Zeit um 1
    int before = t.seconds_left();
    t.Tick();
    assert(t.seconds_left() == before - 1);

    // Test 7: nach Pause gestoppt und pausiert
    t.Pause();
    assert(t.is_running() == false);
    assert(t.is_paused() == true);

    // Test 8: während Pause verringert Tick die Zeit nicht
    int paused_val = t.seconds_left();
    t.Tick();
    assert(t.seconds_left() == paused_val);

    // Test 9: nach Resume wieder laufend
    t.Resume();
    assert(t.is_running() == true);
    assert(t.is_paused() == false);

    // Test 10: eine vollständige Arbeitsphase beendet, Pomodoro +1, in kurze Pause
    Timer t2;
    t2.Start();
    int work_total = t2.total_seconds();
    bool ended = false;
    for(int i = 0; i < work_total; i++){
        ended = t2.Tick();
    }
    assert(ended == true);                              // letzter Tick gibt true zurück
    assert(t2.pomodoros_done() == 1);                  // ein Pomodoro abgeschlossen
    assert(t2.state() == TimerState::ShortBreak);      // in kurze Pause gewechselt
    assert(t2.is_running() == false);                  // nach Phasenende gestoppt

    // Test 11: nach 4 Arbeitsphasen in lange Pause
    Timer t3;
    for(int round = 0; round < 4; round++){
        t3.Start();
        int total = t3.total_seconds();                // Gesamtdauer der Arbeitsphase
        for(int i = 0; i < total; i++) t3.Tick();      // Arbeitsphase durchlaufen
        if(round < 3){
            // erste 3 Runden in kurze Pause, dann zurück zur Arbeit
            t3.Start();
            int btotal = t3.total_seconds();
            for(int i = 0; i < btotal; i++) t3.Tick();
        }
    }
    assert(t3.pomodoros_done() == 4);                  // insgesamt 4 Pomodoros abgeschlossen
    assert(t3.state() == TimerState::LongBreak);       // nach dem 4. in lange Pause
    assert(t3.pomodoros_in_round() == 0);              // Rundenzähler zurückgesetzt

    // Test 12: nach Reset zurück zum Anfangszustand Work
    Timer t4;
    t4.Start();
    t4.Tick();
    t4.Reset();
    assert(t4.state() == TimerState::Work);
    assert(t4.is_running() == false);
    assert(t4.is_paused() == false);
    assert(t4.pomodoros_in_round() == 0);
    assert(t4.seconds_left() == t4.total_seconds());

    // Test 13: set_pomodoros_done setzt den Wert korrekt
    Timer t5;
    t5.set_pomodoros_done(7);
    assert(t5.pomodoros_done() == 7);

    std::cout << "All Timer tests passed!\n";
    return 0;
}