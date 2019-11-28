###
#File: CMakeLists.txt
#Project: future stream
#Created Date: Wednesday November 27th 2019
#Author: DaGai  <binghan2836@163.com>
#-----
#Last Modified: Wednesday November 27th 2019 1:54:36 pm
#Modified By:   the developer formerly known as DaGai
#-----
#MIT License
#
#Copyright (c) 2019 binghan2836@163.com
#
#Permission is hereby granted, free of charge, to any person obtaining a copy of
#this software and associated documentation files (the "Software"), to deal in
#the Software without restriction, including without limitation the rights to
#use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
#of the Software, and to permit persons to whom the Software is furnished to do
#so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.
#-----
#HISTORY:
#Date          By    Comments
#----------    ---    ----------------------------------------------------------
###
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


PROJECT(Algrithm)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    #ADD_DEFINITIONS(${CMAKE_CXX_FLAGS} "$ENV{CXXFLAGS} -Wall -pthread -DGTEST_HAS_PTHREAD=1 -std=c++11")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -Wall -pthread -DGTEST_HAS_PTHREAD=1 -std=c++11" )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

SET (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib/)
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/bin/)


configure_file (
  "${PROJECT_SOURCE_DIR}/includes/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/includes/config.h"
  )
option(OUTPUT2CONSOLE "write log to console" ON)

INCLUDE_DIRECTORIES(
	./third_parts/googletest/googletest/include/
	./third_parts/googletest/googlemock/include/
  ./third_parts/libevent/include/
  ${CMAKE_CURRENT_BINARY_DIR}/includes/
	./includes/
)

ADD_SUBDIRECTORY(third_parts/googletest/)
#ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)