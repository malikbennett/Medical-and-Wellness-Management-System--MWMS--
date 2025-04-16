cmake_minimum_required(VERSION 3.10)
project(MWMS VERSION 1.0)

include_directories(include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    src/App.cpp
    src/Settings.cpp
    src/core/User.cpp
    src/core/Patient.cpp
    src/core/Employee.cpp
    src/core/Role.cpp
    src/utilities/Session.cpp
    src/utilities/UserManager.cpp
    src/ui/MainFrame.cpp
    src/ui/panels/Dashboard.cpp
    src/ui/panels/AdminDashboard.cpp
    src/ui/panels/HomePanel.cpp
    src/ui/panels/DietitianDashboard.cpp
    src/ui/panels/DoctorDashboard.cpp
    src/ui/panels/LoginPanel.cpp
    src/ui/panels/NurseDashboard.cpp
    src/ui/panels/PatientDashboard.cpp
    src/ui/panels/PsychologistDashboard.cpp
    src/ui/panels/ReceptionistDashboard.cpp
)

set(INCLUDES
    include/core
    include/ui
    include/ui/panels
    include/ui/lists
    include/utilities
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
