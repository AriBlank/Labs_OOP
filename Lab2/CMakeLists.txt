cmake_minimum_required(VERSION 3.16)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6_DIR D:/Qt/6.12.0/mingw_64/lib/cmake/Qt6)

add_executable(Lab2 main.cpp mainwindow.cpp mainwindow.ui drawarea.h drawarea.cpp)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
target_link_libraries(Lab2 PRIVATE Qt6::Widgets)

find_package(Qt6 REQUIRED COMPONENTS Gui)
target_link_libraries(Lab2 PRIVATE Qt6::Gui)