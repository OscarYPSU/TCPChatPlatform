cmake_minimum_required(VERSION 3.31)
project(Client)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)  # not needed here, but good to include
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.0\\mingw_64")

find_package(Qt6Widgets REQUIRED)


add_executable(Client main.cpp
        UI/testUI.cpp
        UI/testUI.h
        UI/testUI.ui
        main.h
        UI/frontPage.cpp
        UI/frontPage.h
        sqlite3/sqlite3.c
        sqlite3/sqlite3.h
        sqlite3/SQL.cpp
        sqlite3/SQL.h
)

add_executable(testSQL
        sqlite3/SQL.cpp
        sqlite3/SQL.h
        sqlite3/sqlite3.c
)

qt_add_resources(RESOURCES_ADDED resources/resources.qrc)
target_sources(Client PRIVATE ${RESOURCES_ADDED})
target_link_libraries(Client ws2_32)
target_link_libraries(Client Qt6::Widgets)
target_link_libraries(testSQL)



