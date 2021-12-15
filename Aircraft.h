#pragma once

#include <list>
#include <queue>
#include <string>

class Flight;
class Service;
class Type;

class Aircraft {
    std::string registration;
    Type * type;
    unsigned capacity;
    std::list<Flight> planned; // TODO, list?
    std::queue<Service> services;

};
