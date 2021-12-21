#include "Airport.h"

#include <istream>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const Airport &airport) {
    os << airport.name << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Airport &airport) {
    std::getline(is >> std::ws, airport.name);
    return is;
}
