cmake_minimum_required(VERSION 3.16)
project(aed_tp01)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_tp01 main.cpp Aircraft.cpp Aircraft.h Flight.cpp Flight.h Service.cpp Service.h Passenger.cpp Passenger.h LuggageVehicle.cpp LuggageVehicle.h Transportation.cpp Transportation.h Time.cpp Time.h Luggage.cpp Luggage.h Airport.cpp Airport.h DateTime.cpp DateTime.h Date.cpp Date.h)
