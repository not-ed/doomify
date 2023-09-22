cmake_minimum_required(VERSION 3.5)

if (WIN32)
	add_compile_definitions(WINDOWS)
elseif (LINUX)
	add_compile_definitions(LINUX)
else ()
	message(FATAL_ERROR "Not building for Windows or Linux.")
endif ()

project(doomify LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(EXTERNAL_DEPENDENCIES
		src/json/nlohmann/json.hpp
	)

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
		src/palette_loaders/palettemanager.h 
        src/palette_loaders/palettemanager.cpp 
        src/palette_loaders/paletteloader.h 
        src/palette_loaders/paletteloaderoutcome.h 
        src/palette_loaders/gplpaletteloader.h 
        src/palette_loaders/gplpaletteloader.cpp
		src/palette_loaders/jsonpaletteloader.h
		src/palette_loaders/jsonpaletteloader.cpp src/platform.h src/platform.cpp)

add_executable(doomify
    ${PROJECT_SOURCES}
    ${EXTERNAL_DEPENDENCIES}
)

target_link_libraries(doomify PRIVATE Qt5::Widgets)
