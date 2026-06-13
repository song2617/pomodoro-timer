#include "../src/Task.hpp"
#include <cassert>
#include <iostream>

using namespace pomodoro;

int main(){
    // Test 1: neue Aufgabe, Name korrekt
    Task t("Write lab report");
    assert(t.name() == "Write lab report");

    // Test 2: neue Aufgabe standardmäßig nicht erledigt
    assert(t.is_done() == false);

    // Test 3: nach set_done(true) erledigt
    t.set_done(true);
    assert(t.is_done() == true);

    // Test 4: nach set_done(false) wieder nicht erledigt
    t.set_done(false);
    assert(t.is_done() == false);

    // Test 5: set_name ändert den Namen
    t.set_name("Review C++ notes");
    assert(t.name() == "Review C++ notes");

    std::cout << "All Task tests passed!\n";
    return 0;
}