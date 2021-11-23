
cmake_minimum_required(VERSION 3.2)
project (forca VERSION 1.0.0 LANGUAGES CXX)

include_directories("include"
                    "src")

add_executable(forca
               include/forca.hpp
               source/forca.cpp
               source/main.cpp)
               
target_compile_features(forca PUBLIC cxx_std_17)
