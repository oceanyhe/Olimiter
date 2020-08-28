CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(seconds_limiter_test)

ADD_DEFINITIONS(-std=c++11)
AUX_SOURCE_DIRECTORY(src SECONDS_LIMITER)
INCLUDE_DIRECTORIES("./include")

ADD_LIBRARY(seconds_limiter SHARED ./include/seconds_limiter.cc)
LINK_LIBRARIES(seconds_limiter)

ADD_EXECUTABLE(seconds_limiter_test ${SECONDS_LIMITER})
TARGET_LINK_LIBRARIES(seconds_limiter_test seconds_limiter -lpthread)
