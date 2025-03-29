cmake_minimum_required(VERSION 3.10)
project(MWMS VERSION 1.0)

include_directories(include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    src/app.cpp
    src/settings.cpp
    src/ui/mainframe.cpp
)

set(INCLUDES
    include/core
    include/ui
    include/
)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    ${wxWidgets_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${wxWidgets_INCLUDE_DIRS}
    ${INCLUDES}
)
