cmake_minimum_required(VERSION 3.16)
project(aed_tp01)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_tp01 main.cpp Aircraft.cpp Aircraft.h Flight.cpp Flight.h Service.cpp Service.h Person.cpp Person.h Staff.cpp Staff.h Passenger.cpp Passenger.h)
