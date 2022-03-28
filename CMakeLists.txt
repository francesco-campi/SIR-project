cmake_minimum_required(VERSION 3.8)
project(SIR VERSION 0.1.0 LANGUAGES CXX)
add_executable(sir main.cpp src/Simulation.cpp src/Population.cpp)
target_compile_features(sir PUBLIC cxx_std_17)