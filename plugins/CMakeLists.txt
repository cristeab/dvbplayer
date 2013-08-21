project(QtProcess)

cmake_minimum_required(VERSION 2.8.10)

find_package(Qt4 4.8.0 REQUIRED)

include_directories(${QT_QTCORE_INCLUDE_DIR} ${CMAKE_BINARY_DIR})

set(QtProcess_SRCS process.cpp qtprocess_plugin.cpp)
set(QtProcess_HDRS process.h qtprocess_plugin.h)

QT4_WRAP_CPP(MOCS ${QtProcess_HDRS})

string(TOLOWER ${CMAKE_PROJECT_NAME} TARGET_NAME)
add_library(${TARGET_NAME} SHARED ${QtProcess_SRCS} ${MOCS})
target_link_libraries(${TARGET_NAME} ${QT_QTCORE_LIBRARY})

install(TARGETS ${TARGET_NAME} DESTINATION ${QT_IMPORTS_DIR}/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_SOURCE_DIR}/qmldir DESTINATION ${QT_IMPORTS_DIR}/${CMAKE_PROJECT_NAME})
