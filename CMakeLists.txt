cmake_minimum_required(VERSION 3.16) #The minimum version of CMake required to build project
project(SentimentEngine LANGUAGES CXX) # Sets the project name and sets the language as CPP

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) #Forces the compiler to use C++ 20

include_directories(include external)
#Adds the folders include and external to the compilers search path for headers.
#This is why nlohmann/json header in the external can be found.

add_executable(sentiment_engine 
    src/main.cpp
    src/preprocess.cpp
    src/features.cpp
    src/model.cpp
)
#Tells CMake to compile src/main.cpp into an executable called sentiment engine.
#Including the new source file preprocess.cpp