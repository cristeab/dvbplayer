project(MPlayerDVBTplasmoid)

cmake_minimum_required(VERSION 2.8.10)

find_package(Qt4 4.8.0 REQUIRED)

include_directories(${QT_QTCORE_INCLUDE_DIR})

file(GLOB MPlayerDVBTplasmoid_SRCS *.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${MPlayerDVBTplasmoid_SRCS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${QT_QTCORE_LIBRARY})
