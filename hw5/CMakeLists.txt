cmake_minimum_required(VERSION 3.10)
project(Bejeweled)

set(CMAKE_CXX_STANDARD 11)

configure_file(images/background.png images/background.png COPYONLY)
configure_file(images/cursor.png images/cursor.png COPYONLY)
configure_file(images/gems.png images/gems.png COPYONLY)
configure_file(sounds/pop.ogg sounds/pop.ogg COPYONLY)
configure_file(fonts/Space.ttf fonts/Space.ttf COPYONLY)

# Define sources and executable
set(EXECUTABLE_NAME "Bejeweled")

add_executable(${EXECUTABLE_NAME} main.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()