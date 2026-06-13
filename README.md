# PomodoroTimer

A desktop productivity timer built with C++ and wxWidgets, based on the Pomodoro Technique.

![Main window](images/main.png)

## About the Pomodoro Technique

The Pomodoro Technique is a time-management method developed by Francesco Cirillo in the late 1980s. The name comes from the Italian word for "tomato", inspired by the tomato-shaped kitchen timer Cirillo used as a student.

The core idea: human attention cannot stay focused for long stretches. Instead of working for hours without a break, work is split into focused 25-minute intervals ("Pomodoros") separated by breaks.

**How it works:**
1. Choose a task from the list.
2. Focus on it for 25 minutes (one Pomodoro).
3. Take a 5-minute short break.
4. After every 4 Pomodoros, take a longer break of 15 minutes.
5. Repeat the cycle.

## Features

- **Task list** – add, select, delete and check off tasks.
- **Visual circular timer** – a colored ring drawn on a canvas shows the remaining time at a glance.
- **Automatic phase switching** – work, short break and long break follow each other automatically, each shown in its own color (work = red, short break = green, long break = blue).
- **Pomodoro counter** – four dots show the progress within the current round.
- **Daily statistics** – the number of Pomodoros completed today and the number of finished tasks are always visible.
- **7-day history** – a separate window lists the Pomodoros completed on each of the last 7 days, with total, average and best-day statistics.
- **Persistent data** – completed Pomodoros are saved to disk and restored on the next start.
- **End-of-phase notification** – when a phase ends, a message box informs the user.

## Screenshots

| Work phase | Short break |
|------------|-------------|
| ![Work](images/work.png) | ![Break](images/short.png) |

| Long break | History | Notification |
|------------|---------|--------------|
| ![Break](images/long.png) | ![History](images/history.png) | ![Notification](images/message.png) |


## Build Instructions

### Requirements

- A C++17 compiler (g++ or clang)
- [wxWidgets](https://www.wxwidgets.org/) 3.2 (development files)
- CMake 3.16 or newer

On Debian/Ubuntu the dependencies can be installed with:

```bash
sudo apt install build-essential cmake libwxgtk3.2-dev
```

### Building

```bash
git clone https://github.com/song2617/pomodoro-timer.git
cd pomodoro-timer
mkdir build
cd build
cmake ..
make -j
```

This produces three executables in the `build` directory:

- `PomodoroTimer` – the main application
- `test_task` – unit tests for the `Task` class
- `test_timer` – unit tests for the `Timer` class

### Running

```bash
./PomodoroTimer
```

### Running the tests

```bash
./test_task
./test_timer
```

Each test program prints `All ... tests passed!` if every assertion succeeds.

## User Manual

![Annotated interface](images/main.png)

### Managing tasks

- Type a task name into the input field at the top left and press the **+** button to add it.
- Click a task to select it.
- Press **X delete selected task** to remove the selected task.
- Tick the checkbox next to a task to mark it as done; the **tasks done** counter updates accordingly.

### Using the timer

- Press **Start** to begin a 25-minute work phase. The circular ring shrinks as time passes.
- While running, the button shows **Pause**; press it to pause. It then shows **Resume** to continue.
- Press **Reset** to abandon the current Pomodoro and return to 25:00.
- When a phase ends, a notification appears. The next phase (break or work) is loaded automatically and waits for you to press **Start**.

### Viewing history

- Press the **...** button in the top-right corner to open the 7-day history window.

## Debug Mode

For testing, `src/Timer.cpp` contains a `#define DEBUG_MODE` at the top. When enabled, the durations are shortened to 10 / 2 / 5 seconds so that phase transitions can be observed quickly. Comment out this line for the normal 25 / 5 / 15-minute durations.

## Project Structure
pomodoro-timer/

├── CMakeLists.txt

├── LICENSE

├── README.md

├── src/

│   ├── app.cpp / app.hpp            # wxWidgets application entry point

│   ├── MainFrame.cpp / .hpp         # main window, layout and event handling

│   ├── PomodoroCanvas.cpp / .hpp    # custom-drawn circular timer

│   ├── Timer.cpp / .hpp             # timer logic (non-GUI)

│   └── Task.cpp / .hpp              # task data model (non-GUI)

└── tests/

├── test_task.cpp                # unit tests for Task

└── test_timer.cpp               # unit tests for Timer

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.