cmake_minimum_required(VERSION 3.10.0)
project(Medical-and-Wellness-Management-System VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCES
    src/main.cpp
)

set(HEADERS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_PREFIX_PATH "C:/Qt/5.x/msvc2019_64")
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MWMS ${SOURCES} ${HEADERS})
target_link_libraries(MWMS Qt5::Widgets)
