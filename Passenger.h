#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Luggage.h"

class Passenger {
private:
    std::string name;
    bool luggage;
public:
    Passenger() : name(), luggage(false) {}

    Passenger(std::string name, bool luggage) : name(std::move(name)), luggage(luggage) {}

    const std::string &getName() const {
        return name;
    }

    bool hasLuggage() const {
        return luggage;
    }

    Luggage getLuggage() const {
        return {name};
    }

    bool operator<(const Passenger &rhs) const {
        return name < rhs.name;
    }

    friend std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
        os << passenger.name << "\n" << passenger.luggage << "\n";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Passenger &passenger) {
        std::getline(is >> std::ws, passenger.name);
        is >> passenger.luggage;
        return is;
    }

    std::string getStringRep() const {
        return name + ", " + (luggage ? "Yes" : "No");
    }

    static std::vector<std::string> getHeaderElements() {
        return {"Name", "Luggage"};
    }

};
