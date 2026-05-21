cmake_minimum_required(VERSION 3.16)
project(PomodoroTimer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)#IDE

# 找到 wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# 源文件
set(SOURCES
    src/app.cpp
    src/MainFrame.cpp
    src/PomodoroCanvas.cpp
    src/Timer.cpp
    src/Task.cpp
)

# 可执行文件
add_executable(PomodoroTimer ${SOURCES})
target_link_libraries(PomodoroTimer ${wxWidgets_LIBRARIES})