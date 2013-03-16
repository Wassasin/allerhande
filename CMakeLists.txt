cmake_minimum_required(VERSION 2.8)

project(allerhande)

include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

file(GLOB_RECURSE allerhande_HEADERS src/*.hpp)
file(GLOB_RECURSE allerhande_SOURCES src/*.cpp)

add_executable(allerhande
	${allerhande_SOURCES}
)

add_definitions("-Wall -Wextra -Weffc++ -std=c++0x -pedantic -g3 -O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      "${PROJECT_SOURCE_DIR}/cmake/modules")

find_package(CURL REQUIRED)
find_package(arabica REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Boost COMPONENTS system program_options filesystem regex REQUIRED)

include_directories(SYSTEM
                    ${CURL_INCLUDE_DIRS}
                    ${arabica_INCLUDE_DIRS}
                    ${jsoncpp_INCLUDE_DIRS}
                    ${Boost_INCLUDE_DIRS})
                    
target_link_libraries(allerhande
                      ${CURL_LIBRARIES}
                      ${arabica_LIBRARIES}
                      ${jsoncpp_LIBRARIES}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_PROGRAM_OPTIONS_LIBRARY}
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_REGEX_LIBRARY})
