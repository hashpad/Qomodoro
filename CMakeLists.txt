cmake_minimum_required(VERSION 3.5)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

project(Qomodoro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB ALL_SRCS src/*.cpp src/ui/*.cpp src/data/*.cpp src/core/*.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/ui
    ${CMAKE_SOURCE_DIR}/src/data
)

add_executable(
	Qomodoro
	${ALL_SRCS}
)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts Multimedia)

target_link_libraries(
Qomodoro PRIVATE 
Qt${QT_VERSION_MAJOR}::Widgets 
Qt${QT_VERSION_MAJOR}::Sql 
Qt${QT_MAJOR_VERSION}::Charts 
Qt${QT_VERSION_MAJOR}::Multimedia
)
