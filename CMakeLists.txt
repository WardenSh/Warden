cmake_minimum_required(VERSION 4.0)
project(WardenGUI)

set(CMAKE_CXX_STANDARD 20)

# Configure Qt, enable: MOC processing, Resource compilation, UI compilation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCES "Source/*.cpp")
file(GLOB_RECURSE HEADERS "Source/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} resources.qrc)

target_include_directories(${PROJECT_NAME} PUBLIC Source)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets DBus)
qt_standard_project_setup()
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::DBus)

# libarchive
pkg_check_modules(LIBARCHIVE REQUIRED libarchive)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBARCHIVE_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIBARCHIVE_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBARCHIVE_LIBRARIES})