cmake_minimum_required(VERSION 3.31)
project(Client)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)  # not needed here, but good to include
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/msvc2022_64")

# Find Qt modules
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

include_directories("C:/Program Files/PostgreSQL/17/include")
link_directories("C:/Program Files/PostgreSQL/17/lib")

add_compile_options(/Zc:__cplusplus)
add_executable(Client main.cpp
        main.h
        UI/frontPage.cpp
        UI/frontPage.h
        UI/frontPage.ui
        globalResource/globals.cpp
        globalResource/globals.h
        sqlQueries/sql.h
        sqlQueries/sql.cpp
)


qt_add_resources(RESOURCES_ADDED resources/resources.qrc)
target_sources(Client PRIVATE ${RESOURCES_ADDED})
# Link Qt libraries and postgre libraries
target_link_libraries(Client
        Qt6::Widgets
        ws2_32
        libpq
)



