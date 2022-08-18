cmake_minimum_required(VERSION 3.5)

project(doomify LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/job.cpp
        src/job.h
        src/palettes.h
        src/doomify.qrc
        src/imageschema.h 
        src/imagegeneration.h 
        src/imagegeneration.cpp 
        src/palettes.cpp
        )


add_executable(doomify
    ${PROJECT_SOURCES}
)

target_link_libraries(doomify PRIVATE Qt5::Widgets)