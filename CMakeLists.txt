cmake_minimum_required(VERSION 3.10)
project(MWMS VERSION 1.0)

set(SOURCES src/main.cpp)
set(HEADERS include/)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
