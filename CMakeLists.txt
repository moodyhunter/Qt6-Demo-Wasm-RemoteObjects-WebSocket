cmake_minimum_required(VERSION 3.5)

project(QtRemoteObjects-Demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0071 NEW)

find_package(Qt6 COMPONENTS Widgets RemoteObjects WebSockets REQUIRED)

add_compile_definitions(QT_DEPRECATED=1)

set(COMMON_FILES
    ${CMAKE_CURRENT_LIST_DIR}/QWebSocketIODevice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomType.hpp)

set(SOURCE_FILES
    ${COMMON_FILES}
    ${CMAKE_CURRENT_LIST_DIR}/source/Window.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/Window.hpp
    ${CMAKE_CURRENT_LIST_DIR}/source/Window.ui)

set(REPLICA_FILES
    ${COMMON_FILES}
    ${CMAKE_CURRENT_LIST_DIR}/replica/Window.cpp
    ${CMAKE_CURRENT_LIST_DIR}/replica/Window.hpp
    ${CMAKE_CURRENT_LIST_DIR}/replica/Window.ui)


if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    qt_add_executable(Demo ${REPLICA_FILES})
    target_include_directories(Demo PRIVATE replica)
else()
    qt_add_executable(Demo ${SOURCE_FILES})
    target_include_directories(Demo PRIVATE source)
endif()


qt6_add_repc_merged(Demo FILES common_rep.rep)

target_link_libraries(Demo PRIVATE Qt::Core Qt::Network Qt::Widgets Qt::RemoteObjects Qt::WebSockets)
