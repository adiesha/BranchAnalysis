cmake_minimum_required(VERSION 3.5)
project(BranchAnalysis)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O -Wall -D_POSIX_C_SOURCE=200809L -g")

set(SOURCE_FILES main.c main.c  predictors.h predictors.c )
add_executable(BPAnalysis ${SOURCE_FILES})