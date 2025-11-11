# Require at least CMake 3.16
cmake_minimum_required(VERSION 3.16)

# ---- Project Info ----
# Name: TodoApp, version 1.0, languages: C++ and C
project(TodoApp
        VERSION 1.0
        LANGUAGES CXX C
)

# ---- Build Type ----
# User can pass -DCMAKE_BUILD_TYPE=Release or Debug
# If not set, default to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# ---- C++ Standard ----
set(CMAKE_CXX_STANDARD 17)         # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Fail if compiler doesn't support it
set(CMAKE_CXX_EXTENSIONS OFF)       # Disable compiler-specific extensions

# ---- Qt Automatic Features ----
# Enable AUTOMOC (auto run moc for Q_OBJECT macros)
# Enable AUTOUIC (auto process .ui files)
# Enable AUTORCC (auto process .qrc files)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ---- Detect Platform ----
if(WIN32)
    message(STATUS "Building on Windows")
elseif(UNIX)
    message(STATUS "Building on Linux / Unix")
else()
    message(WARNING "Unknown platform — flags may need adjustment")
endif()

# ---- Compiler & Linker Flags ----
# Can override externally, e.g.:
# cmake -DCMAKE_CXX_FLAGS="-Wall -Wextra -O2" -DCMAKE_EXE_LINKER_FLAGS="-pthread"
message(STATUS "CXX FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "LINKER FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")

# ---- Find Qt (try Qt6 first, fallback to Qt5) ----
set(QT_REQUIRED_COMPONENTS Core Gui Widgets)

find_package(Qt6 QUIET COMPONENTS ${QT_REQUIRED_COMPONENTS})
if(NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS ${QT_REQUIRED_COMPONENTS})
endif()

if(Qt6_FOUND)
    message(STATUS "Using Qt6 from: ${Qt6_DIR}")
    set(QT_PREFIX Qt6)
elseif(Qt5_FOUND)
    message(STATUS "Using Qt5 from: ${Qt5_DIR}")
    set(QT_PREFIX Qt5)
else()
    message(FATAL_ERROR "Neither Qt6 nor Qt5 could be found! Please set Qt_DIR manually.")
endif()

# ---- Source & Include Files ----
# Recursively find your cpp source files
file(GLOB_RECURSE PROJECT_SOURCES
        "src/main.cpp"
        "src/mainwindow.cpp"
        "src/log/logManager.cpp"
        "src/task/taskManager.cpp"
        "src/command/addTaskCmd.cpp"
        "src/command/listTaskCmd.cpp"
        "src/command/rmTaskCmd.cpp"
        "src/command/completeTaskCmd.cpp"
        "src/command/executeFileCmd.cpp"
        "src/parser/parser.cpp"
)

# Recursively find header files
file(GLOB_RECURSE PROJECT_HEADERS
        "include/mainwindow.h"
        "include/log/logType.h"
        "include/log/logManager.h"
        "include/task/task.h"
        "include/task/taskManager.h"
        "include/command/cmd.h"
        "include/command/addTaskCmd.h"
        "include/command/listTaskCmd.h"
        "include/command/rmTaskCmd.h"
        "include/command/completeTaskCmd.h"
        "include/command/executeFileCmd.h"
        "include/parser/parser.h"
)

# Include the 'include' directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# ---- Create Executable ----
add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
)

# ---- Link Qt libraries ----
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${QT_PREFIX}::Core
        ${QT_PREFIX}::Gui
        ${QT_PREFIX}::Widgets
)

# ---- Platform-Specific Settings ----
if(WIN32)
    # Avoid warnings for unsafe C functions on Windows
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
elseif(UNIX)
    # Link with pthread on Linux / Unix
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

# ---- Installation (optional) ----
#install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# ---- Summary Info ----
message(STATUS "====================================")
message(STATUS " Project: ${PROJECT_NAME}")
message(STATUS " Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS " C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS " Source Files: ${PROJECT_SOURCES}")
message(STATUS " Using Qt Prefix: ${QT_PREFIX}")
message(STATUS "====================================")
