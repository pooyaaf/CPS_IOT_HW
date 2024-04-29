cmake_minimum_required(VERSION 3.14)

project(Server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core WebSockets)
find_package(Qt6 REQUIRED COMPONENTS HttpServer)

add_executable(Server
  main.cpp
  websocketserver.h websocketserver.cpp
  database.cpp database.h
  httpserver.cpp httpserver.h
)

target_link_libraries(Server PUBLIC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(Server PUBLIC Qt::WebSockets)
target_link_libraries(Server PUBLIC Qt6::HttpServer)

include(GNUInstallDirs)
install(TARGETS Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
