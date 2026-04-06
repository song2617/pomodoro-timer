# PomodoroTimer

## Projektbeschreibung

PomodoroTimer ist eine Desktop-Produktivitätsanwendung, entwickelt in C++ mit wxWidgets, basierend auf der Pomodoro-Technik — einer Zeitmanagement-Methode, die Francesco Cirillo Ende der 1980er Jahre entwickelte. Der Name stammt vom italienischen Wort für „Tomate", inspiriert durch den tomatenförmigen Küchentimer, den Cirillo als Student verwendete.

Der Grundgedanke ist einfach: Die menschliche Aufmerksamkeit kann sich nicht über lange Zeiträume hinweg hochkonzentriert halten. Anstatt sich stundenlang durchzubeißen, unterteilt die Pomodoro-Technik die Arbeit in fokussierte 25-Minuten-Einheiten mit kurzen Pausen dazwischen. Dieser Rhythmus fördert die Konzentration und reduziert mentale Erschöpfung.

**Ablauf:**

1. Eine Aufgabe aus der To-do-Liste auswählen
2. 25 Minuten konzentriert daran arbeiten (ein „Pomodoro")
3. 5 Minuten kurze Pause einlegen
4. Nach jeweils 4 Pomodoros eine längere Pause von 15–30 Minuten nehmen
5. Zyklus wiederholen

Die Anwendung bietet einen visuellen Countdown-Timer auf einem Canvas, eine Aufgabenliste mit Hinzufügen/Bearbeiten/Löschen-Funktion, Soundbenachrichtigungen am Ende jedes Intervalls sowie ein Tagesstatistik-Panel mit der Anzahl abgeschlossener Pomodoros.

## Zielgruppe

Studierende, Programmierer und alle, die ihre Fokuszeit effektiver gestalten möchten.

## Technologie

- **Sprache:** C++17
- **GUI-Framework:** wxWidgets
- **Build-System:** CMake
