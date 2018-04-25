cmake_minimum_required(VERSION 3.0)
project(EXACT)

SET (CMAKE_CXX_FLAGS                "-std=c++11 -Wall -O3 -funroll-loops -msse3")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -funroll-loops -DNDEBUG")


message(STATUS "project source dir is ${PROJECT_SOURCE_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

message (STATUS "CMAKE_MODULE_PATH is ${CMAKE_MODULE_PATH}")

find_package(MySQL)

MESSAGE(STATUS "MYSQL_FOUND: ${MYSQL_FOUND}")
IF (MYSQL_FOUND)
  add_definitions( -D_MYSQL_ )

  message(STATUS "including MYSQL_INCLUDE_DIR: ${MYSQL_INCLUDE_DIR}")
  include_directories(${MYSQL_INCLUDE_DIR})
ENDIF (MYSQL_FOUND)

add_executable(demoTest test.cxx db_conn.cxx)
target_link_libraries(demoTest ${MYSQL_LIBRARIES})
#add_executable(db_conn db_conn.cxx)
