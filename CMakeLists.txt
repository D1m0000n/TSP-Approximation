project(TSP)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        TSP
        main.cpp
        approx.cpp
        approx.h
        brute_force.cpp
        brute_force.h
)