cmake_minimum_required(VERSION 3.31)
project(Client)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)  # not needed here, but good to include
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.0\\mingw_64")

add_executable(Client main.cpp
        testUI.cpp
        testUI.h
        testUI.ui
        main.h
)

find_package(Qt6Widgets REQUIRED)

target_link_libraries(Client ws2_32)
target_link_libraries(Client Qt6::Widgets)

qt_add_resources(RESOURCES_ADDED resources/resources.qrc)
target_sources(Client PRIVATE ${RESOURCES_ADDED})

